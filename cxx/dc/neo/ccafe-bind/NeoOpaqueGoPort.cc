#include <neocca.hh>
#include <neoports.hh>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/framework/KernelPort.h"
#include "dc/neo/ccafe-bind/NeoOpaquePort.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueGoPort.hh"

int NeoOpaqueGoPort::goNextNum = 0;

NeoOpaqueGoPort::~NeoOpaqueGoPort()
{
	goNum = -goNum;
	IO_dn2("NeoOpaqueGoPort destroyed %d", goNum);
}

NeoOpaqueGoPort::NeoOpaqueGoPort(neo::cca::ports::GoPort *gp_) :
  NeoOpaquePort(gp_)
{
	goNextNum++;
	goNum = goNextNum;
	IO_dn2("NeoOpaqueGoPort created %d", goNum);
#ifdef CCAFE_AUDIT
  // IO_dn1("NeoOpaqueGoPort::NeoOpaqueGoPort(gp): done initNeo");
#endif
  initKernel();
#ifdef CCAFE_AUDIT
  IO_dn1("NeoOpaqueGoPort::NeoOpaqueGoPort(gp): done initKernel");
#endif

}

int 
NeoOpaqueGoPort::go() {
	::neo::cca::Port *cp = getNeoPort();
	if(cp) {
		neo::cca::ports::GoPort * p = 0;
		p = dynamic_cast<neo::cca::ports::GoPort*>(cp);
		if (p) {
			return p->go();
		} else {
			IO_dn1(":-( NeoOpaqueGoPort::go: neo port not goport.");
			return -1;
		}
	} else {
		IO_dn1(":-( NeoOpaqueGoPort::go: no neo port pointer found.");
		return -1;
	}
}
