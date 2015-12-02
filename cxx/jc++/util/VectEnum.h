/**
 *  Version: $Revision: 1.6 $
 *  Version control file: $RCSfile: VectEnum.h,v $
 *  Date last modified: $Date: 2001/04/25 01:29:09 $
 *  Last modified by: $Author: baallan $
*/
#ifndef VectEnum_seen
#define VectEnum_seen
namespace jcpp {


//#include "jc++/jc++.h"
//#include "jc++/lang/Object.h"
//#include "jc++/util/Enumeration.h"

/** implementation of enumeration for object vectors */
class VectEnum : public virtual Enumeration {

private:
  int index;
  int elementCount;
  Object **elementData;

public:

  CDELETE VectEnum(Object **borrowed_data, int eCount);

  virtual ~VectEnum() ;

  boolean hasMoreElements ();

  Object *nextElement ();

};

}  ENDSEMI //jcpp
#endif // VectEnum_seen
