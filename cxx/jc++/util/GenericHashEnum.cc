/**
 *  Version: $Revision: 1.4 $
 *  Version control file: $RCSfile: GenericHashEnum.cc,v $
 *  Date last modified: $Date: 2000/11/02 07:52:05 $
 *  Last modified by: $Author: baallan $
*/
#include "jc++/jc++.h"
#include "jc++/lang/HashKey.h"
#include "jc++/util/Enumeration.h"
#include "jc++/util/GenericHashEnum.h"
#include "util/IO.h"

#include "util/freefree.h"

#ifndef lint
static char id[]="$Id: GenericHashEnum.cc,v 1.4 2000/11/02 07:52:05 baallan Exp $"; // RCS string
#endif


/** The array ary is hence forth memory managed by the enum. */
jcpp::GenericHashEnum::GenericHashEnum(HashKey **ary, int count) {
  vector_count = count; 
  vector = ary;
  posn = 0;
}

jcpp::GenericHashEnum::~GenericHashEnum() {
  free(vector);
  vector = NULL;
  posn = vector_count = -1;
}

boolean jcpp::GenericHashEnum::hasMoreElements() {
  return (posn < vector_count);
}

jcpp::Object *jcpp::GenericHashEnum::nextElement() {
  if (posn >= vector_count || posn < 0) {
    return 0;
    IO::en("no such element in Hashtable");
  }
  return (vector[posn++]);
}
