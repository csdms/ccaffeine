/**
 *  Version: $Revision: 1.9 $
 *  Version control file: $RCSfile: ResourceHash.h,v $
 *  Date last modified: $Date: 2002/12/19 20:21:08 $
 *  Last modified by: $Author: baallan $
*/
#ifndef ResourceHash_seen
#define ResourceHash_seen
namespace jcpp {


//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"
//#include "jc++/util/Enumeration.h"
//#include "jc++/util/StringEnumeration.h"
//#include "jc++/util/HashEnum.h"
//#include "jc++/util/StringHashEnum.h"
//#include "jc++/util/ResourceBucket.h"

class ResourceBucket; // our implementation detail

/** How to write a lousy hash class, by Ben Allan, 7/99.
Note this used to have string template class dependencies
that have been removed.
 */
class ResourceHash : public virtual Object {

private:

  ResourceBucket **table;
  int table_length;
  /** geometry; the index to a primes list. */
  int N;

  float loadFactor;
  int numberOfKeys;
  int rehashLimit;

  char **okeys; // string array
  char **oelements; // element array

  /** unlike kaffe's rather goofy hash table implementation,
   we're stealing ascends/tcls hash on string. */
  int calculateBucket(register const char *str);

public:

  CDELETE ResourceHash() ;

  CDELETE ResourceHash(char *filename) ;
  
  ~ResourceHash() ;

  int size() ;
  
  boolean isEmpty() ;
  
  /** keys will be enumerated as (char *) */
  StringEnumeration *keys() ;
  
  /** Values in the table */
  StringEnumeration *elements() ;
  
  boolean contains(char *value) ;
  
  boolean containsKey(char *key) ;
  
  /** create array of keys used in table. The array returned should be
   freed, but the keys in it should not. The keys will expire if
   the hashtable is destroyed. The array is nullterminated. */
  CFREE char **charKeysToArray(int& ka_length);

  // string literal flavor
  char *get(char *key) ;
  
  /** key/value will be copied if needed; the pointers given are not kept. */
  char *put(const char *key, const char *value);

  CFREE char *remove(char *key) ;

  void clear() ;

  Object *clone() { return 0; }

  CFREE char *toString() ;

  boolean containsValue(char *s) ;

  void rehash(int & RehashError);

};

} ENDSEMI //jcpp

#endif // ResourceHash_seen
