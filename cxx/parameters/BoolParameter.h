#ifndef BoolParameter_h_seen
#define BoolParameter_h_seen
// package parameters;


//requires
//#include "parameters/BaseParameter.h"

/** This interface is DEPRECATED.
 Boolean parameter class. */
class BoolParameter : public virtual BaseParameter {

public:
  bool Default;
  char *help;
  char *prompt;
  bool value;

    /** Good implementations will take the following, if prompting for text
     (case insensitive, of course):
    /// 0 <-- no, nyet, zip, nada, f, FALSE, 0, n, wrong, buzz
    /// 1 <-- yes, da, yep, y, si, t, TRUE, 1, right, correct, ok, ding! */
  virtual int setValue(char *val);
 
  BoolParameter(char *name_, char *help_, char *prompt_, bool Default_);
  ~BoolParameter() {}
 
  virtual char *toString();
  virtual char *toString(char *infix);

  char *getName() { return name; }
  char *getValueString();

private:
  char *getValueString(bool v);
};
#endif // BoolParameter_h_seen
