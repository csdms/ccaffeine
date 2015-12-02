#ifndef __BUFFEREDREADER_H__
#define __BUFFEREDREADER_H__

#include <sys/time.h>
#include <error.h>
#include <sys/types.h>
#include <unistd.h>
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "util/IO.h"
#include "Reader.h"

class BufferedReader : public virtual Reader {
 private:
  CDELETE Reader* in;

  char* cb;
  long nChars; // last readable char + 1
  int nextChar; // index to the next readable char
  int maxChars; // size of the buffer cb
  long defaultCharBufferSize;
  long defaultExpectedLineLength;
 public:
  BufferedReader(Reader* in) {
    defaultCharBufferSize = 8192;
    defaultExpectedLineLength = 80;
    maxChars = nChars = defaultCharBufferSize;
    nextChar = nChars;
    cb = (char*) malloc(maxChars);
    this->in = in;
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
      fill();
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
      fulfill the request. A negative return value means an error has
      occurred.*/
  int preRead(char* cbuf, int off, int length) {
    if(nextChar >= nChars) { 
      // The buffer is fully drained.  We might as well read directly
      // from the stream and bypass the buffer.
      return in->read(cbuf, off, length);
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
 public:

  /** Read <em length /em> bytes into the buffer pointed to by <em
      cbuf /em> beginning at the offset <em off /em>. */
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
	return len;
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
    if(length < 0) {
      return 0;
    }
    long rmndr = length;
    while(rmndr > 0) {
      if(nextChar >= nChars) {
	fill();
      }
      if(nextChar >= nChars) { //EOF or error
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
  /** Read a line, the terminating newline is replaced with a null. */
  virtual CFREE char* readLine() {
    CDELETE StringBuffer* sb = new StringBuffer(defaultExpectedLineLength);
    while(1) {
      if(nextChar >= nChars) {
	fill();
      }
      if(nextChar >= nChars) { //EOF or Error
	return 0;
      }
      
      int newLine;
      if((newLine = findLineInBuffer()) >= 0) { // found a newLine
	cb[newLine] = '\0';
	sb->append(cb, nextChar, newLine - nextChar);
	nextChar = newLine + 1;
	char* retVal = sb->toString();
	delete sb;
	return retVal;
      } else { // did not find a newLine
	sb->append(cb, nextChar, nChars - nextChar);
	nextChar = nChars;
      }
    }
  }
 private:
  /** See if a newline char appears in the current buffer, if so
      return the index pointing to the newline, otherwise retrun -1.*/
  int findLineInBuffer() {
    for(int i = nextChar;i < nChars;i++) {
      if(cb[i] == '\n') {
	return i;
      }
    }
    return -1;
  }
  /** Fill the buffer; note that this may block. */
  void fill() {
    int n = 0;
    do {
      n = in->read(cb, 0, maxChars);
    } while(n == 0);
    if(n > 0) {
      nChars = n;
      nextChar = 0;
    }
  }
 protected:
  /** Generic error stream. */
  void en(char* str) {
    fprintf(stderr, "%s\n", str);
  }

};


#endif // __BUFFEREDREADER_H__
