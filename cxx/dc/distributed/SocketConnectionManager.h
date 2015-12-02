#ifdef  CCAFE_THREADS
#ifndef SocketConnectionManager_seen
#define SocketConnectionManager_seen

#include "ConnectionManager.h"
/**
   $Author: baallan $
   Created : <2000-08-10 13:35:45 pippin>
   Last modified Time-stamp: <2000-08-10 13:35:58 pippin> 

   This class manages a set of socket connections - connecting to them,
   notifying the rest of the program when they are ready to be read, 
   disconnecting them and reconnecting them.

*/
#ifndef bufsize_seen
#define bufsize_seen
#define BSIZ BUFSIZ

enum {
  NORMAL_BUF,
  LINE_BUF,
  NO_BUF
};
#endif // bufsize_seen



class RunProcess;
class SocketConnection;



class SocketConnectionManager : public ConnectionManager {
private:
  int readWakeup[2];
  int connectWakeup[2];
  JCPN(Vector) connectionsImpl; // shutdown and delete
  JCPN(Vector) disconnected; // leave
  CCAFEThreadSafeQueue disconnectedConnections;
  CCAFEThreadSafeQueue connections;
  int numMachines;
  int serverPort;
  char* serverName; // delete
  boolean amServer;
  boolean amConnected;
  boolean amShutdown;
  boolean asyncNotify;
  int serverSocket; // shutdown
  CCAFEReadWriteMutex mutex;

  // Buffering options, probably LINE_BUF will work best.
  char buffering;
  //Backlog of connections that will wait on a connect.
  int backlog; 

  void initialize();
  int acceptConnections(int timeout);
  int connectToServer();
protected:
  friend class Connection;
  virtual void disconnectConnection(Connection* connection);
public:
  SocketConnectionManager(int myProcNumber, int serverPort, 
			  JCPN(Vector)* machines, boolean asyncNotify = TRUE);
  // constructs a single client connection
  SocketConnectionManager(int serverPort, 
			  char* serverName, boolean asyncNotify = TRUE);
  // constructs a server with multiple connections from clients
  SocketConnectionManager(int serverPort, 
			  int numMachines, boolean asyncNotify = TRUE);
  ~SocketConnectionManager();
  virtual int makeConnection(int timeout);
  /** if this is a server, this is a blocking method which waits for 
      reconnections until shutdown is called on the SocketConnectionManager */
  virtual int notifyReconnect();
  /** This is a blocking method which waits for reads on connections,
      then calls back into the ReadCallback registered for the connection
      to let the rest of the program know there is data waiting. */
  virtual void notifyReads();
  /**
     closes all connections and breaks out of the blocking loops in both
     notifyReconnect and notifyReads.
   */
  virtual void shutdown();
  virtual CCAFEThreadSafeQueue* getConnections();
  virtual int getNumConnections() { return numMachines - 1;};
  virtual boolean isConnected() { return amConnected; };
  boolean isServer();
};

class SocketConnection : public Connection {
private:
  friend class RunProcess; // BUGBUG
  int connSocket;
  int connNumber;
  FILE* in;
  FILE* out;
  JCPN(Reader)* reader;
  JCPN(Writer)* writer;
 protected:
  friend class SocketConnectionManager;
  void doSetup(char buffering, boolean asyncNotify);
public:
  SocketConnection(SocketConnectionManager* manager, int connNumber); 
  ~SocketConnection();
  CDELETE JCPN(Reader)* getIn();
  CDELETE JCPN(Writer)* getOut();
  CFREE char* getName(); 
  void shutdown();
  int getId() { return connNumber; };
};
#endif

#else  // ccafethread
extern int ccafe_no_socketcm;
#endif // CCAFE_THREADS
