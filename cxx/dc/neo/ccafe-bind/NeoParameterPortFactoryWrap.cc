#include "dc/export/AllExport.hh"
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/AllNeoBind.hh"
#include "dc/neo/ccafe-bind/NeoParameterPortFactoryWrap.hh"
#include "dc/neo/ccafe-bind/ccafeTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoServicesHelper.hh"
#include "dc/neo/ccafe-bind/NeoMacros.hh"
using ::std::vector;
using ::std::string;

// private impl stuff
namespace {

////////////////////////////////////////////////////////////
// misc typedefs 


typedef ::std::vector< string > StringVector;
typedef ::std::map< string, string > StringMap;
typedef ::std::map< string, void * > VoidPtrMap;
typedef StringVector::const_iterator SVCI;
// an empty vector for any typemap calls that need one
StringVector defaultVector; 

// always true.
bool whineName() {
#ifdef	CCAFE_AUDIT
	std::cout << "OPPF: portData doesn't contain a port name! BAD" << std::endl;
#endif
  return true;
}

bool whineDelegate() {
#ifdef	CCAFE_AUDIT
	std::cout << "OPPF: portData contains port name not known in delegates."
		<< std::endl;
#endif
  return true;
}

} ENDSEMI // end namespace anonymous

#define PORTNAME ccafe::ParameterPort_Impl::k_PORTNAME()
#define PUBPORTNAME ccafe::ParameterPort_Impl::k_PUBPORTNAME()
#define TITLE ccafe::ParameterPort_Impl::k_TITLE()
#define ALLKEYS ccafe::ParameterPort_Impl::k_ALLKEYS()
#define GROUPS ccafe::ParameterPort_Impl::k_GROUPS()
#define CURGROUP ccafe::ParameterPort_Impl::k_CURGROUP()
#define GROUPKEYS ccafe::ParameterPort_Impl::k_GROUPKEYS()
#define DEFAULT ccafe::ParameterPort_Impl::k_DEFAULT()
#define BOUNDS ccafe::ParameterPort_Impl::k_BOUNDS()
#define BOUNDED ccafe::ParameterPort_Impl::k_BOUNDED()
#define CHOICES ccafe::ParameterPort_Impl::k_CHOICES()
#define HELP ccafe::ParameterPort_Impl::k_HELP()
#define PROMPT ccafe::ParameterPort_Impl::k_PROMPT()
#define HASKEY ccafe::ParameterPort_Impl::k_HASKEY()


////////////////////////////////////////////////////////////
// implementation macros that never leave this file.
////////////////////////////////////////////////////////////
/** insist that we have a port name */
#define VALID if (! portData->hasKey(PORTNAME) && whineName() )  return

/** insist that we have a group name for all parameters.
* if there are none yet, add one with the title. */
#define VALIDGROUP \
	string G = portData->getString(CURGROUP,""); \
	string T = portData->getString(TITLE,""); \
	if (G.size() == 0) setGroupName(portData,T)

// check type against map data possibly already there.
#define VALIDTYPE(X) \
	if (	portData->typeOf(name) != ::ccafeopq::X && \
		portData->typeOf(name) != ::ccafeopq::NoType) return

// add to total list, if not there, or punt
// fixme whine redefinition
#define UNIQUEKEY \
	StringVector alist = portData->getStringArray(ALLKEYS, defaultVector); \
	if ( std::find(alist.begin(), alist.end(), name) != alist.end() ) \
	{ \
		return; \
	} \
	alist.push_back(name); \
	portData->putStringArray(ALLKEYS,alist)

#define SETKEY(X) \
	if ( !portData->hasKey(name) ) portData->put##X(name, deflt)

// add key to list for group
#define ADDTOGROUP \
	string gname = GROUPKEYS; \
	gname += portData->getString(CURGROUP,""); \
	StringVector glist = portData->getStringArray(gname, defaultVector); \
	glist.push_back(name); \
	portData->putStringArray(gname,glist)

// take care of default, help, prompt
#define SETATTR(X) \
	string tmp = DEFAULT; \
	tmp += name; \
	portData->put##X(tmp,deflt); \
	tmp = HELP; \
	tmp += name; \
	portData->putString(tmp,help); \
	tmp = PROMPT; \
	tmp += name; \
	portData->putString(tmp,prompt)

// take care of bounds on bounded types
// whine fixme deflt outside of bounds case,
// current out of bounds case.
#define SETBOUNDS(X, Y) \
	vector< X > bounds(2); \
	if (low > high) { \
		X sw = low; \
		low = high; \
		high = sw; \
	} \
	bounds[0] = low; \
	bounds[1] = high; \
	string tmp2 = BOUNDED; \
	tmp2 += name; \
	portData->putBool(tmp2,true); \
	tmp = BOUNDS; \
	tmp += name; \
	portData->put##Y##Array(tmp,bounds)

#define PPI_DECL \
	string portName = portData->getString(PORTNAME,""); \
	void *vppi = delegates[portName]; \
	if (!vppi) { \
		whineDelegate(); \
		return; \
	} \
	ccafe::ParameterPort_Impl * ppi = static_cast<ccafe::ParameterPort_Impl *>(vppi)

////////////////////////////////////////////////////////////
// begin interface NeoParameterPortFactoryWrap
	//
int
NeoParameterPortFactoryWrap::genSerial=0;

/** Due to the scoping issue involved in creating
* delegated ports with specific names, it is easier
* to organize this code as one service instance
* per using component instance. It could also
* be organized as a global service running a table
* of typemaps with keys which are componentname+keyname.
* Memory management is also easier for the PPF
* if we associate 1:1; once the component is
* dead, we know we can blow away any stateful service
* such as this that it may have left behind.
*/
NeoParameterPortFactoryWrap::NeoParameterPortFactoryWrap( ccafeopq::ports::ParameterPortFactory *oppf_)
{
	oppf = oppf_;
	IO_dn1("NeoParameterPortFactoryWrap: CTOR");
}

NeoParameterPortFactoryWrap::NeoParameterPortFactoryWrap(int bogon)
{
	oppf = 0;
}

NeoParameterPortFactoryWrap::~NeoParameterPortFactoryWrap()
{
	IO_dn1("NeoParameterPortFactoryWrap: DTOR");
	oppf = 0;
}




#define WRAPMAP(x) N2OMAP(x,otm)

void NeoParameterPortFactoryWrap::createParameterPort(neo::cca::TypeMap_shared portData, const ::std::string & portName)
{
	checkthrow("createParameterPort");
	WRAPMAP(portData);
	oppf->createParameterPort(otm, portName);
}


void NeoParameterPortFactoryWrap::setBatchTitle(neo::cca::TypeMap_shared portData, const ::std::string & title)
{
	checkthrow("setBatchTitle");
	WRAPMAP(portData);
	oppf->setBatchTitle(otm, title);
}

void NeoParameterPortFactoryWrap::setGroupName(neo::cca::TypeMap_shared portData, const std::string & newGroupName)
{
	checkthrow("setGroupName");
	WRAPMAP(portData);
	oppf->setGroupName(otm, newGroupName);
}

void NeoParameterPortFactoryWrap::setGroupNameAndTitle(neo::cca::TypeMap_shared portData, const std::string & newGroupName, const std::string & title)
{
	checkthrow("setGroupNameAndTitle");
	WRAPMAP(portData);
	oppf->setGroupNameAndTitle(otm, newGroupName, title);
}

void NeoParameterPortFactoryWrap::addRequestBoolean(neo::cca::TypeMap_shared portData,
				const std::string & name, 
				const std::string & help,
				const std::string & prompt,
				bool deflt)
{
	checkthrow("addRequestBoolean");
	WRAPMAP(portData);
	oppf->addRequestBoolean(otm, name, help, prompt, deflt);
}

void NeoParameterPortFactoryWrap::addRequestInt(neo::cca::TypeMap_shared portData,
				const std::string & name, 
				const std::string & help,
				const std::string & prompt,
				int deflt,
				int low,
				int high)
{
	checkthrow("addRequestInt");
	WRAPMAP(portData);
	oppf->addRequestInt(otm, name, help, prompt, deflt, low, high);
}

void NeoParameterPortFactoryWrap::addRequestLong(neo::cca::TypeMap_shared portData,
				const std::string & name, 
				const std::string & help,
				const std::string & prompt,
				int64_t deflt,
				int64_t low,
				int64_t high)
{
	checkthrow("addRequestLong");
	WRAPMAP(portData);
	oppf->addRequestLong(otm, name, help, prompt, deflt, low, high);
}

void NeoParameterPortFactoryWrap::addRequestFloat(neo::cca::TypeMap_shared portData,
				const std::string & name, 
				const std::string & help,
				const std::string & prompt,
				float deflt,
				float low,
				float high)
{
	checkthrow("addRequestFloat");
	WRAPMAP(portData);
	oppf->addRequestFloat(otm, name, help, prompt, deflt, low, high);
}

void NeoParameterPortFactoryWrap::addRequestDouble(neo::cca::TypeMap_shared portData,
				const std::string & name, 
				const std::string & help,
				const std::string & prompt,
				double deflt,
				double low,
				double high)
{
	checkthrow("addRequestDouble");
	WRAPMAP(portData);
	oppf->addRequestDouble(otm, name, help, prompt, deflt, low, high);
}

void NeoParameterPortFactoryWrap::addRequestString(neo::cca::TypeMap_shared portData,
				const std::string & name, 
				const std::string & help,
				const std::string & prompt,
				const std::string & deflt)
{
	checkthrow("addRequestString");
	WRAPMAP(portData);
	oppf->addRequestString(otm, name, help, prompt, deflt);
}

void NeoParameterPortFactoryWrap::addRequestStringChoice(neo::cca::TypeMap_shared portData,
		const std::string & key, const std::string &choice)
{
	checkthrow("addRequestStringChoice");
	WRAPMAP(portData);
	oppf->addRequestStringChoice(otm, key, choice);
}

void NeoParameterPortFactoryWrap::addStringChoices(neo::cca::TypeMap_shared portData,
	                        const std::string & key,
				std::vector< std::string > choices)
{
	checkthrow("addStringChoices");
	WRAPMAP(portData);
	oppf->addStringChoices(otm, key, choices);
}

void NeoParameterPortFactoryWrap::addIntChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::vector< int32_t > choices)
{
	checkthrow("addIntChoices");
	WRAPMAP(portData);
	oppf->addIntChoices(otm, key, choices);
}

void NeoParameterPortFactoryWrap::addIntChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	int32_t choices[], size_t nChoices)
{
	checkthrow("addIntChoices");
	WRAPMAP(portData);
	oppf->addIntChoices(otm, key, choices, nChoices);
}

void NeoParameterPortFactoryWrap::addLongChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::vector< int64_t > choices)
{
	checkthrow("addLongChoices");
	WRAPMAP(portData);
	oppf->addLongChoices(otm, key, choices);
}

void NeoParameterPortFactoryWrap::addLongChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	int64_t choices[], size_t nChoices)
{
	checkthrow("addLongChoices");
	WRAPMAP(portData);
	oppf->addLongChoices(otm, key, choices, nChoices);
}

void NeoParameterPortFactoryWrap::addFloatChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::vector< float > choices)
{
	checkthrow("addFloatChoices");
	WRAPMAP(portData);
	oppf->addFloatChoices(otm, key, choices);
}

void NeoParameterPortFactoryWrap::addFloatChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	float choices[], size_t nChoices)
{
	checkthrow("addFloatChoices");
	WRAPMAP(portData);
	oppf->addFloatChoices(otm, key, choices, nChoices);
}

void NeoParameterPortFactoryWrap::addDoubleChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::vector< double > choices)
{
	checkthrow("addDoubleChoices");
	WRAPMAP(portData);
	oppf->addDoubleChoices(otm, key, choices);
}

void NeoParameterPortFactoryWrap::addDoubleChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	double choices[], size_t nChoices)
{
	checkthrow("addDoubleChoices");
	WRAPMAP(portData);
	oppf->addDoubleChoices(otm, key, choices, nChoices);
}

void NeoParameterPortFactoryWrap::addFcomplexChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::vector< std::complex< float > > choices)
{
	checkthrow("addFcomplexChoices");
	WRAPMAP(portData);
	oppf->addFcomplexChoices(otm, key, choices);
}

void NeoParameterPortFactoryWrap::addFcomplexChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::complex< float > choices[], size_t nChoices)
{
	checkthrow("addFcomplexChoices");
	WRAPMAP(portData);
	oppf->addFcomplexChoices(otm, key, choices, nChoices);
}

void NeoParameterPortFactoryWrap::addDcomplexChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::vector< std::complex< double > > choices)
{
	checkthrow("addDcomplexChoices");
	WRAPMAP(portData);
	oppf->addDcomplexChoices(otm, key, choices);
}

void NeoParameterPortFactoryWrap::addDcomplexChoices(neo::cca::TypeMap_shared portData,
	const std::string & key,
	std::complex< double > choices[], size_t nChoices)
{
	checkthrow("addDcomplexChoices");
	WRAPMAP(portData);
	oppf->addDcomplexChoices(otm, key, choices, nChoices);
}


void NeoParameterPortFactoryWrap::clearRequests(neo::cca::TypeMap_shared portData)
{
	checkthrow("clearRequests");
	WRAPMAP(portData);
	oppf->clearRequests(otm);
}


void NeoParameterPortFactoryWrap::registerUpdater(neo::cca::TypeMap_shared portData, 
		neo::cca::ports::ParameterGetListener *powner)
{
	checkthrow("registerUpdater");
	WRAPMAP(portData);
	NeoOpaqueParameterGetListener * opgl = new NeoOpaqueParameterGetListener(powner);
	ccafeopq::ports::ParameterGetListener_shared sopgl(opgl);
	// when the framework/port drops the data, the wrapper gets deleted.
	oppf->registerUpdater(otm, sopgl);
}

void NeoParameterPortFactoryWrap::registerUpdatedListener(neo::cca::TypeMap_shared portData,
		neo::cca::ports::ParameterSetListener *powner)
{
	checkthrow("registerUpdatedListener");
	WRAPMAP(portData);
	NeoOpaqueParameterSetListener * opsl = new NeoOpaqueParameterSetListener(powner);
	ccafeopq::ports::ParameterSetListener_shared sopsl(opsl);
	oppf->registerUpdatedListener(otm, sopsl);
}

void NeoParameterPortFactoryWrap::addParameterPort(neo::cca::TypeMap_shared portData, neo::cca::Services * svc)
{
	checkthrow("addParameterPort");
	WRAPMAP(portData);
	NeoServices *ns = dynamic_cast< NeoServices *>(svc);
	if (ns == 0) {
		NEO_THROW(ex,neo::cca::Nonstandard, "NeoParameterPortFactoryWrap::addParameterPort: Buddy, we don't know where this Services came from, but it isn't a good one.");
	}
	ccafeopq::Services *osvc = ns->unwrapServices();
	oppf->addParameterPort(otm, osvc);
}

void NeoParameterPortFactoryWrap::removeParameterPort(neo::cca::TypeMap_shared portData, neo::cca::Services * svc)
{
	checkthrow("removeParameterPort");
	WRAPMAP(portData);
	NeoServices *ns = dynamic_cast< NeoServices *>(svc);
	// FIXME if cast fails, die.
	if (ns == 0) {
		NEO_THROW(ex,neo::cca::Nonstandard, "NeoParameterPortFactoryWrap::addParameterPort: Buddy, we don't know where this Services came from, but it isn't a good one.");
	}
	ccafeopq::Services *osvc = ns->unwrapServices();
	oppf->removeParameterPort(otm, osvc);
}

void 
NeoParameterPortFactoryWrap::checkthrow(const char *funcName)
{
	NeoServicesHelper::checkthrow("NeoParameterPortFactoryWrap", "oppf",
		       	static_cast<void *>(oppf), funcName);
}

// test dummy
NeoParameterPortFactoryWrap NeoParameterPortFactoryWrap_test(0);
#undef WRAPMAP
