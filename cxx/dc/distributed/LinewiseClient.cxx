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
#include "jc++/io/Reader.h"
#include "jc++/io/Writer.h"
#include "jc++/io/BufferedReader.h"
#include "jc++/io/StdWriter.h"
#include "util/IO.h"
#include "ProcessorInfo.h"
#include "ConnectionManager.h"
#include "ClientInterfaces.h"
#include "LinewiseClient.h"


void cleanup_func( void* arg ) {
  CCAFEMutex* mutex = (CCAFEMutex*) arg;
  mutex->unlock();
  // BUGBUG - the string returned from readLine is not being
  // free-d here. 
};

/** 
    LinewiseClient::run() attempts to read messages from the connection until
    there
 */
void* LinewiseClient::run() {

  // this will block if the connection being used does not have reads set 
  // up as non-blocking

  CLIENT_TRACE(("thread started \n"));
  {
      char* str;
      pthread_cleanup_push(&cleanup_func, &mutex);
      CCAFEThread::enableInterrupts();
      while(1)
	{ 
	  { // scope for the read lock
	    CCAFEReadLock lock(&mutex);
	    if (amDisconnected || finished)
	      {
		CLIENT_TRACE(("disconnected - cancelling read\n"));
		break;
	      }
	    if ((str = reader->readLine()) == 0)
	      break;
	  } //end scope for read lock
	  CLIENT_TRACE(("output - %s\n", str));
	  addOutput(str);
	  notifyOutput(str);
	  if (str)
	    free(str);
	}
      CCAFEThread::disableInterrupts();
      pthread_cleanup_pop(0 /* don't execute the cleanup func before popping*/);
      
      if (amDisconnected || finished)
	{
	  CLIENT_TRACE(("disconnected - cancelling read\n"));
	  return NULL;
	}
  }
  //errors:
  // EAGAIN : no more data, wait for more writes
  // EINTR : signal recieved, wait again
  // exit the thread and wait for another read to come in from
  // the <code> ConnectionManager </code>
  
  // EPIPE : the socket is gone
  // EIO, EISDIR, EBADF, EINVAL, EFAULT etc - fd is unusable for
  // some reason, must be recreated before it can be used
      // do shutdown code, exit, and wait for the user to start us up 
  // again
  perror("finished reading with error ");
  CLIENT_TRACE(( "errno is: %x eagain is: %x eintr is %x\n", errno, EAGAIN, EINTR));
  if (!((errno == EAGAIN) || (errno == EINTR)/* || (errno == 0)*/)) {
    CLIENT_TRACE(("Disconnecting client due to error: %i\n", errno));
    disconnect();
  }

  CLIENT_TRACE(("Output from client finished, returning from run\n"));
  return NULL;
}


void LinewiseClient::readReady(Connection* connection)  
{
  //  assert (connection == this->connection);
  (void)connection;
  
  // this will block if there are no threads available - watch out for
  // deadlock.
  CCAFEThread* thread = threadpool->dequeueThread();
  //assert (thread);
  thread->setRunnable(this);
  thread->start();
}

void LinewiseClient::disconnect() 
{
  // the disconnect call must come first and be outside the 
  // write lock for the following reason:
  // if the connection is not non-blocking, the read thread will almost always
  // have a read lock taken and be waiting for input on the reader. Disconnect
  // will bump the reader thread out of the blocking call, after which point we
  // can safely take the lock and continue mucking with the instance variables
  // we need to change.
  amDisconnected = TRUE;
  connection->disconnect();

  CCAFEWriteLock lock(&mutex);

  delete reader;
  writer = NULL;
  reader = NULL;
}

void LinewiseClient::shutdown() 
{ 
  finished = TRUE; 
  connection->disconnect();
  connection->shutdown(); 
};

void LinewiseClient::connected(Connection* connection) 
{
  CCAFEWriteLock lock(&mutex);
  //assert(connection == this->connection);
  writer = connection->getOut();
  delete reader;
  reader = NULL;
  reader = new JCPN(BufferedReader)(connection->getIn());
  amDisconnected = FALSE;
}
// BUGBUG - may not be able to aquire the lock here, because 
// we already have the read lock. Add "ownership" to the read/write lock
// and allow increasing and decreasing ownership.
void LinewiseClient::disconnected(Connection* connection) 
{
  //assert(connection == this->connection);
 (void)connection;
  CLIENT_TRACE((" client disconnected\n"));
}

// called from run, which already has a read lock - re-take the lock?
void LinewiseClient::notifyOutput(char* output) 
{
  for (int i =0 ; i < clientOutputListeners.size(); i++) {
    ClientOutputListener* listener = dynamic_cast<ClientOutputListener*> (clientOutputListeners.elementAt(i));
    ClientOutputEvent evt( this, output );
    listener->clientOutput(&evt);
  }
}

void LinewiseClient::addOutput(char* output)
{
	(void) output;
}

int LinewiseClient::hashValue()
{ return getId(); };
#else // CCAFE_THREADS
int ccafe_no_linewiseclient=1;
#endif // CCAFE_THREADS
