#include <neocca.hh>
#include <neoports.hh>
#include <dc/export/AllExport.hh>

#include "dc/neo/ccafe-bind/NeoParameterPortWrap.hh"
#include "dc/neo/ccafe-bind/ccafeTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoServicesHelper.hh"
#include "dc/neo/ccafe-bind/NeoHelper.hh"
#include "dc/neo/ccafe-bind/NeoMacros.hh"

int NeoParameterPortWrap::genSerial = 0;

NeoParameterPortWrap::NeoParameterPortWrap( int bogon )
{
	opp  = 0;
}

NeoParameterPortWrap::NeoParameterPortWrap( ccafeopq::ports::ParameterPort *copp)
{
	opp = copp;
#ifdef CCAFE_AUDIT
	serial = nextNum();
	IO_dn2("NeoParameterPortWrap CTOR %d", serial);
#endif
}

NeoParameterPortWrap::~NeoParameterPortWrap()
{
#ifdef CCAFE_AUDIT
	serial = -serial;
	IO_dn2("NeoParameterPortWrap DTOR %d", serial);
#endif
	opp = 0;
}


neo::cca::TypeMap_shared
NeoParameterPortWrap::readConfigurationMap() 
throw ( ::neo::cca::Exception )
{
	checkthrow("readConfigurationMap");
	ccafeopq::TypeMap_shared otm;
	try {
		otm = opp->readConfigurationMap();
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readConfigurationMap: ");

	neo::cca::TypeMap_shared btm;
	btm = ccafe::TypeMap::neoWrap(otm);
	return btm;
}

void
NeoParameterPortWrap::writeConfigurationMap( ::neo::cca::TypeMap_shared map ) 
throw ( ::neo::cca::Exception)
{
	checkthrow("writeConfigurationMap");

	N2OMAP(map, otm);

	try {
		opp->writeConfigurationMap(otm);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::writeConfigurationMap: ");
}

::std::vector< ::std::string>
NeoParameterPortWrap::readConfigurationKeys () 
throw ( ::neo::cca::Exception)
{
	checkthrow("readConfigurationKeys");
	std::vector< std::string > svec;
	try {
		svec = opp->readConfigurationKeys();
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readConfigurationKeys: ");
	return svec;
}

void 
NeoParameterPortWrap::checkthrow(const char *funcName)
{
	NeoServicesHelper::checkthrow("NeoParameterPortWrap", "opp",
		       	static_cast<void *>(opp), funcName);
}



std::string 
NeoParameterPortWrap::readTitle()
{
	std::string result;
	try {
		result = opp->readTitle();
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readTitle: ");
	return result;
}

std::vector< std::string >
NeoParameterPortWrap::readGroupNames()
{
	std::vector< std::string > result;
	try {
		result = opp->readGroupNames();
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readGroupNames: ");
	return result;
}

std::string 
NeoParameterPortWrap::readGroupTitle( const std::string & groupName)
{
	std::string result;
	try {
		result = opp->readGroupTitle(groupName);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readGroupTitle: ");
	return result;
}

std::vector< std::string > 
NeoParameterPortWrap::readGroupKeys( const std::string & groupName )
{
	std::vector< std::string > result;
	try {
		result = opp->readGroupKeys(groupName);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readGroupKeys: ");
	return result;
}

std::string 
NeoParameterPortWrap::readHelp( const std::string & key)
{
	std::string result;
	try {
		result = opp->readHelp(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readHelp: ");
	return result;
}

std::string 
NeoParameterPortWrap::readPrompt( const std::string & key)
{
	std::string result;
	try {
		result = opp->readPrompt(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readPrompt: ");
	return result;
}

bool
NeoParameterPortWrap::hasBounds( const std::string & key)
{
	bool result;
	try {
		result = opp->hasBounds(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::hasBounds: ");
	return result;
}

bool 
NeoParameterPortWrap::hasChoices( const std::string & key)
{
	bool result;
	try {
		result = opp->hasChoices(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::hasChoices: ");
	return result;
}

bool 
NeoParameterPortWrap::readDefaultBoolean( const std::string & key)
{
	bool result;
	try {
		result = opp->readDefaultBoolean(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultBoolean: ");
	return result;
}

std::string 
NeoParameterPortWrap::readDefaultString ( const std::string & key)
{
	std::string result;
	try {
		result = opp->readDefaultString(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultString: ");
	return result;
}

int32_t 
NeoParameterPortWrap::readDefaultInt( const std::string & key)
{
	int32_t result;
	try {
		result = opp->readDefaultInt(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultInt: ");
	return result;
}

int64_t
NeoParameterPortWrap::readDefaultLong( const std::string & key)
{
	int64_t result;
	try {
		result = opp->readDefaultLong(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultLong: ");
	return result;
}

float 
NeoParameterPortWrap::readDefaultFloat ( const std::string & key)
{
	float result;
	try {
		result = opp->readDefaultFloat(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultFloat: ");
	return result;
}

double 
NeoParameterPortWrap::readDefaultDouble( const std::string & key)
{
	double result;
	try {
		result = opp->readDefaultDouble(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultDouble: ");
	return result;
}

std::complex<float> 
NeoParameterPortWrap::readDefaultFcomplex( const std::string & key)
{
	std::complex<float> result;
	try {
		result = opp->readDefaultFcomplex(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultFcomplex: ");
	return result;
}

std::complex<double> 
NeoParameterPortWrap::readDefaultDcomplex( const std::string & key)
{
	std::complex<double> result;
	try {
		result = opp->readDefaultDcomplex(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultDcomplex: ");
	return result;
}

std::vector< std::string > 
NeoParameterPortWrap::readDefaultStringArray( const std::string & key)
{
	std::vector< std::string > result;
	try {
		result = opp->readDefaultStringArray(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultStringArray: ");
	return result;
}

std::vector< bool > 
NeoParameterPortWrap::readDefaultBooleanArray( const std::string & key)
{
	std::vector< bool > result;
	try {
		result = opp->readDefaultBooleanArray(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultBooleanArray: ");
	return result;
}

std::vector< int32_t > 
NeoParameterPortWrap::readDefaultIntArray( const std::string & key)
{
	std::vector< int32_t > result;
	try {
		result = opp->readDefaultIntArray(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultIntArray: ");
	return result;
}

std::vector< int64_t > 
NeoParameterPortWrap::readDefaultLongArray( const std::string & key)
{
	std::vector< int64_t > result;
	try {
		result = opp->readDefaultLongArray(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultLongArray: ");
	return result;
}

std::vector< float > 
NeoParameterPortWrap::readDefaultFloatArray( const std::string & key)
{
	std::vector< float > result;
	try {
		result = opp->readDefaultFloatArray(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultFloatArray: ");
	return result;
}

std::vector< double > 
NeoParameterPortWrap::readDefaultDoubleArray( const std::string & key)
{
	std::vector< double > result;
	try {
		result = opp->readDefaultDoubleArray(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultDoubleArray: ");
	return result;
}

std::vector< std::complex<float> > 
NeoParameterPortWrap::readDefaultFcomplexArray( const std::string & key)
{
	std::vector<  std::complex<float> > result;
	try {
		result = opp->readDefaultFcomplexArray(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultFcomplexArray: ");
	return result;
}

std::vector< std::complex<double> > 
NeoParameterPortWrap::readDefaultDcomplexArray( const std::string & key)
{
	std::vector<  std::complex<double> > result;
	try {
		result = opp->readDefaultDcomplexArray(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readDefaultDcomplexArray: ");
	return result;
}
	
void 
NeoParameterPortWrap::readBoundsInt(const std::string & key, int32_t & low, int32_t & high)
{
	try {
		opp->readBoundsInt(key, low, high);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readBoundsInt: ");
}

void 
NeoParameterPortWrap::readBoundsLong(const std::string & key, int64_t & low, int64_t & high)
{
	try {
		opp->readBoundsLong(key, low, high);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readBoundsLong: ");
}

void 
NeoParameterPortWrap::readBoundsFloat(const std::string & key, float & low, float & high)
{
	try {
		opp->readBoundsFloat(key, low, high);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readBoundsFloat: ");
}

void 
NeoParameterPortWrap::readBoundsDouble(const std::string & key, double & low, double & high)
{
	try {
		opp->readBoundsDouble(key, low, high);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readBoundsDouble: ");
}

std::vector< std::string > 
NeoParameterPortWrap::readChoicesString(const std::string & key)
{
	std::vector< std::string > result;
	try {
		result = opp->readChoicesString(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readChoicesString: ");
	return result;
}

std::vector< int32_t > 
NeoParameterPortWrap::readChoicesInt(const std::string & key)
{
	std::vector< int32_t > result;
	try {
		result = opp->readChoicesInt(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readChoicesInt: ");
	return result;
}

std::vector< int64_t > 
NeoParameterPortWrap::readChoicesLong(const std::string & key)
{
	std::vector< int64_t > result;
	try {
		result = opp->readChoicesLong(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readChoicesLong: ");
	return result;
}

std::vector< float > 
NeoParameterPortWrap::readChoicesFloat(const std::string & key)
{
	std::vector< float > result;
	try {
		result = opp->readChoicesFloat(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readChoicesFloat: ");
	return result;
}

std::vector< double > 
NeoParameterPortWrap::readChoicesDouble(const std::string & key)
{
	std::vector< double > result;
	try {
		result = opp->readChoicesDouble(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readChoicesDouble: ");
	return result;
}

std::vector< std::complex<float> > 
NeoParameterPortWrap::readChoicesFcomplex(const std::string & key)
{
	std::vector< std::complex<float> > result;
	try {
		result = opp->readChoicesFcomplex(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readChoicesFcomplex: ");
	return result;
}

std::vector< std::complex<double> > 
NeoParameterPortWrap::readChoicesDcomplex(const std::string & key)
{
	std::vector< std::complex<double> > result;
	try {
		result = opp->readChoicesDcomplex(key);
	}
	NEO_RETHROW_PREPEND("NeoParameterPortWrap::readChoicesDcomplex: ");
	return result;
}

