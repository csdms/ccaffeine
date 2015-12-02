#include "dc/export/AllExport.hh"
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/AllNeoBind.hh"
#include "dc/neo/ccafe-bind/NeoLoaderWrap.hh"
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
// begin interface NeoLoaderWrap

int NeoLoaderWrap::genSerial=0;

NeoLoaderWrap::NeoLoaderWrap( ccafeopq::ComponentFactory *ocf_)
{
	ocf = ocf_;
#ifdef	CCAFE_AUDIT
	IO_dn1("NeoLoaderWrap: CTOR");
#endif
}

NeoLoaderWrap::NeoLoaderWrap(int bogon)
{
	ocf = 0;
}

NeoLoaderWrap::~NeoLoaderWrap()
{
#ifdef	CCAFE_AUDIT
	IO_dn1("NeoLoaderWrap: DTOR");
#endif
	ocf = 0;
}

void 
NeoLoaderWrap::checkthrow(const char *funcName)
{
	NeoServicesHelper::checkthrow("NeoLoaderWrap", "ocf",
		       	static_cast<void *>(ocf), funcName);
}

void 
NeoLoaderWrap::setPath(const std::vector< std::string > & paths)
{
	ocf->setComponentPath(paths);
}

std::vector< std::string > 
NeoLoaderWrap::getPath()
{
	return ocf->getComponentPath();
}

int
NeoLoaderWrap::loadPortLibrary( const std::string & portLibraryName)
{
	return ocf->loadPorts(portLibraryName);
}

void 
NeoLoaderWrap::loadComponent( const std::string & paletteClassAlias , bool global, bool lazy)
{
	ocf->loadClass(paletteClassAlias, global, lazy);
}



// test dummy
NeoLoaderWrap NeoLoaderWrap_test(0);
