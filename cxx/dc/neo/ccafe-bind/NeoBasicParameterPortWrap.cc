#include <neocca.hh>
#include <neoports.hh>
#include <dc/export/AllExport.hh>

#include "dc/neo/ccafe-bind/ccafeTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoBasicParameterPortWrap.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoServicesHelper.hh"
#include "dc/neo/ccafe-bind/NeoHelper.hh"
#include "dc/neo/ccafe-bind/NeoMacros.hh"

int NeoBasicParameterPortWrap::genSerial = 0;

NeoBasicParameterPortWrap::NeoBasicParameterPortWrap(int bogon)
{
	opp = 0;
	serial = 0;
}

NeoBasicParameterPortWrap::NeoBasicParameterPortWrap( ccafeopq::ports::BasicParameterPort *obpp )
{
  opp = obpp;
#ifdef CCAFE_AUDIT
  serial = nextNum();
  IO_dn2("NeoBasicParameterPortWrap CTOR %d", serial);
#endif
}

NeoBasicParameterPortWrap::~NeoBasicParameterPortWrap()
{
#ifdef CCAFE_AUDIT
  serial = -serial;
  IO_dn2("NeoBasicParameterPortWrap DTOR %d", serial);
#endif
  opp = 0;
}

neo::cca::TypeMap_shared
NeoBasicParameterPortWrap::readConfigurationMap() 
throw ( ::neo::cca::Exception )
{
	checkthrow("readConfigurationMap");
	ccafeopq::TypeMap_shared otm;
	try {
		otm = opp->readConfigurationMap();
	}
	NEO_RETHROW_PREPEND("NeoBasicParameterPortWrap::writeConfigurationMap: ");
	neo::cca::TypeMap_shared btm;
	btm = ccafe::TypeMap::neoWrap(otm);
	return btm;
}

void
NeoBasicParameterPortWrap::writeConfigurationMap( ::neo::cca::TypeMap_shared map ) 
throw ( ::neo::cca::Exception)
{
	checkthrow("writeConfigurationMap");
	N2OMAP(map,ctm);
	try {
		opp->writeConfigurationMap(ctm);
	}
	NEO_RETHROW_PREPEND("NeoBasicParameterPortWrap::writeConfigurationMap: ");
}

::std::vector< ::std::string>
NeoBasicParameterPortWrap::readConfigurationKeys () 
throw () 
{
	checkthrow("readConfigurationKeys");
	std::vector< std::string > svec;
	try {
		svec = opp->readConfigurationKeys();
	}
	NEO_RETHROW_PREPEND("NeoBasicParameterPortWrap::writeConfigurationMap: ");
	return svec;
}

void 
NeoBasicParameterPortWrap::checkthrow(const char *funcName)
{
	NeoServicesHelper::checkthrow("NeoBasicParameterPortWrap", "opp", 
		static_cast<void *>(opp), funcName);
}

