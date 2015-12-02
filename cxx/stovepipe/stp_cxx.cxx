#include <stdlib.h>
#include <stdio.h>
#include "jc++/util/jc++util.h"
#include "jc++/util/StringHash.h"
using namespace jcpp;
#include "stp.h"
#include "StpMap.h"


extern "C" {

  static StpMap* stp_map;

  void 
  stp_init(int argc, char** argv) {
    stp_map = new StpMap();
// #define STPDEBUG
#ifdef STPDEBUG
	  int i;
  fflush(0);
  printf("stp_init (cxx version) argc=%d: ", argc);
  for (i=0; i < argc; i++) {
    printf("%s ",argv[i]);
  }
  printf("\n");
#endif
    stp_map->init(argc, argv);
  }

  /** Return the value keyed to the commandline argument name, or return
      NULL if no such argument was given.  Note that if the argumentName
      was given without a value an empty string will be returned. */
  const char* 
  stp_get(const char* argName) {
    if(!stp_map) {
      fprintf(stderr, ":-( stp_getn: stovepipe must call stp_init first\n");
      return NULL;
    }
#ifdef STPDEBUG
    const char * s = stp_map->get(argName);
    printf("stp_get( %s )",argName);
    if (s == 0) {
      printf(" returning 0\n");
    } else {
      printf(" returning %s\n", s);
    }
    return s;
#else
    return stp_map->get(argName);
#endif
  }


  /** By convention, namespaces for arguments are designated with a
      selected prefix in front of the argument name separated by a dash.
      For example: myprog --myNamespace-myArgName argValue.  stp_getn is
      a convenience function that enforces that convention.  This call
      is equivalent to stp_get(strcat(strcat(namespace, "-"),argName)). */
  const char* 
  stp_getn(const char* namespc, const char* argName) {
    if(!stp_map) {
      fprintf(stderr, ":-( stp_getn: stovepipe must call stp_init first\n");
      return NULL;
    }
    return stp_map->getn(namespc, argName);
  }

  /** Stovepipe will no longer be needed. Calling on any stp function
      after this except stp_init will cause problems. */
  void 
  stp_shutdown() {
    if(!stp_map) {
      delete stp_map;
    }
    stp_map = NULL;
  }

  /** Put a value into stovepipe. */
void
stp_put(const char* option, const char* value) {
  stp_map->put(option, value);
}


  /** Put a value into stovepipe with a namespace. */
void
stp_putn(const char* namespc, const char* option, const char* value) {
  stp_map->putn(namespc, option, value);
}

};
