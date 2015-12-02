#ifndef lint
static char id[]="$Id: FloatJC.cxx,v 1.5 2000/11/02 07:52:04 baallan Exp $"; // RCS string
#endif

#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#ifdef __sun
#include <strings.h>
#endif // __sun

#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/lang/FloatJC.h"
#include <float.h>
#include <limits.h>


float jcpp::FloatJC::valueOf0(char *s, int &err) {
  err = 0;
  int numcon=0;
  float val;
  numcon = sscanf(s,"%f",&val);
  if (numcon == 0) { err = -1; val= 0.0; } else { err = 0; }
  return val;
}

char *jcpp::FloatJC::toStringWithPrecision(float value_, int precision) {
  char *result = (char *)malloc(30);
  sprintf(result,"%.*g",precision,value_);
  return result;
}
  
char *jcpp::FloatJC::toString(float value_) {
  return toStringWithPrecision(value_, 12);
}

jcpp::FloatJC::FloatJC(float value_) {
    value = value_;
}

jcpp::FloatJC::FloatJC(char *s, int & NumberFormatErrJC) {
  value = valueOf(s,NumberFormatErrJC)->value;
}

float jcpp::FloatJC::floatValue() {
  return value;
}

CFREE char *jcpp::FloatJC::toString() {
  return toString(value);
}

// uses c == semantics, not javas
boolean jcpp::FloatJC::equals(Object *obj) {
  if (obj != 0) {
    jcpp::FloatJC *djc;
    djc = dynamic_cast<jcpp::FloatJC *>(obj);
    if (djc != 0) {
      return (djc->floatValue() == value);
    }
  }
  return FALSE;
}
  
double jcpp::FloatJC::doubleValue() {
  return (double)value;
}

int jcpp::FloatJC::intValue(int &err) {
  if (value > INT_MAX ) {
    err = -1;
    return INT_MAX;
  }
  if (value < INT_MIN) {
    err = -1;
    return INT_MIN;
  }
  return ((int)value);
}
  
long jcpp::FloatJC::longValue(int &err) {
  if (value > LONG_MAX) {
    err = -1;
    return LONG_MAX;
  }
  if (value < LONG_MIN) {
    err = -1;
    return LONG_MIN;
  }
  return (long) value;
}

jcpp::FloatJC *jcpp::FloatJC::valueOf(char *s, int & err) {
  if (s == 0) {
    err = -1;
    return 0;
  }
  return (new jcpp::FloatJC(valueOf0(s,err)));
}

float jcpp::FloatJC::parseFloat(char *s, int & ErrJC) {

  ErrJC = 0;
  if (s == 0) {
    ErrJC = -1;
    return 0.0;
  }
  return valueOf0(s,ErrJC);
}
