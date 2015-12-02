#ifndef __STRINGLIST_H__
#define __STRINGLIST_H__

/** Presumably will become Scott's Vector class. */

namespace gov {
  namespace cca {
    /** A container of simple strings interface. Somewhat more useful
	than an or vector array of strings because it is growable and
	could be passed empty into a function and returned full. This
	interface has reasonable typesafe, semantics in any language
	binding. */
    class StringList {

    public:

      StringList(){}
      virtual ~StringList(){}

      /** Fetch the requested string.  @param index input - a number from
	  0 to this.getSize-1.  @return the value, or null if the index is
	  out of range.  The returned string should be freed after use.  */
      virtual CFREE char* get(int index) = 0;

      /** Get the current number of strings in this list.
	  @return the list length.
      */
      virtual int getSize() = 0;
      /** Get the current number of strings in this list.
	  @return the list length.
      */
      virtual int size() = 0;

      /** Add a string to the list, the container makes a copy of the
	  string for its own purposes.  */
      virtual void append(char* s) = 0;

      /** Forget all the data in the list. */
      virtual void clear() = 0;
    };
  };
};

#endif // __STRINGLIST_H__
