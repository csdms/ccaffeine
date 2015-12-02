/**
 *  Version: $Revision: 1.5 $
 *  Version control file: $RCSfile: StringHashEnum.cc,v $
 *  Date last modified: $Date: 2000/11/02 07:52:05 $
 *  Last modified by: $Author: baallan $
*/

#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/StringEnumeration.h"
#include "jc++/util/StringHashEnum.h"
#include "util/IO.h"
#ifndef lint
static char id[]="$Id: StringHashEnum.cc,v 1.5 2000/11/02 07:52:05 baallan Exp $"; // RCS string
#endif


#include "util/freefree.h"


/** The array ary is hence forth memory managed by the enum. */
jcpp::StringHashEnum::StringHashEnum(char **ary, int count) {
  vector_count = count; 
  vector = ary;
  posn = 0;
}

jcpp::StringHashEnum::~StringHashEnum() {
  ::free(vector);
  vector = NULL;
  posn = vector_count = -1;
}

boolean jcpp::StringHashEnum::hasMoreElements() {
  return (posn < vector_count);
}

char *jcpp::StringHashEnum::nextElement() {
  if (posn >= vector_count || posn < 0) {
    IO::en("no such element in StringHashtable");
    return 0;
  }
  return vector[posn++];
}
