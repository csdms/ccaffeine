#include <stdio.h>
#include "jc++/util/jc++util.h"
using namespace jcpp;
#include "StpMap.h"

int 
StpMap::chkptr(void* ptr, char* prefix0, char* prefix1) {
  if(!ptr) {
    fprintf(stderr, ":-( %s%s: NULL pointer\n", prefix0, prefix1);
    return false;
  }
  return true;
}

void
StpMap::init(int argc, char** argv) {
  for(int i = 0;i < argc;i++) {
    chkptr(argv[i], "stp_init(int argc, char** argv):", __FILE__);
    if((strlen(argv[i]) < 2) || 
       (argv[i][0] != '-') || 
       (argv[i][1] != '-')) {
      continue;
    }
    // got a hit
    if(strlen(argv[i]+2) == 0) { //`--' by itself = end of arg switch list.
      break;
    }
    char* argName = argv[i] + 2;
    char* argValue;
    if(argc == i + 1) { // last argument in the list.
      argValue = "";
      hash->put(argName, new AString(argValue));
      break;
    }
    chkptr(argv[i + 1], "stp_init(int argc, char** argv):", __FILE__);
    if((strlen(argv[i + 1]) < 2) || 
       (argv[i + 1][0] != '-') ||
       (argv[i][1] != '-')       ) { 
      // we have an argument val

      argValue = argv[i+1];
      i++;
    } else { // we have no argument value
      argValue = "";
    }
    char* val = argValue;
    hash->put(argName, new AString(val));
  }

}

void 
StpMap::insert(const char* key, const char* value) {
 hash->put(key, new AString(value));
}

const char* 
StpMap::get(const char* key) {
  if(!key) {
    fprintf(stderr, "stp_get(char* argName): %s: "
	    "argName is NULL, what's up with that?", __FILE__);
    return NULL;
  }
  AString* retVal = dynamic_cast<AString*>(hash->get(key));
  if(retVal != NULL) {
    return retVal->str;
  } else {
    return NULL;
  }
}

void
StpMap::put(const char* key, const char* value) {
  insert(key, value);
}

const char* 
StpMap::getn(const char* namespc, const char* key) {
  int testLen = strlen(namespc) + strlen(key) + 1 /* dash */ + 1 /* null */;
  char* test = (char*) malloc(testLen);
  memset(test, 0 , testLen);
  test = strcat(test, namespc);
  test = strcat(test, "-");
  test = strcat(test, key);
  const char* ret = get(test);
  free(test);
  return ret;
}

void
StpMap::putn(const char* namespc, const char* key, const char* value) {
  int testLen = strlen(namespc) + strlen(key) + 1 /* dash */ + 1 /* null */;
  char* test = (char*) malloc(testLen);
  memset(test, 0 , testLen);
  test = strcat(test, namespc);
  test = strcat(test, "-");
  test = strcat(test, key);
  insert(test, value);
  free(test);
}

void 
StpMap::remove(const char *key) {
  AString* s = dynamic_cast<AString*>(hash->remove(key));
  if(s == NULL) {
    return;
  } else {
    delete s;
    return;
  }
}
  

#ifdef CXXMAP_MAIN

#include <stdio.h>

int main() {
  StpMap st;
  st.insert((const char *)"rob",(const char *)"poobah");
  const char *s;
  s = st.get((const char *)"rob");
  fprintf(stdout, "rob = %s\n", s);
  st.remove((const char *)"rob");
  s = st.get((const char *)"rob");
  if (s != 0) {
    fprintf(stdout, "erase didn't work\n");
  } else {
    fprintf(stdout, "erase worked\n");
  }
}

#endif // CXXMAP_MAIN
