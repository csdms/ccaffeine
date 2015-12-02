#ifdef CCAFE_THREADS

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#ifdef __sun
#ifdef __SUNPRO_CC
     #include <fcntl.h>
#endif
#endif
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <assert.h>
#include <errno.h>

#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "jc++/util/Thread.h"
#include "jc++/io/Reader.h"
#include "jc++/io/Writer.h"
#include "jc++/io/StdReader.h"
#include "jc++/io/StdWriter.h"
#ifdef HAVE_CLASSIC
#include <cca.h>
#endif // HAVE_CLASSIC
#include "util/IO.h"
#include "ProcessorInfo.h"
#include "ConnectionManager.h"
#include "SocketConnectionManager.h"


#ifdef DEBUG
#define SOCKET_TRACE(x) printf("SOCKMGR: "); printf x
#else
#define SOCKET_TRACE(x)
#endif

// hack around broken glibc 2.1.1 headers
#ifndef SHUT_RDWR
#ifdef __linux__
#define SHUT_RDWR 2
#endif
#endif

#if defined(OS_IRIX5) | defined(OS_IRIX64)
# ifndef socklen_t
#  define socklen_t int
# endif
#endif /* OS_IRIX */

/**
   Constructors 
 */

  
SocketConnectionManager::SocketConnectionManager(int myProcNumber, 
						 int serverPort, 
						 JCPN(Vector)* machines,
						 boolean asyncNotify)
  :disconnectedConnections(&disconnected), connections(&connectionsImpl) {
  this->asyncNotify = asyncNotify;
  int serverProcNumber = 0;
  this->serverPort = serverPort;
  numMachines = machines->size();
  for(int i = 0;i < numMachines;i++) {
    ProcessorInfo *pi = (ProcessorInfo*)machines->elementAt(i);
    if(pi->isServer()) serverProcNumber = i;
    
  }
  if (serverProcNumber == myProcNumber) {
    amServer = TRUE;
  }
  if (!isServer())
    {
      ProcessorInfo* serv = 
	(ProcessorInfo*)machines->elementAt(serverProcNumber);
      serverName = strdup(serv->getName()); // make a copy of the string
    }
  initialize();
}

SocketConnectionManager::SocketConnectionManager(int serverPort,
						 char* serverName,
						 boolean asyncNotify )
  :disconnectedConnections(&disconnected), connections(&connectionsImpl) 
{
  this->asyncNotify = asyncNotify;
  this->serverPort = serverPort;
  this->amServer = FALSE;
  this->serverName = strdup(serverName);
  initialize();
}


SocketConnectionManager::SocketConnectionManager(int serverPort,
						 int numMachines,
						 boolean asyncNotify )
  :disconnectedConnections(&disconnected), connections(&connectionsImpl)
{
  this->asyncNotify = asyncNotify;
  this->serverPort = serverPort;
  this->amServer = TRUE;
  this->numMachines = numMachines+1;
  initialize();
}

/** called by all the constructors */
void SocketConnectionManager::initialize()
{
  amConnected = FALSE;
  amShutdown = FALSE;
  if(isServer()) {
    connections.ensureCapacity(numMachines-1);
  } else {
    SOCKET_TRACE(("initializing client %s\n", serverName));
    numMachines = 2;
    connections.ensureCapacity(numMachines-1);
  }
  buffering = (char)LINE_BUF;
  // Number of processes that can be backed up waiting for me to accept
  // connections.
  backlog = 100; 
  pipe(readWakeup);
  pipe(connectWakeup);
}


void SocketConnectionManager::shutdown()
{
  amShutdown = TRUE;

  connections.shutdown();
  disconnectedConnections.shutdown();
  // shutdown all sockets
  for (int i = 0; i < connections.size(); i++) {
    SocketConnection* connection = dynamic_cast<SocketConnection*> (connections.elementAt(i)); CHECKDC(connection);
    connection->shutdown();
  }
  
  SOCKET_TRACE(("Waking up the connect thread\n"));
  write(connectWakeup[1], " ", 1);

  {
    CCAFEWriteLock lock (&mutex);
    // shutdown the serverSocket. This should cause notifyReconnect to 
    // fail in <code>accept</code>, then stop because amShutdown is set.
    ::shutdown(serverSocket, SHUT_RDWR);
    serverSocket = -1;
  }

  // if there is a thread waiting for reads, we also need to wake up 
  // that thread so that it can notice amShutdown and exit gracefully.
  SOCKET_TRACE(("Waking up the read thread\n"));
  write(readWakeup[1], " ", 1);
}


SocketConnectionManager::~SocketConnectionManager(){

  shutdown();
  while (disconnectedConnections.size() >0) {
    JCPN(Object)* obj = disconnectedConnections.nonblockRemoveFirst();
    //SocketConnection* connection = dynamic_cast<SocketConnection*> (obj); CHECKDC(connection);
    delete obj;
  }
  disconnectedConnections.removeAllElements(); 

  // shutdown and delete all connections
  while (connections.size()>0) {
    SocketConnection* connection = dynamic_cast<SocketConnection*> (connections.nonblockRemoveFirst()); CHECKDC(connection);
    connection->shutdown();
    delete connection;
  }

  // close the pipe
  ::close(readWakeup[0]);
  ::close(readWakeup[1]);
  ::close(connectWakeup[0]);
  ::close(connectWakeup[1]);

  // delete our char*
  if (serverName)
    delete serverName;

  // close the server socket
  if (isServer())
    {
      int result = ::close(serverSocket);
      if (result != 0)
	{
	  perror("SocketConnectionManager::~SocketConnectionManager");
	}
    }
}

CCAFEThreadSafeQueue* SocketConnectionManager::getConnections() 
{
  return &connections; 
}

/** Go ahead and make the connection that has already been set up.
    Returns: 0 for sucess, -1 for failure due to inconsistency in
    the current configuration, -2 for failure due to a network
    problem  BUGBUG: old comment, doesn't appear to be true, looking 
    at the code below. Fix? */
int SocketConnectionManager::makeConnection(int timeout)
{
  if(isServer()) {
    if(acceptConnections(timeout) != 0) return -1;
  }
  else {
    if(connectToServer() != 0) return -1;
  }

  return 0;
}

void SocketConnectionManager::disconnectConnection(Connection* connection)
{
  // check for in/out valid first? do these throw? or access violate?
  SocketConnection* conn = dynamic_cast<SocketConnection*> (connection); CHECKDC(conn);

  // only disconnect the connection if it was previously in the connected pile
  // otherwise you may end up adding it to the disconnected list twice
  if (connections.remove(conn))
    disconnectedConnections.addLast(conn);
  else 
    return;

  // More nit-pickiness. The connection _must_ be shutdown after the connection
  // is removed from the list of valid connections because: shutdown on the 
  // connection causes select to wake up with an event on that connection. If
  // shutdown is called while the connection is in the valid connection list,
  // notifyReads can wake up and do a select on an invalid fd.
  conn->shutdown();
  conn->doDisconnectCallback();
}


/** Blocking call to monitor the socket for reconnects, if this is a server.
    If this is not a server, a no-op. */

int SocketConnectionManager::notifyReconnect()
{
  if (isServer()) {
    struct sockaddr_in from;
    memset(&from, 0, sizeof(from));

    if (serverSocket < 0) // not a valid socket
      return -4; // copied error code from accept connections
    
    listen(serverSocket, backlog);
    size_t len = sizeof(from);
#if __linux
    unsigned int ulen = len;
#endif

    // This loop has two blocking calls - the call to get a connection from
    // the disconnected queue and the call to accept socket connections.
    // On shutdown, the queue is shutdown, which will cause the blocking 
    // dequeue to fail and return, and the socket is shutdown, which will 
    // cause the blocking accept to fail and return. At that point we return
    // to the top of the loop and break out of the method.
    while(!amShutdown) {

      SOCKET_TRACE(("Entering while loop for reconnects\n"));


      //Note that the order of sockets in array ss is not the same as
      //the order in JCPN(Vector) machines.
      SocketConnection* connection = dynamic_cast<SocketConnection*> (disconnectedConnections.blockRemoveFirst()); 

      
      if (!connection)
	if (!amShutdown)
	  CHECKDC(connection);
	else
	  continue;


      if (amShutdown) {
	  return 0;
      }

      SOCKET_TRACE(("Got a disconnected connection, waiting for sockets\n"));
      // the only reason the select is here is to enable a clean shutdown -
      // with a blocking accept, even when the socket is closed, this thread 
      // continues to wait for a connection. If we add a select, we can use a 
      // second file descriptor to signal the thread when shutdown has been 
      // called, thus breaking out of the select call and allowing us to 
      // continue
      
      // add in an extra file descriptor to a pipe in this class - we'll use the 
      // pipe to break into the select if it needs to be interrupted.
      fd_set read_fds;
      FD_ZERO(&read_fds);
      int maxId = 0;
      FD_SET(connectWakeup[0], &read_fds);
      maxId = (connectWakeup[0] > maxId) ? connectWakeup[0] : maxId;

      int retval = 0;
      {
	CCAFEReadLock lock(&mutex);
	if (amShutdown) {
	  return 0;
	}

	FD_SET(serverSocket, &read_fds);
	maxId = (serverSocket > maxId) ? serverSocket : maxId;
     
	// the select call
	retval = ::select (maxId+1, &read_fds, NULL, NULL, NULL);
      }
      
      SOCKET_TRACE(("Got %i connections\n", retval));
      
      if (retval <= 0) {
	  perror("Error accepting connections on server socket:");
	  return -1;
      }	  
      if (amShutdown) {
	return 0;
      }
      assert(FD_ISSET(serverSocket, &read_fds));

#if __linux
      connection->connSocket = accept(serverSocket, (sockaddr*)&from, &ulen);
      len = ulen;
#else
      socklen_t ilen = (socklen_t)len;
      connection->connSocket = accept(serverSocket, (sockaddr*)&from, &ilen);
      len = (int) ilen;
#endif // else linux

      if (connection->connSocket == -1) { /* error from accept */
	perror(("Could not connect socket"));
	disconnectedConnections.addLast(connection);
	continue;
      }
      SOCKET_TRACE(("Got a reconnected connection\n"));


      struct hostent* frm = gethostbyaddr((char*)&from, len, AF_INET);
      if(frm != NULL) {
	IO::en("connected to: %s", frm->h_name);
      } else {
	IO::en("Hey! cannot tell who connected ... (proceeding)");
      }
      connection->doSetup(buffering, asyncNotify);
      connection->doConnectCallback();
      connections.addLast(connection);
      SOCKET_TRACE(("Waking up the select thread\n"));
      write(readWakeup[1], " ", 1);
    }
  } else {
    IO::en("SocketConnectionManager: Cannot reconnect a client connection");
  }

  return 0;
}

/** 
    This method loops, blocking in a select call until something is written
    to one of the sockets, then calling back into the <code>ReadCallback</code>
    objects registered with the <code>Connection</code>s. The select call
    can be interrupted by writing to the readWakeup pipe - this provides a 
    graceful way to break out of the loop without using a thread interrupt.
*/
void SocketConnectionManager::notifyReads()
{
  while (!amShutdown) {
    fd_set read_fds;
    FD_ZERO(&read_fds);
    int maxId = 0;

    // add file descriptors for all the currently active connections
    // to the select call

    // lock the queue while iterating through the connections, so that
    // the size does not change while we are in the loop. Disconnects and
    // reconnects will be blocked for as long as this takes.
    {
      CCAFEQueueLock lock(&connections);
      for (int i = 0; i < connections.size(); i++) {
	SocketConnection* connection = dynamic_cast<SocketConnection*> (connections.elementAt(i)); CHECKDC(connection);
	FD_SET(connection->connSocket, &read_fds);
	maxId = (connection->connSocket > maxId) ? connection->connSocket : maxId;
      }
    }

    // add in an extra file descriptor to a pipe in this class - we'll use the 
    // pipe to break into the select if it needs to be interrupted.
    FD_SET(readWakeup[0], &read_fds);
    maxId = (readWakeup[0] > maxId) ? readWakeup[0] : maxId;
    
    // the select call
    int retval = ::select (maxId+1, &read_fds, NULL, NULL, NULL);
    SOCKET_TRACE(("Got %i writes on sockets\n", retval));
    
    if (retval >= 0) {
      // check for messages for connections

      // lock the queue while in the loop
      CCAFEQueueLock lock(&connections);
      for (int i = 0; i < connections.size(); i++) {
	SocketConnection* connection = dynamic_cast<SocketConnection*> (connections.elementAt(i)); CHECKDC(connection);
	if (FD_ISSET(connection->connSocket, &read_fds)) {
	  SOCKET_TRACE(("Notifying connection\n"));
	  connection->doReadCallback();
	}
      }
      // clear the wakeup pipe, if it was set
      if (FD_ISSET(readWakeup[0], &read_fds))
	{
	  SOCKET_TRACE(("Read char from pipe\n"));
	  char cread;
	  read(readWakeup[0], &cread, 1);
	}
    } else {
      perror("error in SocketConnectionManager::notifyReads while doing a select");
      /* errors:
	 EBADF  An  invalid file descriptor was given in one of the
	 sets.
	 
	 EINTR  A non blocked signal was caught.
	 
       EINVAL n is negative.
       
       ENOMEM select was unable to allocate memory  for  internal
       tables.
      */
    }
  }
}



/** BUGBUG - timeout not used yet. May not be useable... 
    This method is stolen from the ClientServerSocket class */
int SocketConnectionManager::acceptConnections(int timeout) {
  (void) timeout;
  SOCKET_TRACE(("accepting connections\n"));
  struct sockaddr_in from, sin;
  memset(&sin, 0, sizeof(sin));
  memset(&from, 0, sizeof(from));
  sin.sin_port = htons(serverPort);
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if(bind(serverSocket, (const sockaddr*)&sin, sizeof(sin))) { 
    perror("SocketConnectionManager::acceptConnections");
    IO::en("bind: network problem");
    return -4;
  }
  listen(serverSocket, backlog);
  size_t len = sizeof(from);
#if __linux
  unsigned int ulen = len;
#endif

  // Probably should set an alarm...
  for(int i = 0;i < numMachines - 1;i++) {
    //Note that the order of sockets in array ss is not the same as
    //the order in JCPN(Vector) machines.
    SocketConnection* connection = new SocketConnection(this, i);
#if __linux
    connection->connSocket = accept(serverSocket, (sockaddr*)&from, &ulen);
    len = ulen;
#else
    socklen_t ilen = (socklen_t)len;
    connection->connSocket = accept(serverSocket, (sockaddr*)&from, &ilen);
    len = (int) ilen;
#endif // else linux
    struct hostent* frm = gethostbyaddr((char*)&from, len, AF_INET);
    if(frm != NULL) {
      IO::en("connected to: %s", frm->h_name);
    } else {
      IO::en("Hey! cannot tell who connected ... (proceeding)");
    }
    connection->doSetup(buffering, asyncNotify);
    // the connection is ready to be used - now we can add it to the 
    // list of connections
    connections.addLast(connection);
  }
  amConnected = TRUE;
  return 0;
}

int SocketConnectionManager::connectToServer() {
  hostent* hp = gethostbyname(serverName);
  if(hp == NULL) { 
    perror("SocketConnectionManager::connectToServer");
    IO::en("unknown host: %s\n", serverName);
    return -1;
  }
  struct sockaddr_in server;
  memset(&server, 0, sizeof(server));
  memcpy(&(server.sin_addr), hp->h_addr, hp->h_length);
  server.sin_family = hp->h_addrtype;
  server.sin_port = htons(serverPort);  
  SocketConnection* connection = new SocketConnection(this, 0);
  connection->connSocket = socket(AF_INET,SOCK_STREAM,0);
  if(connection->connSocket < 0) { 
    perror("SocketConnectionManager::connectToServer:");
    IO::en("socket: there is some network problem\n");
    return -3;
  }
#ifdef __linux
  if(connect(connection->connSocket, (const sockaddr*)&server, sizeof(server)) < 0) {
#else
  if(connect(connection->connSocket, (sockaddr*)&server, sizeof(server)) < 0) {
#endif
    perror("SocketConnectionManager::connectToServer");
    IO::en("connect: there is some network problem\n");
    return -3; 
  }
  connection->doSetup(buffering, asyncNotify);
  connections.addLast(connection);
  amConnected = TRUE;
  return 0;
}

boolean SocketConnectionManager::isServer() {
  return amServer;
}
 
 








SocketConnection::SocketConnection(SocketConnectionManager* manager,
				   int connNumber) 
  :Connection(manager)
  {
    this->connNumber = connNumber;
  }
SocketConnection::~SocketConnection()
  { 
    delete reader;
    delete writer;
    reader = NULL;
    writer = NULL;
  }
void SocketConnection::doSetup(char buffering, boolean asyncNotify)
  {
    // set up the connection to be non-blocking
    if (asyncNotify) {
      SOCKET_TRACE(("setting non-blocking reads\n"));
      fcntl(connSocket, F_SETFL, O_NONBLOCK);
    }
    // set up the input and output streams
    in = fdopen(connSocket, "r");
    out = fdopen(connSocket, "w");
    switch((char)buffering)
      {
      case NORMAL_BUF:
	break;
      case LINE_BUF:
	setvbuf(in, NULL, _IOLBF, BSIZ);
	setvbuf(out, NULL, _IOLBF, BSIZ);
	break;
      case NO_BUF:
	setvbuf(in, NULL, _IONBF, BSIZ);
	setvbuf(out, NULL, _IONBF, BSIZ);
	break;
      }
    reader = new JCPN(StdReader)(fileno(in));
    writer = new JCPN(StdWriter)(fileno(out));
  }
JCPN(Reader)* SocketConnection::getIn() 
{ 
  return reader; 
}; //BUGBUG - not safe mem management

JCPN(Writer)* SocketConnection::getOut()
{
  return writer;
}; //BUGBUG - not safe mem management

CFREE char* SocketConnection::getName() {
  sockaddr *from = (sockaddr*)::malloc(sizeof(sockaddr_in));
  unsigned int size = (unsigned int)sizeof(sockaddr_in);
  if(::getpeername(connSocket, from, (socklen_t*) &size) != 0) {
    IO::en("SocketConnection::getName: getpeername: can't get peer sockaddr\n");
  } else {
    IO::en("SocketConnection::getName: getpeername: sockaddr = %hu", *from);
    IO::en("SocketConnection::getName: getpeername: sockaddr = %.14s", 
	   from->sa_data);
  }
  struct hostent *he = ::gethostbyaddr((const char *)from, size, AF_INET);
  if(he != 0) {
    IO::en("SocketConnection::getName: official name of host = %s", 
	   he->h_name);
  }
  char *result;
  result = STRDUP(he->h_name);
  assert(result !=0);
  return result;
 
//was pippins:
//   sockaddr from;
//   int size = sizeof(from);
//   getpeername(connSocket, &from, &size);
//   return (char*) &from; // BUGBUG: returning piece of stack.
}
  

void SocketConnection::shutdown() 
{
  int result = ::shutdown(connSocket, SHUT_RDWR);
  if (result < 0)
      perror("Shutdown of socketconnection had error ");
  else
      SOCKET_TRACE(("Closed socketconnection\n"));
  ::close(fileno(in));
  ::close(fileno(out));
  ::close(connSocket);
} 

#else  // ccafethread
int ccafe_no_socketcm=1;
#endif // CCAFE_THREADS
