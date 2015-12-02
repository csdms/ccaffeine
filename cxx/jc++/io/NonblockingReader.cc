#ifndef lint
static char id[]="$Id: NonblockingReader.cc,v 1.8 2003/05/15 20:52:28 baallan Exp $"; // RCS string
#endif

#include <sys/time.h>
#ifdef __linux
//#include <error.h>
//#include <errno.h>
#endif
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "jc++/jc++.h"
#include "jc++/lang/jc++lang.h"
#include "jc++/util/jc++util.h"
#include "util/IO.h"
#include "Reader.h"
#include "NonblockingReader.h"

/** Move the start of the heap down to the start of the
      buffer. Actually doesn't compact anything, just kind of tamps it
      down.*/
void jcpp::NonblockingReader::compactBuffer() {
  if(nextChar == 0) return;
  memcpy(tmp, cb + nextChar, nChars - nextChar);
  memcpy(cb, tmp, nChars - nextChar);
  nChars = nChars - nextChar;
  nextChar = 0;
}

/** Fill buffer without blocking, returns TRUE if fill completed,
      returns FALSE if fill was truncated because it would block.  */
boolean jcpp::NonblockingReader::fillNonblocking() {
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
void jcpp::NonblockingReader::expandBufferMemory() {
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

jcpp::NonblockingReader::NonblockingReader(Reader* in_) {
  in = in_;
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
jcpp::NonblockingReader::~NonblockingReader() {
  if(cb) {
    free(cb);
  }
  if(tmp) {
    free(tmp);
  }
  in->close();
  delete in;
}
/** Read a single character off the stream. */
int jcpp::NonblockingReader::read() {
  if(nextChar >= nChars) {
    fillNonblocking();
    if(nextChar >= nChars) {
      return -1;
    }
  }
  return cb[nextChar++];
}

/** This reads a blob of characters, but does not necessarily
      fulfill the request. A negative return value means an error, EOF
      or block has occurred.*/
int jcpp::NonblockingReader::preRead(char* cbuf, int off, int length) {
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

/** Does the same as read(char* cbuf, int off, int length), but
      never blocks. */
int jcpp::NonblockingReader::nonblockingRead(char* cbuf, int off, int length) {
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

/** Read <em length /em> bytes into the buffer pointed to by <em
      cbuf /em> beginning at the offset <em off /em>. Returns the
      number of characters actually read or -1 if there is an error. */
int jcpp::NonblockingReader::read(char* cbuf, int off, int length) {
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

/** Skip length bytes or to end-of-file whichever comes first. */
long jcpp::NonblockingReader::skip(long length) {
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
CFREE char* jcpp::NonblockingReader::readLine() {
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

int jcpp::NonblockingReader::findLineInBuffer() {
  for(int i = nextChar;i < nChars;i++) {
    if(cb[i] == '\n') {
      return i;
    }
  }
  return -1;
}
