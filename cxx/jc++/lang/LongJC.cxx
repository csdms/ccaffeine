#ifndef lint
static char id[]="$Id: LongJC.cxx,v 1.5 2001/04/25 01:29:08 baallan Exp $"; 
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
#include "jc++/lang/LongJC.h"
#include <float.h>
#include <limits.h>

#define IJC_MIN_RADIX 2
#define IJC_MAX_RADIX 36

char jcpp::LongJC::forDigit(long long digit, int radix)
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


char *jcpp::LongJC::toUnsignedString(long long i, int bits) {
  if (i == 0) {
    return ((char *)"0");
  }

  char buf[256]; 
  int len = 0;
  long long radix = 1 << bits; 
  long long mask = radix-1;
  while (i != 0) {
    char digit = jcpp::LongJC::forDigit(i & mask, radix);
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


jcpp::LongJC::LongJC ( char * s , int & NumberFormatErr)
{
  value = parseLong(s,NumberFormatErr);
}

jcpp::LongJC::LongJC(long long value_)
{
  value = value_;
}

boolean jcpp::LongJC::equals(Object *obj) {
  if (obj != 0) {
    jcpp::LongJC *djc;
    djc = dynamic_cast<jcpp::LongJC *>(obj);
    if (djc != 0) {
      return (djc->longValue() == value);
    }
  }
  return FALSE;
}

double jcpp::LongJC::doubleValue() {
  return ((double)value);
}

float jcpp::LongJC::floatValue() {
  return (float )value;
}

int jcpp::LongJC::intValue(int &rangeError) {
  if (value > INT_MAX) {
    rangeError = -1;
    return INT_MAX; 
  }
  if (value < INT_MIN) {
    rangeError = -1;
    return INT_MIN;
  }
  rangeError = 0;
  return value;
}

long long jcpp::LongJC::longValue() {
  return value;
}

CFREE char * jcpp::LongJC::toString() {
  return toString(value);
}

// you get strtol(s,x,0) behavior, likeit or lumpit.
// except we round down to INT_MAX/MIN if needed.
long long jcpp::LongJC::parseLong(char * s, int & NumberFormatErr)
{
  char *ep;
  NumberFormatErr=0;
  long val;
  val = strtol(s,&ep,0);
  return (long long) val;
}

CFREE char * jcpp::LongJC::toBinaryString(long long i) {
  return toUnsignedString(i, 1);
}

CFREE char * jcpp::LongJC::toHexString(long long i) {
  return toUnsignedString(i, 4);
}

CFREE char * jcpp::LongJC::toOctalString(long long i) {
  return toUnsignedString(i, 3);
}

CFREE char * jcpp::LongJC::toString(long long i) {
  return toString(i, 10);
}

CFREE char * jcpp::LongJC::toString(long long i, int radix) {
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
    char digit = forDigit(labs(i % radix), radix);
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

jcpp::LongJC *jcpp::LongJC::valueOf(char * s, int & NumberFormatErr)
{
  return new jcpp::LongJC(parseLong(s,NumberFormatErr));
}

