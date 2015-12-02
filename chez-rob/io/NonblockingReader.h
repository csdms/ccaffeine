#ifndef __NONBLOCKINGREADER_H__
#define __NONBLOCKINGREADER_H__

#include <sys/time.h>
#include <error.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "util/IO.h"
#include "Reader.h"

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
  void compactBuffer() {
    if(nextChar == 0) return;
    memcpy(tmp, cb + nextChar, nChars - nextChar);
    memcpy(cb, tmp, nChars - nextChar);
    nChars = nChars - nextChar;
    nextChar = 0;
  }
  /** Fill buffer without blocking, returns TRUE if fill completed,
      returns FALSE if fill was truncated because it would block.  */
  boolean fillNonblocking() {
    compactBuffer();
    while(in->ready()) {
      if(nChars >= maxChars) {
	return TRUE;
      }
      char c;
      if((c = (char)in->read()) >= 0) {
	cb[nChars++] = c;
      }
    }
    return FALSE;
  }
  /** Add some more memory to the buffer.  There is a chance that we
      may have an enormous buffer if we have an enormous line that we
      are reading in. */
  void expandBufferMemory() {
    int newMaxChars = maxChars + incrChars;
    char* nBuf = (char*)malloc(newMaxChars);
    assert(nBuf);
    memset(nBuf, 0, newMaxChars);
    memcpy(nBuf, cb, maxChars);
    free(cb);
    free(tmp);
    tmp = (char*)malloc(newMaxChars);
    assert(tmp);
    cb = nBuf;
    maxChars = newMaxChars;
  }

 public:

  NonblockingReader(Reader* in) {
    this->in = in;
    defaultCharBufferSize = 8192;
    defaultExpectedLineLength = 80;
    maxChars = defaultCharBufferSize;
    incrChars = defaultCharBufferSize;
    nChars = 0;
    nextChar = 0;
    cb = (char*)malloc(maxChars);
    assert(cb);
    tmp = (char*)malloc(maxChars);
    assert(tmp);
  }
  virtual ~NonblockingReader(){
    if(cb) {
      free(cb);
    }
    if(tmp) {
      free(tmp);
    }
    in->close();
    delete in;
  }
  /** Close the underlying file descriptor. */
  virtual void close() {
    in->close();
  }
  /** Mark this point in the read stream. */
  virtual void mark() {
    en("not allowed to use mark() in Reader");
  }
  /** Determine if this stream supports marking the stream. */
  virtual boolean markSupported() {
    return FALSE;
  }
  /** Read a single character off the stream. */
  virtual int read() {
    if(nextChar >= nChars) {
      fillNonblocking();
      if(nextChar >= nChars) {
	return -1;
      }
    }
    return cb[nextChar++];
  }
  /** Read length bytes into the buffer pointed to by cbuf. */
  virtual int read(char* cbuf, int length) {
    return read(cbuf, 0 , length);
  }
 private:
  /** This reads a blob of characters, but does not necessarily
      fulfill the request. A negative return value means an error, EOF
      or block has occurred.*/
  int preRead(char* cbuf, int off, int length) {
    if(nextChar >= nChars) { 
      // The buffer is fully drained.  We might as well read directly
      // from the stream and bypass the buffer.
      return nonblockingRead(cbuf, off, length);
    }
    if(length > (nChars - nextChar)) {
      memcpy(cbuf + off, cb + nextChar, nChars - nextChar);
      nextChar = nChars;
      return nChars - nextChar;
    } else {
      memcpy(cbuf + off, cb + nextChar, length);
      nextChar += length;
      return length;
    }
  }
  int nonblockingRead(char* cbuf, int off, int length) {
    int n = 0;
    char* buf = cbuf + off;
    while(in->ready()) {
      buf[n++] = (char)in->read();
      if(n >= length) {
	break;
      }
    }
    return n;
  }
 public:

  /** Read <em length /em> bytes into the buffer pointed to by <em
      cbuf /em> beginning at the offset <em off /em>. Returns the
      number of characters actually read or -1 if there is an error. */
  virtual int read(char* cbuf, int off, int length) {
    boolean check = (off < 0) || (length < 0) || ((off + length) < 0);
    if(check) {
      return -1;
    }
    int n = preRead(cbuf, off, length);
    if(n <= 0) {
      return n;
    }
    while(n < length) {
      int len = preRead(cbuf, off + n, length - n);
      if(len <= 0) {
	break;
      }
      n += len;
    }
    return n;
  }
  /** Answers TRUE if the stream is ready to be read. */
  virtual boolean ready() {
    return (nextChar < nChars) || in->ready();
  }
  /** Reset the stream back to the previously set mark, if supported,
      error otherwise. */
  virtual void reset() {
    en(":-( Reader::reset() not supported");
  }
  /** Skip length bytes or to end-of-file whichever comes first. */
  virtual long skip(long length) {
    if(length <= 0) {
      return 0;
    }
    long rmndr = length;
    while(rmndr > 0) {
      if(nextChar >= nChars) {
	fillNonblocking();
      }
      if(nextChar >= nChars) { //EOF or error or block
	break;
      }
      long chg = nChars - nextChar;
      if(rmndr <= chg) {
	nextChar += rmndr;
	rmndr = 0;
	break;
      } else {
	rmndr -= chg;
	nextChar = nChars;
      }
    }
    return length - rmndr;
  }

  /** Read a line, the terminating newline is replaced with a null,
      returning 0 if it would block or the line if it is
      available. */
  virtual CFREE char* readLine() {
    StringBuffer* sb = new StringBuffer(defaultExpectedLineLength);
    int newLine = 0;
    do {
      if((newLine = findLineInBuffer()) >= 0) { // found a newLine
	cb[newLine] = '\0';
	sb->append(cb, nextChar, newLine - nextChar);
	nextChar = newLine + 1;
	char* retVal = sb->toString();
	delete sb;
	return retVal;
      } else { // no newLine yet ...
	expandBufferMemory();
      }
    } while(fillNonblocking());
    // Fell through because we would block.  But let's see if we got a
    // line with whatever filling did occur.
    if((newLine = findLineInBuffer()) >= 0) { // found a newLine
      cb[newLine] = '\0';
      sb->append(cb, nextChar, newLine - nextChar);
      nextChar = newLine + 1;
      char* retVal = sb->toString();
      delete sb;
      return retVal;
    }    
    // Nope didn't get a line this time.
    delete sb;
    return 0;
  }

 private:

  int findLineInBuffer() {
    for(int i = nextChar;i < nChars;i++) {
      if(cb[i] == '\n') {
	return i;
      }
    }
    return -1;
  }

 public:
};



#endif // __NONBLOCKINGREADER_H__
