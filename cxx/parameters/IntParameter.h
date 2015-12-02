#ifndef IntParameter_h_seen
#define IntParameter_h_seen
// package parameters;

//requires
//#include "parameters/BaseParameter.h"

/**  This interface is DEPRECATED.
integer parameter class. */
class IntParameter : public virtual BaseParameter {

public:
  int low;
  int high;
  int Default;
  char *name;
  char *help;
  char *prompt;
  int value;

  IntParameter(char *name_, char *help_, char *prompt_, int Default_, int low_, int high_) ;

  ~IntParameter();

  int setValue(char *val);

  /*CFREE*/ virtual char *toString() ;
  /*CFREE*/ virtual char *toString(char *infix);


  char *getName() { return name; }

  char *getValueString();
};
#endif // IntParameter_h_seen
