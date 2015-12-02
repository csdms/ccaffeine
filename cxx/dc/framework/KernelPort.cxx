#include "dc/export/AllExport.hh"
#include "dc/framework/KernelPort.h"
#include "util/IO.h"

int KernelPort::kernel_nextNum = 0;

KernelPort::~KernelPort()
{
	kernel_num = -kernel_num;
	IO_dn2("KernelPort destroyed %d", kernel_num);
}

KernelPort::KernelPort()
{
	kernel_nextNum++;
	kernel_num = kernel_nextNum;
	IO_dn1("KernelPort::KernelPort() CTOR");
	// calling initKernel here doesn't do what we want.
}

void
KernelPort::initKernel()
{
	 //ccafeopq::support::Port::addSupportedKind( ::ccafeopq::OPAQUE_PORT );
	addSupportedKind( ::ccafeopq::OPAQUE_PORT );
}
