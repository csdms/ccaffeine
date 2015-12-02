/**
 *  Version: $Revision: 1.5 $
 *  Version control file: $RCSfile: GenericHashEnum.h,v $
 *  Date last modified: $Date: 2005/02/01 00:14:31 $
 *  Last modified by: $Author: baallan $
*/
#ifndef GenericHashEnum_seen
#define GenericHashEnum_seen

namespace jcpp {


//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"
//#include "jc++/util/Enumeration.h"

/** This enumeration class is used in conjunction with a
javalike hash table. The exception to this behavior is
that unlike java, adding/deleting in a hashtable after
starting the enumeration is not supported.  */

class GenericHashEnum : public virtual Enumeration {

private:

  /** we take ary and make a vector out of it. */
  HashKey **vector; 
  /** next element pointer */
  int posn;
  int vector_count;

public:

  /** The array ary is hence forth memory managed by the enum. */
  GenericHashEnum(HashKey **ary, int count);

  virtual ~GenericHashEnum() ;

  virtual boolean hasMoreElements() ;

  virtual Object *nextElement() ;
};
} ENDSEMI //jcpp
#endif // GenericHashEnum_seen
