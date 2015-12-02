#include <neocca.hh>
#include <neoports.hh>
#include <dc/export/AllExport.hh>

#include "dc/neo/ccafe-bind/ccafeTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoServicesHelper.hh"
#include "dc/neo/ccafe-bind/NeoGoPortWrap.hh"
#include "dc/neo/ccafe-bind/NeoComponentID.hh"
#include "dc/neo/ccafe-bind/NeoConnectionID.hh"
#include "dc/neo/ccafe-bind/NeoHelper.hh"

int NeoGoPortWrap::genSerial = 0;

NeoGoPortWrap::NeoGoPortWrap( ccafeopq::GoPort *obpp )
{
	cbs = obpp;
#ifdef CCAFE_AUDIT
	serial = nextNum();
	IO_dn2("NeoGoPortWrap CTOR %d", serial);
#endif
}
NeoGoPortWrap::NeoGoPortWrap( int bogon)
{
	cbs = 0;
	serial = 0;
}

NeoGoPortWrap::~NeoGoPortWrap()
{
#ifdef CCAFE_AUDIT
	serial = -serial;
	IO_dn2("NeoGoPortWrap DTOR %d", serial);
#endif
	cbs = 0;
}


void 
NeoGoPortWrap::checkthrow(const char *funcName)
{
	NeoServicesHelper::checkthrow("NeoGoPortWrap", "cbs", 
			static_cast<void *>(cbs), funcName);
}

#include "dc/neo/ccafe-bind/NeoMacros.hh"
#define RETHROW(s) NEO_RETHROW_PREPEND(s)


/** Get component list.
 * Memory lifecycle:
 * The vector is returned on the stack and when it goes out of scope,
 * all the ComponentID_shared take care of themselves.
 * @return a ComponentID for each component currently created.
 */
int
NeoGoPortWrap::go() 
throw ( ::neo::cca::Exception )
{
	checkthrow("go");
	try {
		int res = cbs->go();
		return res;
	}
	RETHROW("NeoGoPortWrap::go: ");


}

NeoGoPortWrap NeoGoPortWrap_test(1);
