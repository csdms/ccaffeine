#include <AllCCA.hh>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/framework/KernelPort.h"
#include "dc/babel/ccafe-bind/BabelOpaquePort.hh"
#include "dc/babel/ccafe-bind/BabelOpaqueGoPort.hh"

BabelOpaqueGoPort::BabelOpaqueGoPort(gov::cca::ports::GoPort gp_) 
// : BabelOpaquePort(gp)
{
  gp = gp_; 
  setPort(gp); 
#ifdef CCAFE_AUDIT
  IO_dn1(" BabelOpaqueGoPort created");
#endif
  initBabel();
#ifdef CCAFE_AUDIT
  IO_dn1("BabelOpaqueGoPort::BabelOpaqueGoPort(gp): done initBabel");
#endif
    initKernel();
#ifdef CCAFE_AUDIT
    IO_dn1("BabelOpaqueGoPort::BabelOpaqueGoPort(gp): done initKernel");
#endif

}

BabelOpaqueGoPort::~BabelOpaqueGoPort()
{
#ifdef CCAFE_AUDIT
  IO_dn1(" BabelOpaqueGoPort destroyed");
#endif
}

int
BabelOpaqueGoPort::BabelOpaqueGoPort::go() {
  if(gp._not_nil()) {
    return gp.go();
  } else {
    IO_en1("! :-( Go port is nil, not doing anything");
  }
  return 0;
}

