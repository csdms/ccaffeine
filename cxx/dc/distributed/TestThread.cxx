#include <stdio.h>
#include <errno.h>
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/Enumeration.h"
#include "jc++/util/VectEnum.h"
#include "jc++/util/ResourceBucket.h"
#include "jc++/util/StringHashBucket.h"
#include "jc++/util/Vector.h"
#include "jc++/util/StringBuffer.h"

#include "jc++/util/Thread.h"
int count;

class TestThread : public CCAFEThread {
private:
    CCAFEMutex* mutex;
    CCAFECondition* condition;
    int i;
  void cleanup_func(void* args) {
    printf("thread in cleanup function\n");
    TestThread* thread = (TestThread*) args;
    //    thread->condition->signal();
    mutex->unlock();
  }
public:
    
  TestThread (CCAFEMutex* newMutex, CCAFECondition* cond, int num) { i= num; mutex = newMutex; condition = cond; };
  virtual void* run() {
    { // scope for the lock
      CCAFEMutexLock lock(mutex);
      { // scope for the lock2
	CCAFEMutexLock lock2(mutex); // just making sure we can nest locks
	count++;
      } // end scope lock 2
      while (count < 10) {
	printf("thread %i waiting\n", i);
	int error = 0;
	pthread_cleanup_push(&cleanup_func, this);
	error = condition->wait(mutex);
	pthread_cleanup_pop(0);
	if (error == EINTR) {
	  printf("thread %i interrupted\n", i);
	  return NULL;
	}
	printf("thread %i looping\n", i);
      }
    } // end scope for the lock
    for (int j = 0; j < (10-i); j++) 
      {
	printf("this is test thread # %i\n", i);
      }
    { // scope for the lock
      CCAFEMutexLock lock(mutex);
      printf("signalling next thread %i\n", i);
      condition->broadcast();
    } // end scope for the lock
  };
};

class QueueElement : public virtual JCPN(Object), public CCAFERunnable {
private:
    int id;
public:
    QueueElement(int i) { id = i; };
    void print( int threadId ) 
    {
	printf(" Element %i printed by thread %i\n", id, threadId); 
    }
    void* run() {
	printf( " Element %i printed by itself\n", id );
    }
};
class ConsumerThread : public virtual CCAFEThread {
private:
    CCAFEThreadSafeQueue* queue;
    int id;
public:
    ConsumerThread (CCAFEThreadSafeQueue* newQueue, int i) {
	queue = newQueue;
	id = i;
    };
    void* run() {
	QueueElement* elem = dynamic_cast<QueueElement*> (queue->blockRemoveFirst());
	elem->print(id);
	return NULL;
    }
};

class ControllerThread : public virtual CCAFEThread {
private:
    CCAFEThreadPool pool;
    CCAFEThreadSafeQueue* queue;
public:
    ControllerThread(CCAFEThreadSafeQueue* newQueue) :pool(10) 
    { queue = newQueue; };
    void* run() {
	for (int i = 0; i < 10; i++) {
	    QueueElement* elem = dynamic_cast<QueueElement*> (queue->blockRemoveFirst());
	    CCAFEThread* thread = pool.dequeueThread();
	    thread->setRunnable(elem);
	    thread->start();
	}
	//	pool.join();
    }
};
void poolTest() {
    JCPN(Vector) vec;
    CCAFEThreadSafeQueue queue(&vec);
    ControllerThread looper(&queue);
    looper.start();
    for (int i = 0; i < 10; i++) {
	fprintf(stdout, "queued element %i\n", i);
	queue.addLast(new QueueElement(i));
    }
    looper.join();
};

void queueTest() {
    JCPN(Vector) vec;
    CCAFEThreadSafeQueue queue(&vec);
    CCAFEThread* threads[10];
  for (int i =0; i <10; i++) {
    fprintf(stdout, "created thread %i\n", i);
    threads[i] = new ConsumerThread(&queue, i);
    threads[i]->start();
  }
  for (int i = 0; i < 10; i++) {
      fprintf(stdout, "queued element %i\n", i);
      queue.addLast(new QueueElement(i));
  }
  for (int i =0; i <10; i++) {
    void * retValue = threads[i]->join();
    fprintf(stdout, "thread %i returned value %x \n", i, retValue);
    delete threads[i];
  }

};

void testLock(CCAFEReadWriteMutex* mutex) {
  CCAFEWriteLock lock(mutex);
  throw("test");
}

void basicTest() {
  CCAFEMutex mutex;
  CCAFECondition cond;
  fprintf(stdout, "this is the main program\n");
  TestThread* threads[10];
  count = 0;
  for (int i =0; i <10; i++) {
    fprintf(stdout, "created thread %i\n", i);
    threads[i] = new TestThread(&mutex, &cond, i);
    threads[i]->start();
  }
  for (int i =0; i <10; i++) {
    fprintf(stdout, "interrupting thread %i \n", i);
    int error = threads[i]->interrupt();
    if (error)
      printf("Could not interrupt thread b/c: %x", i);
  }
  for (int i =0; i <10; i++) {
    void * retValue = threads[i]->join();
    fprintf(stdout, "thread %i returned value %x \n", i, retValue);
    if (retValue != PTHREAD_CANCELED)
      fprintf(stdout, "unexpected return value\n");
    delete threads[i];
  }

};
int main () {

  basicTest();

  CCAFEReadWriteMutex mutex;
  try {
    testLock(&mutex);
  } catch (...) {
    printf("trying lock\n");
    CCAFEWriteLock lock(&mutex);
    printf("lock was released\n");
  }
};
