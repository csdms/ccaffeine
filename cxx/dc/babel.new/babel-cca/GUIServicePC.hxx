#ifndef __GUIServicePCPT_HH__
#define __GUIServicePCPT_HH__

#include <unistd.h>
#include "dc/export/AllExport.hh"
#include "dc/babel.new/babel-cca/AllBabelCCA.hxx"

class GUIServicePC : public virtual PortConverter {
private:
	ccafeopq::ComponentID_shared cid;
public:
  virtual ~GUIServicePC(){}

  virtual gov::cca::Port convert(::ccafeopq::Port * op) {
    ccafeopq::GUIService *opp = dynamic_cast< ccafeopq::GUIService * >(op);
    if (opp == 0) {
	IO_en1("GUIServicePC: fails to cast ::ccafeopq::Port * "
	       "to a ::ccafeopq::GUIService *, returning nil");
	return  gov::cca::Port();
    }
    ccaffeine::ports::GUIServiceWrap gsPort = 
      ccaffeine::ports::GUIServiceWrap::_create();
    // void * vp = static_cast<void *>(&cid);
    gsPort.initialize(opp);
    gov::cca::Port p = gsPort; // CAST
    return p;
  }

};

#endif // __GUIServicePCPT_HH__
