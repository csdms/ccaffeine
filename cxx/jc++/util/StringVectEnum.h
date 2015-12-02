/**
 *  Version: $Revision: 1.6 $
 *  Version control file: $RCSfile: StringVectEnum.h,v $
 *  Date last modified: $Date: 2001/04/25 01:29:09 $
 *  Last modified by: $Author: baallan $
*/
#ifndef StringVectEnum_seen
#define StringVectEnum_seen
//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"
//#include "jc++/util/StringEnumeration.h"

namespace jcpp {


/** implementation of enumeration for string vectors. */
class StringVectEnum : public virtual StringEnumeration {

private:
  int index;
  int elementCount;
  char **elementData;

public:

  CDELETE StringVectEnum(char **borrowed_data, int eCount);

  virtual ~StringVectEnum() ;

  boolean hasMoreElements ();

  /** at variance in the delete behavior from VectEnum. */
  CDELETE char *nextElement ();

};

} ENDSEMI //jcpp
#endif // StringVectEnum_seen
