/**
 *  Version: $Revision: 1.12 $
 *  Version control file: $RCSfile: Vector.cc,v $
 *  Date last modified: $Date: 2004/03/26 01:52:01 $
 *  Last modified by: $Author: baallan $
*/

#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/Enumeration.h"
#include "jc++/util/VectEnum.h"
#include "jc++/util/ResourceBucket.h"
#include "jc++/util/StringHashBucket.h"
#include "jc++/util/Vector.h"
#include "jc++/util/StringBuffer.h"


#ifdef _ODEBUG
#include "util/IO.h"
#endif

#ifndef lint
static char id[]="$Id: Vector.cc,v 1.12 2004/03/26 01:52:01 baallan Exp $"; // RCS string
#endif


#include "util/freefree.h"

const int jcpp::Vector::DEFAULTCAP = 10;


/** iterate delete over the list. */
void jcpp::ObjectIteratedDelete::doIt(Object *s) {
				  delete s;
}

/** only for use in Vector. could be inner maybe */
class Mosquito : public virtual jcpp::Object {
public:
  /** mosquito does not destroy any pointers it is handed. */
  Mosquito(char *s) { st = s; }
  ~Mosquito() { st = NULL; }
  char *st;
};

// done
void jcpp::Vector::increaseCapacity() {
  int newCapacity = elementData_length;
  int i;
  if (capacityIncrement > 0) {
    newCapacity += capacityIncrement;
  } else { 
    if (newCapacity == 0) {
      newCapacity = DEFAULTCAP;
    } else {
      newCapacity *= 2;
    }
  }

  CFREE jcpp::Object **oldBuffer = elementData;
  elementData = (jcpp::Object **)::malloc(sizeof(jcpp::Object *)*newCapacity);

  // copy
  for (i = 0; i < elementCount; i++) {
    elementData[i] = oldBuffer[i];
  }

  // init
  for (i = elementCount; i < newCapacity; i++) { elementData[i] = 0; }
  elementData_length = newCapacity;
  ::free(oldBuffer);
    
}


// done
jcpp::Vector::Vector() {

  elementData = (jcpp::Object **)::malloc(sizeof(jcpp::Object *)*DEFAULTCAP);
  elementData_length = DEFAULTCAP;
  elementCount = 0;
  capacityIncrement = 0;

}

// done
jcpp::Vector::Vector ( int initialCapacity ) {

  if (initialCapacity < 1) { initialCapacity = DEFAULTCAP; }
  elementData = (jcpp::Object **)::malloc(sizeof(jcpp::Object *)*initialCapacity);
  elementData_length = initialCapacity;
  elementCount = 0;
  capacityIncrement = 0;

}

// done
/** 0 increment indicates doubling on reallocation */
jcpp::Vector::Vector(int initialCapacity, int increment) {

  if (initialCapacity < 1) { initialCapacity = DEFAULTCAP; }
  if (increment < 0) { increment = 0; }
  elementData = (jcpp::Object **)::malloc(sizeof(jcpp::Object *)*initialCapacity);
  elementData_length = initialCapacity;
  elementCount = 0;
  capacityIncrement = increment;

}

// done
jcpp::Vector::~Vector() {
  for (int i = 0 ;  i < elementCount; i++ ) {
    Mosquito *m = dynamic_cast<Mosquito *>(elementData[i]);
    if (m != NULL) {
      delete m;
    }
  }
  ::free(elementData);
  elementData = NULL;
  elementCount = elementData_length = capacityIncrement = -1;
}

// done
 void jcpp::Vector::add(jcpp::Object * obj) {
	addElement(obj);
}

 void jcpp::Vector::addElement(jcpp::Object * obj) {
#ifdef _ODEBUG
  printf("Vector(%p)::addElement(%p)\n",this,obj);
#endif
  if (elementCount == elementData_length) {
    increaseCapacity();
  }
  elementData[elementCount++] = obj;
}

// done
int jcpp::Vector::capacity() {
  return elementData_length;
}

// done
 jcpp::Object * jcpp::Vector::clone () {
  jcpp::Vector *v = new jcpp::Vector(elementData_length,capacityIncrement);
  return v;
}

  // done
boolean jcpp::Vector::contains(jcpp::Object * elem) {
  return (indexOf(elem) != -1);
}

// done, but sprintf
 jcpp::Object * jcpp::Vector::elementAt ( int index ) {
// required because we might have a large enough, pre-allocated, empty element
// array that doesn't give us (physical) access errors
  if ( index >= elementCount ) {
#ifdef _ODEBUG
    IO::en("index (%d) >= elementCount (%d)",index,elementCount);
#endif
    return 0;
  }
  return elementData[index];
}

// done
jcpp::Enumeration *jcpp::Vector::elements () {
  return new VectEnum(elementData,elementCount);
}

// done
 void jcpp::Vector::ensureCapacity(int newCapacity) { 
  int i;

  if (elementData_length < newCapacity) {
    jcpp::Object * *oldBuffer = elementData;
    elementData = (jcpp::Object **)::malloc(sizeof(jcpp::Object *)*newCapacity);

    // copy
    for (i = 0; i < elementCount; i++) {
      elementData[i] = oldBuffer[i];
    }

    // init
    for (i = elementCount; i < newCapacity; i++) { elementData[i] = 0; }
    elementData_length = newCapacity;
    ::free(oldBuffer);
  }
}

// done
 jcpp::Object * jcpp::Vector::firstElement () {
  if ( elementCount <= 0 ) {
#ifdef _ODEBUG
    IO::en("No first element, empty vector.");
#endif
    return 0;
  }
  return elementData[0];
}

// done
jcpp::Object * jcpp::Vector::get(int idx) {
  return (elementAt(idx));
}

// done
int jcpp::Vector::indexOf(jcpp::Object * elem) {
  return indexOf(elem, 0);
}

// done
/** elem must be in vector, not just have same value of some element,
 except in the case of strings. */
 int jcpp::Vector::indexOf(jcpp::Object * elem, int index) {

  for (int pos = index; pos < elementCount; pos++) {
    jcpp::Object * obj = elementData[pos];
    if (elem == obj ) {
      return (pos);
    }
  }

  return (-1);
}

// done
 void jcpp::Vector::insertElementAt ( jcpp::Object * obj, int index ) {

#ifdef _ODEBUG
  printf("jcpp::Vector(%p)::insertElementAt(%p,%d)\n",this,obj,index);
#endif
  if ( elementCount == elementData_length ) {
    increaseCapacity();
  }

  if ( (index > elementCount) || (index < 0) ) {
#ifdef _ODEBUG
    IO::en(" ArrayIndexOutOfBounds ");
#endif
  } else {
    if ( index < elementCount ) {
      for ( int i = elementCount; i > index; i--) {
        elementData[i] = elementData[i-1];
      }
    }
  }

  elementData[index] = obj;
  elementCount++;
}

// done
boolean jcpp::Vector::isEmpty () {
  return (elementCount == 0);
}

// done
 jcpp::Object * jcpp::Vector::lastElement () {

  if ( elementCount == 0 ) {
#ifdef _ODEBUG
    IO::en("NoSuchElement");
#endif
    return 0;
  }
  return elementData[elementCount-1];

}

// done
int jcpp::Vector::lastIndexOf(jcpp::Object * elem) {
  return (lastIndexOf(elem, size()-1));
}

// done
 int jcpp::Vector::lastIndexOf(jcpp::Object * elem, int index) {

  for (int pos = index; pos >= 0; pos--) {

    jcpp::Object * obj = elementData[pos];
    if (elem == obj ) {
      return (pos);
    }

  }

  return (-1);
}

// done
/** return element at index specified and return that element */
 jcpp::Object * jcpp::Vector::remove(int idx) {
  jcpp::Object * obj = elementAt(idx);
  removeElementAt(idx);
  return (obj);
}

// done
/** the use of this function may not be too bright, as it does not
   call any destructors on the elements as they are removed. */
 void jcpp::Vector::removeAllElements () {
  for ( int i=elementCount-1; i>= 0; i-- ) {
    elementData[i] = null;
  }
  elementCount = 0;
}

// done
/** the use of this function may not be too bright, as it does not
 call any destructors on the elements as they are removed. */
 boolean jcpp::Vector::removeElement(jcpp::Object * obj) {
  if (contains(obj)) {
    removeElementAt(indexOf(obj));
    return (true);
  } else {
    return (false);
  }
}

// done
/** the use of this function may not be too bright, as it does not
 call any destructors on the elements as they are removed. */
 void jcpp::Vector::removeElementAt ( int index ) {
  if ( index >= elementCount ) {
#ifdef _ODEBUG
    IO::en("ArrayIndexOutOfBounds");
#endif
    return;
  }

  for (int i = index+1; i < elementCount; i++) {
    elementData[i-1] = elementData[i];
  }
  elementCount--;

  elementData[elementCount] = null;
}

// done
/** the use of this function may not be too bright, as it does not
 call any destructors on the elements as they are overwritten. */
 void jcpp::Vector::setElementAt(jcpp::Object * obj, int index) {
  if (index >= elementCount) {
#ifdef _ODEBUG
    IO::en("ArrayIndexOutOfBound");
#endif
    return;
  }
  elementData[index] = obj;
}

// done
 void jcpp::Vector::setSize(int newSize) {
  ensureCapacity(newSize);
  for (int i = elementCount; i < newSize; i++) {
    elementData[i] = NULL;
  }
  elementCount = newSize;
}

// done
int jcpp::Vector::size() {
  return elementCount;
}

 char *jcpp::Vector::toString() {
  char *ret;
  char  val[40];
  StringBuffer *result = new StringBuffer();

  result->append((char *)"[",1);
  for (int pos = 0; pos < elementCount; pos++) {
    if (pos > 0) {
      result->append((char *)", ",2);
    }
    sprintf(val,"(void *) 0x%p",elementData[pos]);
    result->append(val);
  }
  result->append((char *)"]",1);
  ret = result->toString();
  delete result;
  return ret;
}

// done
void jcpp::Vector::trimToSize() {
  if (elementCount != elementData_length) {
    jcpp::Object * *oldBuffer = elementData;
    elementData = (jcpp::Object **)::malloc(sizeof(jcpp::Object *)*elementCount);
    for (int i = 0; i < elementCount; i++) {
      elementData[i] = oldBuffer[i];
    }
    delete [] oldBuffer;
  }
}

/** non-javA extensions */


void jcpp::Vector::doAll(ObjectIterated & f) {
  for (int i = 0; i < elementCount; i++) {
    f.doIt(elementData[i]);
  }
}

CFREE jcpp::Object * *jcpp::Vector::toArgv(int &argc) {
  jcpp::Object * *ret = (jcpp::Object **)::malloc((elementCount+1)*sizeof(jcpp::Object *));
  if (ret == NULL) {
    argc = -1;
    return ret;
  }
  copyOut(ret, elementCount);
  argc = elementCount;
  ret[elementCount] = 0;
  return ret;
}

void jcpp::Vector::copyOut(jcpp::Object * *array, int length) {

  if (elementCount > length) {
#ifdef _ODEBUG
    IO::en("copyOut: length of array is less than length of vector");
#endif
    return;
  }

  if (elementCount < length) {
#ifdef _ODEBUG
    IO::en("copyOut: length of array is greater than size of vector.");
    IO::en("copyOut: vector will be NULL padded.");
#endif
    for (int i=elementCount; i < length; i++) {
      array[i] = NULL;
    }
  }

  for (int i = 0; i < elementCount; i++) {
    array[i] = elementData[i];
  }
}

void jcpp::Vector::addString(char *str) {
  add(new Mosquito(str));
}

char * jcpp::Vector::getString(int idx) {
  jcpp::Object *o = elementAt(idx);
  Mosquito *m = dynamic_cast<Mosquito *>(o);
  if (m==NULL) {
#ifdef _ODEBUG
    IO::en("jcpp::Vector::getString called on non-string jcpp::Object index");
#endif
    return 0;
  }
  return m->st;
}

