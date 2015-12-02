#ifdef CCAFE_THREADS

#ifndef ClientInterfaces_seen
#define ClientInterfaces_seen

#include <string.h>
/**
   Created by: apwolfe (Pippin Wolfe)
   Created : <2000-08-10 13:35:45 pippin>
   Last modified Time-stamp: <2000-08-10 13:35:58 pippin> 

   Interfaces for the multiplexor to use in attempting to communicate with
   the clients (at both end of the multiplexor)
*/

class ClientOutputListener;

class Client :public virtual JCPN(HashKey), public CCAFERunnable, 
	      public ReadCallback, public ConnectCallback 
{
 public:
  /** Add a listener for Output from this client. */
    virtual void addClientOutputListener(ClientOutputListener* l) = 0;
  /** Remove a listener for Output from this client. */
    virtual void removeClientOutputListener(ClientOutputListener* l) = 0;
  /** Write a string to a client.*/
    virtual void write(char* s) = 0;
  /** Flush the output already written to the client. */
    virtual void flush() = 0;
  /** Get the int ID unique over the ServerMux's clients */
    virtual int getId() = 0;
  /** Get the int ID unique over the ServerMux's clients */
    virtual char* getSourceName() = 0;
  /** Finish IO and close input and output streams, does not terminate
      the thread.*/
    virtual void disconnect() = 0;
  /** Finish IO and close input and output streams, does not terminate
      the thread (but does signal the thread to stop when it gets a chance).*/
    virtual void shutdown() = 0;

    virtual int hashValue() { return getId(); }
};						 

// BUGBUG - give the src a specific interface.

class ClientOutputEvent :public virtual JCPN(Object) {	 
 private:
    char* s;	 
    Client* source;
 public:
    ClientOutputEvent(Client* source, char*& s) 
      {				 
	this->source = source;
	this->s = strdup(s);				 
      }				
    ~ClientOutputEvent(){
      delete s;
    }
    Client* getSource() { return source; };
    char* getString() {			 
	return s;					 
    }						 
};

// BUGBUG - give the src a specific interface.

class OutOfBandEvent :public virtual JCPN(Object) {
 private:
  Client* source;
  char* cmd;
 public:
  OutOfBandEvent(Client* src, char* cmd) {
    this->source = src;
    this->cmd = strdup(cmd);
  }
  ~OutOfBandEvent() {
    delete cmd;
  }
  char* getOutOfBandCommand() {
    return cmd;
  }
  Client* getSource() { return source; };
};


class ClientOutputListener :public virtual JCPN(Object) {
 public:
    virtual void clientOutput(ClientOutputEvent* evt) = 0;
};

/** This interface is used by the DataCollectors to relay messages to clients
    and get information about the current number of active clients */
class ClientOutputRelay {
 public:
    virtual void relayMessageFromDataProducers(char* s) = 0;
     virtual void relayMessageFromController(char* s) = 0;
     virtual void setDataCollectorByName( char* className ) = 0;
     virtual int getNumClients() = 0;
};



class OutOfBandListener :public virtual JCPN(Object) {

    /** Process the out of band message sent to a Client.  The char*
	cmd does not include the out of band token that originally
	indicated the presence of the out of band command. */
 public:
    virtual void processOutOfBand(OutOfBandEvent* evt) = 0;
};


class ClientOutputCollector :public virtual OutOfBandListener {
 public:
    virtual void computeClientOutput(ClientOutputEvent* evt) = 0;
    virtual void controllerClientOutput(ClientOutputEvent* evt) = 0;
    virtual void setClientOutputRelay( ClientOutputRelay* cR) = 0;
}; 


#endif // seen client
#else //CCAFE_THREADS
extern int ccafe_no_clientinterfaces;
#endif //CCAFE_THREADS
