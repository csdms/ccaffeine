#include <unistd.h>
#include "dc/export/AllExport.hh"
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoBasicParameterPortWrap.hh"
#include "dc/neo/ccafe-bind/NeoBasicParameterPortPC.hh"
#include "util/IO.h"

//------------------------------------------------------

NeoBasicParameterPortPC::NeoBasicParameterPortPC(int bogon)
{
}

NeoBasicParameterPortPC::NeoBasicParameterPortPC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("NeoBasicParameterPortPC: CTOR ");
#endif
}

NeoBasicParameterPortPC::~NeoBasicParameterPortPC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("NeoBasicParameterPortPC: DTOR ");
#endif
}

neo::cca::Port *
NeoBasicParameterPortPC::convert(::ccafeopq::Port * op)
{
	ccafeopq::ports::BasicParameterPort *opp = 
		dynamic_cast< ccafeopq::ports::BasicParameterPort * >(op);
	if (opp == 0) {
		IO_en1("NeoBasicParameterPortPC: fails to cast ::ccafeopq::Port * "
		"to a ::ccafeopq::ports::BasicParameterPort *, returning nil");
		return  0;
	}
	NeoBasicParameterPortWrap *nbsPort = 
		new NeoBasicParameterPortWrap(opp);
	neo::cca::Port *p = nbsPort; 
	return p;
}

