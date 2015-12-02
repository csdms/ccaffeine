#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cca.h>
#include "StringList.h"
#include "DefaultStringList.h"

int
DefaultStringList::allocate(long incr) {
  if(debug) {
    fprintf(stderr, "allocate called\n");
  }
  char** newList = (char**)malloc((sizeAllocated + incr)*sizeof(char*));
  memset(newList, 0, (sizeAllocated + incr)*sizeof(char*));
  if(newList == NULL) {
    fprintf(stderr, "DefaultStringList::allocate: :-( out of memory\n");
    return -1;
  }
  if(list != NULL) {
    memcpy(newList, list, sizeAllocated*sizeof(char*));
    free(list);
  }
  list = newList;
  sizeAllocated = sizeAllocated + incr;
  return 0;
}

DefaultStringList::DefaultStringList() {
  siz = 0;
  sizeAllocated = 0;
  sizeIncr = 1024;
  list = NULL;
  debug = false;
}
DefaultStringList::~DefaultStringList() {
  clear();
}
  

/** Fetch the requested string.  @param index input - a number from
      0 to this.getSize-1.  @return the value, or null if the index is
      out of range.  The returned string should be freed after use.  */
char* 
DefaultStringList::get(int index) {
  if(index < siz) {
    return list[index];
  } else {
    fprintf(stderr, "Bad index to DefaultStringList::get(int index) index = %d", index);
    return 0;
  }
}

void
DefaultStringList::dump() {
  for(int i = 0;i < siz;i++) {
    fprintf(stderr, "list[%d] = %s\n", i, list[i]);
  }
}


/** Get the current number of strings in this list.
      @return the list length.
   */
int 
DefaultStringList::getSize() {
  return siz;
}
 
int 
DefaultStringList::size() {
  return siz;
}
 
/** Add a string to the list, the container makes a copy of the
   string for its own purposes.  */
void 
DefaultStringList::append(char* s) {
  if(siz >= sizeAllocated) {
    if(allocate(sizeIncr) < 0) {
      fprintf(stderr, "DefaultStringList: could not allocat memory");
      return;
    }
  }
  list[siz++] = strdup(s);
  if(debug) {
    fprintf(stdout, "list[%d] = %s\n", siz - 1, list[siz - 1]);
  }
  return;
}

/** Forget all the data in the list. */
void 
DefaultStringList::clear() {
  for(int i = 0;i < siz; i++) {
    free(list[i]);
  }
  if(list != NULL) {
    free(list);
  }
  siz = 0;
}

