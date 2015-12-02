/**
 *  Version: $Revision: 1.3 $
 *  Version control file: $RCSfile: VectEnum.cc,v $
 *  Date last modified: $Date: 2000/11/02 07:52:05 $
 *  Last modified by: $Author: baallan $
*/
#ifndef lint
static char id[]="$Id: VectEnum.cc,v 1.3 2000/11/02 07:52:05 baallan Exp $"; // RCS string
#endif



#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/Enumeration.h"
#include "jc++/util/VectEnum.h"

#include "util/IO.h"
#include "util/freefree.h"


jcpp::VectEnum::VectEnum(jcpp::Object **borrowed_data, int eCount) {
  elementCount = eCount;
  index=0;
  elementData = borrowed_data;
}

jcpp::VectEnum::~VectEnum() {
  elementData = NULL;
  index = elementCount = -1;
}

boolean jcpp::VectEnum::hasMoreElements (){
  return (index < elementCount);
}

jcpp::Object *jcpp::VectEnum::nextElement () {
  if ( index >= elementCount ) {
    IO::en("no such element in vector");
    return 0;
  }
  return elementData[index++];
}

