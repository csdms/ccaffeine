#ifndef __ParameterPortFactoryPCPT_HH__
#define __ParameterPortFactoryPCPT_HH__

#include <unistd.h>
#include "dc/export/AllExport.hh"
#include "dc/framework/KernelPort.h"

class ParameterPortFactoryPC : public virtual PortConverter {
private:
public:
  virtual ~ParameterPortFactoryPC(){}

  virtual gov::cca::Port convert( ::ccafeopq::Port * op) {
    ccafeopq::ports::ParameterPortFactory *oppf = 
      dynamic_cast< ::ccafeopq::ports::ParameterPortFactory * >(op);
    if (oppf == 0) {
	IO_en1("ParameterPortFactoryPC: fails to cast ::ccafeopq::Port * "
	       "to a ::ccafeopq::ports::ParameterPortFactory *. Returning nil port");
	return  gov::cca::Port();
    }
    ccaffeine::ports::ParameterPortFactoryWrap ppfPort = 
      ccaffeine::ports::ParameterPortFactoryWrap::_create();
    ppfPort.initialize(oppf);
    gov::cca::Port p = ppfPort; // cast
    return p;
  }

};

#endif // __ParameterPortFactoryPCPT_HH__
