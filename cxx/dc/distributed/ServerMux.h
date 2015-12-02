#ifdef CCAFE_THREADS

#ifndef ServerMux_seen
#define ServerMux_seen

/**
   $Author: baallan $
   Created : <2000-08-10 13:35:45 pippin>
   Last modified Time-stamp: <2000-08-10 13:35:58 pippin> 

   Copied (mostly) from the java version by rob. This class serves as the 
   communication mechanism for a controller process and the distributed clients
   it controlls. ServerMuxes can be chained together to form large trees of
   ServerMuxes with many, many clients.
*/





/**
   A thread which listens for io on the distributed client connection manager
 */
class IOThread :public CCAFEThread {
private:
  ConnectionManager* manager;
  boolean running;
public:
  IOThread(ConnectionManager* manager) {this->manager = manager; running = TRUE; };
  void* run() 
  {
      manager->notifyReads();
      return NULL;
  };
};





/**
   A thread which listens for reconnect events on the distributed client 
   connection manager.
 */
class ConnectThread :public CCAFEThread {
private:
  ConnectionManager* manager;
  boolean running;
public:
  ConnectThread(ConnectionManager* manager) {this->manager = manager; running = TRUE; };
  void* run() 
  {
      manager->notifyReconnect();
      return NULL;
  };
};





/**
   The server mux. see comment at top of file
*/
class ServerMux :public virtual ClientOutputListener, 
		 public virtual ClientOutputRelay {
private:
  Client* controllerClient;
  CCAFEThread* controllerThread;
  Client** clients;
  int numClients;
  CCAFEThreadPool threadpool;
  boolean isStarted;
  ConnectionManager* computationalClientManager;
  ClientOutputCollector* dataCollector;
  JCPN(Vector) listeners;
  IOThread ioThread;
  ConnectThread connThread;
  static char* outOfBandToken;
  DataCollectorFactory dataCollectorFactory;
  CCAFEReadWriteMutex dataCollectorMutex;

public:
  static const char* SERVER_SRC ;// = "ServerMux";
  static const char* DATA_COLLECTOR_ACK ;// = "DATA_COLLECTOR_ACK";
  static const char* DATA_COLLECTOR_ERR ;// = "DATA_COLLECTOR_NOT_SET";
  static const char* DATA_COLLECTOR_MSG ;// = "DATA_COLLECTOR=";
  static const char* SHUTDOWN_MSG  ;//= "SHUTDOWN_MSG";
  static const char* REMOVE_CLIENT_MSG ;// = "REMOVE_CLIENT_MSG";
  ServerMux(ConnectionManager* computeManager, Connection* controllerConnect);
  ~ServerMux();
  void shutdown();
  void join();

  // BUGBUG - no longer applicable - how do we tell when to shutdown?
  CCAFEThread* getControllerClientThread();

  void setExternalClientOutputListener(ClientOutputListener* xLsnr);
  void doClientIO();
  void broadcastToClients(const char* s);
  boolean isRunning() { return isStarted; };

  // ClientOutputListener
  virtual void clientOutput(ClientOutputEvent* evt);

  // ClientOutputRelay
  virtual void relayMessageFromDataProducers(char* s);
  virtual void relayMessageFromController(char* s);
  virtual void setDataCollectorByName( char* className );
  virtual int getNumClients();

  // related to OutOfBandListeners
  void addOutOfBandListener(OutOfBandListener* l) {
    listeners.addElement(l);
  }
  void removeOutOfBandListener(OutOfBandListener* l) {
    listeners.removeElement(l);
  }
  /** Set the out of band token that gets recognized and passed on to
      outOfBandListeners that may be interested in special commands.
      These commands will not be written on the normal output JCPN(Writer).
      This could be improved by having any number of different tokens
      that would be associated with any number of listener classes.
      In this way there could be a variety of out of band listeners
      for different contexts.  The out of band token must appear first
      on a line with the subsequent command completed with out
      breaking the line.*/
  /** Return the out of band token. */
  static const char* getOutofBandToken(); 

private:
  /** Check for the presence of out of band command, if not just return. */
  void doOutOfBandCommands(char* line, Client* src);
  /** execute out of band commands */
  void fireOOBListeners(char* cmd, Client* client);
};
#endif // seen servermux
#else
extern int ccafe_no_servermux;
#endif // CCAFE_THREADS
