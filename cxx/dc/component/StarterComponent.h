#ifndef __STARTERCOMPONENT_H__
#define __STARTERCOMPONENT_H__

/**
Prints a string on its PrintfPort in response to its GoPort. 
*/

class StarterComponent : public virtual classic::gov::cca::Component, public virtual classic::gov::cca::GoPort {

private:

  classic::gov::cca::Services *myCore;
  classic::gov::cca::StringConsumerPort *out;

public:

  StarterComponent();
  virtual ~StarterComponent();
  virtual void setServices(classic::gov::cca::Services *cc);
  /** This generates a string and sends it to the connected string consumer.*/
  virtual int go();

};


#endif //__STARTERCOMPONENT_H__
