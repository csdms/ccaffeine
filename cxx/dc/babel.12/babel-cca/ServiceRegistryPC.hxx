#ifndef __ServiceRegistryPCPT_HH__
#define __ServiceRegistryPCPT_HH__

#include <unistd.h>
#include "dc/export/AllExport.hh"
#include "dc/babel.12/babel-cca/AllBabelCCA.hxx"

class ServiceRegistryPC : public virtual PortConverter {
private:
	ccafeopq::ComponentID_shared cid;
public:
  virtual ~ServiceRegistryPC(){}

  void initialize(ccafeopq::ComponentID_shared c)
  {
	  cid = c;
  }
  virtual gov::cca::Port convert(::ccafeopq::Port * op) {
    ccafeopq::ServiceRegistry *opp = dynamic_cast< ccafeopq::ServiceRegistry * >(op);
    if (opp == 0) {
	IO_en1("ServiceRegistryPC: fails to cast ::ccafeopq::Port * "
	       "to a ::ccafeopq::ServiceRegistry *, returning nil");
	return  gov::cca::Port();
    }
    ccaffeine::ports::ServiceRegistryWrap bsPort = 
      ccaffeine::ports::ServiceRegistryWrap::_create();
    void * vp = static_cast<void *>(&cid);
    bsPort.initialize(opp, vp); // fixme?
    gov::cca::Port p = bsPort; // CAST
    return p;
  }

};

#endif // __ServiceRegistryPCPT_HH__
