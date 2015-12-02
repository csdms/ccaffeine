#include <stdio.h>
#include "stp.h"

int main(int argc, char** argv) {
  stp_init(argc, argv);
  fprintf(stdout, "--hello arg value = \"%s\", ", stp_get("hello"));
  fprintf(stdout, "--hello-world arg value = \"%s\"\n",
	  stp_get("hello-world"));
  fprintf(stdout, "namespace:hello,argName:world arg value =  \"%s\"\n",
	  stp_getn("hello", "world"));

  exit(0);
}
