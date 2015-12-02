#ifdef CCAFE_THREADS /* not visible unless threads supported */
#ifndef Thread_seen
#define Thread_seen

/**
   File: Thread.h
   Created By: apwolfe (Pippin Wolfe)
   Created: <2000-07-25 09:53:29 pippin>
   Last Modified Time-stamp: <2000-08-10 13:34:51 pippin>

   Includes a variety of thread related classes.
   Includes nonportable pthreads code.
*/
#include "pthread.h"
#include <stdio.h>
#include <signal.h>
#include <semaphore.h>
// #include <errno.h>

/** MacOSX's pthread implementation is not complete */
#ifdef OS_MACOSX
# include "pth_rwlock.h"

#define pthread_rwlock_t      pth_rwlock_t
#define pthread_rwlock_init   pth_rwlock_init
#define pthread_rwlock_rdlock pth_rwlock_rdlock
#define pthread_rwlock_wrlock pth_rwlock_wrlock
#define pthread_rwlock_unlock pth_rwlock_unlock

#endif /* OS_MACOSX */


class CCAFECondition;

class CCAFERunnable {
public:
  virtual void* run() = 0;

};


/** A Thread class. */
class CCAFEThread : public virtual jcpp::Object {
private:
  CCAFERunnable* runnable;
  pthread_t thread_id;
  static void* startThread(void* targetThread);
public:
  CCAFEThread()
  {
    runnable = NULL;
  };
  
  CCAFEThread(CCAFERunnable* newRunnable)
  {
    runnable = newRunnable;
  };
  /** 
      Destroys all data associated with the thread. This causes problems
      if the thread is still running. Therefore, join the thread and wait
      until it ends.
  */
  virtual ~CCAFEThread() 
  {
    join();
  }
  inline void setRunnable(CCAFERunnable* newRunnable) 
  {
    runnable = newRunnable;
  }
  /** 
      Warning: if a subclass overrides run _and_ has a runnable instance var
      set, subclass's run takes precedence - the runnable will not be called 
      unless the subclass calls it explicitly or by calling its superclass -
      CCAFEThread::run(). 
  */
  virtual void* run(); 
  
  virtual int start() 
  {
    return pthread_create( &thread_id, NULL, &CCAFEThread::startThread, this);
  }
  virtual void* join(); 
  /** 
      Enables interrupts on the current (calling) thread (hence the static 
      method). 
      Warning: Interrupts do _not_ clean up the stack - always include a 
      cleanup function to take care of locked mutexes and un-destructed local
      variables. See pthread_cleanup_push() and 
      pthread_cleanup_pop() for information on how to do this.
      
  */
  inline static void enableInterrupts() {
    pthread_setcancelstate( PTHREAD_CANCEL_ENABLE, NULL );
    pthread_setcanceltype( PTHREAD_CANCEL_DEFERRED, NULL );
  }
  /** 
      Disables interrupts on the current (calling) thread.
  */
  inline static void disableInterrupts() {
    pthread_setcancelstate( PTHREAD_CANCEL_DISABLE, NULL );
  }
  /** 
      If interrupts are enabled, this will interrupt the thread. Interrupts 
      are disabled by default, and I highly recommend leaving them that way - 
      see the comment for enableInterrupts. Local variables will _not_ have 
      their destructors called when an interrupt exits a method.

      There are some cases where it may be necessary to enable interrupts for
      a brief period while waiting on a blocking system call. I also 
      recommend attempting to keep all calls to interrupt limited to the 
      program's shutdown sequence.
  */
  inline int interrupt()
  {
    return pthread_cancel( thread_id );
  }
};




/** 
    Mutex class - used to lock out other threads from pieces of code 
    (temporarily). Use the MutexLock class to acquire and release the lock.

    by default, a "recursive" mutex - a thread can own the lock and still 
    take the lock again. 
*/
class CCAFEMutex {
private:
  friend class CCAFECondition;
  pthread_mutex_t mutex_id;
  int unlock_internal()
  {
    return pthread_mutex_unlock(&mutex_id);
  };
public:
  
  CCAFEMutex(); 
  
  ~CCAFEMutex()
  {
    int error = pthread_mutex_destroy(&mutex_id);
    if (error == EBUSY)
      {
	// if there are errors here, no way to recover - ignoring them
	pthread_mutex_unlock(&mutex_id);
	pthread_mutex_destroy(&mutex_id);
      }
  };
  
  /** this method blocks until the lock is available */
  inline int lock()
  { 
    return pthread_mutex_lock(&mutex_id);
  };
  
  /** this method takes the lock if available, but 
      returns EBUSY immediately if the lock is not available. 
      ( see pthread_mutex_trylock ) */
  inline int tryLock()
  {
    return pthread_mutex_trylock(&mutex_id);
  };
  
  /** releases the lock on the mutex */
  inline int unlock()
  {
    // remove the last cleanup function for the thread, since
    // the mutex is now unlocked.
    //pthread_mutex_cleanup_pop(0);
    return unlock_internal();
  };
};

/** An exception safe method of locking a mutex within a brief scope - create a
    class around the mutex. When the class is destroyed, the mutex is
    unlocked. MutexLocks should typically be used as short lived local
    variables (created on the stack).  Alloc-ing them with new just
    creates a new headache. */

class CCAFEMutexLock {
private:
  CCAFEMutex* mutex;
public:

  /** locks a mutex */
  CCAFEMutexLock(CCAFEMutex* newMutex) 
  { 
    mutex = newMutex; 
    if (mutex) mutex->lock(); 
  };

  /** releases the mutex that was locked in the constructor */
  ~CCAFEMutexLock()   { if (mutex) mutex->unlock(); };
  
};

/**
   A Condition class. Threads can wait on the condition, a signal or 
   broadcast from another thread is necessary to wake them up again. 
   Takes a mutex, should already be locked, and releases it for the length 
   of the wait, then reaquires it when re-awakened.

   Example of semantic difference compared to a semaphore:
   The sequence thread 2 sem->post, thread 1 sem->wait lets thread 1 through
   using semaphores, but the sequence thread 2 cond->signal, thread 1 
   cond->wait will cause thread 1 to block until another signal is recieved.
*/
class CCAFECondition {
private:
  pthread_cond_t cond;

public:

  CCAFECondition() {
    pthread_cond_init(&cond, NULL);
  }

  ~CCAFECondition() { pthread_cond_destroy (&cond); };
  
  /** the mutex passed in here should be locked when the method is called. It
      will be released by wait, then reaquired when wait returns. (see 
      pthread_cond_wait */
  inline int wait(CCAFEMutex* mutex) { return pthread_cond_wait (&cond, &(mutex->mutex_id)); };
  
  /** wakes up one waiting thread. If no threads are waiting, this is a no-op 
   */
  inline int signal() { return pthread_cond_signal (&cond); };
  
  /** wakes up all waiting threads. If no threads are waiting, this is a 
      no-op. */
  inline int broadcast() { return pthread_cond_broadcast (&cond); };
};


class CCAFEReadLock;
class CCAFEWriteLock;

/** a simple readers/writers lock implemented using a mutex and a couple of 
    conditions. see ReadLock and WriteLock. BUGBUG - make sure writers can't 
    starve.
    Warning: you CANNOT reaquire this lock for writes (reads are of course 
    fine) - if a thread tries to lock it twice in a row, (either write/write or
    read/write) it will immediately 
    deadlock.
*/
class CCAFEReadWriteMutex {
private:
  pthread_rwlock_t rwlock;
public:

  CCAFEReadWriteMutex()
  {
    pthread_rwlock_init(&rwlock, NULL);
  };

protected:
  friend class CCAFEReadLock;
  friend class CCAFEWriteLock;
  
  /** we can read as long as there are no writers in the lock currently */
  void readLock(){
    pthread_rwlock_rdlock(&rwlock);
  }

  /** In order to write, we need to have both no writers and no readers */
  void writeLock() {
    pthread_rwlock_wrlock(&rwlock);
  }

  void unlock() {
    pthread_rwlock_unlock(&rwlock);
  }

};

/** takes a read lock in the constructor, releases it in the destructor */
class CCAFEReadLock {
private:
  CCAFEReadWriteMutex* rw_mut;
public:

  CCAFEReadLock( CCAFEReadWriteMutex* rw_mut_ ) {
    rw_mut = rw_mut_;
    rw_mut->readLock();
  }

  ~CCAFEReadLock() {
    rw_mut->unlock();
  }
};
/** takes a write lock in the constructor, releases it in the destructor */
class CCAFEWriteLock {
private:
  CCAFEReadWriteMutex* rw_mut;
public:

  CCAFEWriteLock( CCAFEReadWriteMutex* rw_mut_ ) {
    rw_mut = rw_mut_;
    rw_mut->writeLock();
  }

  ~CCAFEWriteLock() {
    rw_mut->unlock();
  }
};

/** 
    A semaphore class, useful for synchronization. Semaphores are counters
    which can be incremented and decremented, but can never go below zero. If a
    thread tries to decrement the semaphore and the current value is zero, the 
    thread will block until someone else increments the semaphore. Useful when 
    you want a little more precision than conditions and mutexes can provide.
*/
class CCAFESemaphore {
private:
  sem_t sem_id;
public:
  /** the semaphore starts with a value of 0 */
  CCAFESemaphore(){
    sem_init(&sem_id, 0 /* not shared between processes*/, 0 /*initial value*/);
  }

  ~CCAFESemaphore(){
    sem_destroy(&sem_id);
  }

  /** block until the semaphore's value is above zero, then decrement and
      continue. Always returns 0 (see sem_wait) */
  int wait() {
    return sem_wait(&sem_id);
  }

  /** non-blocking check of the semaphore value (see sem_trywait) */
  int tryWait() {
    return sem_trywait(&sem_id);
  }

  /** increments the semaphore value (see sem_post). non-blocking */
  int post() {
    return sem_post(&sem_id);
  }
};

class CCAFEQueueLock;

class CCAFEThreadSafeQueue {
private:
  jcpp::Vector* list; // the list object used to implement the queue
  CCAFECondition condition;
  CCAFEMutex mutex;
  boolean amShutdown;

 protected:
  friend class CCAFEQueueLock;
  /** if an external class needs to freeze the queue for a short period,
      this method allows them to lock it. Nothing will be added or removed 
      from the queue while the lock is held, so it should only be taken for
      short, non-blocking periods */
  void lockQueue() {
    mutex.lock();
  };

  /** the inverse of lockQueue */
  void unlockQueue() {
    mutex.unlock();
  };

public:
  CCAFEThreadSafeQueue(jcpp::Vector* newList) { list = newList; amShutdown = FALSE;};
  
  // BUGBUG do we "own" the vector? the items in the vector?
  ~CCAFEThreadSafeQueue() {};
  
  /** adds an element and wakes up any threads which were waiting to do
      a remove. */
  void addLast(jcpp::Object* elem) {
    CCAFEMutexLock lock(&mutex);
    list->add(elem);
    condition.signal();
  };

  /** This is a blocking operation - if there is nothing in the queue 
      it will wait for another element to be added and take that */
  jcpp::Object* blockRemoveFirst() {
    CCAFEMutexLock lock(&mutex);
    while (((list->size()) <1) && (!amShutdown)) {
      // wait releases the mutex so that another thread can come
      // in and fill the list
      condition.wait(&mutex);
    }
    return list->remove(0);
  };

  /** This is the non-blocking version of remove - if there is nothing
      in the queue, it immediately returns a null pointer */
  jcpp::Object* nonblockRemoveFirst() {
    CCAFEMutexLock lock(&mutex);
    if (list->size() < 1)
      return NULL;
    else
      return list->remove(0);
  };

  /** non-blocking */
  boolean remove(jcpp::Object* elem) {
    CCAFEMutexLock lock(&mutex);
    return list->removeElement(elem); 
  };

  int size() {
    CCAFEMutexLock lock(&mutex);
    return list->size();
  };
  
  void ensureCapacity(int cap) {
    CCAFEMutexLock lock(&mutex);
    list->ensureCapacity(cap);
  };
  
  jcpp::Object* elementAt(int index) {
    CCAFEMutexLock lock(&mutex);
    return list->elementAt(index);
    
  };
  
  /** Does not destroy the elements - use only if this list doesn't "own"
      the elements it points to. */
  void removeAllElements() {
    CCAFEMutexLock lock(&mutex);
    list->removeAllElements();
  };
  
  boolean contains(jcpp::Object* obj) {
    CCAFEMutexLock lock(&mutex);
    return list->contains(obj);
  }

  /** kicks out any threads waiting on the queue */
  void shutdown()
  {
    CCAFEMutexLock lock(&mutex);
    amShutdown = TRUE;
    condition.broadcast();
  }
};




class CCAFEQueueLock {
 private:
  CCAFEThreadSafeQueue* queue;
 public:

  CCAFEQueueLock(CCAFEThreadSafeQueue* queue_) {
    queue = queue_;
    queue->lockQueue();
  }

  ~CCAFEQueueLock() {
    queue->unlockQueue();
  };
};






class CCAFEThreadPool;


/** Odd properties of thread pool threads:
    The real "thread" actually loops, waiting for a signal from start(), then
    calling Thread::run(), rather than starting a separate thread each time 
    start is called.
 
    join() returns when a single iteration of the loop is done (ie, when run() 
    returns). joinFinal() returns when the thread is finished, which can only 
    happen after a call to stop and after the last run() has exited. stop and
    joinFinal should really only be used by the thread pool itself.
*/
class CCAFEThreadPoolThread : public CCAFEThread {
private:
  CCAFEThreadPool* pool;
  CCAFESemaphore done;
  CCAFESemaphore start_requested;
  boolean shutdown;
  void* returnValue;

protected:
  friend class CCAFEThreadPool;
  void initialize();
  void stop();
  void* joinFinal();

public:

  CCAFEThreadPoolThread(CCAFEThreadPool* newPool) 
  { pool = newPool; shutdown = FALSE; };
  /** remove self from the pool - BUGBUG - delete return value? */

  ~CCAFEThreadPoolThread(); 

  /** run the runnable, then return to the thread pool and wait for start
      to be called again (on the semaphore "start"). */
  void* run(); 

  /** signal the semaphore "start" so that run() goes through another loop */
  int start();

  /** wait for the semaphore "done", which will be set by run() after it
      finishes a loop */
  void* join();
};

/** A Thread pool */
class CCAFEThreadPool {
private:
  jcpp::Vector vec1;
  jcpp::Vector vec2;
  CCAFEThreadSafeQueue availableQueue;
  CCAFEThreadSafeQueue runningQueue; // neccessary for shutdown
  CCAFEMutex mutex; // must be very careful not to deadlock with the 
  // queues.
  CCAFECondition cond;
  int maxSize;

protected:
  friend class CCAFEThreadPoolThread;

  // may destroy the thread if there are max Size threads in the pool already
  void queueThread(CCAFEThread* thread);

  void removeThread(CCAFEThread* thread);

public:
  CCAFEThreadPool(int size) :availableQueue(&vec1), runningQueue(&vec2)
  { 
    maxSize = size;
  };

  CCAFEThread* dequeueThread(); 

  void setSize(int size); // the maximum # of threads this pool will hand out. 

  void shutdown(); // kill all threads in the pool

};

#endif // thread.h seen
#else
extern int ccafe_no_jcpp_util_Thread;
#endif // CCAFE_THREADS 
