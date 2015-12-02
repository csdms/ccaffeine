/**
 *  Version: $Revision: 1.3 $
 *  Version control file: $RCSfile: StringVectEnum.cc,v $
 *  Date last modified: $Date: 2000/11/02 07:52:05 $
 *  Last modified by: $Author: baallan $
*/
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/StringEnumeration.h"
#include "jc++/util/StringVectEnum.h"
#include "util/IO.h"

#ifndef lint
static char id[]="$Id: StringVectEnum.cc,v 1.3 2000/11/02 07:52:05 baallan Exp $"; // RCS string
#endif


#include "util/freefree.h"


jcpp::StringVectEnum::StringVectEnum(char **borrowed_data, int eCount) {
  elementCount = eCount;
  index=0;
  elementData = borrowed_data;
}

jcpp::StringVectEnum::~StringVectEnum() {
  elementData = NULL;
  index = elementCount = -1;
}

boolean jcpp::StringVectEnum::hasMoreElements (){
  return (index < elementCount);
}

char *jcpp::StringVectEnum::nextElement () {
  if ( index >= elementCount ) {
    IO::en("no such element in vector");
    return 0;
  }
  return elementData[index++];
}

