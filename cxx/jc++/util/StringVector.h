/**
 *  Version: $Revision: 1.9 $
 *  Version control file: $RCSfile: StringVector.h,v $
 *  Date last modified: $Date: 2003/09/08 19:38:23 $
 *  Last modified by: $Author: baallan $
*/
#ifndef StringVector_seen
#define StringVector_seen
namespace jcpp {


//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"
//#include "jc++/util/StringEnumeration.h"

/** an interface for operations to be applied over
 * an entire list.
 */
class StringIterated {
public:
	virtual ~StringIterated(){}
	virtual void doIt(char *) = 0;
};

/** iterate free() over the list. */
class StringIteratedFree : public virtual StringIterated {
public:
				StringIteratedFree() {}
				virtual ~StringIteratedFree() {}
				virtual void doIt(char *);
};

/** iterate delete[] over the list. */
class StringIteratedDelete : public virtual StringIterated {
public:
				StringIteratedDelete() {}
				virtual ~StringIteratedDelete() {}
				virtual void doIt(char *);
};

/** A vector class with interface similar to the Java vector,
but this class is concrete, not an interface spec and
not really expected to be subclassed.
*/
class StringVector : public virtual Object {

protected:

  /** expansion size */
  int capacityIncrement; 
  /** number of actual entries */
  int elementCount;

  CFREE char **elementData;
  /** total capacity */
  int elementData_length;

private:

  static const int DEFAULTCAP;

  void increaseCapacity();

public:
    
  CDELETE StringVector();

  CDELETE StringVector ( int initialCapacity );

  /** 0 increment indicates doubling on reallocation */
  CDELETE StringVector(int initialCapacity, int increment);

  ~StringVector();

  void add(char * str);
  void addElement(char * str);

  int capacity();

  CDELETE Object *clone ();

  boolean contains(char * elem);

  char * elementAt ( int index );

  CDELETE StringEnumeration *elements ();

  void ensureCapacity(int newCapacity);

  char * firstElement ();

  char * get(int idx);

  int indexOf(char * elem);

  /** elem must be in vector, not just have same value of some element,
   except in the case of strings. */
  int indexOf(char * elem, int index);

  void insertElementAt ( char * str, int index );

  boolean isEmpty ();

  char * lastElement ();

  int lastIndexOf(char * elem);

  int lastIndexOf(char * elem, int index);

  /** delete element at index specified and return that element.
    memory of returned element becomes callers responsibility.
   */
  CFREE char * remove(int idx) ;

  /** the use of this function may not be too bright, as it does not
   call any destructors on the elements as they are removed. */
  void removeAllElements () ;

  /** the use of this function may not be too bright, as it does not
   call any destructors on the elements as they are removed. */
  boolean removeElement(char * str) ;

  /** the use of this function may not be too bright, as it does not
   call any destructors on the elements as they are removed. */
  void removeElementAt ( int index ) ;

  /** the use of this function may not be too bright, as it does not
   call any destructors on the elements as they are overwritten. */
  void setElementAt(char * str, int index);

  void setSize(int newSize) ;

  int size() ;

  char *toString();

  void trimToSize();

  /** apply the StringIterated do() given to all elements of the
      the vector. The user is expected to know what they are doing.
  */
  void doAll(StringIterated &);

  /** Return an array of pointers to vector elements and set argc
      to the length of the array.
      If malloc fails, argc -> -1, return NULL.
      free the return value, not the data in its pointers.
      This is not a classical argv ala C in that it is not NULL-terminated.
   */
  CFREE char **toArgv(int &argc);

  /** Copy char *s from vector into users array, which must be at least
      as long as the size of the vector. length is the space available
      in the array given. If array is bigger than vector, its
      remaining entries will be set to NULL. */
  void copyOut(char **array, int length);

  /** sort strings by strcmp + qsort. */
  void sort();
};

}  ENDSEMI //jcpp

#endif //StringVector_seen
