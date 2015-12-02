#ifndef lint
static char id[]="$Id: StdReader.cc,v 1.9 2003/06/26 17:30:40 rob Exp $"; // RCS string
#endif


#include <sys/time.h>
#ifdef __linux

/* See man 3 errno, in Linux */
#include <errno.h>
extern int errno;
#else
extern int errno;
#endif
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "jc++/jc++.h"
#include "util/IO.h"
#include "Reader.h"
#include "StdReader.h"

jcpp::StdReader::StdReader(int fd_) {
  debug = FALSE;
  numFDs = 1;
  fd = fd_;
}

void jcpp::StdReader::close() {
  ::close(fd);
}


int jcpp::StdReader::read() {
  if(debug) {
    en((char *)"about to read 1 char\n");
  }
  char c;
  int ret = ::read(fd, &c, 1);
  if(debug) {
    en((char *)"done.");
  }
  return ret == 1 ? (int)c : -1;
}

int jcpp::StdReader::read(char* cbuf, int off, int length) {
  int ret = ::read(fd, cbuf+off, length);
  return ret;
}

boolean jcpp::StdReader::ready() {
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
#if 0
    int len = strlen(err) + 512;
    char str[len];
    memset(str, 0, len);
    strcat(str, "jcpp::StdReader::ready:");
    strcat(str, err);
    en(str);
#else
    en((char *)"jcpp::StdReader::ready:(err)");
    en(err);
#endif
  } else if(ret == 0) { // nothing available
    return FALSE;
  } else {
    // can't happen, but might anyway ...
    en((char *)"Unknown error in jcpp::StdReader::ready:");
    return FALSE;
  }
  return FALSE; // never reached.
}

long jcpp::StdReader::skip(long length) {
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
