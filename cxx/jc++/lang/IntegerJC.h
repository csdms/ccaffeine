#ifndef IntegerJC_h_seen
#define IntegerJC_h_seen

namespace jcpp {

// requires
// #include "jc++/jc++.h"
// #include "jc++/lang/Object.h"
/** integer container ala java. buggy in printing nondecimal. */
class IntegerJC : public virtual Object {

private:
  int value;

  static char forDigit(int digit, int radix);

/** completely buggy. java >>>= is what in c? */
  static char *toUnsignedString(int i, int bits);

public:

  IntegerJC(char *s, int & NumberFormatErr);

  IntegerJC(int value_);

  double doubleValue();

  boolean equals(Object *obj);

  float floatValue();

  int intValue();

  long longValue();

  CFREE char *toString();

  /** You get strtol(s,x,0) behavior, likeit or lumpit.
   Except we round down to INT_MAX/MIN if needed.*/
  static int parseInt(char * s, int & NumberFormatErr);

// completely buggy. java >>>= is what in c?
  static CFREE char *toBinaryString(int i);

// completely buggy. java >>>= is what in c?
  static CFREE char *toHexString(int i);

// completely buggy. java >>>= is what in c?
  static CFREE char *toOctalString(int i);

  static CFREE char *toString(int i);

// completely buggy. java >>>= is what in c?
  static CFREE char *toString(int i, int radix);

  static IntegerJC *valueOf(char * s, int & NumberFormatErr);

};

} ENDSEMI //jcpp

#endif // IntegerJC_h_seen
