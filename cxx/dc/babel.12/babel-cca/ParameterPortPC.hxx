#ifndef __ParameterPortPCPT_HH__
#define __ParameterPortPCPT_HH__

#include <unistd.h>
#include "dc/export/AllExport.hh"
// #include "dc/framework/KernelPort.h"
#include "dc/babel.12/babel-cca/AllBabelCCA.hxx"
//#include "dc/classic/ccafe-bind/AllCcafeBind.hh"

class ParameterPortPC : public virtual PortConverter {
private:
public:
  virtual ~ParameterPortPC(){}

  virtual gov::cca::Port convert(::ccafeopq::Port * op) {
    ccafeopq::ports::ParameterPort *opp = dynamic_cast< ccafeopq::ports::ParameterPort * >(op);
    if (opp == 0) {
	IO_en1("ParameterPortPC: fails to cast ::ccafeopq::Port * "
	       "to a ::ccafeopq::ports::ParameterPort *, returning nil");
	return  gov::cca::Port();
    }
    ccaffeine::ports::ParameterPortWrap bsPort = 
      ccaffeine::ports::ParameterPortWrap::_create();
    bsPort.initialize(opp);
    gov::cca::Port p = bsPort; // cast
    return p;
  }

};

class BasicParameterPortPC : public virtual PortConverter {
private:
public:
  virtual ~BasicParameterPortPC(){}

  virtual gov::cca::Port convert(::ccafeopq::Port * op) {
    ccafeopq::ports::BasicParameterPort *opp = dynamic_cast< ccafeopq::ports::BasicParameterPort * >(op);
    if (opp == 0) {
	IO_en1("BasicParameterPortPC: fails to cast ::ccafeopq::Port * "
	       "to a ::ccafeopq::ports::BasicParameterPort *, returning nil");
	return  gov::cca::Port();
    }
    ccaffeine::ports::BasicParameterPortWrap bsPort = 
      ccaffeine::ports::BasicParameterPortWrap::_create();
    bsPort.initialize(opp);
    gov::cca::Port p = bsPort; // cast
    return p;
  }

};

#endif // __ParameterPortPCPT_HH__
