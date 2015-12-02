#include <string>
using namespace std;
#include <cca.h>
#include <stdPorts.h>
#include "util/IO.h"
#include "util/TypeMap.h"
#include "dc/export/AllExport.hh"
#include "dc/framework/KernelPort.h"
#include "dc/classic/ccafe-bind/ClassicPortInfo.hh"
#include "dc/classic/ccafe-bind/ClassicOpaquePort.hh"
#include "dc/classic/ccafe-bind/ClassicOpaqueGoPort.hh"
#include "dc/classic/ccafe-bind/ClassicPortConverter.hh"
#include "dc/classic/ccafe-bind/ClassicServices.hh"
#include "dc/classic/ccafe-bind/ClassicServicesHelper.hh"
#include "dc/classic/ccafe-bind/ClassicComponentID.hh"


ClassicServices::ClassicServices(ccafeopq::Services* svcs) : svc(svcs) {
  IO_dn1("ClassicServices created");
}

/** obligatory virtual destructor */
ClassicServices::~ClassicServices()
{
	if (portConversions.size() > 0) {
		IO_en1("ClassicServices: destroyed with elements remaining in portConversions map.");
		IO_en1("ClassicServices: The following uses ports need to be unregistered:");
		std::map< std::string, ClassicPortConverter_shared >::const_iterator pci;
		for (pci = portConversions.begin(); pci != portConversions.end(); pci++) {
			std::string n2 = pci->first;
			IO_en2("ClassicServices:       %s", n2.c_str());
		}

	}

        if (portAdapters.size() > 0) {
                IO_en1("ClassicServices: destroyed with elements remaining in portAdapters map.");
                IO_en1("ClassicServices: the following ports need to be released:");
                std::map< std::string, classic::gov::cca::Port * >::const_iterator pai;
                for (pai = portAdapters.begin(); pai !=  portAdapters.end(); pai++) {
                        std::string n = pai->first;
                        IO_en2("NeoServices:       %s",n.c_str());
                }
        }

	IO_dn1("ClassicServices destroyed");
}

static void digestProperties(ClassicOpaquePort *cop, ClassicPortInfo *pi);

/** Creates a PortInfo to be used in subsequent
    calls to describe a Port. The arguments given are copied, not kept.
    properties is an even length list (argv) of key/value pairs 
    terminated by a NULL key. Note that names of Ports in a 
    component are not distinct for used and provided ports. 
    Standard properties: (UNADOPTED, extensible list)
    gov.cca.port.minConnections (int >= 0; default 0)
    gov.cca.port.maxConnections (int >= 1, default 1)
    gov.cca.port.proxyAllowed   (true,false; default false)
*/

classic::gov::cca::PortInfo *  
ClassicServices::createPortInfo(CONST char *name, CONST char *type, 
                                CONST char** properties) {

// All this wrapperness *must* be properly onioned, or 
// we go insane when deleting per the interface semantics.
  ClassicPortInfo * res_impl = 0;
  ::classic::gov::cca::PortInfo * res = 0;
  ::ccafeopq::PortInfo * opi = 0;

  ::std::map< ::std::string, ::std::string > sm =
    ::gov::sandia::util::TypeMap::props2stringmap(properties);

  int i = 0;
  IO_dn1("==============Properties dump===================");
  while(true) {
    if((!properties) || (properties[i] == 0 )) {
      break;
    }
    IO_dn3("!Classic createPortInfo props: key = %s; value = %s", properties[i], properties[i+1]);
    i += 2;
  }

  IO_dn1("==================StringMap dump====================");
  for(::std::map< ::std::string, ::std::string >::iterator it = sm.begin(); 
      it != sm.end();++it) {
    std::string fs = it->first;
    std::string ss = it->second;
    IO_dn3("key = %s; value = %s", fs.c_str(), ss.c_str());
  }

  opi = svc->createPortInfo(name, type, sm);

  // wrap it
  i = 0;
  res_impl = new ClassicPortInfo(opi);
  while(true) {
    if((!properties) || (properties[i] == 0 )) {
      break;
    }
    if (strcmp(properties[i],"SupportsKind") == 0) {
        IO_dn2("!Classic createPortInfo res_impl: binding = %s", properties[i+1]);
	res_impl->addSupportsKind(properties[i+1]);
    }
    i += 2;
  }
  res = res_impl;
  return res;
}

/**  Fetch a port from the framework. Normally this means a uses port.
     If no uses port is connected and a provided port of the name requested
     is available, the component will be handed back that port.
     Returns NULL if no provided port or uses port connection matches name.
     UNADOPTED C++ definition of "an error occurs".
*/
classic::gov::cca::Port * 
ClassicServices::getPort(CONST char *name) {
  return getPort_internal(name);
}

classic::gov::cca::Port * 
ClassicServices::getPort_internal(const char *name) {
  std::string sn = name;
  enum ccafeopq::ExceptionType status;
  ccafeopq::Port * op = svc->getPort(sn, status);
  if (!op) {
    if (status == ccafeopq::PortNotDefined) {
      IO_dn1("Attempted to get a undefined port in ClassicServices");
    }
    if (status == ccafeopq::PortNotConnected) {
      IO_dn1("Attempted to get a unconnected port in ClassicServices");
    }
    IO_dn1("Failed attempt to get port in ClassicServices");
    return 0;
  }

  if (op->supportsKind(ccafeopq::CLASSIC_PORT)) {
    ClassicOpaquePort * cop = dynamic_cast< ClassicOpaquePort *>(op);
    if( cop == 0) {
      IO_dn1("ClassicServices::getPort dynamic_cast to ClassicOpaquePort failed.");
      exit(1);
    }
    classic::gov::cca::Port * cp= 0;
    cp = cop->getClassicPort();
    if ( cp == 0) {
      IO_dn1("ClassicServices::getPort ClassicOpaquePort wrapper around null.");
      exit(1);
    }

    return cp;
  }


  // hrrrmmm. not a classic port by default. need a wrapper or bust.

  // is it a special case for this binding set up during registerUses?
  if (portConversions.find(name) != portConversions.end()) {
    // if so, generate the wrapper around the opaque port
    classic::gov::cca::Port *p = portConversions[name]->convert(op);
    portAdapters[name] = p;
    // when the caller does releaseport we will trash the wrapper.
    return p;
  }

  IO_dn1("Attempt to get a non-CLASSIC_PORT in ClassicServices");
  const std::string base = op->getKind();
  IO_dn2("Support base: %s", base.c_str());
  const std::vector< std::string > sv = op->getSupportedKinds();
  for (size_t ik = 0 , nk = sv.size(); ik < nk; ik++) {
    IO_dn2("Supported: %s", sv[ik].c_str());
  }
  return 0;
}

/** Free's the port indicated by the instance name for modification
    by the component's containing framework.  After this call the
    port will not be valid for use until getPort() is called
    again.*/
void 
ClassicServices::releasePort(CONST char *name) {
  // svc->releasePort(name);
  releasePort_internal(name);
}

/** Notifies the framework that a port described by PortInfo
    may be used by this component. The portinfo is obtained 
    from createPortInfo. Returns nonzero if there is an error
    in registering, such as bad PortInfo or already registered.
     UNADOPTED C++ definition of "an error occurs".
*/
int 
ClassicServices::registerUsesPort(CDELETE classic::gov::cca::PortInfo *name)
{
  if (name == 0) { return -1; }
  ClassicPortInfo *pi = 0;
  pi = dynamic_cast< ClassicPortInfo * >(name);
  if (pi == 0) {
    IO::en("ClassicServices::registerUsesPort(portinfo) bad wrapper");
    return -1;
  }
  ccafeopq::PortInfo * opi = 0;
  opi = pi->getpi(); // unwrap that puppy.
  if (opi == 0 ) {
    IO::en("ClassicServices::registerUsesPort(portinfo) bad core");
    return -1;
    // should whine here. fatal crap has occured.
  }

  ccafeopq::ComponentID_shared cid = svc->getComponentID();
  std::string portName = opi->getName();
  std::string portType = opi->getType();
  std::string ntype = ClassicServicesHelper::registerForConversionType(cid,
			  portName, portType, portConversions);
  IO_dn5("ClassicServices::registerUsesPort(%s,%s,props) maps to opqRUP(%s,%s,otm)",
  portName.c_str(), portType.c_str(), portName.c_str(), ntype.c_str());
  opi->setType(ntype);


  // reversing the next two statements corrupts mem.
  svc->registerUsesPort(opi); // core destroyed by opq layer.
  pi->resetPortInfo(); // wrapper informed.
  delete name; // wrapper destroyed.
  return 0;
}

/** Notify the framework that a Port, previously
    registered by this component, is no longer desired.
    Returns nonzero if the port is still in use, ignoring
    the unregister request.
    UNADOPTED C++ definition of "an error occurs".
*/
int 
ClassicServices::unregisterUsesPort(CONST char *name) {
  try {
    svc->unregisterUsesPort( ::std::string(name));
    portConversions.erase(name);
  } catch(std::exception& e) {
    return -1;
  }
  return 0;
}

/** Exports a Port implemented by this component to the framework.  
    This Port is now available for the framework to
    connect to other components. The PortInfo is obtained 
    from createPortInfo. Returns nonzero if addProvidesPort fails,
    for example, because that name is already provided.
    UNADOPTED C++ definition of "an error occurs". */
int 
ClassicServices::addProvidesPort(classic::gov::cca::Port *inPort, 
                                 classic::gov::cca::PortInfo *name) {

  if (name == 0 || inPort == 0) { return -1; }
  ClassicPortInfo *pi = 0;
  pi = dynamic_cast< ClassicPortInfo * >(name);
  if (pi == 0) {
    IO::en("ClassicServices::addProvidesPort(p,portinfo) bad wrapper");
    return -1;
    // should whine here. pinfo didn't come from createPortInfo
  }
  ccafeopq::PortInfo * opi = 0;
  opi = pi->getpi(); // unwrap that puppy.
  if (opi == 0 ) {
    IO::en("ClassicServices::addProvidesPort(p,portinfo) bad core");
    return -1;
    // should whine here. memory severely abused.
  }

  if(strcmp("::classic::gov::cca::GoPort", pi->getType()) == 0 ||
     strcmp("::classic::gov::cca::ports::GoPort", pi->getType()) == 0 ||
     strcmp("classic::gov::cca::GoPort", pi->getType()) == 0 ||
     strcmp("classic::gov::cca::ports::GoPort", pi->getType()) == 0 ||
     strcmp("gov.cca.ports.GoPort", pi->getType()) == 0 ||
     strcmp("GoPort", pi->getType()) == 0 ||
     strcmp("gov.cca.GoPort", pi->getType()) == 0) {

    IO_dn3("Adding an apparent GoPort of type: %s and named: %s",
	   pi->getType(), pi->getName());


    classic::gov::cca::GoPort * gp = 
      dynamic_cast< classic::gov::cca::GoPort* >(inPort);
    if (gp) {
	    // ignore supportskind on pi, as go is special
      ClassicOpaqueGoPort * cop = new ClassicOpaqueGoPort(gp);
      // FIXME -- cop wrapper never deleted in teardown elsewhere.
      try {
	opi->setType("::ccafeopq::GoPort");
        svc->addProvidesPort(cop, opi);
        opi = 0; // the opaque call just deleted the opi 
        pi->resetPortInfo(); // tell our pi to forget opi.
      } catch(std::exception& e) {
	IO_en2("exception: %s", e.what());
        pi->resetPortInfo(); // tell our pi to forget opi.
	delete name; // we take care of the wrapper
	return -1;
      }
      delete name; // we take care of the wrapper
      return 0;
    } else {
      IO_en1("you seem to have named a non- classic::gov::cca::GoPort"
	     " as GoPort by mistake (?)");
      ClassicOpaquePort * cop = new ClassicOpaquePort(inPort);
      digestProperties(cop, pi);
      // FIXME -- cop wrapper never deleted in teardown elsewhere.
      try {
	svc->addProvidesPort(cop, opi);
        opi = 0; // the opaque call just deleted the opi 
        pi->resetPortInfo(); // tell our pi to forget opi.
      } catch(std::exception& e) {
	IO_en2("exception: %s", e.what());
        pi->resetPortInfo(); // tell our pi to forget opi.
	delete name; // we take care of wrapper
	return -1;
      }
      delete name; // we take care of the wrapper
      return 0;
    }
  } else { 
    std::string gt = opi->getType();
    std::string gn = opi->getName();
    IO_dn3("Adding an port of type: %s and named: %s",
	   gt.c_str(), gn.c_str());
    ClassicOpaquePort * cop = new ClassicOpaquePort(inPort);
    digestProperties(cop, pi);
      // FIXME -- cop wrapper never deleted in teardown elsewhere.
    try {
      svc->addProvidesPort(cop, opi);
      opi = 0; // the opaque call just deleted the opi 
      pi->resetPortInfo(); // tell our pi to forget opi.
    } catch(std::exception& e) {
      IO_en2("exception: %s", e.what());
      pi->resetPortInfo(); // tell our pi to forget opi.
      delete name; // we take care of the wrapper
      return -1;
    }
    delete name; // we take care of the wrapper
    return 0;
  }
}

static void
digestProperties(ClassicOpaquePort *cop, ClassicPortInfo *pi)
{
	// set the non-classic binding flags if given.
	const std::vector< std::string > kinds = pi->getSupportsKind();
	for (size_t i=0; i < kinds.size(); i++) {
    		IO_dn2("! Classic port adding binding to opaque: %s", kinds[i].c_str());
		cop->addSupportedKind(kinds[i]);
	}
	// do other special flags, if any
}
  
/** Notifies the framework that a previously exported Port is no longer 
    available for use. */
void 
ClassicServices::removeProvidesPort(CONST char *name) {
  svc->removeProvidesPort(name);
}

/** Get a reference to the component which this 
    Services object belongs. */
/*CDELETE*/ classic::gov::cca::ComponentID* ClassicServices::getComponentID()
{
  ClassicComponentID *ccid = 0;
  ::ccafeopq::ComponentID_shared ocid = svc->getComponentID();
  ccid = new ClassicComponentID(ocid);
  return ccid;
}

::ccafeopq::Services * ClassicServices::unwrapServices()
{
	return svc;
}

classic::gov::cca::Port *ClassicServices::getPort (const std::string & name)
{
  return getPort_internal(name.c_str());
}

void ClassicServices::releasePort_internal (const std::string & name)
{
  svc->releasePort(name);
  if (portAdapters.find(name) != portAdapters.end()) {
    classic::gov::cca::Port *p = portAdapters[name];
    portAdapters.erase(name);
    delete p;
  }
}

void ClassicServices::releasePort (const std::string & name)
{
  releasePort_internal(name);
}

int ClassicServices::registerUsesPort(const std::string & name, const std::string & type)
{
  ccafeopq::TypeMap_shared tm = svc->createTypeMap();
  ccafeopq::ComponentID_shared cid = svc->getComponentID();
  std::string portName = name;
  std::string portType = type;
  std::string ntype = ClassicServicesHelper::registerForConversionType(cid,
			  portName, portType, portConversions);
  IO_dn5("ClassicServices::registerUsesPort(%s,%s,props) maps to opqRUP(%s,%s,otm)",
  portName.c_str(), portType.c_str(), portName.c_str(), ntype.c_str());

  svc->registerUsesPort(name, ntype, tm);
  return 0;
}

int ClassicServices::unregisterUsesPort(const std::string & name)
{
  svc->unregisterUsesPort( name);
  return 0;
}

int ClassicServices::addProvidesPort(classic::gov::cca::Port *inPort,
const std::string & name, const std::string & type)
{
  // this implementation is horrendous, but only because the
	// addProvidesPort it wraps is even more horrendous
	// and we don't want to duplicate that crap.
  ::classic::gov::cca::PortInfo * res = 
    createPortInfo(const_cast<char *>(name.c_str()), 
		   const_cast<char *>( type.c_str()), 0);
  return addProvidesPort(inPort,res);
}

void ClassicServices::removeProvidesPort(const std::string & name)
{
  svc->removeProvidesPort(name);
}

#include <cstring> // for strdup, which isn't very portable
CFREE char *ClassicComponentID::toString()
{
    char *res = 0;
    std::string gin = cid->getInstanceName();
    res = strdup(gin.c_str());
    return res;
}
