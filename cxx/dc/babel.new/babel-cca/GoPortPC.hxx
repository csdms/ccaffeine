#ifndef __GoPortPCPT_HH__
#define __GoPortPCPT_HH__

#include <unistd.h>
#include "dc/export/AllExport.hh"
#include "dc/babel.new/babel-cca/AllBabelCCA.hxx"

class GoPortPC : public virtual PortConverter {
private:
public:
  virtual ~GoPortPC(){}

  virtual gov::cca::Port convert(::ccafeopq::Port * op) {
    ccafeopq::GoPort *opp = dynamic_cast< ccafeopq::GoPort * >(op);
    if (opp == 0) {
	IO_en1("GoPortPC: fails to cast ::ccafeopq::Port * "
	       "to a ::ccafeopq::GoPort *, returning nil");
	return  gov::cca::Port();
    }
    ccaffeine::ports::GoPortWrap bsPort = 
      ccaffeine::ports::GoPortWrap::_create();
    bsPort.initialize(opp); 
    gov::cca::Port p = bsPort; // CAST
    return p;
  }

};

#endif // __GoPortPCPT_HH__
