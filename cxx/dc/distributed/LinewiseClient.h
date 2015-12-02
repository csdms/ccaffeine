#ifdef CCAFE_THREADS

#ifndef LinewiseClient_seen
#define LinewiseClient_seen

/**
   $Author: baallan $
   Created : <2000-08-10 13:35:45 pippin>
   Last modified Time-stamp: <2000-08-10 13:35:58 pippin> 
   
   This class reads from and writes to a connection, on the other end of which
   there is presumably some sort of client. Handles the job of actually reading
   and writing lines of text, then passes off the lines of text to other 
   classes (the server mux and data collector plugins) to be dealt with and 
   forwarded.
*/
#include <assert.h>
#define CLIENT_TRACE(x) printf("CLIENT: "); printf x

class LinewiseClient : public virtual Client {
 private:
  JCPN(Vector) clientOutputListeners;
  int clientId;
  JCPN(Vector) output;
  JCPN(BufferedReader)* reader;
  JCPN(Writer)* writer;
  boolean finished;
  boolean amDisconnected;
  Connection* connection;
  char* name;
  CCAFEThreadPool* threadpool;
  CCAFEReadWriteMutex mutex;
 protected:
  void notifyOutput(char* s);
  void addOutput(char* s);
 public:
  LinewiseClient(Connection* connect, CCAFEThreadPool* threadpool) {
    this->threadpool = threadpool;
    this->connection = connect;
    writer = connection->getOut();
    reader = new JCPN(BufferedReader)(connection->getIn());
    finished = FALSE;
    amDisconnected = FALSE;
    connect->setReadCallback(this);
    connect->setConnectCallback(this);
  };

  /** From <code> CCAFERunnable </code> interface. This method runs in
      a separate thread and handles reading strings from the in stream of
      the connection. 
     @return 0 in all cases.
  */
  void* run();
  
  /** From <code> ReadCallback </code> interface */
  void readReady(Connection* connection);

  /** From <code> ConnectCallback </code> interface */
  void connected(Connection* connection);
  void disconnected(Connection* connection);

  void shutdown (); 
  void disconnect ();
  void addClientOutputListener(ClientOutputListener* l)
    {clientOutputListeners.addElement(l); };
  void removeClientOutputListener(ClientOutputListener* l)
    {clientOutputListeners.removeElement(l); };
  JCPN(Vector)* getOutput() { return &output; };
  void write(char* s)
    { 
      CCAFEReadLock lock(&mutex); 
      CLIENT_TRACE (("Writing string: %s to connection\n", s)); 
      if (writer) 
	{ 
	  writer->write(s); 
	  writer->write("\n");
	  writer->flush();
	}
    };
  void flush()
    { CCAFEReadLock lock(&mutex); if (writer) writer->flush(); };
  int getId()
    { return (connection->getId()); };
  char* getSourceName() // BUGBUG - really need a string class
    { CCAFEReadLock lock(&mutex); return connection->getName(); };

  /** From <code>Object</code> */
  // boolean equals(Object* other); pointer comparison (which is what the 
  // version of equals inherited from JCPN(Object) does) is sufficient, do not
  // need to override equals.
  
  // hash based on the id of the client 
  virtual int hashValue();
};
#endif
#else
extern int ccafe_no_linewiseclient;
#endif // CCAFE_THREADS
