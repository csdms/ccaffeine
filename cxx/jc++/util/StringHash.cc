/**
 *  Version: $Revision: 1.12 $
 *  Version control file: $RCSfile: StringHash.cc,v $
 *  Date last modified: $Date: 2002/12/19 20:21:08 $
 *  Last modified by: $Author: baallan $
*/
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/JString.h"
#include "jc++/util/Enumeration.h"
#include "jc++/util/StringEnumeration.h"
#include "jc++/util/HashEnum.h"
#include "jc++/util/StringHashEnum.h"
#include "jc++/util/StringHashBucket.h"
#include "jc++/util/ResourceBucket.h"
#include "jc++/util/StringHash.h"
#include "jc++/util/StringBuffer.h"
#include "util/IO.h"

#ifndef lint
static char id[]="$Id: StringHash.cc,v 1.12 2002/12/19 20:21:08 baallan Exp $"; // RCS string
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

int jcpp::StringHash::calculateBucket(register const char *str) {
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

jcpp::StringHash::StringHash() {
  N = 1;
  table_length = __jcpp_prime_list[N];

  CFREE table =  (jcpp::StringHashBucket **)::malloc(sizeof(jcpp::StringHashBucket *)*table_length);
  for (int i = 0; i < table_length; i++) {
    table[i] = NULL;
  }

  loadFactor = 0.75;
  numberOfKeys = 0;
  rehashLimit = (int)(loadFactor * (float)table_length);
  oelements = NULL;
  okeys = NULL;
}
  
jcpp::StringHash::~StringHash() {

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

int jcpp::StringHash::size() {
  return (numberOfKeys);
}
  
boolean jcpp::StringHash::isEmpty() {
  return (numberOfKeys == 0);
}
  
/// keys will be enumerated as (String *), needing casting from Object.
jcpp::StringEnumeration *jcpp::StringHash::keys() {

  jcpp::StringHashBucket *b;
  jcpp::StringHashEnum *e;
  int keyNum = 0;

  CFREE okeys = (char **)::malloc(sizeof(char *)*(numberOfKeys+1));

  for (int pos = table_length-1; pos >= 0; pos--) {
    b = table[pos];
    while (b != NULL) {
      okeys[keyNum++] = b->key();
      b = b->next();
    }
  }

  okeys[numberOfKeys] = 0;
  e = new jcpp::StringHashEnum(okeys,keyNum);
  okeys = NULL;
  return e;

}
  
jcpp::Enumeration *jcpp::StringHash::elements() {

  jcpp::StringHashBucket *b;
  jcpp::HashEnum *e;
  int keyNum = 0;
  jcpp::Object *o;

  oelements = (jcpp::Object **)::malloc(sizeof(jcpp::Object *)*(numberOfKeys+1));

  for (int pos = table_length-1; pos >= 0; pos--) {
    b = table[pos];
    while (b != NULL) {
      o = b->element();
      if (o != NULL) {
        oelements[keyNum++] = o;
      }
      b = b->next();
    }
  }

  oelements[numberOfKeys] = 0;
  e = new jcpp::HashEnum(oelements,keyNum);
  oelements = NULL;
  return e;

}

boolean jcpp::StringHash::contains(jcpp::Object * value) {

  jcpp::StringHashBucket *b;
  jcpp::Object *ob;

  for (int pos = table_length-1; pos >= 0; pos--) {
    b = table[pos];
    while (b != NULL) {
      ob = b->element();
      if (ob == value ) {
        return (true);
      }
      b = b->next();
    }
  }
  return false;

}
  
boolean jcpp::StringHash::containsKey(char *key) {
  return (get(key) != null);
}

CFREE char **jcpp::StringHash::charKeysToArray(int& ka_length) {

  jcpp::StringHashBucket *b;
  char **result = (char **)::malloc((1+numberOfKeys)*sizeof(char *));

  // extract char * from all strings to an argv.
  result[numberOfKeys] = NULL;
  ka_length = 0;
  for (int pos=0; pos < table_length; pos++) {
    b = table[pos];
    while (b != NULL) {
      result[ka_length]= (char *)(b->key());
      ka_length++;
      b = b->next();
    }
  }
  assert(ka_length == numberOfKeys);

  return result;
}

// String literal flavor
jcpp::Object * jcpp::StringHash::get(const char *key) {

  jcpp::StringHashBucket *b;

  int posn = calculateBucket(key);
  b = table[posn];
  while (b != NULL) {
    if ((char *)b->key() == key /* a miracle */ || strcmp(key,(char *)b->key()) == 0) {
      return b->element();
    }
    b = b->next();
  }

  return (NULL);

}
// String literal flavor
jcpp::Object * jcpp::StringHash::get(const std::string skey) {

  const char * key = skey.c_str();
  jcpp::StringHashBucket *b;

  int posn = calculateBucket(key);
  b = table[posn];
  while (b != NULL) {
    if ((char *)b->key() == key /* a miracle */ || strcmp(key,(char *)b->key()) == 0) {
      return b->element();
    }
    b = b->next();
  }

  return (NULL);

}
// String literal flavor
CONST char * jcpp::StringHash::getKey(char *key) {

  jcpp::StringHashBucket *b;

  int posn = calculateBucket(key);
  b = table[posn];
  while (b != NULL) {
    if ((char *)b->key() == key /* a miracle */ || strcmp(key,(char *)b->key()) == 0) {
      return b->key();
    }
    b = b->next();
  }

  return (NULL);

}
  

jcpp::Object * jcpp::StringHash::put(const char *key, jcpp::Object * value)  {

  jcpp::StringHashBucket *b;
  jcpp::Object * element = NULL;

  if (key == NULL || value == NULL || strlen(key) == 0) {
    IO::en("NullPointerErrJC in StringHash::put");
    return 0;
  }

  if (numberOfKeys >= rehashLimit) {
    int err;
    rehash(err);
    if (err) {
      return 0;
    }
  }

  int posn = calculateBucket(key);
  b = table[posn];

  while ( b != NULL ) {
    if (b->key() == key /* a miracle */ || strcmp(key,b->key()) == 0) {
      element = b->element();
      b->setValue(value);
      return element;
    }
    b = b->next();
  }

  // we make the key so we can delete it later
  char *s = STRDUP(key);
  b = new jcpp::StringHashBucket(s,value);
  b->setNext(table[posn]);
  table[posn] = b;
  numberOfKeys++;
  return NULL;

}

jcpp::Object * jcpp::StringHash::put(const std::string skey, jcpp::Object * value)  {

  const char * key = skey.c_str();

  jcpp::StringHashBucket *b;
  jcpp::Object * element = NULL;

  if (key == NULL || value == NULL || strlen(key) == 0) {
    IO::en("NullPointerErrJC in StringHash::put");
    return 0;
  }

  if (numberOfKeys >= rehashLimit) {
    int err;
    rehash(err);
    if (err) {
      return 0;
    }
  }

  int posn = calculateBucket(key);
  b = table[posn];

  while ( b != NULL ) {
    if (b->key() == key /* a miracle */ || strcmp(key,b->key()) == 0) {
      element = b->element();
      b->setValue(value);
      return element;
    }
    b = b->next();
  }

  // we make the key so we can delete it later
  char *s = STRDUP(key);
  b = new jcpp::StringHashBucket(s,value);
  b->setNext(table[posn]);
  table[posn] = b;
  numberOfKeys++;
  return NULL;

}
  
//fixed
jcpp::Object * jcpp::StringHash::remove(const char *key) {

  if (key==NULL || strlen(key) == 0) {
    return NULL; 
  }

  int posn = calculateBucket(key);
  jcpp::StringHashBucket *last;
  jcpp::StringHashBucket *b = table[posn];

  // search for key
  last = NULL;
  while (b!=NULL && strcmp(key,b->key()) != 0) {
    last = b;
    b = b->next();
  }

  if (b != NULL) {
    jcpp::Object * val;
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

void jcpp::StringHash::clear() {

  jcpp::StringHashBucket *b;

  for (int pos = table_length-1; pos >= 0; pos--) {
    b = table[pos];
    while (b != NULL) {
      table[pos] = b->next();
      ::free(b->key());
      delete b;
      b = table[pos];
    }
  }

  numberOfKeys = 0;

}
  

// could be prettier.
CFREE char *jcpp::StringHash::toString() {

  CDELETE jcpp::StringBuffer *result = new jcpp::StringBuffer();
  jcpp::StringHashBucket *b;
  char *ret;
  int did1 = 0;
  jcpp::Object * p;

  result ->append((char *)"{",1);
  for (int pos=0; pos < table_length; pos++) {
    b = table[pos];
    while (b != NULL) {
      if (did1) {
        result->append((char *)", ",2);
      } else {
        did1 = 1;
      }
      result->append((char *)b->key());
      p = b->element();
      result->append((char *)"=(jcpp::Object *)",11);
      result->append(p);
      b = b->next();
    }
  }
  result->append((char *)"}",1);

  ret = result->toString();
  delete result;
  return ret;
}


boolean jcpp::StringHash::containsValue(jcpp::Object * o) {
  return (contains(o));
}


void jcpp::StringHash::rehash(int & RehashError)
{

  jcpp::StringHashBucket *b;
  jcpp::StringHashBucket **oldtable;
  int oldlen, oldkeys, newpos;

  if (N == __jcpp_num_primes) { return;} // damn big, no more resizing 

  oldtable = table;
  oldlen = table_length;
  oldkeys = numberOfKeys;

  // update hashing info
  N++;
  table_length = __jcpp_prime_list[N];
  CFREE table = (jcpp::StringHashBucket **)::malloc(sizeof(jcpp::StringHashBucket *)*table_length);
  rehashLimit = (int)(loadFactor * (float)table_length);
  numberOfKeys = 0;
  /* Go through adding all the data to the new data */
  for (int pos = 0; pos < oldlen; pos++) {
    while (oldtable[pos] != NULL) {
      b = oldtable[pos];
      oldtable[pos] = b->next();
      newpos = calculateBucket((char *)b->key());
      b->setNext(table[newpos]);
      table[newpos] = b;
      numberOfKeys++;
    }
  }

  RehashError = 0;
  if (numberOfKeys != oldkeys) {
    RehashError = -1;
    IO::en("rehash error StringHash");
    return;
  }

  ::free( oldtable);

}
