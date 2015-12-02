#ifndef __READER_H__
#define __READER_H__

namespace jcpp {

// Depends on:
/* #include <sys/types.h> */
/* #include <unistd.h> */
/* #include "jc++/jc++.h" */
/* #include "util/IO.h" */


/** A knockoff of the Reader class in java.io, this is just an
    interface, StdReader takes a file descriptor and makes it a
    Reader. */
class Reader {
public:
  /** Close the underlying file descriptor. */
  virtual void close()=0;
  /** Mark this point in the read stream. */
  virtual void mark() {
    en((char *)"not allowed to use mark() in Reader");
  }
  /** Determine if this stream supports marking the stream. */
  virtual boolean markSupported() {
    return FALSE;
  }
  /** Read a single character off the stream. */
  virtual int read()=0;
  /** Read length bytes into the buffer pointed to by cbuf. */
  virtual int read(char* cbuf, int length) {
    return read(cbuf, 0 , length);
  }
  /** Read <em length /em> bytes into the buffer pointed to by <em
      cbuf /em> beginning at the offset <em off /em>. */
  virtual int read(char* cbuf, int off, int length)=0;
  /** Answers TRUE if the stream is ready to be read. */
  virtual boolean ready()=0;
  /** Reset the stream back to the previously set mark, if supported,
      error otherwise. */
  virtual void reset() {
    en((char *)":-( Reader::reset() not supported");
  }
  /** Skip length bytes or to end-of-file whichever comes first. */
  virtual long skip(long length)=0;
 protected:
  void en(char* str) {
    ::fprintf(stderr, "%s\n", str);
  }
};

} ENDSEMI //jcpp



#endif // __READER_H__
