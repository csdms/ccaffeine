#ifndef FloatJC_h_seen
#define FloatJC_h_seen

namespace jcpp {

// requires
// #include "jc++/jc++.h"
/** float container ala java. 
  @see DoubleJC
*/
class FloatJC : public virtual Object {

private:
  float value;

public:

  // Will NOT take NULL input for s or err.
  // returns -1 in err if parse fails.
  // returns the value, or 0.0 if err.
  static float valueOf0(char *s, int & NumberFormatErrJC);

  static CFREE char *toStringWithPrecision(float value_, int precision);
  
  static CFREE char *toString(float value_);

  FloatJC(float value_);

  FloatJC(char *s, int & NumberFormatErrJC);

  float floatValue();

  CFREE char *toString();

// uses c == semantics, not javas
  boolean equals(Object *obj);
  
  double doubleValue();
// the range sanity of the next 2 is checked. returns rangeError -1 if bad.
  int intValue(int &rangeError);
  long longValue(int &rangeError);

  // NumberFormatErrJC comes back -1 if bad string.
  static FloatJC *valueOf(char *s, int & NumberFormatErrJC);

  static float parseFloat(char *s, int & NumberFormatErrJC);

};

} ENDSEMI // jcpp
#endif // FloatJC_h_seen
