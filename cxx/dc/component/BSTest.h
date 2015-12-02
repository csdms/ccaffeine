#ifndef __BSTEST_H__
#define __BSTEST_H__

/**
Prints a string on its PrintfPort in response to its GoPort. 
*/

class BSTest : public virtual classic::gov::cca::Component, public virtual classic::gov::cca::GoPort {

private:

  classic::gov::cca::Services *myCore;
  classic::gov::cca::StringConsumerPort *out;
  classic::gov::cca::JPrintfPort *pfp;
  int numtests;

public:

  BSTest();
  virtual ~BSTest();
  virtual void setServices(classic::gov::cca::Services *cc);
  /** This generates components, connection, and runs things. */
  virtual int go();

};


#endif //__BSTEST_H__
