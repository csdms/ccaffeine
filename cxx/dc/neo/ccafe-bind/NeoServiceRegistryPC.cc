#include <unistd.h>
#include "dc/export/AllExport.hh"
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoServiceRegistryWrap.hh"
#include "dc/neo/ccafe-bind/NeoServiceRegistryPC.hh"
#include "util/IO.h"


//----------------------------------------------------------
//
NeoServiceRegistryPC::NeoServiceRegistryPC(ccafeopq::ComponentID_shared c)
{
	cid = c;
#ifdef CCAFE_AUDIT
	IO_dn1("NeoServiceRegistryPC CTOR");
#endif
}

NeoServiceRegistryPC::~NeoServiceRegistryPC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("NeoServiceRegistryPC DTOR");
#endif
}

neo::cca::Port *
NeoServiceRegistryPC::convert( ::ccafeopq::Port * op) {
	ccafeopq::ServiceRegistry *opp = 
		dynamic_cast< ccafeopq::ServiceRegistry * >(op);
	if (opp == 0) {
		IO_en1("NeoServiceRegistryPC: fails to cast ::ccafeopq::Port * "
	       "to a ::ccafeopq::ServiceRegistry *, returning nil");
		return  0;
	}
	NeoServiceRegistryWrap *nbsPort = 
		new NeoServiceRegistryWrap(opp,cid);
	neo::cca::Port *p = nbsPort; // cast
	return p;
}

