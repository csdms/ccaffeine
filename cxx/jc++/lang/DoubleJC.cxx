#ifndef lint
static char id[]="$Id: DoubleJC.cxx,v 1.5 2000/11/02 07:52:04 baallan Exp $"; // RCS string
#endif

#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#ifdef __sun
#include <strings.h>
#endif // __sun

#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/lang/DoubleJC.h"
#include <float.h>
#include <limits.h>


double jcpp::DoubleJC::valueOf0(char *s, int & err) {
  char *ep;
  double val = strtod(s,&ep);
  if (ep == s) { err = -1; } else { err = 0; }
  return val;
}

char *jcpp::DoubleJC::toStringWithPrecision(double value_, int precision) {
  char *result = (char *)malloc(30);
  sprintf(result,"%.*g",precision,value_);
  return result;
}
  
char *jcpp::DoubleJC::toString(double value_) {
  return toStringWithPrecision(value_, 21);
}

jcpp::DoubleJC::DoubleJC(double value_) {
    value = value_;
}

jcpp::DoubleJC::DoubleJC(char *s, int & NumberFormatErrJC) {
  value = valueOf(s,NumberFormatErrJC)->value;
}

double jcpp::DoubleJC::doubleValue() {
  return value;
}

CFREE char *jcpp::DoubleJC::toString() {
  return toString(value);
}

// uses c == semantics, not javas
boolean jcpp::DoubleJC::equals(Object *obj) {
  if (obj != 0) {
    jcpp::DoubleJC *djc;
    djc = dynamic_cast<jcpp::DoubleJC *>(obj);
    if (djc != 0) {
      return (djc->doubleValue() == value);
    }
  }
  return FALSE;
}
  
float jcpp::DoubleJC::floatValue(int & rangeError) {
  double d;
  d = fabs(value);
  if (d > FLT_MAX || d < FLT_MIN) {
    // underflow quietly
    rangeError = -1;
  }
  return ((float)value);
}

int jcpp::DoubleJC::intValue(int & rangeError) {
  if (value > INT_MAX || value < INT_MIN) {
    // underflow quietly
    rangeError = -1;
  }
  return ((int)value);
}
  
long jcpp::DoubleJC::longValue(int & rangeError) {
  if (value > LONG_MAX || value < LONG_MIN) {
    // underflow quietly
    rangeError = -1;
  }
  return (long) value;
}

jcpp::DoubleJC *jcpp::DoubleJC::valueOf(char *s, int & err) {
  if (s == 0) {
    err = -1; 
    return 0;
  }
  return (new jcpp::DoubleJC(valueOf0(s,err)));
}

double jcpp::DoubleJC::parseDouble(char *s,int & err) {

  if (s == 0) {
    err = -1;
    return 0.0;
  }
  return valueOf0(s,err);
}
