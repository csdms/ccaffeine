/**
 *  Version: $Revision: 1.5 $
 *  Version control file: $RCSfile: HashEnum.cc,v $
 *  Date last modified: $Date: 2000/11/02 07:52:05 $
 *  Last modified by: $Author: baallan $
*/
#include "jc++/jc++.h"
#include "jc++/util/Enumeration.h"
#include "jc++/util/HashEnum.h"
#include "util/IO.h"

#include "util/freefree.h"

#ifndef lint
static char id[]="$Id: HashEnum.cc,v 1.5 2000/11/02 07:52:05 baallan Exp $"; // RCS string
#endif


/** The array ary is hence forth memory managed by the enum. */
jcpp::HashEnum::HashEnum(Object **ary, int count) {
  vector_count = count; 
  vector = ary;
  posn = 0;
}

jcpp::HashEnum::~HashEnum() {
  free(vector);
  vector = NULL;
  posn = vector_count = -1;
}

boolean jcpp::HashEnum::hasMoreElements() {
  return (posn < vector_count);
}

jcpp::Object *jcpp::HashEnum::nextElement() {
  if (posn >= vector_count || posn < 0) {
    return 0;
    IO::en("no such element in Hashtable");
  }
  return (vector[posn++]);
}
