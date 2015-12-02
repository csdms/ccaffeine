#include "BufferedReader.h"
#include <string.h>

int main(int argc, char** argv) {
  Reader* rdr = (Reader*)new StdReader(0 /** stdin */);
  BufferedReader* br = new BufferedReader(rdr);
  int c;
  fprintf(stderr, "Single char reading test, type x to go on\n");
  while(1) {
    if((c = br->read()) != -1) {
      fprintf(stderr,"Single character read:%c\n",  (unsigned char)c);
      if(c == 'x') {
	break;
      }
    }
  }
  int len = 10;
  int off = 0;
  char buf[len];
  fprintf(stderr, "Buffer reading test, type a bonch of x\'s to go on\n");
  while(1) {
    int n;
    if((n = br->read(buf, off, len)) > 0) {
      fprintf(stderr, "Buffer of length %d:", n);
      for(int i = off;i < n + off;i++) {
	fprintf(stderr, "%c", buf[i]);
      }
      fprintf(stderr, "\n");
      if(buf[0] == 'x') {
	break;
      }
    }
  }
  char* line;
  while(1) {
    if((line = br->readLine()) != 0) {
      fprintf(stderr, "Here is a line of length %d:", strlen(line));
      fprintf(stderr, "%s\n", line);
      free(line);
    }
  }
}
