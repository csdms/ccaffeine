#include "dc/export/AllExport.hh"
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/AllNeoBind.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueServiceProvider.hh"
#include "dc/neo/ccafe-bind/NeoServiceRegistryWrap.hh"
// #include "dc/neo/ccafe-bind/ccafeTypeMap.hh"
// #include "dc/neo/ccafe-bind/NeoServicesHelper.hh"
// #include "dc/neo/ccafe-bind/NeoMacros.hh"
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

////////////////////////////////////////////////////////////
// begin interface NeoServiceRegistryWrap

int
NeoServiceRegistryWrap::genSerial =0;

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
NeoServiceRegistryWrap::NeoServiceRegistryWrap( ccafeopq::ServiceRegistry *oppf_, ccafeopq::ComponentID_shared c)
{
	oppf = oppf_;
	cid = c;
#ifdef	CCAFE_AUDIT
	IO_dn1("NeoServiceRegistryWrap: CTOR");
#endif
}

NeoServiceRegistryWrap::NeoServiceRegistryWrap(int bogon)
{
	oppf = 0;
}

NeoServiceRegistryWrap::~NeoServiceRegistryWrap()
{
#ifdef	CCAFE_AUDIT
	IO_dn1("NeoServiceRegistryWrap: DTOR");
#endif
	oppf = 0;
}

void 
NeoServiceRegistryWrap::checkthrow(const char *funcName)
{
	NeoServicesHelper::checkthrow("NeoServiceRegistryWrap", "oppf",
		       	static_cast<void *>(oppf), funcName);
}

ccafeopq::ComponentID_shared 
NeoServiceRegistryWrap::getProviderID()
{
	return cid;
}
/**
* Add a ServiceProvider that can be asked to produce service Port's
* for other components to use subsequently.
* True means success. False means that for some reason, the
* provider isn't going to function.
*/
bool 
NeoServiceRegistryWrap::addService(const std::string & type, neo::cca::ports::ServiceProvider * portProvider)
{
	if (portProvider == 0) { return false; }
	ccafeopq::ServiceProvider_shared osp = NeoOpaqueServiceProvider::createWrap(portProvider, cid);
	bool result = oppf->addService(type, osp);
	// the osp reclaims memory when erased from opq layer
	return result;
}

/** Add a "reusable" service gov.cca.Port for other components to use 
* subsequently.
*/
bool 
NeoServiceRegistryWrap::addSingletonService(const std::string & type, neo::cca::Port * service)
{
	std::string canonicalType = type;
	ccafeopq::TypeMap_shared dummy;
	std::string dname = "SINGLETON_SERVICE";
	ccafeopq::Port * cop =
                NeoServicesHelper::createSpecialProvider(service, dname, type, dummy, canonicalType); 
        if (cop == 0) {
                cop = new NeoOpaquePort(service);
#ifdef	CCAFE_AUDIT
                IO_dn2("Adding singleton service of type: %s ", type.c_str());
#endif // CCAFE_AUDIT
        } else {
#ifdef	CCAFE_AUDIT
                IO_dn3("Adding singleton service type: %s, canonical type %s", type.c_str(), canonicalType.c_str());
#endif // CCAFE_AUDIT
        }

	bool result = oppf->addSingletonService(canonicalType, cop);
	if ( !result)
	{ 
		delete cop;
	} else {
		opqSingletons[type] = cop;
		opqSingletonCanonical[type] = canonicalType;
	}

	return result;
	
}

/** Inform the framework that this service Port is no longer to
* be used, subsequent to this call. This is likely to
* cause an exception unless all the ports obtained from the
* previously added services have been released and disconnected.
*/
void 
NeoServiceRegistryWrap::removeService(const std::string & serviceType)
{
	std::map< std::string, std::string  >::const_iterator si;
	si = opqSingletonCanonical.find(serviceType);
	if (si != opqSingletonCanonical.end())
	{
		std::string ctype = opqSingletonCanonical[serviceType];
		ccafeopq::Port *cop = opqSingletons[serviceType];
		oppf->removeService(ctype);
		delete cop;
		opqSingletonCanonical.erase(serviceType);
		opqSingletons.erase(serviceType);
		return;
	}
	oppf->removeService(serviceType);
}

// test dummy
NeoServiceRegistryWrap NeoServiceRegistryWrap_test(0);
