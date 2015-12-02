#ifndef __COMPLICATEDSTARTERCOMPONENT_H__
#define __COMPLICATEDSTARTERCOMPONENT_H__

/**
Prints a string on its PrintfPort in response to its GoPort. 
*/

class ComplicatedStarterComponent : public virtual classic::gov::cca::Component, public virtual classic::gov::cca::GoPort {

private:

  classic::gov::cca::Services *myCore;
  classic::gov::cca::StringConsumerPort *out;
  classic::gov::cca::JPrintfPort *pfp;

public:

  ComplicatedStarterComponent();
  virtual ~ComplicatedStarterComponent();
  virtual void setServices(classic::gov::cca::Services *cc);
  /** This generates a string and sends it to the connected string consumer.*/
  virtual int go();

};


#endif //__COMPLICATEDSTARTERCOMPONENT_H__
