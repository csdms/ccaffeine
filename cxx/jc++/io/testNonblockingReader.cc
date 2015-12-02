#include <sys/time.h>
#ifdef __linux
//#include <error.h>
//#include <errno.h>
#endif
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "util/IO.h"
#include "Reader.h"
#include "StdReader.h"
#include "NonblockingReader.h"
#include <string.h>

static void doSpinner() {
  static char toggle = -1;
  toggle++;
  toggle = toggle % 4;
  switch(toggle) {
  case 0:
    ::fprintf(stderr, "-");
    ::fflush(stderr);
    break;
  case 1:
    ::fprintf(stderr, "\\");
    ::fflush(stderr);
    break;
  case 2:
    ::fprintf(stderr, "|");
    ::fflush(stderr);
    break;
  case 3:
    ::fprintf(stderr, "/");
    ::fflush(stderr);
    break;
   }
  ::usleep(10000L);
  ::fprintf(stderr, "\b");
  ::fflush(stderr);
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  jcpp::Reader* rdr = (jcpp::Reader*)new jcpp::StdReader(0 /** stdin */);
  jcpp::NonblockingReader* br = new jcpp::NonblockingReader(rdr);
  int c;
  ::fprintf(stderr, "Single char reading test, type x to go on\n");
  while(1) {
    if((c = br->read()) != -1) {
      ::fprintf(stderr,"Single character read:%c\n",  (unsigned char)c);
      if(c == 'x') {
	break;
      }
    } else { // failed to get anything
      doSpinner();
    }
  }
#define BLEN 10
  int len = BLEN;
  int off = 0;
  char buf[BLEN];
  ::fprintf(stderr, "Buffer reading test, type a bonch of x\'s to go on\n");
  while(1) {
    int n;
    if((n = br->read(buf, off, len)) > 0) {
      ::fprintf(stderr, "Buffer of length %d:", n);
      for(int i = off;i < n + off;i++) {
	::fprintf(stderr, "%c", buf[i]);
      }
      ::fprintf(stderr, "\n");
      if(buf[0] == 'x') {
	break;
      }
    } else { // failed to get anything
      doSpinner();
    }
  }
  char* line;
  while(1) {
    if((line = br->readLine()) != 0) {
      ::fprintf(stderr, "Here is a line of length %d:", strlen(line));
      ::fprintf(stderr, "%s\n", line);
      free(line);
    } else { // failed to get anything
      doSpinner();
    }
  }
}
