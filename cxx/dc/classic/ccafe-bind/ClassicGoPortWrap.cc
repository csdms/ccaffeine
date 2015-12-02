#include <cca.h>
#include <stdPorts.h>
#include <dc/export/AllExport.hh>

#include "dc/classic/ccafe-bind/ClassicPortConverter.hh"
#include "dc/classic/ccafe-bind/ClassicServicesHelper.hh"
#include "dc/classic/ccafe-bind/ClassicGoPortWrap.hh"
#include "dc/classic/ccafe-bind/ClassicComponentID.hh"

int ClassicGoPortWrap::genSerial = 0;

ClassicGoPortWrap::ClassicGoPortWrap( ccafeopq::GoPort *obpp )
{
	cbs = obpp;
#ifdef CCAFE_AUDIT
	serial = nextNum();
	IO_dn2("ClassicGoPortWrap CTOR %d", serial);
#endif
}
ClassicGoPortWrap::ClassicGoPortWrap( int bogon)
{
	cbs = 0;
	serial = 0;
}

ClassicGoPortWrap::~ClassicGoPortWrap()
{
#ifdef CCAFE_AUDIT
	serial = -serial;
	IO_dn2("ClassicGoPortWrap DTOR %d", serial);
#endif
	cbs = 0;
}


void 
ClassicGoPortWrap::checkthrow(const char *funcName)
{
	ClassicServicesHelper::checkthrow("ClassicGoPortWrap", "cbs", 
			static_cast<void *>(cbs), funcName);
}

#include "dc/classic/ccafe-bind/ClassicMacros.hh"
#define RETHROW(s) CLASSIC_RETHROW_PREPEND(s)


/** Get component list.
 * Memory lifecycle:
 * The vector is returned on the stack and when it goes out of scope,
 * all the ComponentID_shared take care of themselves.
 * @return a ComponentID for each component currently created.
 */
int
ClassicGoPortWrap::go() 
{
	checkthrow("go");
	try {
		int res = cbs->go();
		return res;
	}
	RETHROW("ClassicGoPortWrap::go: ");
	return -2;
}

ClassicGoPortWrap ClassicGoPortWrap_test(1);
