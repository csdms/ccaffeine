#ifndef DoubleJC_h_seen
#define DoubleJC_h_seen

namespace jcpp {

// requires
// #include "jc++/jc++.h"

/** double container ala java. conversion range errors
return nonzero error rangeErrors, appropriately rounded
to infinities, instead of throwing exceptions. */
class DoubleJC : public virtual Object {

private:
  double value;

public:

  /** Will NOT take NULL input for s or err.
  // returns -1 in err if parse fails.
  // returns the value, or 0.0 if err.
  */
  static double valueOf0(char *s, int & NumberFormatErrJC);

  static CFREE char *toStringWithPrecision(double value_, int precision);
  
  static CFREE char *toString(double value_);

  DoubleJC(double value_);

  DoubleJC(char *s, int & NumberFormatErr);

  double doubleValue();

  CFREE char *toString();

// uses c == semantics, not javas
  boolean equals(Object *obj);
  
  float floatValue(int & rangeError);
  int intValue(int & rangeError);
  long longValue(int & rangeError);

  static DoubleJC *valueOf(char *s, int & NumberFormatErr);

  static double parseDouble(char *s, int & NumberFormatErr);

};

} ENDSEMI //jcpp
#endif // DoubleJC_h_seen
