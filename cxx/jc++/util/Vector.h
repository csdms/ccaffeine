/**
 *  Version: $Revision: 1.9 $
 *  Version control file: $RCSfile: Vector.h,v $
 *  Date last modified: $Date: 2003/09/08 19:38:23 $
 *  Last modified by: $Author: baallan $
*/
#ifndef Vector_seen
#define Vector_seen
//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"
//#include "jc++/util/Enumeration.h"
//#include "jc++/util/VectEnum.h"

namespace jcpp {


/** an interface for operations to be applied over
 * an entire list.
 */
class ObjectIterated {
public:
  virtual ~ObjectIterated(){}
  virtual void doIt(Object *) = 0;
};

/** iterate delete over the list. */
class ObjectIteratedDelete : public virtual ObjectIterated {
public:
  ObjectIteratedDelete() {}
  virtual ~ObjectIteratedDelete() {}
  virtual void doIt(Object *);
};


/** A vector class with interface similar to the Java vector,
but this class is concrete, not an interface spec and
not really expected to be subclassed.
*/
class Vector : public virtual Object {

protected:

  int capacityIncrement;    // expansion size
  int elementCount;        // number of actual entries

  CFREE Object * *elementData;
  int elementData_length;    // total capacity

private:

  static const int DEFAULTCAP;

  void increaseCapacity();

public:
    
  CDELETE Vector();

  CDELETE Vector ( int initialCapacity );

  /** 0 increment indicates doubling on reallocation */
  CDELETE Vector(int initialCapacity, int increment);

  ~Vector();

  void add(Object *obj);
  void addElement(Object *obj);

  int capacity();

  CDELETE Object *clone ();

  boolean contains(Object * elem);

  Object * elementAt ( int index );

  CDELETE Enumeration *elements ();

  void ensureCapacity(int newCapacity);

  Object * firstElement ();

  Object * get(int idx);

  int indexOf(Object * elem);

  /** Elem must be in vector, not just have same value of some element,
   except in the case of strings. */
  int indexOf(Object * elem, int index);

  void insertElementAt ( Object * obj, int index );

  boolean isEmpty ();

  Object * lastElement ();

  int lastIndexOf(Object * elem);

  int lastIndexOf(Object * elem, int index);

  /** Delete element at index specified and return that element.
    memory of returned element becomes callers responsibility.
   */
  CDELETE Object * remove(int idx) ;

  /** The use of this function may not be too bright, as it does not
   call any destructors on the elements as they are removed. */
  void removeAllElements () ;

  /** The use of this function may not be too bright, as it does not
   call any destructors on the elements as they are removed. */
  boolean removeElement(Object * obj) ;

  /** The use of this function may not be too bright, as it does not
   call any destructors on the elements as they are removed. */
  void removeElementAt ( int index ) ;

  /** The use of this function may not be too bright, as it does not
   call any destructors on the elements as they are overwritten. */
  void setElementAt(Object * obj, int index);

  /** Set the number of active entries in the vector, initing them
      to 0 if the size is an expansion. */
  void setSize(int newSize) ;

  /** Get the number of active entries in the vector. */
  int size() ;

  char *toString();

  /** Truncate the vector. */
  void trimToSize();

  /** Apply the function f given to all elements of the
      the vector. The user is expected to know what they are doing.
  */
  void doAll(ObjectIterated &f);

  /** Return an array of pointers to vector elements and set argc
      to the length of the array.
      If malloc fails, argc -> -1, return NULL. */
  CFREE Object * *toArgv(int &argc);

  /** Copy Object *s from vector into users array, which must be at least
      as long as the size of the vector. length is the space available
      in the array given. If array is bigger than vector, its
      remaining entries will be set to NULL. */
  void copyOut(Object * *array, int length);

  /** Mosquito functions. These will sting you if you don't
   know exactly what you are doing with your pointers.
   In particular Enumeration will not return the string pointers,
   but instead their Object wrappers.
  */
  void addString(char *str);
  /** Return the string value at element idx, if that element is indeed a string.
    @return NULL if idxth element is not a string. */
  char *getString(int idx);
};

} ENDSEMI //jcpp

#endif //Vector_seen
