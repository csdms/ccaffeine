#ifndef LongParameter_h_seen
#define LongParameter_h_seen
// package parameters;

//requires
//#include "parameters/BaseParameter.h"

/**  This interface is DEPRECATED.
Long integer parameter class. */
class LongParameter : public virtual BaseParameter {

public:
  long low;
  long high;
  long Default;
  char *name;
  char *help;
  char *prompt;
  long value;

  LongParameter(char *name_, char *help_, char *prompt_, long Default_, long low_, long high_) ;

  ~LongParameter();

  int setValue(char *val);

  /*CFREE*/ virtual char *toString() ;
  /*CFREE*/ virtual char *toString(char *infix);


  char *getName() { return name; }

  char *getValueString();
};
#endif // LongParameter_h_seen
