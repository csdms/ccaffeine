#ifndef __VECTORSTRINGLIST_H__
#define __VECTORSTRINGLIST_H__

#include <cca.h>
#include "StringList.h"
#include <vector>
#include <string>


class VectorStringList : public gov::cca::StringList {
 private:
  std::vector<std::string>* strVec;
  char** charList;
  bool charListAllocated;

 public:

  VectorStringList();
  VectorStringList(char** argv);
  virtual ~VectorStringList();
  
  char** argvList();

  std::vector<std::string>* vector() { return strVec; }

    /** Fetch the requested string.  @param index input - a number from
      0 to this.getSize-1.  @return the value, or null if the index is
      out of range.  The returned string should be freed after use.  */
  virtual char* get(int index) { return (char*) (*strVec)[index].c_str(); }

   /** Get the current number of strings in this list.
      @return the list length.
   */
  virtual int getSize() { return strVec->size(); }
 
   /** Get the current number of strings in this list.
      @return the list length.
   */
  virtual int size() { return strVec->size(); }
 
  /** Add a string to the list, the container makes a copy of the
   string for its own purposes.  */
  virtual void append(char* s) { strVec->push_back(s); }

   /** Forget all the data in the list. */
  virtual void clear();

  void dump();
};

#endif // __VECTORSTRINGLIST_H__
