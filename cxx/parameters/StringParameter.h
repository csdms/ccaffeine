#ifndef StringParameter_h_seen
#define StringParameter_h_seen
//package parameters;
// see parametersStar.h

#include <string>
#include <vector>
/**  This interface is DEPRECATED.
User must pick one of the Strings in choices, unless choices is empty.
 If no input, value is the empty (not NULL) String. */
class StringParameter : public virtual BaseParameter {


private:

  /** list of choices */
  std::vector< ::std::string > stringlist;

public:

  /** these pointers are owned by this object and should not
   be freed/replaced by clients. */
  /** READ_ONLY */
  char *Default;
  /** READ_ONLY */
  char *help;
  /** READ_ONLY */
  char *prompt;
  /** READ_ONLY */
  char *value;

  /** Strings input in these functions will be copied, so the caller
   remains responsible for the memory deallocation of inputs. */
  StringParameter(char *name_, char *help_, char *prompt_, char *Default_) ;
  ~StringParameter();
  int setValue(char *val);
  void addChoice(char *s);
  
  std::vector< ::std::string > getChoices();
  /*CFREE*/ char *toString() ;
  /*CFREE*/ virtual char *toString(char *infix);


  char *getName() { return name; }

  char *getValueString();
};
#endif //StringParameter_h_seen
