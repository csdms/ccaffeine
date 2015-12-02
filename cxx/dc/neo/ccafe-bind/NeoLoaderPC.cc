#include <unistd.h>
#include "dc/export/AllExport.hh"
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoLoaderWrap.hh"
#include "dc/neo/ccafe-bind/NeoLoaderPC.hh"
#include "util/IO.h"


//----------------------------------------------------------
//
NeoLoaderPC::NeoLoaderPC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("NeoLoaderPC CTOR");
#endif
}

NeoLoaderPC::~NeoLoaderPC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("NeoLoaderPC DTOR");
#endif
}

neo::cca::Port *
NeoLoaderPC::convert( ::ccafeopq::Port * op) {
	ccafeopq::ComponentFactory *opp = 
		dynamic_cast< ccafeopq::ComponentFactory * >(op);
	if (opp == 0) {
		IO_en1("NeoLoaderPC: fails to cast ::ccafeopq::Port * "
	       "to a ::ccafeopq::ComponentFactory *, returning nil");
		return  0;
	}
	NeoLoaderWrap *nbsPort = new NeoLoaderWrap(opp);
	neo::cca::Port *p = nbsPort; // cast
	return p;
}

