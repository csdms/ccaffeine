/**
 *  Version: $Revision: 1.6 $
 *  Version control file: $RCSfile: GenericHashTable.cc,v $
 *  Date last modified: $Date: 2003/09/08 19:38:23 $
 *  Last modified by: $Author: baallan $
*/
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/lang/HashKey.h"
#include "jc++/util/Enumeration.h"
#include "jc++/util/HashEnum.h"
#include "jc++/util/GenericHashEnum.h"
#include "jc++/util/GenericHashBucket.h"
#include "jc++/util/StringHashBucket.h"
#include "jc++/util/ResourceBucket.h"
#include "jc++/util/GenericHashTable.h"
#include "jc++/util/StringBuffer.h"
#include "util/IO.h"
#ifndef lint
static char id[]="$Id: GenericHashTable.cc,v 1.6 2003/09/08 19:38:23 baallan Exp $"; // RCS string
#endif

#include "util/freefree.h"

const long jcpp::GenericHashTable::magic = 1103515245;

int jcpp::GenericHashTable::calculateBucket(HashKey * key) {
  int ret = ((key->hashValue() >> ttmNm2) & twoNm1);
  assert(ret < table_length);
  return ret;
}


// done
jcpp::GenericHashTable::GenericHashTable() {
  N = 8; // all N must be even
  table_length = 1<<N; //fprintf(stderr,"hashlen %d\n",table_length);
  ttmNm2 = table_length -1;
  twoNm1 = 32 - N - 2;
  loadFactor = 0.75;
  rehashLimit = (int)(loadFactor * (float)table_length);
  numberOfKeys = 0;
  okeys = NULL;
  oelements = NULL;
  CFREE table = (GenericHashBucket **)malloc(sizeof(GenericHashBucket *)*table_length);
  for (int i = 0; i < table_length; i++) {
    table[i] = NULL;
  }
}

// done
jcpp::GenericHashTable::~GenericHashTable() {

  clear();
  free(table);
  table = NULL;

  N = -1;
  table_length = -1;
  ttmNm2 = -1;
  twoNm1 = -1;
  loadFactor = -1;
  rehashLimit = -1;
  okeys = NULL;
  oelements = NULL;
  numberOfKeys = 0;

}
     
  
// done
int jcpp::GenericHashTable::size() {
  return (numberOfKeys);
}
  
// done
boolean jcpp::GenericHashTable::isEmpty() {
  return (numberOfKeys == 0);
}
  
// done
/** must call delete on this pointer when you are done with it. */
jcpp::Enumeration *jcpp::GenericHashTable::keys() {

  GenericHashBucket *b;
  Enumeration *e;
  int keyNum = 0;

  okeys = (HashKey **)malloc(sizeof(HashKey *)*numberOfKeys);

  for (int pos = table_length-1; pos >= 0; pos--) {
    b = table[pos];
    while (b != NULL) {
      okeys[keyNum++] = b->key();
      b = b->next();
    }
  }

  e = new GenericHashEnum(okeys,keyNum);
  okeys = NULL;
  return e;

}

// done
jcpp::Enumeration *jcpp::GenericHashTable::elements() {

  GenericHashBucket *b;
  HashEnum *e;
  int keyNum = 0;

  oelements = (Object **)malloc(sizeof(Object *)*numberOfKeys);

  for (int pos = table_length-1; pos >= 0; pos--) {
    b = table[pos];
    while (b != NULL) {
      oelements[keyNum++] = b->element();
      b = b->next();
    }
  }

  e = new HashEnum(oelements,keyNum);
  oelements = NULL;
  return e;

}
  
// done
boolean jcpp::GenericHashTable::contains(Object * value) {

  GenericHashBucket *b;

  for (int pos = table_length-1; pos >= 0; pos--) {
    b = table[pos];
    while (b != NULL) {
      if (b->element() == value) {
        return (true);
      }
      b = b->next();
    }
  }
  return false;
}

// done
boolean jcpp::GenericHashTable::containsKey(HashKey * key) {
  return (get(key) != null);
}

CFREE char **jcpp::GenericHashTable::charKeysToArray(int& ka_length) {
  static char *x[1];
  x[0]=NULL;
  ka_length=0;
  IO::en("NotStringHashErrJC");
  return x; 
}

// done
jcpp::Object * jcpp::GenericHashTable::get(HashKey * key) {
  GenericHashBucket *b;
  int posn = calculateBucket(key);
  b = table[posn];
  while (b != NULL) {
    if (b->key()->equals(key)) {
      return b->element();
    }
    b = b->next();
  }
  return (null);
}
  
//done 

jcpp::Object * jcpp::GenericHashTable::put(HashKey * key, Object * value) { 

  GenericHashBucket *b;
  Object * element = NULL;

  if (key==NULL||value==NULL) {
    IO::en("NullPointerErrJC");
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
    if (b->key() == key) {
      element = b->element();
      b->setValue(value);
      return element;
    }
    b = b->next();
  }

  b = new GenericHashBucket(key,value);
  b->setNext(table[posn]);
  table[posn] = b;
  numberOfKeys++;
  return NULL;
}
  
//done
jcpp::Object * jcpp::GenericHashTable::remove(HashKey * key) {

  if (key==NULL) {
    return NULL; 
  }

  int posn = calculateBucket(key);
  GenericHashBucket *last;
  GenericHashBucket *b = table[posn];

  // search for key
  last = NULL;
  while (b!=NULL && b->key() != key) {
    last = b;
    b = b->next();
  }

  if (b != NULL) {
    // remove from table
    if (last != NULL) {
      last->setNext(b->next());
    } else {
      table[posn] = b->next();
    }
    numberOfKeys--;

    // return value.
    Object * val;
    val = b->element();
    b->setValue(NULL);
    delete b;
    return val;
  }

  return (null);

}
  
void jcpp::GenericHashTable::clear() {

  GenericHashBucket *b;
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
  
  
char *jcpp::GenericHashTable::toString() {

  StringBuffer *result = new StringBuffer();
  GenericHashBucket *b;
  char *ret;
  char buf[100];
  int did1 = 0;
  Object * p;
  HashKey *kp;

  result->append((char *)"{",1);
  for (int pos=0; pos < table_length; pos++) {
    b = table[pos];
    while (b != NULL) {
      if (did1) {
        result->append((char *)", ",2);
      } else {
        did1 = 1;
      }
      kp = b->key();
      p = b->element();
      sprintf(buf,"key_0x%p=(HashKey *)",kp);
      result->append(buf);
      result->append(p);
      b = b->next();
    }
  }
  result->append((char *)"}",1);

  ret = result->toString();
  delete result;
  return ret;
}

boolean jcpp::GenericHashTable::containsValue(Object * o) {
  return (contains(o));
}

void jcpp::GenericHashTable::rehash(int & err) {

  GenericHashBucket *b;
  GenericHashBucket **oldtable;
  int oldlen, oldkeys, newpos;

  if (N==28) { return;} // damn big, no more resizing 

  oldtable = table;
  oldlen = table_length;
  oldkeys = numberOfKeys;

  // update hashing info
  N = N+2; // all N must be even
  table_length = 1 << N;
  CFREE table = (GenericHashBucket **)malloc(sizeof(GenericHashBucket *)*table_length);
  ttmNm2 = table_length -1;
  twoNm1 = 32 - N - 2;
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

  err = 0;
  if (numberOfKeys != oldkeys) {
    IO::en("rehash error");
    err = -1;
    return;
  }

  free(oldtable);
}


