#ifdef CCAFE_THREADS // otherwise we just get an int visible in the debugger
#include <pthread.h>
#include <errno.h>
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/Enumeration.h"
#include "jc++/util/VectEnum.h"
#include "jc++/util/ResourceBucket.h"
#include "jc++/util/StringHashBucket.h"
#include "jc++/util/Vector.h"
#include "jc++/util/StringBuffer.h"
#include "Thread.h"

//#ifdef DEBUG
#define THREAD_DEBUG(x) printf ("THREAD DEBUG: "); printf x ;
//#else
//#define THREAD_DEBUG(x)
//#endif

//==========================================================================
//==========================================================================
CCAFEMutex::CCAFEMutex()
{ 
  pthread_mutexattr_t mutex_attr;
  pthread_mutexattr_init( &mutex_attr );
  /* 
     according to the man pages, mutexes are supposed to start out as 
     PTHREAD_MUTEX_FAST_NP and then must get switched to 
     PTHREAD_MUTEX_RECURSIVE_NP. However, in reality they seem to start
     out as PTHREAD_MUTEX_RECURSIVE_NP and pthread_mutexattr_setkind_np is
     not defined.
  */

  /* Changed by Rob 1Dec00 */
#ifndef OS_MACOSX
  pthread_mutexattr_settype( &mutex_attr, PTHREAD_MUTEX_RECURSIVE );
#endif /* OS_MACOSX */

  pthread_mutex_init( &mutex_id, &mutex_attr ); 
  pthread_mutexattr_destroy( &mutex_attr );
};

//==========================================================================
//==========================================================================
void* CCAFEThread::startThread(void* targetThread)
{ 
  pthread_setcancelstate( PTHREAD_CANCEL_DISABLE, NULL );
  pthread_setcanceltype( PTHREAD_CANCEL_DEFERRED, NULL );
  CCAFEThread* pThread = (CCAFEThread*) targetThread;
  return pThread->run();
};

//==========================================================================
void* CCAFEThread::run()
{
  if (runnable != NULL)
    runnable->run();
  return NULL;
};

//==========================================================================
inline void* CCAFEThread::join()
{
  void* thread_return;
  pthread_join( thread_id, &thread_return );
  return thread_return;
};

//==========================================================================
//==========================================================================

CCAFEThreadPoolThread::~CCAFEThreadPoolThread() { 
  pool->removeThread(this);
};
 
//==========================================================================
void* CCAFEThreadPoolThread::run()
{
  while (!shutdown)
    {
      THREAD_DEBUG(("waiting for start request\n"));
      start_requested.wait();
      if (shutdown)
	break;
      returnValue = CCAFEThread::run();
      THREAD_DEBUG(("Run finished, attempting to requeue thread\n"));
      pool->queueThread(this);
      done.post();
    }
  
  return returnValue;
}

//==========================================================================
void CCAFEThreadPoolThread::initialize() {
  THREAD_DEBUG(("initializing thread\n"));
  CCAFEThread::start();
}

//==========================================================================
void CCAFEThreadPoolThread::stop() {
  shutdown = TRUE;
  start_requested.post();
}

//==========================================================================
void* CCAFEThreadPoolThread::joinFinal() {
  return CCAFEThread::join();
}

//==========================================================================
// override some of the methods from the Thread class so that
// we don't have to call pthread_create each time start is called.
void* CCAFEThreadPoolThread::join() {
  done.wait();
  return returnValue; //BUGBUG - can this get corrupted?
}

//==========================================================================
int CCAFEThreadPoolThread::start() {
  THREAD_DEBUG(("starting thread\n"));
  start_requested.post();
  return 0;
};




//==========================================================================
void CCAFEThreadPool::queueThread(CCAFEThread* thread) 
{
  THREAD_DEBUG(("requeueing thread\n"));
  runningQueue.remove(thread);
  if ((availableQueue.size() + runningQueue.size()) < maxSize) {
    availableQueue.addLast(thread);    
  } else {
    THREAD_DEBUG(("Deleting a thread. pool size should be %i. available threads: %i. running threads: %i \n", maxSize, availableQueue.size(), runningQueue.size()));
    thread->interrupt();
    delete thread;
  }
};

//==========================================================================
void CCAFEThreadPool::removeThread(CCAFEThread* thread) 
{
  runningQueue.remove(thread);
  availableQueue.remove(thread);
};

//==========================================================================
CCAFEThread* CCAFEThreadPool::dequeueThread() 
{ 

  THREAD_DEBUG(("Dequeueing thread\n"));
  // attempt to remove a thread without blocking
  CCAFEThreadPoolThread* thread = dynamic_cast<CCAFEThreadPoolThread*> 
    (availableQueue.nonblockRemoveFirst());
  
  // if we failed, the queue was empty (it may not be now, but a little
  // imprecision is OK here). If we have space, make a new thread. 
  // Otherwise, ask for a connection from the queue and wait until one 
  // is available.
  if (!thread) {
    if ((availableQueue.size() + runningQueue.size()) < maxSize) {
      THREAD_DEBUG(("Creating a new thread\n"));
      thread = new CCAFEThreadPoolThread(this);
      thread->initialize();
    } else {
      THREAD_DEBUG(("Waiting for a thread\n"));
      thread = dynamic_cast<CCAFEThreadPoolThread*> (availableQueue.blockRemoveFirst()); 
    }
  }
  // add the thread to the list of running threads and return a pointer to it
  runningQueue.addLast(thread);
  return thread;
}; 

//==========================================================================
/** The queue may grow a little larger than size */
void CCAFEThreadPool::setSize( int size ) 
{
  maxSize = size;
  while (((runningQueue.size() + availableQueue.size()) > maxSize) &&
	 (availableQueue.size() > 0 ))
    {
      CCAFEThread* thread = dynamic_cast<CCAFEThread*> (availableQueue.nonblockRemoveFirst());
      delete thread;
    }
};

 
//==========================================================================
void CCAFEThreadPool::shutdown() 
{
  availableQueue.shutdown();
  runningQueue.shutdown();
  CCAFEThreadPoolThread* thread;
  while ((thread = dynamic_cast<CCAFEThreadPoolThread*> (availableQueue.nonblockRemoveFirst()))){
    thread->stop();
    thread->interrupt(); //BUGBUG - interrupt doesn't seem to work properly
    thread->joinFinal();
    delete thread;
  }
  while ((thread = dynamic_cast<CCAFEThreadPoolThread*> (runningQueue.nonblockRemoveFirst()))) {
    thread->stop();
    thread->interrupt();
    thread->joinFinal();
    delete thread;
  }
};

//==========================================================================
//==========================================================================
#else
int ccafe_no_jcpp_util_Thread=1;
#endif // CCAFE_THREADS 
