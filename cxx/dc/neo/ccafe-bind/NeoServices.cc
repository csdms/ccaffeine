#include <string>
using namespace std;
#include <neocca.hh>
#include <neoports.hh>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/neo/ccafe-bind/NeoOpaquePort.hh"
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoServices.hh"
#include "dc/neo/ccafe-bind/NeoComponentID.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoHelper.hh"
#include "dc/neo/ccafe-bind/ccafeTypeMap.hh"
#include "dc/neo/ccafe-bind/NeoServicesHelper.hh"

#include "dc/neo/ccafe-bind/NeoMacros.hh"

NeoServices::NeoServices(ccafeopq::Services* svcs) : svc(svcs) {
#ifdef CCAFE_AUDIT
	IO_dn1("NeoServices created");
#endif
	nextNum++;
	nsNum = nextNum;
}

NeoServices::NeoServices(int bogon)
{
	svc = 0;
	nsNum = 0;
}

int
NeoServices::nextNum = 0;

/** obligatory virtual destructor */
NeoServices::~NeoServices()
{
	if (portConversions.size() > 0) {
		IO_en1("NeoServices: destroyed with elements remaining in portConversions map.");
		IO_en1("NeoServices: The following uses ports need to be unregistered:");
		std::map< std::string, NeoPortConverter_shared >::const_iterator pci;
		for (pci = portConversions.begin(); pci != portConversions.end(); pci++) {
			std::string n2 = pci->first;
			IO_en2("NeoServices:       %s", n2.c_str());
		}

	}
	if (opaquePorts.size() > 0) {
		IO_en1("NeoServices: destroyed with elements remaining in opaquePorts map.");
		IO_en1("NeoServices: the following provides ports need to be removed:");
		std::map< std::string, ccafeopq::Port * >::const_iterator opi;
		for (opi = opaquePorts.begin(); opi !=  opaquePorts.end(); opi++) {
			std::string n1 = opi->first;
			IO_en2("NeoServices:       %s", n1.c_str());
		}

	}
	if (portAdapters.size() > 0) {
		IO_en1("NeoServices: destroyed with elements remaining in portAdapters map.");
		IO_en1("NeoServices: the following ports need to be released:");
		std::map< std::string, neo::cca::Port * >::const_iterator pai;
		for (pai = portAdapters.begin(); pai !=  portAdapters.end(); pai++) {
			std::string n = pai->first;
			IO_en2("NeoServices:       %s",n.c_str());
		}
	}
	nsNum = -nsNum;
#ifdef CCAFE_AUDIT
	IO_dn2("NeoServices %d destroyed",nsNum);
#endif
}

neo::cca::Port * 
NeoServices::getPort(const string & name)
throw(neo::cca::Exception)
{
	checkthrow("getPort");
	ccafeopq::Port * op;
	ccafeopq::ExceptionType status = ccafeopq::Correct;
	try {
		op = svc->getPort(name, status);
	}
	NEO_RETHROW_PREPEND("NeoServices::getPort: ");
	if (!op) {
                switch(status) {
		case ccafeopq::PortNotConnected: {
		  NEO_THROW(ex, neo::cca::PortNotConnected, "Attempt to get a unconnected port in NeoServices");
                  break;
                }
		case ccafeopq::PortNotDefined: {
		  NEO_THROW(ex, neo::cca::PortNotDefined, "Attempt to get an undefined port in NeoServices");
                  break;
                }
                default: {
		  NEO_THROW(ex, neo::cca::Unexpected, "Unanticipated problem getting port in NeoServices.");
                  break;
                }
                } // end switch
		return 0; // not reached
	}

	// See if it is a normal port in our binding.
	// Thus, if a third party/component implements a service
	// that we also support in ccafeopq, the third party
	// neo implementation can be accessed over the framework default
	// if explicitly connected.
	if ( op->supportsKind( ccafeopq::NEO_PORT) ) {

		// is it native neoport
		NeoOpaquePort * nop = dynamic_cast<NeoOpaquePort*>(op);
		if (nop != 0) {
			neo::cca::Port * np = nop->getNeoPort();
			if (! np) {
				NEO_THROW(ex7, neo::cca::Nonstandard, "null neo port pointer found in opq port.");
			}
			return np;
		}
		// is it something that needs a translators help?
		// to get the pointer out of another pointer-style binding?
		neo::cca::Port *np = NeoServicesHelper::translate(name,op);
		if (!np) {
			NEO_THROW(ex3, neo::cca::Nonstandard, "extraction of NEO_PORT failed unexpectedly in NeoServices.");
			return 0; // notreached
		}
		return np;
	}

	// hrrrmmm. not a neo port by default. need a wrapper or bust.

	// is it a special case for this binding set up during registerUses?
	if (portConversions.find(name) != portConversions.end()) {
		// if so, generate the wrapper around the opaque port
		::neo::cca::Port *p = portConversions[name]->convert(op);
		portAdapters[name] = p;
		// when the caller does releaseport we will trash the wrapper.
		return p;
	}
  
	// Is it a special case of us getting a provides port specific to
	// our component (or its gizzard) that happens to be opaque and
	// not a port that went through registerUses
	// setup and needs a wrapper?
	// This would include a component getting framework-decoration-provides
	// ports on self. arguably, there shouldn't be any of those--
	// they should be connections to real ports on service components.
	//
	// We do the special case here first time only and thereafter we
	// have the conversion defined in the table.
	//
	// Because of these table entries, well-written components may
	// still end up (thanks to the framework) with leftover objects
	// in portConversions. Since it's all shared pointers and only
	// portConversions holds them, they'll get deleted when the
	// NeoServices does.
	if (op->supportsKind( ccafeopq::OPAQUE_PORT) ) {
		NeoPortConverter_shared conversion = NeoServicesHelper::findConversion(op);
		if (conversion != 0) {
			portConversions[name] = conversion;
			::neo::cca::Port *p = portConversions[name]->convert(op);
			if ( p ) {
				portAdapters[name] = p;
				// when the caller does releaseport 
				// we will trash the wrapper.
				return p;
			}
		}
	}

	NEO_THROW(ex2, neo::cca::BadPortType, "Attempt to get a non-NEO_PORT in NeoServices");
	return 0; // notreached
}

neo::cca::Port * 
NeoServices::getPortNonBlocking(const string & name)
throw(neo::cca::Exception)
{
	return getPort(name); // FIXME - blocking semantics?
}


neo::cca::TypeMap_shared 
NeoServices::getPortProperties(const ::std::string & portName)
throw (neo::cca::Exception)
{
	checkthrow("getPortProperties");
	::ccafeopq::TypeMap_shared tm;
	try {
		tm = svc->getPortProperties(portName);
	}
	NEO_RETHROW;

	if (! tm) {
#ifdef CCAFE_AUDIT
		IO_dn2("Services_impl getPortProperties received null from opq Services. %d", 0);
#endif
		neo::cca::TypeMap_shared ntm; // nil map
		return ntm;
	}

	neo::cca::TypeMap_shared ntm = ccafe::TypeMap::neoWrap(tm);

	return ntm;

}

/** Free's the port indicated by the instance name for modification
    by the component's containing framework.  After this call the
    port will not be valid for use until getPort() is called
    again.*/
void 
NeoServices::releasePort(const string & name)
throw(neo::cca::Exception)
{
	checkthrow("releasePort");
	try {
		svc->releasePort(name);
	}
	NEO_RETHROW;
	if (portAdapters.find(name) != portAdapters.end()) {
		neo::cca::Port *p = portAdapters[name];
		portAdapters.erase(name);
		delete p;
	}
}

void
NeoServices::registerUsesPort(const string & portName, const string & portType, neo::cca::TypeMap_shared properties)
throw(neo::cca::Exception)
{
	checkthrow("registerUsesPort");
	if (portName == "") {
		NEO_THROW(ex, neo::cca::BadPortName, "Attempt to get no-name port NeoServices");
	}
	N2OMAP(properties, otm);

	// Here we map requests for neo core services to requests for
	// opq core services, through the portConversions data.
	ccafeopq::ComponentID_shared cid = svc->getComponentID();
	string ntype = NeoServicesHelper::registerForConversionType(cid,
			portName, portType, portConversions);
	IO_dn5("NeoServices::registerUsesPort(%s,%s,props) maps to opqRUP(%s,%s,otm)",
			portName.c_str(),portType.c_str(), portName.c_str(), ntype.c_str());

	try {
		svc->registerUsesPort(portName, ntype, otm); 
	}
	NEO_RETHROW;
}

void 
NeoServices::unregisterUsesPort(const string & name) 
throw (neo::cca::Exception)
{
	checkthrow("unregisterUsesPort");
	try {
		svc->unregisterUsesPort( name);
		portConversions.erase(name);
	}
	NEO_RETHROW;
}

void 
NeoServices::addProvidesPort(neo::cca::Port *inPort, 
const std::string & name, const std::string & type)
throw(neo::cca::Exception)
{
	neo::cca::TypeMap_shared tm;
	addProvidesPort(inPort, name, type, tm);
}

void 
NeoServices::addProvidesPort(neo::cca::Port *inPort, 
const std::string & name, const std::string & type, neo::cca::TypeMap_shared ntm) 
throw (neo::cca::Exception)
{
	checkthrow("addProvidesPort");

	if (inPort == 0) { 
		NEO_THROW(ex,neo::cca::PortNotDefined,"NeoServices::addProvidesPort(NULL,...) illegal");
	}
	if (name == "" || type == "") { 
		NEO_THROW(ex,neo::cca::PortNotDefined,"NeoServices::addProvidesPort(..) bad string input.");
	}
	N2OMAP(ntm,otm);

	std::string canonicalType = type;
	// Either way, we create a wrapper we have to delete later
	// in removeProvidesPort.
	ccafeopq::Port * cop = 
		NeoServicesHelper::createSpecialProvider(
			inPort, name, type, otm, canonicalType);
	if (cop == 0) {
		cop = new NeoOpaquePort(inPort);
		IO_dn3("Adding a port of type: %s and named: %s", type.c_str(), name.c_str());
	} else {
		IO_dn4("Adding port type: %s, canonical type %s and named: %s", type.c_str(), canonicalType.c_str(), name.c_str());
	}

	try {
		svc->addProvidesPort(cop, name, canonicalType, otm);
		opaquePorts[name] = cop;
	} catch(std::exception& e6) {

		IO_en2("exception: %s", e6.what());
		string s = "NeoServices::addProvidesPort() failed: ";
		s += e6.what();
		NEO_THROW(ex6, neo::cca::Nonstandard, s.c_str());
	}
	return ;
}

/** Get a reference to the component which this 
    Services object belongs. */
neo::cca::ComponentID_shared
NeoServices::getComponentID()
{
	checkthrow("getComponentID");
	NeoComponentID_shared ccid_s;
	ccafeopq::ComponentID_shared oid = svc->getComponentID();
	ccid_s = NeoComponentID::neoWrap(oid);
	return ccid_s;
}

::ccafeopq::Services * NeoServices::unwrapServices()
{
	if (! svc) {
		NEO_THROW(ex, neo::cca::Nonstandard, "NeoServices::unwrapServices called with uninit svc");
	}
	return svc;
}

void NeoServices::registerUsesPort(const std::string & name, const std::string & type) 
throw (neo::cca::Exception)
{
	neo::cca::TypeMap_shared tm; // = svc->createTypeMap();
	registerUsesPort(name, type, tm);
}


void NeoServices::removeProvidesPort(const std::string & name)
throw (neo::cca::Exception)
{
	checkthrow("removeProvidesPort");
	try {
		svc->removeProvidesPort(name); 
		if (opaquePorts.find(name) != opaquePorts.end()) {
			ccafeopq::Port *p = opaquePorts[name];
			opaquePorts.erase(name);
			delete p;
		}
	}
	NEO_RETHROW_PREPEND("NeoServices::removeProvidesPort failed: ");
}

neo::cca::TypeMap_shared NeoServices::createTypeMap()
throw (neo::cca::Exception)
{
	checkthrow("createTypeMap");
	::ccafeopq::TypeMap_shared tm = svc->createTypeMap();
	neo::cca::TypeMap_shared ntm = ccafe::TypeMap::neoWrap(tm);
	return ntm;
}

::std::string NeoServices::genUniquePortName(const ::std::string & base)
{
	checkthrow("genUniquePortName");
	return svc->genUniquePortName(base);
}

void 
NeoServices::registerForRelease(neo::cca::ComponentRelease *callBack) throw (neo::cca::Exception )
{
	if (callBack != 0) {
		releaseListeners.push_back(callBack);
	} else {
		NEO_THROW(ex, neo::cca::Nonstandard, "NeoServices::registerForRelease given null callBack pointer");
	}
}

void 
NeoServices::notifyReleaseListeners()
{
	neo::cca::ComponentRelease *cr = 0;
	neo::cca::Services * s = this;
	// why does the iterator syntax have to be
	// so darned clunky in c++?
	size_t n = releaseListeners.size();
	for (size_t i = 0; i < n; i++)
	{
		cr = releaseListeners[i];
		cr->releaseServices(s);
	}
	releaseListeners.clear();
}

void
NeoServices::checkthrow(const char *funcName)
{
	NeoServicesHelper::checkthrow("NeoServices", "svc",
		static_cast<void *>(svc), funcName);
}

NeoServices NeoServices_test(1);

