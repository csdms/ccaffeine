#include <vector>
#include <map>
#include <string>
#include <unistd.h>

#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_support.hh"
#include "dc/framework/KernelPort.h"
#include "util/IO.h"
#include "dc/framework/OpqAbstractFramework.h"

namespace {
char id[]=
"$Id: OpqAbstractFramework.cxx,v 1.7 2006/07/31 23:48:37 baallan Exp $";
} ENDSEMI

#define CCAFE_FRAME_PRIVATE_OK
#include "dc/framework/Frame.h"

// require frame be set.
#define CHECKFRAME(s) checkFrame(s)

void ccafe::AbstractFramework::checkFrame(const char *s)
{
  if (f == 0) { 
	  ::std::cerr <<"ccafe::AbstractFramework::" << s 
		  << " frame not set." << ::std::endl;
  } 
  assert(f != 0);
}

void ccafe::AbstractFramework::initWithString( const ::std::string & arg)
{
	CHECKFRAME("initWithString");
	f->initialize(arg);
}

void ccafe::AbstractFramework::initWithArgv( const char **argv, int argc)
{
	CHECKFRAME("initWithArgv");
	exit(1); // FIXME not supported yet.
}

ccafe::AbstractFramework::AbstractFramework(int64_t fComm, bool useComm)
{
	f = new ccafe::Frame(fComm,useComm);
	IO_dn3("ccafe::AbstractFramework::AbstractFramework(%d,%s)",(int)fComm,(useComm?"TRUE":"FALSE"));
	if (useComm) {
		fortranMPIComm = fComm;
	}
	hasComm = useComm;
}

ccafe::AbstractFramework::~AbstractFramework()
{
	// double check shutdown here. FIXME
	delete f;
	f = 0;
}

::ccafeopq::TypeMap_shared ccafe::AbstractFramework::createTypeMap()
{
	// done
	CHECKFRAME("createTypeMap");
	return f->createTypeMap();
}


::ccafeopq::Services *ccafe::AbstractFramework::getServices(const std::string & selfInstanceName, const std::string & selfClassName, ::ccafeopq::TypeMap_shared selfProperties)
{
	// done
	CHECKFRAME("getServices(i,c,tm)");
	return f->getServices(selfInstanceName, selfClassName, selfProperties);
}

::ccafeopq::Services *ccafe::AbstractFramework::getServices(const std::string & selfInstanceName, const std::string & selfClassName)
{
	// done
	CHECKFRAME("getServices(i,c)");
	::ccafeopq::TypeMap_shared dummy;
	return getServices(selfInstanceName, selfClassName, dummy);
}

void ccafe::AbstractFramework::releaseServices( ::ccafeopq::Services * svc)
{
	// done
	CHECKFRAME("releaseServices");
	f->releaseServices(svc);
}

void ccafe::AbstractFramework::shutdownFramework()
{
	CHECKFRAME("shutdownFramework");
	f->shutdownFramework();
	// more? FIXME
}

::ccafeopq::AbstractFramework * ccafe::AbstractFramework::createEmptyFramework()
{
	// done
	ccafe::AbstractFramework *caf = 0;
	::ccafeopq::AbstractFramework *oaf = 0;
	caf = new ::ccafe::AbstractFramework(fortranMPIComm,hasComm);
	oaf = caf;
	return oaf;
}

void ccafe::AbstractFramework::destroyEmptyFramework( ::ccafeopq::AbstractFramework * subframe)
{
	// check is it ours?
	if (subframe == 0) { return; }
	ccafe::AbstractFramework *ours;
	ours = dynamic_cast< ccafe::AbstractFramework * >(subframe);
	if (!ours) {
		// whine bitterly
		return;
	}
	// was it shutdown?
	// whack it.
	// FIXME
}

