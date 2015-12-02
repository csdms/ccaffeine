#include "dc/export/AllExport.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#endif
#include "dc/framework/KernelPort.h"
#include "dc/port/StringableParameterPort.h"
#ifdef HAVE_CLASSIC
#include "dc/classic/ccafe-bind/ClassicOpaquePort.hh"
#endif // HAVE_CLASSIC
#include "dc/port/OpqParameterPort.h"
#include "dc/port/OpqParameterPortFactory.h"
#include "util/TypeMap.h"

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
// begin interface OpqParameterPortFactory

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
OpqParameterPortFactory::OpqParameterPortFactory()
{
#ifdef HAVE_CLASSIC
	initClassic();
#endif // HAVE_CLASSIC
#ifdef  CCAFE_AUDIT
IO_dn1("OpqParameterPortFactory::OpqParameterPortFactory(): call initKernel");
#endif
	initKernel();
#ifdef CCAFE_AUDIT
IO_dn1("OpqParameterPortFactory::OpqParameterPortFactory(): done initKernel");
#endif
}

OpqParameterPortFactory::OpqParameterPortFactory(int bogon)
{
}

OpqParameterPortFactory::~OpqParameterPortFactory()
{
	VoidPtrMap::iterator vi;
	for (vi = delegates.begin(); vi != delegates.end(); ++vi)
	{
		void * vppi = vi->second;
		ccafe::ParameterPort_Impl * ppi = static_cast<ccafe::ParameterPort_Impl *>(vppi);
		if (ppi->getPublished()) {
		// whine. fixme
		// something is now gonna be leaked, because
		// remove wasn't done before the component
		// was destroyed.
		// This leak is better than having someone
		// call on a dead pointer, which potentially
		// is the alternative.
		} else {
	  		delete ppi;
		}
		delegates[vi->first] = 0;
	}
}

#ifdef HAVE_CLASSIC
classic::gov::cca::Port * OpqParameterPortFactory::getClassicPort()
{
  return this;
}
#endif


void OpqParameterPortFactory::createParameterPort(
			::ccafeopq::TypeMap_shared portData, 
			const string & portName)
{
	if (!portData) { return; }

	if ( delegates.find(portName) != delegates.end() )
	{
#ifdef	CCAFE_AUDIT
		std::cout << "OPPF: createParameterPort w/already known portName" << std::endl;
		// really whine fixme
#endif
		return; 
	}

	ccafe::ParameterPort_Impl * ppi = new ccafe::ParameterPort_Impl(portData);
	void * vppi = 0;
	vppi = static_cast< void *>(ppi);
	delegates[portName] = vppi;

	if (portData->hasKey(PORTNAME) )
	{
		return; // should whine fixme
	}
	portData->putString(PORTNAME, portName);
	portData->putString(PUBPORTNAME, portName);
	portData->putString(TITLE, portName);
}


/** Define the window title for the parameter dialog.
**/
void OpqParameterPortFactory::setBatchTitle(
	       			::ccafeopq::TypeMap_shared portData, 
				const string & title)
{
	if (!portData) { return; }
	VALID;
	if (portData->hasKey(TITLE) )
	{
		portData->remove(TITLE);
	}
	portData->putString(TITLE, title);
}


/** Define the next tab/group title to use. All
 * addRequest subsequent calls will add to this group.
 * Multiple dialog tabs/groups can be defined in this way.
 */
void OpqParameterPortFactory::setGroupName( 
				::ccafeopq::TypeMap_shared portData, 
				const string & newGroupName)
{

	if (!portData) { return; }
	VALID;
	StringVector sv = portData->getStringArray(GROUPS,defaultVector);
	if ( std::find(sv.begin(), sv.end(), newGroupName) != sv.end() )
	{
		return;
	}
	sv.push_back(newGroupName);
	portData->putStringArray(GROUPS,sv);
	portData->putString(CURGROUP, newGroupName);

}


/** Define a boolean parameter and its default state.
 * The configured value is always available by
 * portData->getBool(name, ...)
 */
void OpqParameterPortFactory::addRequestBoolean( 
				::ccafeopq::TypeMap_shared portData,
				const string & name, 
				const string & help,
				const string & prompt,
				bool deflt)
{

	if (!portData) { return; }

	VALID;
	VALIDGROUP;
	VALIDTYPE(Bool); // fixme whine mismatch
	UNIQUEKEY;
	SETKEY(Bool);
	ADDTOGROUP;
	SETATTR(Bool);

}

/** Define a int parameter and its default state.
 * The configured value is always available by
 * portData->getInt(name, ...) and it will be
 * in the range [low, high].
 */
void OpqParameterPortFactory::addRequestInt( 
				::ccafeopq::TypeMap_shared portData,
				const string & name, 
				const string & help,
				const string & prompt,
				int deflt,
				int low,
				int high)
{
	if (!portData) { return; }
	VALID;
	VALIDGROUP;
	VALIDTYPE(Int); // fixme whine mismatch
	UNIQUEKEY;
	SETKEY(Int);
	ADDTOGROUP;
	SETATTR(Int);
	SETBOUNDS(int32_t, Int);
}

/** Define a long parameter and its default state.
 * The configured value is always available by
 * portData->getLong(name, ...) and it will be
 * in the range [low, high].
 */
void OpqParameterPortFactory::addRequestLong(
	       			::ccafeopq::TypeMap_shared portData,
				const string & name, 
				const string & help,
				const string & prompt,
				int64_t deflt,
				int64_t low,
				int64_t high)
{
	if (!portData) { return; }
	VALID;
	VALIDGROUP;
	VALIDTYPE(Long); // fixme whine mismatch
	UNIQUEKEY;
	SETKEY(Long);
	ADDTOGROUP;
	SETATTR(Long);
	SETBOUNDS(int64_t, Long);
}

/** Define a float parameter and its default state.
 * The configured value is always available by
 * portData->getFloat(name, ...) and it will be
 * in the range [low, high].
 */
void OpqParameterPortFactory::addRequestFloat(
	       			::ccafeopq::TypeMap_shared portData,
				const string & name, 
				const string & help,
				const string & prompt,
				float deflt,
				float low,
				float high)
{
	if (!portData) { return; }
	VALID;
	VALIDGROUP;
	VALIDTYPE(Float); // fixme whine mismatch
	UNIQUEKEY;
	SETKEY(Float);
	ADDTOGROUP;
	SETATTR(Float);
	SETBOUNDS(float, Float);
}

/** Define a double parameter and its default state.
 * The configured value is always available by
 * portData->getDouble(name, ...) and it will be
 * in the range [low, high].
 */
void OpqParameterPortFactory::addRequestDouble(
	       			::ccafeopq::TypeMap_shared portData,
				const string & name, 
				const string & help,
				const string & prompt,
				double deflt,
				double low,
				double high)
{
	if (!portData) { return; }
	VALID;
	VALIDGROUP;
	VALIDTYPE(Double); // fixme whine mismatch
	UNIQUEKEY;
	SETKEY(Double);
	ADDTOGROUP;
	SETATTR(Double);
	SETBOUNDS(double, Double);
}

/** Define a string parameter and its default state.
 * The configured value is always available by
 * portData->getString(name, ...).
 * If no addRequestStringChoice calls are made, the
 * user input may be any string. If addRequestStringChoice
 * is used, the value will be one among the choices.
 * If addRequestStringChoice is used, deflt must
 * be among the choices defined.
 */
void OpqParameterPortFactory::addRequestString(
	       			::ccafeopq::TypeMap_shared portData,
				const string & name, 
				const string & help,
				const string & prompt,
				const string & deflt)
{
	if (!portData) { return; }
	VALID;
	VALIDGROUP;
	VALIDTYPE(String); // fixme whine mismatch
	UNIQUEKEY;
	SETKEY(String);
	ADDTOGROUP;
	SETATTR(String);

	// init to empty
	StringVector bounds;
	tmp = BOUNDS; 
	tmp += name;
	portData->putStringArray(tmp,bounds);
}

/** define a new choice for a string parameter. */
void OpqParameterPortFactory::addRequestStringChoice(
	       		::ccafeopq::TypeMap_shared portData,
			const string & name,
		       	const string &choice)
{
	if (!portData) { return; }
	VALID;
	if (portData->typeOf(name) != ::ccafeopq::String) 
	{
		// fixme whine
		return;
	}
	string tmp = CHOICES; 
	tmp += name;
	StringVector bounds =  portData->getStringArray(tmp,defaultVector); \
	if ( std::find(bounds.begin(), bounds.end(), choice) == bounds.end())
	{
		bounds.push_back(choice);
		portData->putStringArray(tmp,bounds);
	}
}

 /** Clear all previously added requests, titles, groups. After
  *  this call, it is as if the ParameterPort has
  *  been created but never configured. The values of
  *  previously defined parameters will, nonethesless,
  *  remain in the typemap.
  *  Typically, this is used only by someone implementing
  *  the updateParameterPort function from
   *  class ::ccafeopq::ParameterGetListener {
  */
void OpqParameterPortFactory::clearRequests(
	       		::ccafeopq::TypeMap_shared portData)
{
	if (!portData) { return; }
	VALID;
	portData->remove(TITLE);
	StringVector groups = portData->getStringArray(GROUPS,defaultVector);
	portData->remove(CURGROUP);
	portData->remove(GROUPS);
	size_t i;
	for ( i = 0; i < groups.size(); i++)
	{
		string gkey = GROUPKEYS;
		gkey += groups[i];
		portData->remove(gkey);
	}
	StringVector names =  portData->getStringArray(ALLKEYS,defaultVector);
	portData->remove(ALLKEYS);
	for (i = names.size() ; i > 0 ; i--)
	{
		string name = names[i-1];
		string tmp = DEFAULT;
		tmp += name;
		portData->remove(tmp);
		tmp = BOUNDS;
		tmp += name;
		portData->remove(tmp);
		tmp = HELP;
		tmp += name;
		portData->remove(tmp);
		tmp = PROMPT;
		tmp += name;
		portData->remove(tmp);
	}
	// fixme remove listeners
	PPI_DECL;
	ppi->clearListeners();
}

/** 
 * Register listener (the component) that wishes to have
 * a chance to change the contents of its ParameterPort
 * just before the parameters typemap is used to
 * render the parameter dialog.
 * @param powner a pointer to the listener that will be
 * forgotten when it is no longer needed. 
 */
void OpqParameterPortFactory::setUpdater(
			::ccafeopq::TypeMap_shared portData, 
			::ccafeopq::ports::ParameterGetListener_shared powner)
{
	if (!portData) { return; }
	VALID;
	PPI_DECL;
	ppi->addGetListener(powner);
}

/** Register listener (the component) if it wishes to be
 * informed when an parameter is set.
 * Listeners are called after values are set.
 */
void OpqParameterPortFactory::setUpdatedListener( 
			::ccafeopq::TypeMap_shared portData,
			::ccafeopq::ports::ParameterSetListener_shared powner)
{
	if (!portData) { return; }
	VALID;
	PPI_DECL;
	ppi->addSetListener(powner);
}

/** Signal that the ParameterPort is fully defined and should
 * now pop out on the component. The  ::ccafeopq::Services passed here
 * must be the component's own  ::ccafeopq::Services handle.
 */
void OpqParameterPortFactory::publishParameterPort(
	       		::ccafeopq::TypeMap_shared portData,
		      	::ccafeopq::Services * svc)
{
	if (!portData) {
#ifdef	CCAFE_AUDIT
	std::cout << "OPPF: publishParameterPort called w/null portData" << std::endl;
#endif
		return; 
	}
	VALID;
	PPI_DECL;
	if ( ppi->getPublished() ) {
#ifdef	CCAFE_AUDIT
	std::cout << "OPPF: publishParameterPort called w/already published." << std::endl;
#endif
		return; // whine fixme
	}
	string ptype = "::ccafeopq::ports::ParameterPort";
	string pname = portData->getString(PORTNAME,"");
	ccafeopq::Port * op = ppi;
	ccafeopq::TypeMap_shared props = svc->createTypeMap();
	props->putString("ccafe.babel.portType","gov.cca.ports.ParameterPort");
	props->putString("ccafe.neo.portType","neo::cca::ports::ParameterPort");
#ifdef	CCAFE_AUDIT
	std::cout << "OPPF: publishParameterPort calling addProvidesPort" << std::endl;
#endif
	svc->addProvidesPort(op, pname, ptype, props);
	ppi->setPublished(true);
}

/** Cause a previously defined parameter port to go away. */
void OpqParameterPortFactory::unpublishParameterPort(
	       		::ccafeopq::TypeMap_shared portData,
			::ccafeopq::Services * svc)
{
	if (!portData) { return; }
	VALID;
	PPI_DECL;
	if (!ppi->getPublished() ) {
		return; // whine fixme
	}
	string pname = portData->getString(PORTNAME,"");
	svc->removeProvidesPort(pname);
	ppi->setPublished(false);
}

///////////////////////// new stuff


void OpqParameterPortFactory::setGroupNameAndTitle(ccafeopq::TypeMap_shared,
	const std::string& groupName, const std::string& title)
{
	// FIXME setGroupNameAndTitle
}

void OpqParameterPortFactory::registerUpdater(ccafeopq::TypeMap_shared tm, ccafeopq::ports::ParameterGetListener_shared pgl)
{
	setUpdater(tm, pgl);
}

void OpqParameterPortFactory::registerUpdatedListener(ccafeopq::TypeMap_shared tm, ccafeopq::ports::ParameterSetListener_shared psl)
{
	setUpdatedListener(tm,psl);
}

void OpqParameterPortFactory::addParameterPort(ccafeopq::TypeMap_shared tm, ccafeopq::Services* svc)
{
#ifdef	CCAFE_AUDIT
	std::cout << "OPPF: addParameterPort called." << std::endl;
#endif
	publishParameterPort(tm,svc);
}

void OpqParameterPortFactory::removeParameterPort(ccafeopq::TypeMap_shared tm, ccafeopq::Services* svc)
{
	unpublishParameterPort(tm,svc);
}

void OpqParameterPortFactory::addStringChoices(ccafeopq::TypeMap_shared portData,
				const std::string & name,
				std::vector< std::string > choices)
{
	if (!portData) { return; }
	VALID;
	if (portData->typeOf(name) != ::ccafeopq::String) 
	{
		// fixme whine
		return;
	}
	string tmp2 = BOUNDED; 
	tmp2 += name;
	portData->putBool(tmp2, false);
	string tmp = CHOICES; 
	tmp += name;
	portData->putStringArray(tmp, choices);
}

void OpqParameterPortFactory::addIntChoices(ccafeopq::TypeMap_shared portData,
	const std::string & name,
	std::vector< int32_t > choices)
{
	// semantics are overwrite for both formerly bounded and
	// previous choices defined cases.
	if (!portData) { return; }
	VALID;
	if (portData->typeOf(name) != ::ccafeopq::Int) 
	{
		// fixme whine
		return;
	}
	string tmp = CHOICES; 
	tmp += name;
	portData->putIntArray(tmp, choices);
	string tmp2 = BOUNDED; 
	tmp2 += name;
	portData->putBool(tmp2, false);
}

void OpqParameterPortFactory::addIntChoices(ccafeopq::TypeMap_shared portData,
	const std::string & name,
	int32_t choices[], size_t nChoices)
{
	// fixme addIntChoices -- semantics append vs overwrite?
	if (!portData) { return; }
	VALID;
	if (portData->typeOf(name) != ::ccafeopq::Int) 
	{
		// fixme whine
		return;
	}
	string tmp = CHOICES; 
	tmp += name;
	portData->putIntArray(tmp, choices, nChoices);
	string tmp2 = BOUNDED; 
	tmp2 += name;
	portData->putBool(tmp2, false);
}

void OpqParameterPortFactory::addLongChoices(ccafeopq::TypeMap_shared portData,
	const std::string & key,
	std::vector< int64_t > choices)
{
	// FIXME addFloatChoices
}

void OpqParameterPortFactory::addLongChoices(ccafeopq::TypeMap_shared portData,
	const std::string & key,
	int64_t choices[], size_t nChoices)
{
	// FIXME addFloatChoices
}

void OpqParameterPortFactory::addFloatChoices(ccafeopq::TypeMap_shared portData,
	const std::string & key,
	std::vector< float > choices)
{
	// FIXME addFloatChoices
}

void OpqParameterPortFactory::addFloatChoices(ccafeopq::TypeMap_shared portData,
	const std::string & key,
	float choices[], size_t nChoices)
{
	// FIXME addFloatChoices
}

void OpqParameterPortFactory::addDoubleChoices(ccafeopq::TypeMap_shared portData,
	const std::string & key,
	std::vector< double > choices)
{
	// FIXME addDoubleChoices
}

void OpqParameterPortFactory::addDoubleChoices(ccafeopq::TypeMap_shared portData,
	const std::string & key,
	double choices[], size_t nChoices)
{
	// FIXME addDoubleChoices
}

void OpqParameterPortFactory::addFcomplexChoices(ccafeopq::TypeMap_shared portData,
	const std::string & key,
	std::vector< std::complex< float > > choices)
{
	// FIXME addFcomplexChoices
}

void OpqParameterPortFactory::addFcomplexChoices(ccafeopq::TypeMap_shared portData,
	const std::string & key,
	std::complex< float > choices[], size_t nChoices)
{
	// FIXME addFcomplexChoices
}

void OpqParameterPortFactory::addDcomplexChoices(ccafeopq::TypeMap_shared portData,
	const std::string & key,
	std::vector< std::complex< double > > choices)
{
	// FIXME addDcomplexChoices
}

void OpqParameterPortFactory::addDcomplexChoices(ccafeopq::TypeMap_shared portData,
	const std::string & key,
	std::complex< double > choices[], size_t nChoices)
{
	// FIXME addDcomplexChoices
}

// end interface OpqParameterPortFactory

/////////////////// test stuff ///////////////////////
#ifdef OpqParameterPortFactory_MAIN
#include "util/TypeMap.h"
typedef ::gov::sandia::util::TypeMap SMap;
#define GS ::gov::sandia::util::TypeMap
typedef ::ccafeopq::TypeMap_shared CMap;
using namespace std;
int main() {
	GS *s = new GS();
	CMap c(s);
	OpqParameterPortFactory d;
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

	// string ui = d.getConfigurationString();
	d.clearRequests(c);
	cout << "   all cleared" << endl;
	GS::dump(c);
	// cout << " menu dump:" << endl << ui << endl;

}
#endif // OpqParameterPortFactory_MAIN
