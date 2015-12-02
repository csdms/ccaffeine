#ifndef NO_NUMERIC_LIMITS
#include <limits>
#endif // NO_NUMERIC_LIMITS
#include "dc/export/AllExport.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#endif // HAVE_CLASSIC
#include "dc/framework/KernelPort.h"
#include "dc/port/StringableParameterPort.h"
#ifdef HAVE_CLASSIC
#include "dc/classic/ccafe-bind/ClassicOpaquePort.hh"
#endif // HAVE_CLASSIC
#include "dc/port/OpqParameterPortFactory.h"
#include "dc/port/OpqParameterPort.h"
#include "util/TypeMap.h"
#include <float.h>
#include <stdexcept>
#include <climits>

using ::std::vector;
using ::std::string;

#define GSU ::gov::sandia::util::TypeMap

// private impl stuff
namespace {

////////////////////////////////////////////////////////////
// misc typedefs 


typedef ::std::vector< string > StringVector;
typedef ::std::vector< std::complex<float> > FCVector;
typedef ::std::vector< std::complex<double> > DCVector;
typedef ::std::map< string, string > StringMap;
typedef ::std::map< string, void * > VoidPtrMap;
typedef StringVector::const_iterator SVCI;
// an empty vector for any typemap calls that need one
StringVector defaultVector; 
DCVector defaultDCVector; 
FCVector defaultFCVector; 

////////////////////////////////////////////////////////////
/*
 * The structure of the typemap data is as follows:
 * (where the stuff in all caps is actually larger
 *  strings defined below.)
 *
 * PORTNAME: The name of the parameter port that goes with this map.
 * TITLE: The name of the dialog, for UI purposes.
 * GROUPS: The names of the tabs w/in the dialog; if the
 * 	empty array, then there is just the main tab.
 * GROUPKEYS.{$group}: The sequence of the keys w/in the group.
 * {$key}: The default value per the user, until set.
 * DEFAULT.{$key}: The default value per the user.
 * BOUNDS.{$key}: For bounded values, 2 elem vector of bounds [lo,hi];
 *                For enumerated values, n elem vector of choices.
 * HELP.{$key}: The long help string.
 * PROMPT.{$key}: The short prompt string.
 * BOUNDED.{$key}: Whether the value is ranged (true) or enumerated (false).
 *                 All numbers are bounded by machine limits if not enumerated.
 *                 Unenumerated strings appear as BOUNDED=true, w/any value ok.
 * CHOICES.{$key}: string choice list of arbitrary list.
 */

string PORTNAME = "gcpPPF.Dialog.PortName";
string PUBPORTNAME = "gcpPPF.ParameterPortFactory.portName";
string TITLE = "gcpPPF.Dialog.Title";
string ALLKEYS = "gcpPPF.Dialog.AllKeys";
string GROUPS = "gcpPPF.Dialog.Group.List";
string CURGROUP = "gcpPPF.Dialog.Group.Current";
string GROUPKEYS = "gcpPPF.Dialog.Group.Keys.";
string DEFAULT = "gcpPPF.Default.";
string BOUNDS = "gcpPPF.Limits.";
string BOUNDED = "gcpPPF.Bounded.";
string CHOICES = "gcpPPF.Choices.";
string HELP = "gcpPPF.Help.";
string PROMPT = "gcpPPF.Prompt.";
string HASKEY = "gcpPPF.HasKey.";

} ENDSEMI // anonymous namespace
////////////////////////////////////////////////////////////
// private port implementation

#ifdef HAVE_CLASSIC
classic::gov::cca::Port * ccafe::ParameterPort_Impl::getClassicPort()
{
  return this;
}
#endif

const std::string & 
ccafe::ParameterPort_Impl::k_PORTNAME() 
{ return PORTNAME; }

const std::string & 
ccafe::ParameterPort_Impl::k_PUBPORTNAME()
{ return PUBPORTNAME; }

const std::string & 
ccafe::ParameterPort_Impl::k_TITLE()
{ return TITLE; }

const std::string & 
ccafe::ParameterPort_Impl::k_ALLKEYS()
{ return ALLKEYS; }

const std::string & 
ccafe::ParameterPort_Impl::k_GROUPS()
{ return GROUPS; }

const std::string & 
ccafe::ParameterPort_Impl::k_CURGROUP()
{ return CURGROUP; }

const std::string & 
ccafe::ParameterPort_Impl::k_GROUPKEYS()
{ return GROUPKEYS; }

const std::string & 
ccafe::ParameterPort_Impl::k_DEFAULT() 
{ return DEFAULT; }

const std::string &
ccafe::ParameterPort_Impl::k_CHOICES() 
{ return CHOICES; }

const std::string &
ccafe::ParameterPort_Impl::k_BOUNDED() 
{ return BOUNDED; }

const std::string &
ccafe::ParameterPort_Impl::k_BOUNDS() 
{ return BOUNDS; }

const std::string &
ccafe::ParameterPort_Impl::k_HELP()
{ return HELP; }

const std::string & 
ccafe::ParameterPort_Impl::k_PROMPT()
{ return PROMPT; }

const std::string & 
ccafe::ParameterPort_Impl::k_HASKEY()
{ return HASKEY; }

bool
ccafe::ParameterPort_Impl::hasKey( const std::string & key )
{
	if (!basiconly) {
		string paramKey = DEFAULT;
		paramKey += key;
		if ( portData->hasKey(key) && portData->hasKey(paramKey) ) {
			return true;
		}
		// IO_dn3("key %s not found or map not containing %s",key.c_str(),paramKey.c_str());
		return false;
	}
	return portData->hasKey(key);
}

int 
ccafe::ParameterPort_Impl::setConfigurationString( const std::string & key, const std::string & value)
{
	// fixme setConfigurationString
	if (!portData) { return -1; } // we're init'd
	if (!hasKey(key)) { 
	        ::gov::sandia::util::TypeMap::dump(portData);
		return -2; 
	} // key is for a parameter, not private
	std::string kts = GSU::stringType(portData, key);
	int err;
        err = GSU::putValueByStrings(portData, key, kts, value);
        return err;
}


std::string 
ccafe::ParameterPort_Impl::getConfigurationString( const std::string & prefix, const std::string & key)
{
	if (! portData) {
		std::string sb = "!DEAD OpqParameterPort_Impl";
		return sb;
	}
	if (!basiconly) {
		string n = portData->getString(PORTNAME,"");
		for (size_t j = glv.size(); j > 0; j--)
		{
			::ccafeopq::ports::ParameterGetListener_shared gl;
			gl = glv[j-1];
			gl->updateParameterPort(n);
		}
	}

	string sb;
	if ( portData->hasKey(key) ) {
		enum ccafeopq::Type kt = portData->typeOf(key);
		switch (kt)
		{
		case ccafeopq::Bool:
		case ccafeopq::Long:
		case ccafeopq::Int:
		case ccafeopq::Double:
		case ccafeopq::Float:
		case ccafeopq::Fcomplex:
		case ccafeopq::Dcomplex:
		case ccafeopq::String:
			sb += toString(prefix,portData,key);
			break;
		case ccafeopq::BoolArray:
		case ccafeopq::LongArray:
		case ccafeopq::IntArray:
		case ccafeopq::DoubleArray:
		case ccafeopq::FloatArray:
		case ccafeopq::FcomplexArray:
		case ccafeopq::DcomplexArray:
		case ccafeopq::StringArray:
			sb += toStringArray(prefix,portData,key);
			break;
		default:
			break;
		}
	}
	return sb;
}

std::string 
ccafe::ParameterPort_Impl::getConfigurationString(const string & prefix)
{
	if (! portData) {
		std::string sb = "!DEAD ParameterPort_Impl";
		return sb;
	}
/* debugging  ::gov::sandia::util::TypeMap::dump(portData); */
	if (!basiconly) {
		string n = portData->getString(PORTNAME,"");
		for (size_t j = glv.size(); j > 0; j--)
		{
			::ccafeopq::ports::ParameterGetListener_shared gl;
			gl = glv[j-1];
			gl->updateParameterPort(n);
		}
	}
	std::string sb = "newParamDialog ";
	sb += prefix;
       	sb += " "; 
	string title = readTitle();
	sb += title;
       	sb += "\n";
	vector< string  > groups = readGroupNames();

	// for all tabs
	for (size_t i = 0; i < groups.size(); i++)
	{
		string gkey = GROUPKEYS;
		gkey += groups[i];
		vector< string  > keys = readGroupKeys(groups[i]);
		sb += "newParamTab ";
		sb += prefix;
		sb += " ";
		sb += groups[i];
		sb += "\n";
		for (size_t j = 0; j < keys.size(); j++)
		{
			sb += toString(prefix,portData,keys[j]);
		}
	}
	sb += "paramEndDialog ";
	sb += prefix;
	sb += "\n";
	return sb;
}

string 
typeToString(enum ::ccafeopq::Type t)
{
	switch(t) {
		case ::ccafeopq::Bool: return "BOOL";
		case ::ccafeopq::String: return "STRING";
		case ::ccafeopq::Long: return "LONG";
		case ::ccafeopq::Int: return "INT";
		case ::ccafeopq::Float: return "FLOAT";
		case ::ccafeopq::Double: return "DOUBLE";
		case ::ccafeopq::Fcomplex: return "FCOMPLEX";
		case ::ccafeopq::Dcomplex: return "DCOMPLEX";

		case ::ccafeopq::BoolArray: return "ARRAY_BOOL";
		case ::ccafeopq::StringArray: return "ARRAY_STRING";
		case ::ccafeopq::LongArray: return "ARRAY_LONG";
		case ::ccafeopq::IntArray: return "ARRAY_INT";
		case ::ccafeopq::FloatArray: return "ARRAY_FLOAT";
		case ::ccafeopq::DoubleArray: return "ARRAY_DOUBLE";
		case ::ccafeopq::FcomplexArray: return "ARRAY_FCOMPLEX";
		case ::ccafeopq::DcomplexArray: return "ARRAY_DCOMPLEX";

		default:
		return "ERROR";
	}
}

std::string 
ccafe::ParameterPort_Impl::toStringArray( const std::string & prefix, ::ccafeopq::TypeMap_shared d, const std::string &key)
{
	// FIXME array stringification also has to be handled by gui.
	string kp = "";
	return kp;
}

std::string 
ccafe::ParameterPort_Impl::toString( const std::string & prefix, ::ccafeopq::TypeMap_shared d, const std::string &key)
{
	string kp = prefix;
	kp += " ";
	kp += key;
	kp += " ";

	string helpkey = HELP;
	helpkey += key;

	string promptkey = PROMPT;
	promptkey += key;

	string defkey = DEFAULT;
	defkey += key;

	string choicekey = CHOICES;
	choicekey += key;

	string boundkey = BOUNDS;
	boundkey += key;

	string  promptdflt, defdflt, choicedflt, bounddflt, helpdflt;
	helpdflt = readHelp(key);
	promptdflt = readPrompt(key);

	enum ccafeopq::Type kt;
	kt = d->typeOf(key);

	string s = "newParamField ";
	s += prefix;
	s += " ";
	s += typeToString(kt);
	s += " ";
	s += key;
	s += "\nparamCurrent ";
	s += kp;
	s += GSU::stringValue(d, key);
	s += "\nparamHelp ";
	s += kp;
	s += d->getString(helpkey, helpdflt);
	s += "\nparamPrompt ";
	s += kp;
	s += d->getString(promptkey, promptdflt);
	if (! basiconly) {
		s += "\nparamDefault ";
		s += kp;
		s += GSU::stringValue(d, defkey);
		if (kt != ccafeopq::String && kt != ccafeopq::Bool)
		{
			s += "\nparamNumberRange ";
			s += kp;
			s += GSU::stringValue(d, boundkey);
		}
		if ( kt == ccafeopq::String )
		{
			vector< string > choices = d->getStringArray(choicekey, defaultVector);
			for (size_t i = 0 ;i < choices.size(); i++)
			{
				s += "\nparamStringChoice ";
				s += kp;
				s += choices[i];
			}
		}
	}
	s += "\n";
	return s;
}

void 
ccafe::ParameterPort_Impl::clearListeners()
{
	for (size_t i = slv.size(); i > 0; i--)
	{
		vector< ::ccafeopq::ports::ParameterSetListener_shared > snew;
		slv = snew;
	}
	for (size_t j = glv.size(); j > 0; j--)
	{
		vector< ::ccafeopq::ports::ParameterGetListener_shared > gnew;
		glv = gnew;
	}
}

void 
ccafe::ParameterPort_Impl::addSetListener( ::ccafeopq::ports::ParameterSetListener_shared sl)
{
	for (size_t i = 0; i < slv.size(); i++)
	{
		if (slv[i] == sl) {
			return;
		}
	}
	slv.push_back(sl);
}

void 
ccafe::ParameterPort_Impl::addGetListener( ::ccafeopq::ports::ParameterGetListener_shared gl)
{
	for (size_t i = 0; i < glv.size(); i++)
	{
		if (glv[i] == gl) {
			return;
		}
	}
	glv.push_back(gl);
}

ccafe::ParameterPort_Impl::ParameterPort_Impl( ::ccafeopq::TypeMap_shared d, bool basic)
{
	portData = d;
	published = false;
        basiconly = basic;
#ifdef HAVE_CLASSIC
	initClassic();
#endif
	initKernel();
}

ccafe::ParameterPort_Impl::~ParameterPort_Impl()
{
}


bool 
ccafe::ParameterPort_Impl::getPublished()
{
	return published;
}

void  
ccafe::ParameterPort_Impl::setPublished(bool tf)
{
	published = tf;
}


std::vector< std::string > 
ccafe::ParameterPort_Impl::readConfigurationKeys()
{
	if (basiconly) {
		return portData->getAllKeys(ccafeopq::NoType);
	} else {
		return portData->getStringArray(ALLKEYS,defaultVector);
        }
}

ccafeopq::TypeMap_shared
ccafe::ParameterPort_Impl::readConfigurationMap()
{
	ccafeopq::TypeMap_shared ttm = portData->cloneData();
	return ttm;
}

void 
ccafe::ParameterPort_Impl::writeConfigurationMap( ccafeopq::TypeMap_shared tm)
{
	StringVector all = portData->getStringArray(ALLKEYS,defaultVector);
	// over keys subset, get from tm and set on portdata.
	// We're ignoring the result that we're to tell what
	// keys got changed. fixme
	GSU::copyInKeysTell(tm, portData, all);
}

std::string 
ccafe::ParameterPort_Impl::readTitle()
{
	if (basiconly) {
		string title("Parameters");
		return title;
	} else {
		string title = portData->getString(TITLE,"NULL_TITLE_ERROR");
		return title;
	}
}

std::vector< std::string > 
ccafe::ParameterPort_Impl::readGroupNames()
{
	if (basiconly) {
		std::vector<std::string> groups;
		groups.push_back(std::string("All"));
		return groups;
	} else {
		std::vector< std::string > groups 
			= portData->getStringArray(GROUPS, defaultVector);
		return groups;
	}
}

std::string 
ccafe::ParameterPort_Impl::readGroupTitle( const std::string & groupName)
{
	// FIXME readGroupTitle
	return groupName;
# if 0
	string ts = GROUPKEYS;
	ts += groupName;
	StringVector keys = portData->getStringArray(ts, defaultVector);
	return keys;
#endif
}

std::vector< std::string > 
ccafe::ParameterPort_Impl::readGroupKeys( const std::string & groupName )
{
	if (basiconly) {
		return readConfigurationKeys();
	} else {
		string ts = GROUPKEYS;
		ts += groupName;
		StringVector keys = portData->getStringArray(ts, defaultVector);
		return keys;
	}
}

std::string 
ccafe::ParameterPort_Impl::readHelp( const std::string & key)
{
	if (basiconly) {
		std::string s = GSU::stringType(portData, key);
		s += " ";
		s += key;
		return s;
	} else {
		string ts = HELP;
		ts += key;
		string help = portData->getString(ts, "NO_HELP_DEFINED");
		return help;
	}
}

std::string 
ccafe::ParameterPort_Impl::readPrompt( const std::string & key)
{
	if (basiconly) {
		return string(key);
	} else {
		string ts = PROMPT;
		ts += key;
		string s = portData->getString(ts, "NO_PROMPT_DEFINED?");
		return s;
	}
}

bool 
ccafe::ParameterPort_Impl::hasBounds( const std::string & key)
{
	if (basiconly) {
		return false;
	} else {
		string ts = BOUNDED;
		ts += key;
		bool s = portData->getBool(ts, false);
		return s;
	}
}

bool 
ccafe::ParameterPort_Impl::hasChoices( const std::string & key)
{
	if (basiconly) {
		return false;
	} else {
		string ts = BOUNDED;
		ts += key;
		bool s = portData->getBool(ts, false);
		return !s;
	}
}

bool 
ccafe::ParameterPort_Impl::readDefaultBoolean( const std::string & key)
{
	if (basiconly) {
		return false;
	} else {
		string ts = DEFAULT;
		ts += key;
		bool b = portData->getBool(ts,false);
		return b;
	}
	
}

std::string 
ccafe::ParameterPort_Impl::readDefaultString ( const std::string & key)
{
	if (basiconly) {
		return "NO_DEFAULT_STRING_DEFINED";
	} else {
		string ts = DEFAULT;
		ts += key;
		string b = portData->getString(ts,"NO_DEFAULT_STRING_DEFINED");
		return b;
	}
}

int32_t 
ccafe::ParameterPort_Impl::readDefaultInt( const std::string & key)
{
	if (basiconly) {
		return 0;
	} else {
		string ts = DEFAULT;
		ts += key;
		int32_t b = portData->getInt(ts,0);
		return b;
	}
}

int64_t 
ccafe::ParameterPort_Impl::readDefaultLong( const std::string & key)
{
	if (basiconly) {
		return 0;
	} else {
		string ts = DEFAULT;
		ts += key;
		int64_t b = portData->getLong(ts,0);
		return b;
	}
}

float 
ccafe::ParameterPort_Impl::readDefaultFloat ( const std::string & key)
{
	if (basiconly) {
		return 0;
	} else {
		string ts = DEFAULT;
		ts += key;
		float b = portData->getFloat(ts,0);
		return b;
	}
}

double 
ccafe::ParameterPort_Impl::readDefaultDouble( const std::string & key)
{
	if (basiconly) {
		return 0;
	} else {
		string ts = DEFAULT;
		ts += key;
		double b = portData->getDouble(ts,0);
		return b;
	}
}

std::complex<float> 
ccafe::ParameterPort_Impl::readDefaultFcomplex( const std::string & key)
{
	if (basiconly) {
		std::complex< float > b(0,0);
		return b;
	} else {
		string ts = DEFAULT;
		ts += key;
		std::complex< float > b = portData->getFcomplex(ts,0);
		return b;
	}
}

std::complex<double> 
ccafe::ParameterPort_Impl::readDefaultDcomplex( const std::string & key)
{
	if (basiconly) {
		std::complex< double > b(0,0);
		return b;
	} else {
		string ts = DEFAULT;
		ts += key;
		std::complex< double > b = portData->getDcomplex(ts,0);
		return b;
	}
}

std::vector< std::string > 
ccafe::ParameterPort_Impl::readDefaultStringArray( const std::string & key)
{
	if (basiconly) {
		std::vector< std::string > b;
		return b;
	} else {
		string ts = DEFAULT;
		ts += key;
		StringVector b = portData->getStringArray(ts,defaultVector);
		return b;
	}
}

std::vector< bool > 
ccafe::ParameterPort_Impl::readDefaultBooleanArray( const std::string & key)
{
	if (basiconly) {
		std::vector< bool > b;
		return b;
	} else {
		string ts = DEFAULT;
		ts += key;
		std::vector< bool > bdummy;
		std::vector< bool > b = portData->getBoolArray(ts,bdummy);
		return b;
	}
}

std::vector< int32_t > 
ccafe::ParameterPort_Impl::readDefaultIntArray( const std::string & key)
{
	if (basiconly) {
		std::vector< int32_t > b;
		return b;
	} else {
		string ts = DEFAULT;
		ts += key;
		std::vector< int32_t > bdummy;
		std::vector< int32_t > b = portData->getIntArray(ts,bdummy);
		return b;
	}
}

std::vector< int64_t > 
ccafe::ParameterPort_Impl::readDefaultLongArray( const std::string & key)
{
	if (basiconly) {
		std::vector< int64_t > b;
		return b;
	} else {
		string ts = DEFAULT;
		ts += key;
		std::vector< int64_t > bdummy;
		std::vector< int64_t > b = portData->getLongArray(ts,bdummy);
		return b;
	}
}

std::vector< float > 
ccafe::ParameterPort_Impl::readDefaultFloatArray( const std::string & key)
{
	if (basiconly) {
		std::vector< float > b;
		return b;
	} else {
		string ts = DEFAULT;
		ts += key;
		std::vector< float > bdummy;
		std::vector< float > b = portData->getFloatArray(ts,bdummy);
		return b;
	}
}

std::vector< double > 
ccafe::ParameterPort_Impl::readDefaultDoubleArray( const std::string & key)
{
	if (basiconly) {
		std::vector< double > b;
		return b;
	} else {
		string ts = DEFAULT;
		ts += key;
		std::vector< double > bdummy;
		std::vector< double > b = portData->getDoubleArray(ts,bdummy);
		return b;
	}
}

std::vector< std::complex<float> > 
ccafe::ParameterPort_Impl::readDefaultFcomplexArray( const std::string & key)
{
	if (basiconly) {
		std::vector< std::complex< float > > b;
		return b;
	} else {
		string ts = DEFAULT;
		ts += key;
		FCVector b = portData->getFcomplexArray(ts,defaultFCVector);
		return b;
	}
}

std::vector< std::complex<double> > 
ccafe::ParameterPort_Impl::readDefaultDcomplexArray( const std::string & key)
{
	if (basiconly) {
		std::vector< std::complex< double > > b;
		return b;
	} else {
		string ts = DEFAULT;
		ts += key;
		DCVector b = portData->getDcomplexArray(ts,defaultDCVector);	
		return b;
	}
}

void 
ccafe::ParameterPort_Impl::readBoundsInt(const std::string & key, int32_t & low, int32_t & high)
{
	if (basiconly) {
		low = INT_MIN;
		high = INT_MAX;
		return ;
	} 
	if (! hasBounds(key) ) {
		throw std::logic_error("readBoundsInt called on unbounded parameter");
	}
	string ts = BOUNDS;
	ts += key;
	std::vector< int32_t > bdummy;
	bdummy.push_back(INT_MIN);
	bdummy.push_back(INT_MAX);
	std::vector< int32_t > b = portData->getIntArray(ts,bdummy);
	if (b.size() == 2) {
		low = b[0];
		high = b[1];
	}
}

void 
ccafe::ParameterPort_Impl::readBoundsLong(const std::string & key, int64_t & low, int64_t & high)
{
#ifdef NO_NUMERIC_LIMITS
#define mylongmax 4611686018427387903LL
#define mylongmin -4611686018427387904LL
#else
#define mylongmax std::numeric_limits<int64_t>::max()
#define mylongmin std::numeric_limits<int64_t>::min()
#endif
	if (basiconly) {
		low = mylongmin;
		high = mylongmax;
		return ;
	} 
	if (! hasBounds(key) ) {
		throw std::logic_error("readBoundsLong called on unbounded parameter");
	}
	string ts = BOUNDS;
	ts += key;
	std::vector< int64_t > bdummy;
	bdummy.push_back(mylongmin);
	bdummy.push_back(mylongmax);
#undef mylongmax
#undef mylognmin
	std::vector< int64_t > b = portData->getLongArray(ts,bdummy);
	if (b.size() == 2) {
		low = b[0];
		high = b[1];
	}
}

void 
ccafe::ParameterPort_Impl::readBoundsFloat(const std::string & key, float & low, float & high)
{
	if (basiconly) {
		low = -FLT_MAX;
		high = FLT_MAX;
		return ;
	} 
	if (! hasBounds(key) ) {
		throw std::logic_error("readBoundsFloat called on unbounded parameter");
	}
	string ts = BOUNDS;
	ts += key;
	std::vector< float > bdummy;
	bdummy.push_back(-FLT_MAX);
	bdummy.push_back(FLT_MAX);
	std::vector< float > b = portData->getFloatArray(ts,bdummy);
	if (b.size() == 2) {
		low = b[0];
		high = b[1];
	}
}

void 
ccafe::ParameterPort_Impl::readBoundsDouble(const std::string & key, double & low, double & high)
{
	if (basiconly) {
		low = -DBL_MAX;
		high = DBL_MAX;
		return ;
	} 
	if (! hasBounds(key) ) {
		throw std::logic_error("readBoundsDouble called on unbounded parameter");
	}
	string ts = BOUNDS;
	ts += key;
	std::vector< double > bdummy;
	bdummy.push_back(-DBL_MAX);
	bdummy.push_back(DBL_MAX);
	std::vector< double > b = portData->getDoubleArray(ts,bdummy);
	if (b.size() == 2) {
		low = b[0];
		high = b[1];
	}
}

std::vector< std::string > 
ccafe::ParameterPort_Impl::readChoicesString(const std::string & key)
{
	if (basiconly) {
		std::vector< std::string > b;
		return b;
	} 
	if (!hasChoices(key))  {
		throw std::logic_error("readChoicesString called on unenumerated parameter");
	}
	string ts = CHOICES;
	ts += key;
	StringVector b = portData->getStringArray(ts,defaultVector);
	return b;
}

std::vector< int32_t > 
ccafe::ParameterPort_Impl::readChoicesInt(const std::string & key)
{
	if (basiconly) {
		std::vector< int32_t > b;
		return b;
	} 
	if (!hasChoices(key))  {
		throw std::logic_error("readChoicesInt called on unenumerated parameter");
	}
	string ts = CHOICES;
	ts += key;
	std::vector< int32_t > bdummy;
	std::vector< int32_t > b = portData->getIntArray(ts,bdummy);
	return b;
}

std::vector< int64_t > 
ccafe::ParameterPort_Impl::readChoicesLong(const std::string & key)
{
	if (basiconly) {
		std::vector< int64_t > b;
		return b;
	} 
	if (!hasChoices(key))  {
		throw std::logic_error("readChoicesLong called on unenumerated parameter");
	}
	string ts = CHOICES;
	ts += key;
	std::vector< int64_t > bdummy;
	std::vector< int64_t > b = portData->getLongArray(ts,bdummy);
	return b;
}

std::vector< float > 
ccafe::ParameterPort_Impl::readChoicesFloat(const std::string & key)
{
	if (basiconly) {
		std::vector< float > b;
		return b;
	} 
	if (!hasChoices(key))  {
		throw std::logic_error("readChoicesFloat called on unenumerated parameter");
	}
	string ts = CHOICES;
	ts += key;
	std::vector< float > bdummy;
	std::vector< float > b = portData->getFloatArray(ts,bdummy);
	return b;
}

std::vector< double > 
ccafe::ParameterPort_Impl::readChoicesDouble(const std::string & key)
{
	if (basiconly) {
		std::vector< double > b;
		return b;
	} 
	if (!hasChoices(key))  {
		throw std::logic_error("readChoicesDouble called on unenumerated parameter");
	}
	string ts = CHOICES;
	ts += key;
	std::vector< double > bdummy;
	std::vector< double > b = portData->getDoubleArray(ts,bdummy);
	return b;
}

std::vector< std::complex<float> > 
ccafe::ParameterPort_Impl::readChoicesFcomplex(const std::string & key)
{
	if (basiconly) {
		std::vector< std::complex< float> > b;
		return b;
	} 
	if (!hasChoices(key))  {
		throw std::logic_error("readChoicesFcomplex called on unenumerated parameter");
	}
	string ts = CHOICES;
	ts += key;
	FCVector b = portData->getFcomplexArray(ts,defaultFCVector);
	return b;
}

std::vector< std::complex<double> > 
ccafe::ParameterPort_Impl::readChoicesDcomplex(const std::string & key)
{
	if (basiconly) {
		std::vector< std::complex< double > > b;
		return b;
	} 
	if (!hasChoices(key))  {
		throw std::logic_error("readChoicesDcomplex called on unenumerated parameter");
	}
	string ts = CHOICES;
	ts += key;
	DCVector b = portData->getDcomplexArray(ts,defaultDCVector);
	return b;
}

/////////////////// test stuff ///////////////////////
#ifdef OpqParameterPort_MAIN
#include "util/TypeMap.h"
typedef ::gov::sandia::util::TypeMap SMap;
#define GS ::gov::sandia::util::TypeMap
typedef ::ccafeopq::TypeMap_shared CMap;
using namespace std;
int main() {
	GS *s = new GS();
	CMap c(s);
	ccafe::ParameterPort_Impl d(c);
	d.createParameterPort(c, "CONFIG");
	d.createParameterPort(c, "CONFIG");
	d.setBatchTitle(c, "CONFIG title");
	d.setGroupName(c, "G1" );
	d.addRequestBoolean(c,"b1","Long b1 hlep", "short b1", true);
	d.addRequestBoolean(c,"b1","Long b1 hlep", "short b1b", true);
	d.addRequestInt(c,"i1","Long i1 hlep", "short i1", 3, 0, 10);
	d.setGroupName(c, "G2" );
	d.addRequestDouble(c,"d1","silly d1 help", "short d1", 4, 0, 10);
	d.setGroupName(c, "G3" );
	d.addRequestString(c,"s1","silly s1 help", "short s1", "default s1 value");
	d.addRequestString(c,"s2","silly s2 help", "short s2", "default s2 value");
	d.addRequestStringChoice(c, "s2", "banana");
	d.addRequestStringChoice(c, "s2", "pear");
	d.addRequestStringChoice(c, "s2", "banana");
	GS::dump(c);
	string ui = d.getConfigurationString();
	d.clearRequests(c);
	cout << "   all cleared" << endl;
	GS::dump(c);
	cout << " menu dump:" << endl << ui << endl;

}

#endif // OpqParameterPort_MAIN
