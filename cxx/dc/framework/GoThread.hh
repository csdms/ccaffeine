#ifdef CCAFE_THREADS /* bypass completely if not in threaded ccaffeine env */
#ifndef __GOTHREAD_HH__
#define __GOTHREAD_HH__

#include <pthread.h>

/**
 * This class enables a "go" command that is wrapped in its own thread.
 */


class GoThreadState {
 public:
  ccafeopq::GoPort * goPort;
  int return_code;
  bool running;

  GoThreadState();
  virtual ~GoThreadState(){}
};

class GoThread {
 private:
  GoThreadState * state;
  pthread_t id;
 public:
  int create_thread(ccafeopq::GoPort * port);
  pthread_t getThreadID();
  bool isRunning();

  GoThread();
  virtual ~GoThread();
};


extern "C" {

  void * ccafe_forked_thread(void * args);
}


typedef boost::shared_ptr< GoThread > GoThread_shared;


#endif // __GOTHREAD_HH__
#else
extern int ccafe_no_GoThread_support;
#endif //  CCAFE_THREADS
