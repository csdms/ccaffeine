#include <stdio.h>
#include "Reader.h"

int main(int argc, char** argv) {
  Reader* rdr = (Reader*)new StdReader(0 /** stdin */);
  while(1) {
    if(rdr->ready()) {
      char c = (char)rdr->read();
      write(1, &c, 1); // put the char on stdout
    } else { // not ready
      printf("not ready.");
      sleep(5);
    }
  }
}

