#ifdef CCAFE_THREADS /* not built without threads. */

#include <boost/shared_ptr.hpp>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include <pthread.h>
#include "GoThread.hh"

/**
 * This class enables a "go" command that is wrapped in its own thread.
 */

int 
GoThread::create_thread(ccafeopq::GoPort * port) {
  state->goPort = port;
  void * vs = (void*)state;
  IO_dn2("ccafe_forked_thread = 0x%x",ccafe_forked_thread);
  IO_dn2("pthread_create = 0x%x",pthread_create);
  int rc = pthread_create(&id, NULL, ccafe_forked_thread, vs);
  if(rc) {
    IO_en1(":-( could not create go command in its own thread");
    perror("create_thread:");
    return -1;
  }
  return 0;
}

pthread_t 
GoThread::getThreadID() {
  return id;
}

bool 
GoThread::isRunning() {
  return state->running;
}
GoThread::~GoThread(){
  delete state;
}
GoThread::GoThread() {
  state = new GoThreadState();
  id = 0;
}
GoThreadState::GoThreadState() {
    goPort = NULL;
    return_code = 0;
    running = false;
  }

extern "C" {

  void * ccafe_forked_thread(void * args) {
    IO_dn1("ccafe_forked_thread entry ...");

    GoThreadState * ts = (GoThreadState*)args;
    IO_dn2("args = 0x%x",args);
    if(!ts) {
      IO::en("Arguments to ccafe_forked_thread null: this can't happen");
      return NULL;
    }
    ts->running = true;
    ccafeopq::GoPort * goPort = ts->goPort;
    ts->return_code = goPort->go();
    ts->running = false;
    return (void*)NULL;
  }
} // extern "C"
#else
int ccafe_no_GoThread_support=1;
#endif //  CCAFE_THREADS
