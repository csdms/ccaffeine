/**
 *  Version: $Revision: 1.5 $
 *  Version control file: $RCSfile: GenericHashTable.h,v $
 *  Date last modified: $Date: 2005/02/01 00:14:31 $
 *  Last modified by: $Author: baallan $
*/
#ifndef GenericHashTable_seen
#define GenericHashTable_seen
//#include "jc++/jc++.h"
// #include "jc++/lang/Object.h"
// #include "jc++/lang/HashKey.h"
// #include "jc++/util/Enumeration.h"
// #include "jc++/util/HashEnum.h"
// #include "jc++/util/HashBucket.h"

namespace jcpp {


/** For the semantics of this class, see (mostly) java's GenericHashTable
interface.
*/
class HashBucket;

class GenericHashTable : public virtual Object {

private:

  GenericHashBucket **table;
  int table_length;

  float loadFactor;
  int numberOfKeys;
  int rehashLimit;

  HashKey **okeys; // void pointer array
  Object **oelements;

  /** unlike kaffe's rather goofy hash table implementation,
   we're stealing ascends/tcls hash on pointer. */
  static const long magic;
  /** shape factor of the table. must be even and <= 30 */
  int N;
  /** 32 - N - 2, shift used to move sig. bits to low bits. */
  int ttmNm2;
  /** 2^N -1, mask of bits. */
  int twoNm1; 

  int calculateBucket(HashKey *key);

public:
  
  GenericHashTable();

  ~GenericHashTable();
  
  int size();
  
  boolean isEmpty();
  
  /** must call delete on this pointer when you are done with it. */
  CDELETE Enumeration *keys();

  /** must call delete on this pointer when you are done with it. */
  CDELETE Enumeration *elements();
  
  boolean contains(Object *value);

  boolean containsKey(HashKey *key);

  /** If you want this functionality, you must use a StringHash.
   returns a 0 length list.*/
  CFREE char **charKeysToArray(int& ka_length);


  Object *get(HashKey *key);
  
  Object *put(HashKey *key, Object *value);
  
  Object *remove(HashKey *key);
  
  void clear();
  
  /**
   * Creates a shallow copy of this hashtable.  
   * The keys and values themselves are not cloned. 
   * @return a clone of the hashtable. 
   */
  HashKey *clone() { return 0; }
  
  /** delete this string when you are done with it. */
  /* cfree */ char *toString();

  boolean containsValue(Object *o);

protected:
  void rehash(int & rehashError);

};

} ENDSEMI //jcpp
#endif //GenericHashTable_seen
