#include <unistd.h>
#include "dc/export/AllExport.hh"
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoParameterPortFactoryWrap.hh"
#include "dc/neo/ccafe-bind/NeoParameterPortFactoryPC.hh"
#include "util/IO.h"


//----------------------------------------------------------
//
NeoParameterPortFactoryPC::NeoParameterPortFactoryPC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("NeoParameterPortFactoryPC CTOR");
#endif
}

NeoParameterPortFactoryPC::~NeoParameterPortFactoryPC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("NeoParameterPortFactoryPC DTOR");
#endif
}

neo::cca::Port *
NeoParameterPortFactoryPC::convert( ::ccafeopq::Port * op) {
	ccafeopq::ports::ParameterPortFactory *opp = 
		dynamic_cast< ccafeopq::ports::ParameterPortFactory * >(op);
	if (opp == 0) {
		IO_en1("NeoParameterPortFactoryPC: fails to cast ::ccafeopq::Port * "
	       "to a ::ccafeopq::ports::ParameterPort *, returning nil");
		return  0;
	}
	NeoParameterPortFactoryWrap *nbsPort = 
		new NeoParameterPortFactoryWrap(opp);
	neo::cca::Port *p = nbsPort; // cast
	return p;
}

