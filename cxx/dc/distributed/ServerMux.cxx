#ifdef CCAFE_THREADS
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#ifdef HAVE_CLASSIC
#include <cca.h>
#endif // HAVE_CLASSIC
#include "jc++/lang/Object.h"
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "jc++/util/Thread.h"
#include "jc++/lang/String.hh"
#include "jc++/io/Reader.h"
#include "jc++/io/Writer.h"
#include "jc++/io/BufferedReader.h"
#include "jc++/io/StdWriter.h"
#include "util/IO.h"
#include "ProcessorInfo.h"
#include "ConnectionManager.h"
#include "ClientInterfaces.h"
#include "MessageData.h"
#include "LinewiseClient.h"
#include "DataCollectorFactory.h"
#include "SingleClientDataCollector.h"
#include "ServerOutOfBandListener.h"
#include "ServerMux.h"

#ifdef DEBUG
#define MUX_TRACE(x) printf("SRVRMUX: "); printf x
#else
#define MUX_TRACE(x)
#endif

// BUGBUG - make configurable
#define NUM_THREADS 10

const char * ServerMux::SERVER_SRC = "ServerMux";
const char * ServerMux::DATA_COLLECTOR_ACK = "DATA_COLLECTOR_ACK";
const char * ServerMux::DATA_COLLECTOR_ERR = "DATA_COLLECTOR_NOT_SET";
const char * ServerMux::DATA_COLLECTOR_MSG = "DATA_COLLECTOR=";
const char * ServerMux::SHUTDOWN_MSG = "SHUTDOWN_MSG";
const char * ServerMux::REMOVE_CLIENT_MSG = "REMOVE_CLIENT_MSG";

ServerMux::ServerMux(ConnectionManager* computeManager, Connection* controllerConnect)
    :threadpool(NUM_THREADS), ioThread(computeManager), 
  connThread(computeManager)
{

  dataCollector = new SingleClientDataCollector(this);
  addOutOfBandListener(new ServerOutOfBandListener(this));

  this->computationalClientManager = computeManager;
  if (!computationalClientManager->isConnected()) {
    computationalClientManager->makeConnection(0);
  }
  CCAFEThreadSafeQueue* connections = computationalClientManager->getConnections();

  numClients = computationalClientManager->getNumConnections();
  clients = new Client*[numClients];

  // make sure the manager can't muck with the vector
  // and change its size before we finish the next bit of work.
  {
    CCAFEQueueLock lock(connections);
    for (int i = 0; i< connections->size(); i++) {
      Connection* connection = dynamic_cast<Connection*> (connections->elementAt(i)); CHECKDC(connection);
      clients[i] = new LinewiseClient(connection, &threadpool);
      clients[i]->addClientOutputListener(this);
    }
  }
  controllerClient = new LinewiseClient(controllerConnect, &threadpool);
  controllerClient->addClientOutputListener(this);
}

ServerMux::~ServerMux() 
{
  shutdown();

  if (controllerClient)
    delete controllerClient;
  for (int i = 0; i < numClients; i++) {
    if (clients[i]) delete clients[i];
  }
  if (clients)
    delete[] clients;
  if (dataCollector)
    delete dataCollector;

  MUX_TRACE(("ServerMux destroyed"));
}

void ServerMux::doClientIO()
{
  ioThread.start();
  connThread.start();
  isStarted = TRUE;
}

/** 
    Shutdown: Do our best to stop all threads. Stop all clients (they
   should finish any threads currently reading from a client
   connection) and shutdown the connection manager (which will finish
   off the threads sitting in notifyRead and notifyReconnect). Finally,
   shutdown the thread pool. 
*/
void ServerMux::shutdown()
{
  for (int i= 0; i < numClients; i++) {
    clients[i]->shutdown();
  }
  controllerClient->shutdown();
  computationalClientManager->shutdown();

  threadpool.shutdown();

  MUX_TRACE(("ServerMux has been shutdown\n"));
}

void ServerMux::join()
{
  ioThread.join();
  connThread.join();
}

void ServerMux::setExternalClientOutputListener(ClientOutputListener* xLsnr)
{
  (void)xLsnr;
  printf("Method not implemented\n");
}
 
void ServerMux::broadcastToClients(const char* s)
{
  for (int i = 0; i< numClients; i++) {
    clients[i]->write((char*)s);
  }
}

void ServerMux::clientOutput(ClientOutputEvent* evt) {
  Client* src = evt->getSource();
  char* str = evt->getString();

  if (!src)
    return;

  // take a lock while using the data collector - the lock will be
  // locked for write whenever the data collector is being replaced
  // and the pointer is therefore invalid.
  if (src == controllerClient) {
    CCAFEReadLock lock(&dataCollectorMutex);
    assert (dataCollector);
    dataCollector->controllerClientOutput(evt);
  } else {
    MUX_TRACE (("Message from data client : %i \n", ((JCPN(HashKey)*)src)->hashValue()));
    CCAFEReadLock lock(&dataCollectorMutex);
    assert (dataCollector);
    dataCollector->computeClientOutput(evt);
  }
  // there is a reason for doing the out of band commands last -
  // one of the out of band commands is "shutdown this server" -
  // if we execute this command first, it becomes rather difficult
  // to propagate the command to everyone else.
  doOutOfBandCommands(str, src);
}


void ServerMux::relayMessageFromDataProducers(char* s)
{
  controllerClient->write(s);
}
void ServerMux::relayMessageFromController(char* s)
{
  MUX_TRACE(("Got a message from the controller\n"));
  broadcastToClients(s);
}
void ServerMux::setDataCollectorByName( char* className )
{
    CCAFEWriteLock lock(&dataCollectorMutex);
    ClientOutputCollector* newDataCollector = dataCollectorFactory.create(className, this);
    if (newDataCollector) {
      if (dataCollector)
	delete dataCollector;
      dataCollector = newDataCollector;
      relayMessageFromDataProducers(MessageData::makeNormalMessage(DATA_COLLECTOR_ACK, SERVER_SRC));
    } else {
      relayMessageFromDataProducers(MessageData::makeErrorMessage(DATA_COLLECTOR_ERR, SERVER_SRC));
    }
}
int ServerMux::getNumClients()
{
  return computationalClientManager->getNumConnections();
}

void ServerMux::doOutOfBandCommands(char* line, Client* src)
{
  jcpp::StringJC lineString(line);
  if(!lineString.startsWith(MessageData::ALERT_BEG)) return;
  MessageData msg(line, src);
  char* cmd = msg.getMessage();
  MUX_TRACE(("Got out of band message: %s\n", cmd));
  
  fireOOBListeners(cmd, src);
}
void ServerMux::fireOOBListeners(char* cmd, Client* client)
{
  
  OutOfBandEvent evt(client, cmd);
  JCPN(Enumeration)* e;
  for(e = listeners.elements();e->hasMoreElements();){
    OutOfBandListener* l = dynamic_cast<OutOfBandListener*> (e->nextElement());
    CHECKDC(l);
    l->processOutOfBand(&evt);
  }
  delete e;
}


const char* ServerMux::getOutofBandToken()
{
  return MessageData::ALERT_BEG;
}
#else
int ccafe_no_servermux=1;
#endif // CCAFE_THREADS
