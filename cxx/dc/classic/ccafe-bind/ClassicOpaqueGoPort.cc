#include <cca.h>
#include <stdPorts.h>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/framework/KernelPort.h"
#include "dc/classic/ccafe-bind/ClassicOpaquePort.hh"
#include "dc/classic/ccafe-bind/ClassicOpaqueGoPort.hh"

int ClassicOpaqueGoPort::goNextNum = 0;

ClassicOpaqueGoPort::~ClassicOpaqueGoPort()
{
  goNum = -goNum;
  IO_dn2("ClassicOpaqueGoPort destroyed %d", goNum);
}

ClassicOpaqueGoPort::ClassicOpaqueGoPort(classic::gov::cca::GoPort *gp_) :
  ClassicOpaquePort(gp_)
{
  goNextNum++;
  goNum = goNextNum;
  IO_dn2("ClassicOpaqueGoPort created %d", goNum);
  initClassic();
#ifdef CCAFE_AUDIT
IO_dn1("ClassicOpaqueGoPort::ClassicOpaqueGoPort(gp): done initClassic");
#endif
  initKernel();
#ifdef CCAFE_AUDIT
IO_dn1("ClassicOpaqueGoPort::ClassicOpaqueGoPort(gp): done initKernel");
#endif
}

int 
ClassicOpaqueGoPort::go() {
  ::classic::gov::cca::Port *cp = getClassicPort();
  if(cp) {
    classic::gov::cca::GoPort * p = 0;
    p = dynamic_cast<classic::gov::cca::GoPort*>(cp);
    if (p) {
    	return p->go();
    } else {
      IO_dn1(":-( classic::gov::cca::GoPort is NULL, to doing anything");
      return -1;
    }
  } else {
    IO_dn1(":-( classic::gov::cca::GoPort is NULL, to doing anything");
    return -1;
  }
}
