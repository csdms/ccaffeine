#ifndef lint
static char id[]="$Id: IntegerJC.cxx,v 1.5 2001/04/25 01:29:08 baallan Exp $"; 
// RCS string
#endif

#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#ifdef __sun
#include <strings.h>
#endif // __sun

#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/lang/IntegerJC.h"
//#include "jc++/util/StringBuffer.h"
#include <float.h>
#include <limits.h>

#define IJC_MIN_RADIX 2
#define IJC_MAX_RADIX 36

char jcpp::IntegerJC::forDigit(int digit, int radix)
{
  if (radix < IJC_MIN_RADIX || radix > IJC_MAX_RADIX) {
    return 0x0000;
  }
  if (digit < 0 || digit >= radix) {
    return 0x0000;
  }
  if (digit < 10) {
    return (char)(((int)'0')+digit);
  }
  else {
    return (char)(((int)'a')+(digit-10));
  }
}


char *jcpp::IntegerJC::toUnsignedString(int i, int bits) {
  if (i == 0) {
    return ((char *)"0");
  }

  char buf[256]; 
  int len = 0;
  int radix = 1 << bits; 
  int mask = radix-1;
  while (i != 0) {
    char digit = jcpp::IntegerJC::forDigit(i & mask, radix);
    // i >>>= bits; //fixme
    buf[len] = digit;
    len++;
  }
  
  char *result = (char *)malloc(len+1);
  int j;
  for (j = len; j > 0; j--) {
    result[len-j] = buf[j];
  }
  result[len] = '\0';
    
  return result;
}


jcpp::IntegerJC::IntegerJC ( char * s , int & NumberFormatErr)
{
  value = parseInt(s,NumberFormatErr);
}

jcpp::IntegerJC::IntegerJC(int value_)
{
  value = value_;
}

double jcpp::IntegerJC::doubleValue() {
  return ((double)value);
}

boolean jcpp::IntegerJC::equals(Object *obj) {
  if (obj != 0) {
    jcpp::IntegerJC *djc;
    djc = dynamic_cast<jcpp::IntegerJC *>(obj);
    if (djc != 0) {
      return (djc->intValue() == value);
    }
  }
  return FALSE;
}

float jcpp::IntegerJC::floatValue() {
  return (float )value;
}

int jcpp::IntegerJC::intValue() {
  return value;
}

long jcpp::IntegerJC::longValue() {
  return (long )value;
}

CFREE char * jcpp::IntegerJC::toString() {
  return toString(value);
}

// you get strtol(s,x,0) behavior, likeit or lumpit.
// except we round down to INT_MAX/MIN if needed.
int jcpp::IntegerJC::parseInt(char * s, int & NumberFormatErr)
{
  char *ep;
  NumberFormatErr=0;
  long val;
  val = strtol(s,&ep,0);
  if (val > INT_MAX) {
    return INT_MAX;
  }
  if (val < INT_MIN) {
    return INT_MIN;
  }
  return (int) val;
}

CFREE char * jcpp::IntegerJC::toBinaryString(int i) {
  return toUnsignedString(i, 1);
}

CFREE char * jcpp::IntegerJC::toHexString(int i) {
  return toUnsignedString(i, 4);
}

CFREE char * jcpp::IntegerJC::toOctalString(int i) {
  return toUnsignedString(i, 3);
}

CFREE char * jcpp::IntegerJC::toString(int i) {
  return toString(i, 10);
}

CFREE char * jcpp::IntegerJC::toString(int i, int radix) {
  if (i == 0) {
    return ((char *)"0");
  }

  if (radix < IJC_MIN_RADIX || radix > IJC_MAX_RADIX) {
    radix = 10;
  }

  char buf[256];
  int sign = (i < 0) ? -1 : 1;
  int len = 0;

  while (i != 0) {
    char digit = forDigit(abs(i % radix), radix);
    i = i / radix;
    buf[len] = digit;
    len++;
  }
  if (sign == -1) {
    buf[len]='-';
    len++;
  }

  char *result = (char *)malloc(len+1);
  int j;
  for (j = len; j > 0; j--) {
    result[len-j] = buf[j];
  }
  result[len] = '\0';
  return result;
}

jcpp::IntegerJC *jcpp::IntegerJC::valueOf(char * s, int & NumberFormatErr)
{
  return new jcpp::IntegerJC(parseInt(s,NumberFormatErr));
}

