#ifdef CCAFE_THREADS

#ifndef ConnectionManager_seen
#define ConnectionManager_seen

namespace jcpp {
  class Writer;
  class Reader;
} ENDSEMI

class Connection;
/**
   $Author: baallan $
   Created : <2000-08-10 13:35:45 pippin>
   Last modified Time-stamp: <2000-08-10 13:35:58 pippin> 

   Connection interfaces.
   
   These classes must be thread safe - read, reconnect, connect and the 
   callbacks will all be happening on separate threads. BUGBUG - put threads 
   in the class and make the methods private? -pippin
   
   Last modified by: $Author: baallan $
*/ 

class ConnectionManager : public virtual JCPN(Object) {
protected:
  friend class Connection;
  virtual void disconnectConnection(Connection* connection) = 0;
public:
  ConnectionManager();
  ~ConnectionManager();
  virtual int makeConnection(int timeout) = 0;

  /** will start a separate thread, if we are a server. If we are a client,
   BUGBUG can either fail or start a thread and retry periodically. */
  virtual int notifyReconnect() = 0;

  /** Read should attempt to read all the connections and call through to
      the appropriate callback object if/when any connection has data to 
      be read. Will start a separate thread. */
  virtual void notifyReads() = 0;
  virtual CCAFEThreadSafeQueue* getConnections() = 0;
  virtual void shutdown() = 0; 
  /** returns the total number of connections this manager handles -
      whether or not they are disconnected at the moment. */
  virtual int getNumConnections() =0;
  virtual boolean isConnected() = 0;
  virtual boolean isServer() = 0;
};


/** ReadCallback: object used to get notifications when there is a 
    read on a connection */
class ReadCallback {
public:
  virtual void readReady(Connection* connection) = 0;
};
/** ConnectCallback: object used to get notifications when a client 
    reconnects */
class ConnectCallback {
public:
  virtual void connected(Connection* connection) = 0;
  virtual void disconnected(Connection* connection) = 0;
};


/**
   Connection: this class provides a handle to an asynchronous connection.
   Callbacks for reading from the connection and disconnect/connect events 
   on the connection should be set here. Most of the work will be done by 
   the connection manager.

   This is an abstract class, subclasses should implement the interface using
   sockets, MPI, PVM, etc.
 */
class Connection : public virtual JCPN(Object) {
private:

  ReadCallback* readCallback;
  ConnectCallback* connectCallback;
  ConnectionManager* manager;
protected:

  // every implementation of ConnectionManager should call these functions
  // (from read, reconnect and disconnectConnection, respectively).
  friend class ConnectionManager;

  void doReadCallback() 
  {if (readCallback) readCallback->readReady(this); } ENDSEMI

  void doConnectCallback() 
  {if (connectCallback) connectCallback->connected(this); } ENDSEMI

  void doDisconnectCallback()
  { if (connectCallback) connectCallback->disconnected(this); } ENDSEMI

public:
  Connection (ConnectionManager* mgr) 
  { manager = mgr; } ENDSEMI

  virtual void disconnect() 
  { if (manager) manager -> disconnectConnection (this); } ENDSEMI

  virtual void setReadCallback( ReadCallback* callback ) 
  { readCallback = callback; } ENDSEMI

  virtual void setConnectCallback( ConnectCallback* callback ) 
  { connectCallback = callback; } ENDSEMI

  // the reader and writer objects should be owned by the connection -
  // the connection should always keep a pointer to them and be prepared to
  // destroy them on shutdown.
  virtual JCPN(Reader)* getIn() =0;
  virtual JCPN(Writer)* getOut() =0;
  virtual void shutdown() =0;
  virtual char* getName() = 0; 
  virtual int getId() = 0;
};

#endif // cm seen
#else
extern int ccafe_no_connectionmanager;
#endif // CCAFE_THREADS
