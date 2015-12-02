#include <unistd.h>
#include "dc/export/AllExport.hh"
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoParameterPortWrap.hh"
#include "dc/neo/ccafe-bind/NeoParameterPortPC.hh"
#include "util/IO.h"


//----------------------------------------------------------
//
NeoParameterPortPC::NeoParameterPortPC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("NeoParameterPortPC CTOR");
#endif
}

NeoParameterPortPC::~NeoParameterPortPC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("NeoParameterPortPC DTOR");
#endif
}

neo::cca::Port *
NeoParameterPortPC::convert( ::ccafeopq::Port * op) {
	ccafeopq::ports::ParameterPort *opp = 
		dynamic_cast< ccafeopq::ports::ParameterPort * >(op);
	if (opp == 0) {
		IO_en1("NeoParameterPortPC: fails to cast ::ccafeopq::Port * "
	       "to a ::ccafeopq::ports::ParameterPort *, returning nil");
		return  0;
	}
	NeoParameterPortWrap *nbsPort = 
		new NeoParameterPortWrap(opp);
	neo::cca::Port *p = nbsPort; // cast
	return p;
}

