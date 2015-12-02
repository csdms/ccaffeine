#ifndef __STDREADER_H__
#define __STDREADER_H__

// Depends on:
/* #include <sys/time.h> */
/* //#include <error.h> */
/* #include <sys/types.h> */
/* #include <unistd.h> */
/* #include "jc++/jc++.h" */
/* #include "util/IO.h" */

// from <errno.h>, without all the extra goop.
//extern int errno;

namespace jcpp {

/** Creates a Reader based on a file descriptor. */
class StdReader : public Reader {

private:
  int numFDs;
  fd_set set;
  int fd;
  int debug;

public:
  /** Takes a file descriptor argument, fd. */
  StdReader(int fd);
  virtual void close();
  virtual int read();
  virtual int read(char* cbuf, int off, int length);
  virtual int read(char* cbuf, int length) {
    return read(cbuf, 0 , length);
  }
  virtual boolean ready();
  virtual long skip(long length);
};

} ENDSEMI // jcpp


#endif // __STDREADER_H__
