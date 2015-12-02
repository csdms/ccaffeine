#ifndef STATICIOCONN_seen
#define STATICIOCONN_seen


/**
   $Author: baallan $
   Created : <2000-08-10 13:35:45 pippin>
   Last modified Time-stamp: <2000-08-10 13:35:58 pippin> 

   A free-standing connection to a couple of file pointers. Because it
   does not depend on a ConnectionManager, it will not have asynchronous 
   reads, nor can it be disconnected and reconnected.
*/
class StaticIOConnection :public virtual Connection
{
 private:
  FILE* in;
  FILE* out;
  JCPN(Reader)* reader;
  JCPN(Writer)* writer;
  int clientId;
 public:
  StaticIOConnection (FILE* in, FILE* out, int clientId) 
    :Connection(NULL)
  { 
    this->in = in;
    this->out = out;
    reader = new JCPN(StdReader)(fileno(in));
    writer = new JCPN(StdWriter)(fileno(out));
    this->clientId = clientId; 
  };
  void setReadCallback( ReadCallback* callback ) 
  { Connection::setReadCallback(callback); doReadCallback(); };
  // the reader and writer objects should be owned by the connection -
  // the connection should always keep a pointer to them and be prepared to
  // destroy them on shutdown.
  virtual JCPN(Reader)* getIn() { return reader; };
  virtual JCPN(Writer)* getOut() {return writer; };
  virtual void shutdown() { close(fileno(in)); close(fileno(out)); };
  virtual char* getName() { return ""; }; // BUGBUG - mem leak
  int getId() { return clientId; }
};

#endif




