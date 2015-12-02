/**
 *  Version: $Revision: 1.7 $
 *  Version control file: $RCSfile: HashEnum.h,v $
 *  Date last modified: $Date: 2005/02/01 00:14:31 $
 *  Last modified by: $Author: baallan $
*/
#ifndef HashEnum_seen
#define HashEnum_seen
//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"
//#include "jc++/util/Enumeration.h"

namespace jcpp {


/** This enumeration class is used in conjunction with a
javalike hash table. The exception to this behavior is
that unlike java, adding/deleting in a hashtable after
starting the enumeration is not supported.  */

class HashEnum : public virtual Enumeration {

private:

  /** we take ary and make a vector out of it. */
  Object **vector; 
  /** next element pointer */
  int posn;
  int vector_count;

public:

  /** The array ary is hence forth memory managed by the enum. */
  HashEnum(Object **ary, int count);

  ~HashEnum() ;

  boolean hasMoreElements() ;

  Object *nextElement() ;
};
} ENDSEMI //jcpp
#endif // HashEnum_seen
