/**
 *  Version: $Revision: 1.5 $
 *  Version control file: $RCSfile: StringEnumeration.h,v $
 *  Date last modified: $Date: 2001/04/25 01:29:09 $
 *  Last modified by: $Author: baallan $
*/

#ifndef StringEnumeration_h_seen
#define StringEnumeration_h_seen
namespace jcpp {


//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"
/** enumeration for string containers. */
class StringEnumeration : public virtual Object {

public:

  virtual ~StringEnumeration(){}
  /** more strings available? */
  virtual boolean hasMoreElements() = 0;
  /** next string */
  virtual char *nextElement() = 0;

};

} ENDSEMI //jcpp
#endif // StringEnumeration_h_seen
