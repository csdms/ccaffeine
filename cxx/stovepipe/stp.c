#include <stdlib.h>
#include <stdio.h>
#include "stp.h"
#include <glib.h>
#include <string.h>

static GHashTable*
stp_table = 0;

static int
chkptr(void* ptr, char* prefix0, char* prefix1) {
  if(!ptr) {
    fprintf(stderr, ":-( %s%s: NULL pointer\n", prefix0, prefix1);
    return FALSE;
  }
  return TRUE;
}

/** Initialize stovepipe with command line arguments. */
void
stp_init(int argc, char** argv) {
  int i = 0;

#ifdef STPDEBUG
  printf("stp_init:");
  for (i=0; i < argc; i++) {
    printf("%s ",argv[i]);
  }
  printf("\n");
#endif
  stp_table = g_hash_table_new(g_str_hash, g_str_equal);
  for(i = 0;i < argc;i++) {
    chkptr(argv[i], "stp_init(int argc, char** argv):", __FILE__);
    if((strlen(argv[i]) < 2) || (argv[i][0] != '-') || (argv[i][1] != '-')) {
      continue;
    }
    // got a hit
    if(strlen(argv[i]+2) == 0) { // `--' by itself = end of arg switch list.
break;
    }
    char* argName = strdup(argv[i]+2);
    char* argValue = 0;
    if(argc == i + 1) { // last argument in the list.
      argValue = strdup("");
      g_hash_table_insert(stp_table, (char* const)argName, 
			  argValue);
      break;
    }
    chkptr(argv[i + 1], "stp_init(int argc, char** argv):", __FILE__);
    if((strlen(argv[i + 1]) < 2) || 
       (argv[i + 1][0] != '-') || 
       (argv[i + 1][1] != '-')) { 
      // we have an argument val

      argValue = strdup(argv[i+1]);
      i++;
    } else { // we have no argument value
      argValue = strdup("");
    }
    g_hash_table_insert(stp_table, argName, 
			argValue);
  }
}

/** Return the value keyed to the commandline argument name, or return
    NULL if no such argument was given.  Note that if the argumentName
    was given without a value an empty string will be returned. */
const char* 
stp_get(const char* argName) {
  if(!argName) {
    fprintf(stderr, "stp_get(char* argName): %s: "
	    "argName is NULL, what's up with that?", __FILE__);
    return NULL;
  }
  if(!stp_table) {
    fprintf(stderr, "stp_get(char* argName): %s: "
	    "stp_get called before initializaion."
	    " You must call stp_init() first.\n", __FILE__);
    return NULL;
  }
  return g_hash_table_lookup(stp_table, (gconstpointer)argName);
}


/** By convention, namespaces for arguments are designated with a
    selected prefix in front of the argument name separated by a dash.
    For example: myprog --myNamespace-myArgName argValue.  stp_getn is
    a convenience function that enforces that convention.  This call
    is equivalent to stp_get(strcat(strcat(namespace, "-"),argName)). */
const char* 
stp_getn(const char* namespace, const char* argName) {
  static int stp_bufsiz = STP_BUFSIZ;
  static char* buf = 0;
  if(buf == 0) { // first time
    buf = (char*)malloc(stp_bufsiz*sizeof(char*)); // I know it is 1
	// there seems to be some confusion here as to type to malloc.
    if(!buf) {
      perror("stp_getn:");
      return NULL;
    }
  }
  int memAllocated = 0;
  int size = strlen(namespace) + strlen(argName) + 2;
  char* key = buf;
  if(stp_bufsiz > size) {
    key = (char*)malloc(size*sizeof(char)); // I know its 1
    if(key == 0) {
      perror("stp_getn");
      return 0;
    }
    memAllocated = 1;
  }
  key[0] = '\0';
  key = strcat(key, namespace);
  key = strcat(key, "-");
  key = strcat(key, argName);
  const char* retVal = stp_get(key);
  if(memAllocated) {
    free(key);
  }
  return retVal;
}

static gboolean 
stp_freeElem(gpointer key, gpointer val, gpointer data) {
  chkptr(key, "stp_freeElem: ", __FILE__);
  free((char*)key);
  chkptr(val, "stp_freeElem: ", __FILE__);
  free((char*)val);
  return TRUE;
}


/** Stovepipe will no longer be needed. Calling on any stp function
    after this except stp_init will cause problems. */
void 
stp_shutdown() {
  if(!stp_table) {
    fprintf(stderr, "stp_shutdown(): %s: attempt to shutdown "
	    "uninitialized stovepipe system", __FILE__);
    return;
  }
  g_hash_table_foreach_remove(stp_table, stp_freeElem, NULL);  
  g_free(stp_table);
}
