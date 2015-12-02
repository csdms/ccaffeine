/**
 *  Version: $Revision: 1.12 $
 *  Version control file: $RCSfile: ResourceHash.cc,v $
 *  Date last modified: $Date: 2002/12/19 20:21:07 $
 *  Last modified by: $Author: baallan $
*/

#include "jc++/jc++.h"
#include "jc++/util/JString.h"
#include "jc++/lang/Object.h"
#include "jc++/util/Enumeration.h"
#include "jc++/util/StringEnumeration.h"
#include "jc++/util/HashEnum.h"
#include "jc++/util/StringHashEnum.h"
#include "jc++/util/StringHashBucket.h"
#include "jc++/util/ResourceBucket.h"
#include "jc++/util/ResourceHash.h"
#include "jc++/util/StringHash.h"
#include "jc++/util/StringBuffer.h"
#include "util/IO.h"


//#include "jc++/util/Enum.h"

#ifndef lint
static char id[]="$Id: ResourceHash.cc,v 1.12 2002/12/19 20:21:07 baallan Exp $"; // RCS string
#endif


#include "util/freefree.h"


static const int __jcpp_num_primes = 25;
static const unsigned long __jcpp_prime_list[__jcpp_num_primes] =
{
  53,         97,         193,       389,       769,
  1543,       3079,       6151,      12289,     24593,
  49157,      98317,      196613,    393241,    786433,
  1572869,    3145739,    6291469,   12582917,  25165843,
  50331653,   100663319,  201326611, 402653189, 805306457
};

int jcpp::ResourceHash::calculateBucket(register const char *str) {
  register const char *p;
  register unsigned long h=0,g;
  for(p = str; *p != '\0'; p++) {
    h = (h << 4) + (*p);
    if ((g = h&0xf0000000)) {
      h = h ^ (g >> 24);
      h = h ^ g;
    }
  }
  return h % table_length;
}

jcpp::ResourceHash::ResourceHash() {
  N = 0;
  table_length = __jcpp_prime_list[N];

  CFREE table =  (ResourceBucket **)::malloc(sizeof(ResourceBucket *)*table_length);
  for (int i = 0; i < table_length; i++) {
    table[i] = NULL;
  }

  loadFactor = 0.75;
  numberOfKeys = 0;
  rehashLimit = (int)(loadFactor * (float)table_length);
  oelements = NULL;
  okeys = NULL;
}

jcpp::ResourceHash::ResourceHash(char* filePath) {
  N = 0;
  table_length = __jcpp_prime_list[N];

  CFREE table =  (ResourceBucket **)::malloc(sizeof(ResourceBucket *)*table_length);
  for (int i = 0; i < table_length; i++) {
    table[i] = NULL;
  }

  loadFactor = 0.75;
  numberOfKeys = 0;
  rehashLimit = (int)(loadFactor * (float)table_length);
  oelements = NULL;
  okeys = NULL;

  int buflen = BUFSIZ;
  // open file and parse the key/value pairs
  FILE* fp = ::fopen(filePath, "r");
  if(fp == 0) {
    IO::pn("could not open file: %s", filePath);
    return;
  }
  CFREE char* buf = (char*)::malloc(buflen);
  if(::fgets(buf, buflen, fp) == NULL) {
    return;
  }
  do {
    char* key = strtok(buf, "\n \t\0");
    char* val = strtok(NULL, "\n \t\0");
    if(val == NULL) {
      IO::en("IO::getResource: format error in %s", filePath);
      return;
    }
    put(key, val);
  } while(::fgets(buf, buflen, fp) != NULL);
  ::free(buf);
  ::fclose(fp);
  return;
}

  
jcpp::ResourceHash::~ResourceHash() {

  clear();
  ::free(table);
  table = NULL;

  N = -1;
  table_length = -1;
  loadFactor = -1;
  rehashLimit = -1;
  okeys = NULL;
  oelements = NULL;
  numberOfKeys = 0;

}

int jcpp::ResourceHash::size() {
  return (numberOfKeys);
}
  
boolean jcpp::ResourceHash::isEmpty() {
  return (numberOfKeys == 0);
}
  
/// keys will be enumerated as (String *), needing casting from Object.
jcpp::StringEnumeration *jcpp::ResourceHash::keys() {

  ResourceBucket *b;
  StringHashEnum *e;
  int keyNum = 0;

  CFREE okeys = (char **)::malloc(sizeof(char *)*(numberOfKeys+1));

  for (int pos = table_length-1; pos >= 0; pos--) {
    b = table[pos];
    while (b != NULL) {
      okeys[keyNum++] = (b->key());
      b = b->next();
    }
  }

  okeys[numberOfKeys] = 0;
  e = new StringHashEnum(okeys,keyNum);
  okeys = NULL;
  return e;

}
  
jcpp::StringEnumeration *jcpp::ResourceHash::elements() {

  ResourceBucket *b;
  StringHashEnum *e;
  int keyNum = 0;
  char *s;

  oelements = (char **)::malloc(sizeof(char *)*numberOfKeys);

  for (int pos = table_length-1; pos >= 0; pos--) {
    b = table[pos];
    while (b != NULL) {
      s = b->element();
      oelements[keyNum++] = s;
      b = b->next();
    }
  }

  e = new StringHashEnum(oelements,keyNum);
  oelements = NULL;
  return e;

}
  
boolean jcpp::ResourceHash::contains(char * value) {

  ResourceBucket *b;
  char *s;

  for (int pos = table_length-1; pos >= 0; pos--) {
    b = table[pos];
    while (b != NULL) {
      s = b->element();
      if ((s == value || strcmp(s,value)==0) ) {
        return (true);
      }
      b = b->next();
    }
  }
  return false;

}
  
boolean jcpp::ResourceHash::containsKey(char *key) {
  return (get(key) != null);
}

CFREE char **jcpp::ResourceHash::charKeysToArray(int& ka_length) {

  ResourceBucket *b;
  char **result = (char **)::malloc((1+numberOfKeys)*sizeof(char *));

  // extract char * from all strings to an argv.
  result[numberOfKeys] = NULL;
  ka_length = 0;
  for (int pos=0; pos < table_length; pos++) {
    b = table[pos];
    while (b != NULL) {
      result[ka_length]= b->key();
      ka_length++;
      b = b->next();
    }
  }
  assert(ka_length == numberOfKeys);

  return result;
}

char * jcpp::ResourceHash::get(char *key) {

  ResourceBucket *b;

  int posn = calculateBucket(key);
  b = table[posn];
  while (b != NULL) {
    if (b->key() == key /* a miracle */ || strcmp(key,b->key()) == 0) {
      return b->element();
    }
    b = b->next();
  }

  return (NULL);

}
  

char * jcpp::ResourceHash::put(const char *key, const char * value) {

  ResourceBucket *b;
  char * element = NULL;

  if (key == NULL || value == NULL || strlen(key) == 0) {
    IO::en("NullPointerErrJC in ResourceHash::put");
    return 0;
  }

  if (numberOfKeys >= rehashLimit) {
    int err;
    rehash(err);
    if (err) { return 0; }
  }

  int posn = calculateBucket(key);
  b = table[posn];

  while ( b != NULL ) {
    if (b->key() == key /* a miracle */ || strcmp(key,b->key()) == 0) {
      element = b->element();
      b->setValue((char*)value);
      return element;
    }
    b = b->next();
  }

  // we make the key so we can delete it later
  b = new ResourceBucket((char*)key,(char*)value);
  b->setNext(table[posn]);
  table[posn] = b;
  numberOfKeys++;
  return NULL;

}
  
char * jcpp::ResourceHash::remove(char *key) {

  if (key==NULL || strlen(key) == 0) {
    return NULL; 
  }

  int posn = calculateBucket(key);
  ResourceBucket *last;
  ResourceBucket *b = table[posn];

  // search for key
  last = NULL;
  while (b!=NULL && strcmp(key,b->key()) != 0) {
    last = b;
    b = b->next();
  }

  if (b != NULL) {
    char * val;
    val = b->element();

    // remove from table
    if (last != NULL) {
      last->setNext(b->next());
    } else {
      table[posn] = b->next();
    }
    numberOfKeys--;

    // return value.
    b->setValue(NULL);
    delete b->key();
    delete b;
    return val;
  }

  return (NULL);

}
  
void jcpp::ResourceHash::clear() {

  ResourceBucket *b;

  for (int pos = table_length-1; pos >= 0; pos--) {
    b = table[pos];
    while (b != NULL) {
      table[pos] = b->next();
      delete b;
      b = table[pos];
    }
  }

  numberOfKeys = 0;

}
  
// could be prettier.
CFREE char *jcpp::ResourceHash::toString() {

  CDELETE StringBuffer *result = new StringBuffer();
  ResourceBucket *b;
  char *ret;
  int did1 = 0;
  char * p;

  result ->append((char *) "{",1);
  for (int pos=0; pos < table_length; pos++) {
    b = table[pos];
    while (b != NULL) {
      if (did1) {
        result->append((char *)", ",2);
      } else {
        did1 = 1;
      }
      result->append(b->key());
      p = b->element();
      result->append((char *)"{",1);
      result->append(p);
      result->append((char *)"}",1);
      b = b->next();
    }
  }
  result->append((char *)"}",1);

  ret = result->toString();
  delete result;
  return ret;
}


boolean jcpp::ResourceHash::containsValue(char *s) {
  return (contains(s));
}

void jcpp::ResourceHash::rehash(int & RehashError)
{

  ResourceBucket *b;
  ResourceBucket **oldtable;
  int oldlen, oldkeys, newpos;

  if (N == __jcpp_num_primes) { return;} // damn big, no more resizing 

  oldtable = table;
  oldlen = table_length;
  oldkeys = numberOfKeys;

  // update hashing info
  N++;
  table_length = __jcpp_prime_list[N];
  CFREE table = (ResourceBucket **)::malloc(sizeof(ResourceBucket *)*table_length);
  rehashLimit = (int)(loadFactor * (float)table_length);
  numberOfKeys = 0;
  /* Go through adding all the data to the new data */
  for (int pos = 0; pos < oldlen; pos++) {
    while (oldtable[pos] != NULL) {
      b = oldtable[pos];
      oldtable[pos] = b->next();
      newpos = calculateBucket(b->key());
      b->setNext(table[newpos]);
      table[newpos] = b;
      numberOfKeys++;
    }
  }

  RehashError = 0;
  if (numberOfKeys != oldkeys) {
    RehashError = -1;
    return;
  }

  ::free( oldtable);

}
