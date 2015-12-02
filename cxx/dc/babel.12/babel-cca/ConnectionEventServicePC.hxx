#ifndef __ConnectionEventServicePCPT_HH__
#define __ConnectionEventServicePCPT_HH__

#include <unistd.h>
#include "dc/export/AllExport.hh"
#include "dc/framework/KernelPort.h"

class ConnectionEventServicePC : public virtual PortConverter {
private:
public:
  virtual ~ConnectionEventServicePC(){}

  virtual gov::cca::Port convert( ::ccafeopq::Port * op) {
    ccafeopq::ports::ConnectionEventService *oces = 
      dynamic_cast< ::ccafeopq::ports::ConnectionEventService * >(op);
    if (oces == 0) {
	IO_en1("ConnectionEventServicePC: fails to cast ::ccafeopq::Port * "
	       "to a ::ccafeopq::ports::ConnectionEventService *. Returning nil port");
	return  gov::cca::Port();
    }
    ccaffeine::ports::ConnectionEventServiceWrap cesPort = 
      ccaffeine::ports::ConnectionEventServiceWrap::_create();
    cesPort.initialize(oces);
    gov::cca::Port p = cesPort; // cast
    return p;
  }

};

#endif // __ConnectionEventServicePCPT_HH__
