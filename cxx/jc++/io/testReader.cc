#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h> 
#include "jc++/jc++.h" 
#include "util/IO.h" 
#include "Reader.h"
#include "StdReader.h"

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  jcpp::Reader* rdr = (jcpp::Reader*)new jcpp::StdReader(0 /** stdin */);
  while(1) {
    if(rdr->ready()) {
      char c = (char)rdr->read();
      ::write(1, &c, 1); // put the char on stdout
    } else { // not ready
      ::printf("not ready.");
      ::sleep(5);
    }
  }
}

