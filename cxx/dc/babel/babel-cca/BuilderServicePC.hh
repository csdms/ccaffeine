#ifndef __BUILDERSERVICEPT_HH__
#define __BUILDERSERVICEPT_HH__

#include <unistd.h>
#include "dc/export/ccafeopq.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <stdPorts.h>
#endif // HAVE_CLASSIC
#include "dc/framework/dc_fwkStar.h"
#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/BuilderView.h"
#include "dc/user_iface/DefaultBuilderModel.h"
#include "dc/user_iface/CmdLineBuilderView.h"
#include "dc/user_iface/CmdLineBuilderViewMux.h"
#include "dc/framework/dc_fwkStar.h"

#include "dc/framework/KernelPort.h"
#include "dc/framework/OpqBuilderService.h"
#include "dc/babel/babel-cca/AllBabelCCA.hh"
#ifdef HAVE_CLASSIC
#include "dc/classic/ccafe-bind/AllCcafeBind.hh"
#endif // HAVE_CLASSIC

class BuilderServicePC : public virtual PortConverter {
private:
public:
  virtual ~BuilderServicePC(){}

  virtual gov::cca::Port convert(::ccafeopq::Port * op) {
    if (op->supportsKind( ccafeopq::OPAQUE_PORT) ) {
      ccafeopq::BuilderService *bsp = dynamic_cast< ccafeopq::BuilderService * >(op);
      if (!bsp) {
        IO_en1("BuilderServicePC: fails to cast ::ccafeopq::Port * "
          "to a ::ccafeopq::BuilderService *, returning null");
        return gov::cca::Port();
      }
      ccaffeine::ports::BuilderService bsPort = ccaffeine::ports::BuilderService::_create();
      bsPort.initialize( bsp );
      gov::cca::Port p = bsPort; // cast
      return p;
    } else {
      std::string ogk =  op->getKind();
      IO_en3("ccafeopq::Port of kind: %s not %s, returning a null port",
        ogk.c_str(), ::ccafeopq::OPAQUE_PORT.c_str());
      return gov::cca::Port();
    }
  }

};

#endif // __BUILDERSERVICEPT_HH__
