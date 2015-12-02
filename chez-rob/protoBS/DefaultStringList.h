#ifndef __DEFAULTSTRINGLIST_H__
#define __DEFAULTSTRINGLIST_H__

class DefaultStringList : public virtual gov::cca::StringList {
 private:
  char** list;
  long siz;
  long sizeAllocated;
  long sizeIncr;
  int debug;

  int allocate(long incr);

 public:

  DefaultStringList();
  virtual ~DefaultStringList();
  

    /** Fetch the requested string.  @param index input - a number from
      0 to this.getSize-1.  @return the value, or null if the index is
      out of range.  The returned string should be freed after use.  */
  virtual char* get(int index);

   /** Get the current number of strings in this list.
      @return the list length.
   */
  virtual int getSize();
 
   /** Get the current number of strings in this list.
      @return the list length.
   */
  virtual int size();
 
  /** Add a string to the list, the container makes a copy of the
   string for its own purposes.  */
  virtual void append(char* s);

   /** Forget all the data in the list. */
  virtual void clear();  

  void dump();
};

#endif // __DEFAULTSTRINGLIST_H__
