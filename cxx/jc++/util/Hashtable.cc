/**
 *  Version: $Revision: 1.8 $
 *  Version control file: $RCSfile: Hashtable.cc,v $
 *  Date last modified: $Date: 2003/09/08 19:38:23 $
 *  Last modified by: $Author: baallan $
*/
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/Enumeration.h"
#include "jc++/util/HashEnum.h"
#include "jc++/util/HashBucket.h"
#include "jc++/util/StringHashBucket.h"
#include "jc++/util/ResourceBucket.h"
#include "jc++/util/Hashtable.h"
#include "jc++/util/StringBuffer.h"
#include "util/IO.h"
#ifndef lint
static char id[]="$Id: Hashtable.cc,v 1.8 2003/09/08 19:38:23 baallan Exp $"; // RCS string
#endif


#include "util/freefree.h"

const long jcpp::Hashtable::magic = 1103515245;

int jcpp::Hashtable::calculateBucket(Object * key) {
  int ret = (((((long) (key))*magic) >> ttmNm2) & twoNm1);
  assert(ret < table_length);
  return ret;
}


// done
jcpp::Hashtable::Hashtable() {
  N = 8; // all N must be even
  table_length = 1<<N; //fprintf(stderr,"hashlen %d\n",table_length);
  ttmNm2 = table_length -1;
  twoNm1 = 32 - N - 2;
  loadFactor = 0.75;
  rehashLimit = (int)(loadFactor * (float)table_length);
  numberOfKeys = 0;
  okeys = NULL;
  oelements = NULL;
  CFREE table = (HashBucket **)::malloc(sizeof(HashBucket *)*table_length);
  for (int i = 0; i < table_length; i++) {
    table[i] = NULL;
  }
}

// done
jcpp::Hashtable::~Hashtable() {

  clear();
  ::free(table);
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
int jcpp::Hashtable::size() {
  return (numberOfKeys);
}
  
// done
boolean jcpp::Hashtable::isEmpty() {
  return (numberOfKeys == 0);
}
  
// done
/** must call delete on this pointer when you are done with it. */
jcpp::Enumeration *jcpp::Hashtable::keys() {

  HashBucket *b;
  HashEnum *e;
  int keyNum = 0;

  okeys = (Object **)::malloc(sizeof(Object *)*numberOfKeys);

  for (int pos = table_length-1; pos >= 0; pos--) {
    b = table[pos];
    while (b != NULL) {
      okeys[keyNum++] = b->key();
      b = b->next();
    }
  }

  e = new HashEnum(okeys,keyNum);
  okeys = NULL;
  return e;

}

// done
jcpp::Enumeration *jcpp::Hashtable::elements() {

  HashBucket *b;
  HashEnum *e;
  int keyNum = 0;

  okeys = (Object **)::malloc(sizeof(Object *)*numberOfKeys);

  for (int pos = table_length-1; pos >= 0; pos--) {
    b = table[pos];
    while (b != NULL) {
      okeys[keyNum++] = b->element();
      b = b->next();
    }
  }

  e = new HashEnum(okeys,keyNum);
  okeys = NULL;
  return e;

}
  
// done
boolean jcpp::Hashtable::contains(Object * value) {

  HashBucket *b;

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
boolean jcpp::Hashtable::containsKey(Object * key) {
  return (get(key) != null);
}

CFREE char **jcpp::Hashtable::charKeysToArray(int& ka_length) {
  static char *x[1];
  x[0]=NULL;
  ka_length=0;
  IO::en("NotStringHashErrJC");
  return x; 
}

// done
jcpp::Object * jcpp::Hashtable::get(Object * key) {
  HashBucket *b;
  int posn = calculateBucket(key);
  b = table[posn];
  while (b != NULL) {
    if (b->key() == key) {
      return b->element();
    }
    b = b->next();
  }
  return (null);
}
  
//done

jcpp::Object * jcpp::Hashtable::put(Object * key, Object * value) { 

  HashBucket *b;
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

  b = new HashBucket(key,value);
  b->setNext(table[posn]);
  table[posn] = b;
  numberOfKeys++;
  return NULL;
}
  
//done
jcpp::Object * jcpp::Hashtable::remove(Object * key) {

  if (key==NULL) {
    return NULL; 
  }

  int posn = calculateBucket(key);
  HashBucket *last;
  HashBucket *b = table[posn];

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
  
void jcpp::Hashtable::clear() {

  HashBucket *b;
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
  
  
char *jcpp::Hashtable::toString() {

  StringBuffer *result = new StringBuffer();
  HashBucket *b;
  char *ret;
  char buf[100];
  int did1 = 0;
  Object * p, *kp;

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
      sprintf(buf,"key_0x%p=(Object *)",kp);
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

boolean jcpp::Hashtable::containsValue(Object * o) {
  return (contains(o));
}

void jcpp::Hashtable::rehash(int & err) {

  HashBucket *b;
  HashBucket **oldtable;
  int oldlen, oldkeys, newpos;

  if (N==28) { return;} // damn big, no more resizing 

  oldtable = table;
  oldlen = table_length;
  oldkeys = numberOfKeys;

  // update hashing info
  N = N+2; // all N must be even
  table_length = 1 << N;
  CFREE table = (HashBucket **)::malloc(sizeof(HashBucket *)*table_length);
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

  ::free(oldtable);
}


