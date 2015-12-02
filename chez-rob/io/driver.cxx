#include <stdio.h>

int main(int argc, char** argv) {
  while(1) {
    printf("this is a line\n");
    fflush(stdout);
    sleep(10);
  }
}
