#ifndef __XFGETS_H__
#define __XFGETS_H__

#include <sys/time.h>
#include <error.h>
#include <sys/types.h>
#include <unistd.h>
#include "jc++/jc++.h"
#include "util/IO.h"

extern int errno;

/** A knockoff of the Reader class in java.io. */
class Reader {
public:
  /** Close the underlying file descriptor. */
  virtual void close()=0;
  /** Mark this point in the read stream. */
  virtual void mark() {
    en("not allowed to use mark() in Reader");
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
    en(":-( Reader::reset() not supported");
  }
  /** Skip length bytes or to end-of-file whichever comes first. */
  virtual long skip(long length)=0;
 protected:
  void en(char* str) {
    fprintf(stderr, "%s\n", str);
  }
};

class StdReader : Reader {

private:
  int numFDs;
  fd_set set;
  int fd;
  int debug;

public:
  StdReader(int fd) {
    debug = FALSE;
    numFDs = 1;
    this->fd = fd;
  }
  virtual void close(){
    ::close(fd);
  }
  int read() {
    if(debug) {
      en("about to read 1 char\n");
    }
    char c;
    int ret = ::read(fd, &c, 1);
    if(debug) {
      en("done.");
    }
    return ret == 1 ? (int)c : -1;
  }
  int read(char* cbuf, int off, int length) {
    int ret = ::read(fd, cbuf+off, length);
    return ret;
  }
  virtual boolean ready(){
    struct timeval tv = {0, 0};
    FD_ZERO(&set);
    FD_SET(fd, &set);
    int ret = ::select(1, &set, 0, 0, &tv);
    if(debug) {
      fprintf(stderr, "select returns %d\n", ret);
    }
    if(ret == 1) {
      return TRUE;
    } else if(ret == -1) { // error condition
      char* err = strerror(errno);
      int len = strlen(err) + 512;
      char str[len];
      memset(str, 0, len);
      strcat(str, "StdReader::ready:");
      strcat(str, err);
      en(str);
    } else if(ret == 0) { // nothing available
      return FALSE;
    } else {
      // can't happen, but might anyway ...
      en("Unknown error in StdReader::ready:");
      return FALSE;
    }
    return FALSE; // never reached.
  }
  virtual long skip(long length) {
    long times = length/1024L;
    int rmdr = length%1024L;
    char* buf = (char*)malloc(1024);
    for(long i = 0;i < times;i++) {
      ::read(fd, buf, 1024);
    }
    ::read(fd, buf, rmdr);
    free(buf);
    return length;
  }
};


// class LineNumberReader {
//  private:

//   CDELETE Reader* in;
//   long lineNumber;

//  public:

//   LineNumberReader(CDELETE Reader* in) {
//     this->in = in;
//   }
//   virtual ~LineNumberReader(){
//     delete in;
//   }
//   virtual int getLineNumber() {
//     return lineNumber;
//   }
//   virtual void mark() {
//     return in->mark();
//   }
//   virtual int read() {
//     return in->read();
//   }
//   virtual boolean markSupported() {
//     return in->markSupported();
//   }
//   virtual void close() {
//     in->close();
//   }
//   virtual CFREE char* readLine() {
//     if(lineOnStack) {
//       lineOnStack = FALSE;
//       return line;
//     }
//     int incrStrSize = 1024;
//     int maxStrSize = incrStrSize;
//     char *str = (char*)malloc(incrStrSize);
//     int size = 0;
//     while(1) {
//       char c = (char)in->read();
//       if(c == '\n') break;
//       str[size++] = c;
//       if(size >= maxStrSize) {
// 	str = addCharMemory(str, &maxStrSize, incrStrSize);
//       }
//     }
//       str[size] = '\0';
//       return str;
//   }
//   void reset() {
//     in->reset();
//   }
//   virtual void setLineNumber(int lineNumber) {
//     this->lineNumber = lineNumber;
//   }
//   virtual long skip(long n) {
//     return in->skip(n);
//   }
//  private:
//   char* addCharMemory(char* str, int* maxSize, int incrSiz) {
//     int newMaxSize = *maxSize + incrSiz;
//     char* retStr = (char*)malloc(newMaxSize);
//     memset(retStr, 0, newMaxSize);
//     memcpy(retStr, str, *maxSize);
//     *maxSize = newMaxSize;
//     free(str);
//     return retStr;
//   }

// };



// /** This is a class to do nonblocking reads on a file descriptor.*/
// class NonblockingIO : public Reader {

// private:

//   int numFDs = 1;
//   fd_set set;
//   int fd;


// public:

//   NonBlockingIO(int fd) {
//     this->fd = fd;
//     FD_ZERO(&set);
//     FD_SET(fd, &set);
//   }


//   void tryRead() {
//     struct timeval tv = {0, 0};

//     if(select(1, &set, 0, 0, &tv)) {
//       int ret = read(fd,);
//     }



//   }

// };

#endif // __XFGETS_H__
