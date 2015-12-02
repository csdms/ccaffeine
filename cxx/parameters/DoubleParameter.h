#ifndef DoubleParameter_h_seen
#define DoubleParameter_h_seen
// package parameters;

//requires
//#include "parameters/BaseParameter.h"

/**  This interface is DEPRECATED.
64 bit float parameter class. */
class DoubleParameter : public virtual BaseParameter {

public:
  double low;
  double high;
  double Default;
  char *help;
  char *prompt;
  double value;

  DoubleParameter(char *name_, char *help_, char *prompt_, double Default_, double low_, double high_) ;

  ~DoubleParameter();

  int setValue(char *val);

  /*CFREE*/ virtual char *toString() ;
  /*CFREE*/ virtual char *toString(char *infix);

  char *getName() { return name; }

  char *getValueString();
};
#endif // DoubleParameter_h_seen
