#ifndef __NONBLOCKINGREADER_H__
#define __NONBLOCKINGREADER_H__

namespace jcpp {

// Depends on:
/* #include <sys/time.h> */
/* #include <error.h> */
/* #include <sys/types.h> */
/* #include <unistd.h> */
/* #include <assert.h> */
/* #include "jc++/jc++.h" */
/* #include "jc++/util/jc++util.h" */
/* #include "util/IO.h" */
/* #include "Reader.h" */

/** A class that has similar features to BufferedReader but never
    blocks on read, instead it will return a zero read indication or
    error, if it would have blocked. */
class NonblockingReader : public virtual Reader {
 private:

  CDELETE Reader* in;

  char* cb;
  char* tmp;
  int nChars; /// One past the last index of the last char in the buffer.
  int nextChar; /// The index of the first char in the buffer.
  int maxChars; /// The total size of the buffer, i.e. nChars <= maxChars.
  int incrChars; /// If the memory is to be increased, this is the increment.
  int defaultCharBufferSize;
  int defaultExpectedLineLength;

  /** Move the start of the heap down to the start of the
      buffer. Actually doesn't compact anything, just kind of tamps it
      down.*/
  void compactBuffer();
  /** Fill buffer without blocking, returns TRUE if fill completed,
      returns FALSE if fill was truncated because it would block.  */
  boolean fillNonblocking();
  /** Add some more memory to the buffer.  There is a chance that we
      may have an enormous buffer if we have an enormous line that we
      are reading in. */
  void expandBufferMemory();

 public:

  NonblockingReader(Reader* in);
  virtual ~NonblockingReader();
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
      fulfill the request. A negative return value means an error, EOF
      or block has occurred.*/
  int preRead(char* cbuf, int off, int length);
  /** Does the same as read(char* cbuf, int off, int length), but
      never blocks. */
  int nonblockingRead(char* cbuf, int off, int length);

 public:

  /** Read <em length /em> bytes into the buffer pointed to by <em
      cbuf /em> beginning at the offset <em off /em>. Returns the
      number of characters actually read or -1 if there is an error. */
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
  /** Read a line, the terminating newline is replaced with a null,
      returning 0 if it would block or the line if it is
      available. */
  virtual CFREE char* readLine();
 private:

  int findLineInBuffer();

};

} ENDSEMI // jcpp



#endif // __NONBLOCKINGREADER_H__
