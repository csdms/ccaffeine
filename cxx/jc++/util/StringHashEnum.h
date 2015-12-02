/**
 *  Version: $Revision: 1.6 $
 *  Version control file: $RCSfile: StringHashEnum.h,v $
 *  Date last modified: $Date: 2001/04/25 01:29:09 $
 *  Last modified by: $Author: baallan $
*/
#ifndef StringHashEnum_seen
#define StringHashEnum_seen
namespace jcpp {


//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"
//#include "jc++/util/StringEnumeration.h"

/** This enumeration class is used in conjunction with a
javalike hash table. The exception to this behavior is
that unlike java, adding/deleting in a hashtable after
starting the enumeration is not supported.  */
class StringHashEnum : public virtual StringEnumeration {

private:

  CFREE char **vector; 
  int posn;
  int vector_count;

public:

  /** The array ary is hence forth memory managed by the enum. */
  CDELETE StringHashEnum(char **ary, int count);

  ~StringHashEnum() ;

  boolean hasMoreElements() ;

  char *nextElement() ;

};

} ENDSEMI //jcpp
#endif // StringHashEnum_seen
