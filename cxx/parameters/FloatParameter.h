#ifndef FloatParameter_h_seen
#define FloatParameter_h_seen
// package parameters;

//requires
//#include "parameters/BaseParameter.h"

/**  This interface is DEPRECATED.
32 bit float parameter class. */
class FloatParameter : public virtual BaseParameter {

public:
  float low;
  float high;
  float Default;
  char *help;
  char *prompt;
  float value;

  FloatParameter(char *name_, char *help_, char *prompt_, float Default_, float low_, float high_) ;

  ~FloatParameter();

  int setValue(char *val);

  /*CFREE*/ virtual char *toString() ;
  /*CFREE*/ virtual char *toString(char *infix);


  char *getName() { return name; }

  char *getValueString();

private:
  char vstring[40];
};
#endif // FloatParameter_h_seen
