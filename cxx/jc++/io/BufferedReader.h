#ifndef __BUFFEREDREADER_H__
#define __BUFFEREDREADER_H__

// Depends on:
/* #include <sys/time.h> */
/* #include <error.h> */
/* #include <sys/types.h> */
/* #include <unistd.h> */
/* #include "jc++/jc++.h" */
/* #include "jc++/util/jc++util.h" */
/* #include "util/IO.h" */
/* #include "Reader.h" */

namespace jcpp {

/** A C++ knockoff of the BufferedReader class in package java.io.*/
class BufferedReader : public virtual Reader {
 private:
  CDELETE Reader* in;

  char* cb;
  long nChars; // last readable char + 1
  int nextChar; // index to the next readable char
  int maxChars; // size of the buffer cb
  long defaultCharBufferSize;
  long defaultExpectedLineLength;
  CDELETE StringBuffer* sb;
 public:
  BufferedReader(Reader* in);
  /** Close the underlying file descriptor. */
  virtual void close() {
    in->close();
  }
  /** Mark this point in the read stream. */
  virtual void mark() {
    en((char *)"not allowed to use mark() in Reader");
  }
  /** Determine if this stream supports marking the stream. */
  virtual boolean markSupported() {
    return FALSE;
  }
  /** Read a single character off the stream. */
  virtual int read();
  /** Read length bytes into the buffer pointed to by cbuf. */
  virtual int read(char* cbuf, int length) {
    return read(cbuf, 0 , length);
  }
 private:
  /** This reads a blob of characters, but does not necessarily
      fulfill the request. A negative return value means an error has
      occurred.*/
  int preRead(char* cbuf, int off, int length);
 public:

  /** Read <em length /em> bytes into the buffer pointed to by <em
      cbuf /em> beginning at the offset <em off /em>. */
  virtual int read(char* cbuf, int off, int length);
  /** Answers TRUE if the stream is ready to be read. */
  virtual boolean ready() {
    return (nextChar < nChars) || in->ready();
  }
  /** Reset the stream back to the previously set mark, if supported,
      error otherwise. */
  virtual void reset() {
    en((char *)":-( Reader::reset() not supported");
  }
  /** Skip length bytes or to end-of-file whichever comes first. */
  virtual long skip(long length);
  /** Read a line, the terminating newline is replaced with a null. */
  virtual CFREE char* readLine();
 private:
  /** See if a newline char appears in the current buffer, if so
      return the index pointing to the newline, otherwise retrun -1.*/
  int findLineInBuffer();
  /** Fill the buffer; note that this may block. */
  void fill();
 protected:
  /** Generic error stream. */
  void en(char* str) {
    ::fprintf(stderr, "%s\n", str);
  }

};

} ENDSEMI //jcpp


#endif // __BUFFEREDREADER_H__
