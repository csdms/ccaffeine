#ifndef LongJC_h_seen
#define LongJC_h_seen

namespace jcpp {

// requires
// #include "jc++/jc++.h"
// #include "jc++/lang/Object.h"

/** long container ala java */
class LongJC : public virtual Object {

private:
  long long value;

  static char forDigit(long long digit, int radix);

/** completely buggy. java >>>= is what in c? */
  static char *toUnsignedString(long long i, int bits);

public:

  LongJC(char *s, int & NumberFormatErr);

  LongJC(long long value_);

  double doubleValue();

  boolean equals(Object *obj);

  float floatValue();

  /** we round to nearest int infinity if int is overflowed. */
  int intValue(int & rangeError);

  long long longValue();

  CFREE char *toString();

  static long long parseLong(char * s, int & NumberFormatErr);

  static CFREE char *toBinaryString(long long i);

  static CFREE char *toHexString(long long i);

  static CFREE char *toOctalString(long long i);

  static CFREE char *toString(long long i);

  static CFREE char *toString(long long i, int radix);

  static LongJC *valueOf(char * s, int & NumberFormatErr);

};

} ENDSEMI //jcpp
#endif // LongJC_h_seen
