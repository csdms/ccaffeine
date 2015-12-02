#ifndef __GOTEST_H__
#define __GOTEST_H__

/**
Prints in response to its GoPort and also tries to call
on a goport it uses.. 
*/
class GoTest : public virtual classic::gov::cca::Component, 
		public virtual classic::gov::cca::GoPort {

private:

  classic::gov::cca::Services *myCore;

public:

  GoTest();
  virtual ~GoTest();

  virtual void setServices(classic::gov::cca::Services *cc);

  /** This generates printouts. */
  virtual int go();

};

#endif //__GOTEST_H__
