/**
 *  Version: $Revision: 1.8 $
 *  Version control file: $RCSfile: Hashtable.h,v $
 *  Date last modified: $Date: 2005/02/01 00:14:31 $
 *  Last modified by: $Author: baallan $
*/
#ifndef Hashtable_seen
#define Hashtable_seen

namespace jcpp {


//#include "jc++/jc++.h"
// #include "jc++/lang/Object.h"
// #include "jc++/util/Enumeration.h"
// #include "jc++/util/HashEnum.h"
// #include "jc++/util/HashBucket.h"

/** For the semantics of this class, see (mostly) java's Hashtable
interface.
*/
class HashBucket;

class Hashtable : public virtual Object {

private:

  HashBucket **table;
  int table_length;

  float loadFactor;
  int numberOfKeys;
  int rehashLimit;

  Object **okeys; // void pointer array
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

  int calculateBucket(Object *key);

public:

  Hashtable();

  ~Hashtable();
  
  int size();
  
  boolean isEmpty();
  
  /** must call delete on this pointer when you are done with it. */
  /* DELETE */ Enumeration *keys();

  /** must call delete on this pointer when you are done with it. */
  /* DELETE */ Enumeration *elements();
  
  boolean contains(Object *value);

  boolean containsKey(Object *key);

  /** If you want this functionality, you must use a StringHash.
   returns a 0 length list.*/
  /* FREE */ char **charKeysToArray(int& ka_length);


  Object *get(Object *key);
  
  Object *put(Object *key, Object *value);
  
  Object *remove(Object *key);
  
  void clear();
  
  /**
   * Creates a shallow copy of this hashtable.  
   * The keys and values themselves are not cloned. 
   * @return a clone of the hashtable. 
   */
  Object *clone() { return 0; }
  
  /** delete this string when you are done with it. */
  /* FREE */ char *toString();

  boolean containsValue(Object *o);

protected:
  void rehash(int & rehashError);

};

} ENDSEMI //jcpp
#endif //Hashtable_seen
