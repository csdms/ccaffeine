#ifndef lint
static char id[]="$Id: BufferedReader.cc,v 1.6 2003/05/15 20:52:28 baallan Exp $"; // RCS string
#endif
#include <sys/time.h>
#ifdef __linux
//#include <error.h>
//#include <errno.h>
#endif
#include <sys/types.h>
#include <unistd.h>
#include "jc++/jc++.h"
#include "jc++/lang/jc++lang.h"
#include "jc++/util/jc++util.h"
#include "util/IO.h"
#include "Reader.h"
#include "BufferedReader.h"

jcpp::BufferedReader::BufferedReader(Reader* in_) {
  defaultCharBufferSize = 8192;
  defaultExpectedLineLength = 80;
  maxChars = nChars = defaultCharBufferSize;
  nextChar = nChars;
  cb = (char*) ::malloc(maxChars);
  in = in_;
  sb = new StringBuffer(defaultExpectedLineLength);
}

/** Read a single character off the stream. */
int jcpp::BufferedReader::read() {
  if(nextChar >= nChars) {
    fill();
    if(nextChar >= nChars) {
	return -1;
    }
  }
  return cb[nextChar++];
}

/** This reads a blob of characters, but does not necessarily
    fulfill the request. A negative return value means an error has
    occurred.*/
int jcpp::BufferedReader::preRead(char* cbuf, int off, int length) {
  if(nextChar >= nChars) { 
    // The buffer is fully drained.  We might as well read directly
    // from the stream and bypass the buffer.
    return in->read(cbuf, off, length);
  }
  if(length > (nChars - nextChar)) {
    ::memcpy(cbuf + off, cb + nextChar, nChars - nextChar);
    nextChar = nChars;
    return nChars - nextChar;
  } else {
    ::memcpy(cbuf + off, cb + nextChar, length);
    nextChar += length;
    return length;
  }
}

/** Read <em length /em> bytes into the buffer pointed to by <em
    cbuf /em> beginning at the offset <em off /em>. */
int jcpp::BufferedReader::read(char* cbuf, int off, int length) {
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

/** Skip length bytes or to end-of-file whichever comes first. */
long jcpp::BufferedReader::skip(long length) {
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
CFREE char* jcpp::BufferedReader::readLine() {
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
	sb = new StringBuffer(defaultExpectedLineLength);
	return retVal;
    } else { // did not find a newLine
	sb->append(cb, nextChar, nChars - nextChar);
	nextChar = nChars;
    }
  }
}

/** See if a newline char appears in the current buffer, if so
    return the index pointing to the newline, otherwise retrun -1.*/
int jcpp::BufferedReader::findLineInBuffer() {
  for(int i = nextChar;i < nChars;i++) {
    if(cb[i] == '\n') {
	return i;
    }
  }
  return -1;
}

/** Fill the buffer; note that this may block. */
void jcpp::BufferedReader::fill() {
  int n = 0;
  //    do {
    n = in->read(cb, 0, maxChars);
    //} while(n == 0);
  if(n > 0) {
    nChars = n;
    nextChar = 0;
  }
}
