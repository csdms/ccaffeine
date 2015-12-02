#ifndef __OPPFTEST_H__
#define __OPPFTEST_H__

/**
Uses opq ParameterPortFactory in response to its GoPort. 
For testing purposes only. Do NOT copy the code
used to implement this class -- it depends on internal
framework interfaces that are highly subject to change
and will NOT be supported in future versions.

REPEAT:
Don't do anything like this component when writing
your own. This service (PPF) is not yet ported to 
classic space, just hacked there.
*/

class OPPFTest : public virtual classic::gov::cca::Component, public virtual classic::gov::cca::GoPort {

private:

  classic::gov::cca::Services *myCore;
  classic::gov::cca::StringConsumerPort *out;
  classic::gov::cca::JPrintfPort *pfp;
  ::ccafeopq::ports::ParameterPortFactory *ppf;
  int numtests;

  std::vector< ::ccafeopq::TypeMap_shared > pplist;

public:

  OPPFTest();
  virtual ~OPPFTest();
  virtual void setServices(classic::gov::cca::Services *cc);
  /** This generates parameter ports, and removes them. */
  virtual int go();

};


#endif //__OPPFTEST_H__
