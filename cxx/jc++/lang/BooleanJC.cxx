#ifndef lint
static char id[]="$Id: BooleanJC.cxx,v 1.5 2000/11/02 07:52:04 baallan Exp $"; // RCS string
#endif

#include <ctype.h>
#ifdef __sun
#include <strings.h>
#endif // __sun

#include <string.h>
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/JString.h"
#include "jc++/lang/BooleanJC.h"


jcpp::BooleanJC::BooleanJC(char * s) {
    value = (s != 0 &&
               (
               strcasecmp("true",s) == 0 ||
               strcasecmp("y",s)==0 ||
               strcasecmp(s,"yes")==0 ||
               strcasecmp(s,"da")==0 ||
               strcasecmp(s,"si")==0 ||
               strcasecmp(s,"yep")==0 ||
               strcasecmp(s,"t")==0 ||
               strcasecmp(s,"1")==0 ||
               strcasecmp(s,"right")==0 ||
               strcasecmp(s,"correct")==0 ||
               strcasecmp(s,"ok")==0 ||
               strcasecmp(s,"ding!")==0
               ) 
             );

}

jcpp::BooleanJC::BooleanJC(boolean value_) {
  value=value_;
}

boolean jcpp::BooleanJC::booleanValue() {
  return (value);
}

boolean jcpp::BooleanJC::equals(Object *obj) {
  
  if (obj != 0) {
    jcpp::BooleanJC *bjc;
    bjc = dynamic_cast<jcpp::BooleanJC *>(obj);
    if (bjc != 0) {
      return (bjc->booleanValue() == value);
    }
  }
  return FALSE;
}

char *jcpp::BooleanJC::toString() {
  return STRDUP((value ? "TRUE" : "FALSE"));
}

jcpp::BooleanJC *jcpp::BooleanJC::valueOf(char * s) {
  return new jcpp::BooleanJC(s);
}
