/**
 *  Version: $Revision: 1.12 $
 *  Version control file: $RCSfile: StringVector.cc,v $
 *  Date last modified: $Date: 2004/03/26 01:52:01 $
 *  Last modified by: $Author: baallan $
*/

#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/StringEnumeration.h"
#include "jc++/util/StringVectEnum.h"
#include "jc++/util/StringVector.h"
#include "jc++/util/ResourceBucket.h"
#include "jc++/util/StringHashBucket.h"
#include "jc++/util/StringBuffer.h"
#include "util/IO.h"
#ifndef lint
static char id[]="$Id: StringVector.cc,v 1.12 2004/03/26 01:52:01 baallan Exp $"; // RCS string
#endif


#include "util/freefree.h"

const int jcpp::StringVector::DEFAULTCAP = 10;


/** iterate free over the list. */
void jcpp::StringIteratedFree::doIt(char *s) {
	free(s);
}

/** iterate delete[] over the list. */
void jcpp::StringIteratedDelete::doIt(char *s) {
	delete [] s;
}


// done
void jcpp::StringVector::increaseCapacity() {
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

  CFREE char **oldBuffer = elementData;
  elementData = (char **)::malloc(sizeof(char *)*newCapacity);

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
jcpp::StringVector::StringVector() {

  elementData = (char **)::malloc(sizeof(char *)*DEFAULTCAP);
  elementData_length = DEFAULTCAP;
  elementCount = 0;
  capacityIncrement = 0;

}

// done
jcpp::StringVector::StringVector ( int initialCapacity ) {

  if (initialCapacity < 1) { initialCapacity = DEFAULTCAP; }
  elementData = (char **)::malloc(sizeof(char *)*initialCapacity);
  elementData_length = initialCapacity;
  elementCount = 0;
  capacityIncrement = 0;

}

// done
/** 0 increment indicates doubling on reallocation */
jcpp::StringVector::StringVector(int initialCapacity, int increment) {

  if (initialCapacity < 1) { initialCapacity = DEFAULTCAP; }
  if (increment < 0) { increment = 0; }
  elementData = (char **)::malloc(sizeof(char *)*initialCapacity);
  elementData_length = initialCapacity;
  elementCount = 0;
  capacityIncrement = increment;

}

// done
jcpp::StringVector::~StringVector() {
  ::free(elementData);
  elementData = NULL;
  elementCount = elementData_length = capacityIncrement = -1;
}

// done
void jcpp::StringVector::add(char * str) {
	addElement(str);
}

void jcpp::StringVector::addElement(char * str) {
#ifdef _ODEBUG
  printf("StringVector(%p)::addElement(%p)\n",this,str);
#endif
  if (elementCount == elementData_length) {
    increaseCapacity();
  }
  elementData[elementCount++] = str;
}

// done
int jcpp::StringVector::capacity() {
  return elementData_length;
}

// done
jcpp::Object *jcpp::StringVector::clone () {
  jcpp::StringVector *v = new StringVector(elementData_length,capacityIncrement);
  return v;
}

  // done
boolean jcpp::StringVector::contains(char * elem) {
  return (indexOf(elem) != -1);
}

// done, but sprintf
char * jcpp::StringVector::elementAt ( int index ) {
// required because we might have a large enough, pre-allocated, empty element
// array that doesn't give us (physical) access errors
  if ( index >= elementCount ) {
    IO::en("index (%d) >= elementCount (%d)",index,elementCount);
    return 0;
  }
  return elementData[index];
}

// done
jcpp::StringEnumeration *jcpp::StringVector::elements () {
  return new jcpp::StringVectEnum(elementData,elementCount);
}

// done
void jcpp::StringVector::ensureCapacity(int newCapacity) { 
  int i;

  if (elementData_length < newCapacity) {
    CFREE char **oldBuffer = elementData;
    elementData = (char **)::malloc(sizeof(char *)*newCapacity);

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
char * jcpp::StringVector::firstElement () {
  if ( elementCount <= 0 ) {
    IO::en("No first element, empty vector.");
    return 0;
  }
  return elementData[0];
}

// done
char * jcpp::StringVector::get(int idx) {
  return (elementAt(idx));
}

// done
int jcpp::StringVector::indexOf(char * elem) {
  return indexOf(elem, 0);
}

// done
/** elem must be in vector, not just have same value of some element,
 except in the case of strings. */
int jcpp::StringVector::indexOf(char * elem, int index) {

  for (int pos = index; pos < elementCount; pos++) {
    char * str = elementData[pos];
    if (elem == str || (elem != NULL && str != NULL && strcmp(elem,str) == 0)) {
      return (pos);
    }
  }

  return (-1);
}

// done
void jcpp::StringVector::insertElementAt ( char * str, int index ) {

#ifdef _ODEBUG
  printf("StringVector(%p)::insertElementAt(%p,%d)\n",this,str,index);
#endif
  if ( elementCount == elementData_length ) {
    increaseCapacity();
  }

  if ( (index > elementCount) || (index < 0) ) {
    IO::en(" ArrayIndexOutOfBounds ");
    return;
  } else {
    if ( index < elementCount ) {
      for ( int i = elementCount; i > index; i--) {
        elementData[i] = elementData[i-1];
      }
    }
  }

  elementData[index] = str;
  elementCount++;
}

// done
boolean jcpp::StringVector::isEmpty () {
  return (elementCount == 0);
}

// done
char * jcpp::StringVector::lastElement () {

  if ( elementCount == 0 ) {
    IO::en("NoSuchElement");
    return 0;
  }
  return elementData[elementCount-1];

}

// done
int jcpp::StringVector::lastIndexOf(char * elem) {
  return (lastIndexOf(elem, size()-1));
}

// done
int jcpp::StringVector::lastIndexOf(char * elem, int index) {

  for (int pos = index; pos >= 0; pos--) {

    char * str = elementData[pos];
    if (elem == str || (elem != NULL && str != NULL && strcmp(elem,str) == 0)) {
      return (pos);
    }

  }

  return (-1);
}

// done
/** return element at index specified and return that element */
char * jcpp::StringVector::remove(int idx) {
  char * str = elementAt(idx);
  removeElementAt(idx);
  return (str);
}

// done
/** the use of this function may not be too bright, as it does not
   call any destructors on the elements as they are removed. */
void jcpp::StringVector::removeAllElements () {
  for ( int i=elementCount-1; i>= 0; i-- ) {
    elementData[i] = null;
  }
  elementCount = 0;
}

// done
/** the use of this function may not be too bright, as it does not
 call any destructors on the elements as they are removed. */
boolean jcpp::StringVector::removeElement(char * str) {
  if (contains(str)) {
    removeElementAt(indexOf(str));
    return (true);
  } else {
    return (false);
  }
}

// done
/** the use of this function may not be too bright, as it does not
 call any destructors on the elements as they are removed. */
void jcpp::StringVector::removeElementAt ( int index ) {
  if ( index >= elementCount ) {
    IO::en("ArrayIndexOutOfBounds");
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
void jcpp::StringVector::setElementAt(char * str, int index) {
  if (index >= elementCount) {
    IO::en("ArrayIndexOutOfBound");
    return;
  }
  elementData[index] = str;
}

// done
void jcpp::StringVector::setSize(int newSize) {
  ensureCapacity(newSize);
  for (int i = elementCount; i < newSize; i++) {
    elementData[i] = NULL;
  }
  elementCount = newSize;
}

// done
int jcpp::StringVector::size() {
  return elementCount;
}

char *jcpp::StringVector::toString() {
  char *ret;
  char  val[40];
  jcpp::StringBuffer *result = new StringBuffer();

  result->append((char *)"[",1);
  for (int pos = 0; pos < elementCount; pos++) {
    if (pos > 0) {
      result->append((char *)", ",2);
    }
    sprintf(val,"(char *) 0x%p {",elementData[pos]);
    result->append(val);
    result->append(elementData[pos]);
    result->append((char *)"}",1);
  }
  result->append((char *)"]",1);
  ret = result->toString();
  delete result;
  return ret;
}

// done
void jcpp::StringVector::trimToSize() {
  if (elementCount != elementData_length) {
    CFREE char **oldBuffer = elementData;
    elementData = (char **)::malloc(sizeof(char *)*elementCount);
    for (int i = 0; i < elementCount; i++) {
      elementData[i] = oldBuffer[i];
    }
    ::free(oldBuffer);
  }
}

/** non-javA extensions */

void jcpp::StringVector::doAll(StringIterated & f) {
  for (int i = 0; i < elementCount; i++) {
    f.doIt(elementData[i]);
  }
}

CFREE char **jcpp::StringVector::toArgv(int &argc) {
  char **ret = (char **)::malloc((elementCount+1)*sizeof(char *));
  if (ret == NULL) {
    argc = -1;
    return ret;
  }
  copyOut(ret, elementCount);
  argc = elementCount; ret[elementCount] = 0;
  return ret;
}

void jcpp::StringVector::copyOut(char **array, int length) {

  if (elementCount > length) {
    IO::en("copyOut: length of array is less than length of vector");
    return;
  }

  if (elementCount < length) {
    IO::en("copyOut: length of array is greater than size of vector.");
    IO::en("copyOut: vector will be NULL padded.");
    for (int i=elementCount; i < length; i++) {
      array[i] = NULL;
    }
  }

  for (int i = 0; i < elementCount; i++) {
    array[i] = elementData[i];
  }
}
 
static int strArrayCompare(const void *sp1,const  void*sp2) {
  char **spc1, **spc2;
  spc1 = (char **)sp1;
  spc2 = (char **)sp2;
  return strcmp(*spc1, *spc2);
}

void jcpp::StringVector::sort() {
  qsort((void *)elementData, (size_t)elementCount, sizeof(char *), strArrayCompare);
}

