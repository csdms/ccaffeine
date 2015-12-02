/**
 *  Version: $Revision: 1.9 $
 *  Version control file: $RCSfile: StringHash.h,v $
 *  Date last modified: $Date: 2002/12/19 20:21:08 $
 *  Last modified by: $Author: baallan $
*/
#ifndef StringHash_seen
#define StringHash_seen
namespace jcpp {

//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"
//#include "jc++/util/Enumeration.h"
//#include "jc++/util/StringEnumeration.h"
//#include "jc++/util/HashEnum.h"
//#include "jc++/util/StringHashBucket.h"

class StringHashBucket; // our implementation detail.

/** how to write a lousy hash class, by Ben Allan, 7/99.
Note this used to have string template class dependencies
that have been removed.
 */
class StringHash : public virtual Object {

private:

  StringHashBucket **table;
  int table_length;
  int N; // geometry; the index to a primes list.

  float loadFactor;
  int numberOfKeys;
  int rehashLimit;

  char **okeys; // string array
  Object **oelements; // element array

  // unlike kaffe's rather goofy hash table implementation,
  // we're stealing ascends/tcls hash on string

  int calculateBucket(register const char *str);

public:

  CDELETE StringHash() ;
  
  ~StringHash() ;

  int size() ;
  
  boolean isEmpty() ;
  
  /// keys will be enumerated as (char *)
  StringEnumeration *keys() ;
  
  Enumeration *elements() ;
  
  boolean contains(Object *value) ;
  
  boolean containsKey(char *key) ;
  
  /** Create array of keys used in table. The array returned should be
  freed, but the keys in it should not. The keys will expire if
  the hashtable is destroyed. */
  CFREE char **charKeysToArray(int& ka_length);

  /** Return the Object indexed by key argument, or if no such Object
      exists in the table, NULL. */
  Object *get(const char *key) ;

  /** Return the Object indexed by key argument, or if no such Object
      exists in the table, NULL. */
  Object *get(const std::string key) ;

  /** Return the string key pointer matching the query. The returned key
      will persist until that key/object pair is removed from the table. */
  CONST char *getKey(char *key) ;
  
  /** Returns value argument or, if there already was an Object in the
      table under that key, returns the Object* it replaces. */
  Object *put(const char *key, Object *value);

  /** Returns value argument or, if there already was an Object in the
      table under that key, returns the Object* it replaces. */
  Object *put(const std::string key, Object *value);

  Object *remove(const char *key) ;

  void clear() ;

  Object *clone() { return 0; }

  CFREE char *toString() ;

  boolean containsValue(Object *o) ;

  void rehash(int & RehashError);

};

} ENDSEMI //jcpp

#endif // StringHash_seen
