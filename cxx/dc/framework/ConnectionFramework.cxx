
#include <map>
#include <vector>
#include <string>

#include "dc/export/AllExport.hh"
#include "util/IO.h"
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <stdPorts.h>
#endif // HAVE_CLASSIC
#ifdef HAVE_NEO
#include <neocca.hh>
#endif // HAVE_NEO
#include "parameters/parametersStar.h"
#include "dc/export/ccafeopq_support.hh"

#include "dc/framework/ComponentChangedEvent.h"
#include "dc/framework/GizzardComponentChangedEvent.h"
#include "dc/framework/ComponentChangedListener.h"
#include "dc/export/AllExport.hh"
//
#ifdef HAVE_CLASSIC
#include "dc/classic/ccafe-bind/AllCcafeBind.hh"
#endif // HAVE_CLASSIC
#include "dc/framework/ConnectionID.h"
#include "dc/framework/UserPortData.h"
#include "dc/framework/ProviderPortData.h"
#include "dc/framework/KernelPort.h"
#include "dc/framework/OpqConnectionEventService.h"
#include "dc/framework/Gizzard.h"
#include "dc/services/registry/OpqServiceRegistry.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#include "dc/services/ContextEventManager/ContextEventManager.hh"
#include "dc/framework/XCmptFactory.hh"
#include "dc/framework/DefaultXCmptFactory.hh"
#include "dc/framework/ServicesHelper.h"
#include "dc/framework/CmpBox.h"
#include "dc/framework/ComponentInfo.h"
#include "dc/framework/ComponentRecord_Impl.h"
#include "dc/framework/ComponentRegistrar.h"
#include "dc/framework/ComponentFactory.h"
#include "dc/framework/GoThread.hh"
#include "port/supportInterfaces.h"
#include "dc/framework/FrameworkConnectionEvent.h"

#include "dc/framework/ConnectedConnectionEvent.h"
#include "dc/framework/DisconnectingConnectionEvent.h"
#include "dc/framework/OpqBuilderService.h"
#include "dc/framework/OpqGUIService.h"
#include "dc/framework/StaticFactory.h"
#include "dc/framework/ConnectionFramework.h"

#include "util/TypeMap.h"
#include "dc/port/StringableParameterPort.h"
#include "dc/port/OpqParameterPort.h"
#include "dc/port/DefaultJPrintfPort.h"

#include "util/freefree.h"
#include <assert.h>
#include "dc/framework/Check.h"
#ifdef HAVE_CLASSIC
#include "dc/classic/ccafe-bind/ClassicOpaquePort.hh"
#endif // HAVE_CLASSIC
#include <cstring>

namespace {
char id[]=
"$Id: ConnectionFramework.cxx,v 1.82 2008/12/24 19:38:41 baallan Exp $";
} ENDSEMI

namespace {
	void whine( ::ccafeopq::ExceptionType et, const ::std::string & msg)  throw ( ::ccafeopq::Exception )
	{
		throw  ::ccafeopq::Exception(et, msg);
	}

	 void whinel( const char * msg)  throw ( ::ccafeopq::Exception )
	 { 
		 throw  ::ccafeopq::Exception(msg);
	 }

	 void whine( const ::std::string & msg)  throw ( ::ccafeopq::Exception )
	 { 
		 throw  ::ccafeopq::Exception(msg);
	 }

}


namespace {
char * STRDUP(const char *s)
{
	size_t n = strlen(s) +1;
	char *v = (char *)malloc(n);
	strcpy(v,s);
	return v;
}
} ENDSEMI

  //======================================================================
  // latter is the safe version.
  //======================================================================
ConnectionFramework::ConnectionFramework(int64_t fComm, bool useComm) {
  // We have no class loader, there is just the stuff hardwired at the start
  IO_dn1("ConnectionFramework::ConnectionFramework() CTOR");
  initInternals(fComm,useComm);
}

void
ConnectionFramework::initInternals(int64_t fComm, bool useComm)
{
  hasComm = useComm;
  if (useComm) {
    fortranMPIComm = fComm;
  } else {
    fortranMPIComm = -1;
  }
  IO_dn3("ConnectionFramework::initInternals(%d,%s)",(int)fComm, (useComm?"TRUE":"FALSE"));
  instantiatingComponent = false;
  IO_dn1("ConnectionFramework::ConnectionFramework() create ocfraw");
  ComponentFactory *ocfraw = new ComponentFactory();
  IO_dn1("ConnectionFramework::ConnectionFramework() done create ocfraw");
  ocf = ComponentFactory_shared(ocfraw);
  pallet = ocf->getComponentClassAliases();
  std::string myname = "FRAMEWORK";
  std::string mytype = "Ccaffeine-Support";
  ::ccafeopq::TypeMap_shared dummy;
  ComponentInfo_shared me = addExternalComponent( mytype, myname, dummy);
  obs = new OpqBuilderService();
  obs->setFrameData(&frameItems);
  osr = new OpqServiceRegistry();
  ogs = new OpqGUIService();
  ogs->setFrameData(&frameItems);
  
  jpfp = new DefaultJPrintfPort();
#ifdef HAVE_CLASSIC
  cbs = new ClassicOpaquePort(obs);
#endif // HAVE_CLASSIC
  cem = new ccafeopq::event::ContextEventManager();

  wall = getGizzard(myname);
  osr->startup(wall);
  wall->addProvidesPort(ocfraw, "Loader", "::ccafeopq::Loader");
  ocfraw = 0;
  wall->addProvidesPort(ogs, "GUIService", "::ccafeopq::GUIService");
  wall->addProvidesPort(osr, "ServiceRegistry", "::ccafeopq::ServiceRegistry");
  wall->addProvidesPort(obs, "BuilderService", "::ccafeopq::BuilderService");
  wall->addProvidesPort(jpfp, "JPrintfPort", "JPrintfPort");
#ifdef HAVE_CLASSIC
// this is a grody hack for testing purposes. make it go away, along w/classic.
  // classic to all the typemap stuff. why bother?
  wall->addProvidesPort(cbs, "fakeBuilderService", "::classic::hack::BuilderService");
#endif // HAVE_CLASSIC
  // need to set some visibility properties here.
  // and hack the gui to deal with them.
  std::string key =  "gov.sandia.ccaffeine.dc.user_iface.gui.visibility.";
  key += myname;
  std::string value = "false";
  setComponentProperty(myname, key, value);

  debug = false;
}

void
ConnectionFramework::initStaticFactory(StaticFactory *sf)
{
  ccafeopq::ComponentFactory *ocfraw = ocf.get();
  assert(ocfraw != 0);
  ComponentFactory *ocfnative = dynamic_cast< ComponentFactory * >(ocfraw);
  assert(ocfnative != 0);
  sf->addClasses(ocfnative);
}

ConnectionFramework::ConnectionFramework(int64_t fComm, bool useComm, int & status) {
  status = 0;
  IO_dn3("ConnectionFramework::ConnectionFramework(%d, %s, status) CTOR",(int)fComm, (useComm?"TRUE":"FALSE"));
  initInternals(fComm,useComm);

  if (ocf == 0 || osr == 0 || wall == 0) {
    status = -1;
  }  
}

  //======================================================================
ConnectionFramework::~ConnectionFramework() {
  // delete instances; // FIXME. delete elements
  size_t i = cmptChgLsnrs.size() ;
  for (  ; i > 0; i--) { cmptChgLsnrs[i-1] = 0; }
  cmptChgLsnrs.clear();

  wall->removeProvidesPort("JPrintfPort");
#ifdef HAVE_CLASSIC
  wall->removeProvidesPort("fakeBuilderService");
#endif // HAVE_CLASSIC
  wall->removeProvidesPort("BuilderService");
  wall->removeProvidesPort("ServiceRegistry");
  wall->removeProvidesPort("Loader");
  osr->shutdown();
  removeExternalComponent("FRAMEWORK");
  delete jpfp; jpfp = 0;
  delete osr; osr = 0;
#ifdef HAVE_CLASSIC
  delete cbs; cbs = 0;
#endif // HAVE_CLASSIC
  delete obs; obs = 0;
  delete cem; cem = 0;
  wall = 0;
}

  //======================================================================
::ccafe::CmpBox_shared ConnectionFramework::getInstance( const ::std::string & name)
{
	::std::map< ::std::string, ::ccafe::CmpBox_shared >::const_iterator pos;
	IO_dn2("ConnectionFramework::getInstance: %s",name.c_str());
	pos = instances.find(name);
	if (pos != instances.end()) {
		return instances[name];
	}
	::ccafe::CmpBox_shared cbs;
	return cbs;
}

  //======================================================================
std::vector< std::string > ConnectionFramework::getComponentClasses() {
	refreshPallet();
	return pallet;
} 

  //======================================================================
ComponentInfo_shared ConnectionFramework::instantiate(char* className, char* instanceName) {
	::ccafeopq::TypeMap_shared tm;
	return instantiate(className,instanceName, tm);
}
  //======================================================================
ComponentInfo_shared ConnectionFramework::instantiate(const std::string & className, const std::string & instanceName, ::ccafeopq::TypeMap_shared tm) {

  ccafeopq::Component * cmpt = 0;
  instantiatingComponent = true; // keep the events from messing us up.

  IO_dn3("className = %s instanceName = %s", 
	  className.c_str(), instanceName.c_str());
  ::ccafe::CmpBox_shared cbs1 = getInstance(instanceName);
  if (cbs1 != 0) {
    IO::en("Instance %s already exists: instantiation failed",
	    instanceName.c_str());
    ComponentInfo_shared x; // null info
    return x;
  }

  IO_dn2("xCmptFactories.size() = %d", xCmptFactories.size());
  for(size_t i = 0, n = xCmptFactories.size() ; i < n ; i++) {
    if(xCmptFactories[i]->hasComponent(className)) {
      cmpt = xCmptFactories[i]->instantiate( className);
      if (cmpt != 0) {
        break; // no point in making n and leaking one.
      }
    }
  }
  if(cmpt == 0) {
    cmpt = ocf->createComponentInstance(className);
  }
  if(cmpt == 0) {
    IO::en(":-( Class: %s doesn\'t exist: instantiation failed", className.c_str());
    ComponentInfo_shared y; // null info
    return y;
  }
  Gizzard *g = new Gizzard(instanceName, fortranMPIComm, hasComm);
  g->setPropertyMapData(tm);
  g->setFrameData(&frameItems);
  g->initDelegates();
  g->addComponentChangedListener(this);
  ::ccafe::CmpBox * cb = 0;
  cb = new ::ccafe::CmpBox(cmpt, g, instanceName);
  cb->setType(className, true);
  ::ccafe::CmpBox_shared cbs(cb);
  instances[instanceName] = cbs;
  cmpt->setServices(g);
  instantiatingComponent = false; // all done.
  IO_dn1("instantiate returning");
  return ComponentInfo::wrapCmpBox(cbs);
}

  //======================================================================

ComponentInfo_shared
ConnectionFramework::addExternalComponent(const ::std::string & className, const ::std::string & instanceName, ::ccafeopq::TypeMap_shared tm) 
{
  instantiatingComponent = true; // keep the events from messing us up.

  IO_dn3("className = %s instanceName = %s", 
	  className.c_str(), instanceName.c_str());
  ::ccafe::CmpBox_shared cbs1 = getInstance(instanceName);
  if (cbs1 != 0) {
    IO::en("Instance %s already exists: instantiation failed",
	    instanceName.c_str());
    ComponentInfo_shared x; // null info
    return x;
  }

  Gizzard *g = new Gizzard(instanceName, fortranMPIComm, hasComm);
  g->setPropertyMapData(tm);
  g->setFrameData(&frameItems);
  g->initDelegates();
  g->addComponentChangedListener(this);
  ::ccafe::CmpBox * cb = 0;
  cb = new ::ccafe::CmpBox(g, instanceName);
  cb->setType(className, false);
  ::ccafe::CmpBox_shared cbs(cb);
  instances[instanceName] = cbs;
  instantiatingComponent = false; // all done.
  IO_dn1("addExternal returning");
  return ComponentInfo::wrapCmpBox(cbs);
}
void
ConnectionFramework::removeExternalComponent(const ::std::string & instanceName)
{
	if(debug) {
		IO::en("ConnectionFramework::removeExternalComponent: in");
		IO::en("instanceName = %s", instanceName.c_str());
	}
	Gizzard *giz = 0;

	giz = getGizzard(instanceName);
	if(debug) {
	  IO::en("getGizzard(\"%s\") = 0x%x",instanceName.c_str(), giz);
	}
	// this should be the last reference to cmpbox after the erase
	::ccafe::CmpBox_shared rc = getInstance(instanceName); 
	instances.erase(instanceName);

	// Here we don't need to deal with notify 
	// Listeners because that is a binding issue.
	// the cmpbox destructor cleans up everything but connections.
	// the cmpbox destructor will be invoked on leaving this
	// function, because noone else should have a reference.
}

  //======================================================================
int ConnectionFramework::connect(const char* fromName, const char* fromPortName, 
                                  const char* toName, const char* toPortName) {
  return directConnect(fromName, fromPortName, toName, toPortName);
}

  //======================================================================
void ConnectionFramework::nullPortMessage(std::string name, ccafeopq::ExceptionType et) {
    std::string sb = "!Port name ";
    sb += name;
    switch(et) {
    case ccafeopq::Correct:
      return;
    case ccafeopq::PortNotConnected:
      sb += " is not connected.";
      IO::en(sb);
      break;
    case ccafeopq::PortNotDefined:
      sb += " is not defined.";
      IO::en(sb);
      break;
    default:
      IO::en("WeirdError in ConnectionFramework::getOpaquePort");
    }
}

  //======================================================================
int  ConnectionFramework::directConnect(
  const char* providerComp,
  const char* providerPortName, 
  const char* userComp,
  const char* userPortName)
{
  const char *fromName = providerComp;
  const char *fromPortName = providerPortName;
  const char *toName = userComp;
  const char *toPortName = userPortName;

  Gizzard *fromG = getGizzard(fromName);
  if(fromG == 0) {
    IO::en(":-( Instance: %s does not exist (0) in", fromName);
    IO::en("directConnect(%s, %s, %s, %s)\n",fromName, fromPortName, toName, toPortName);
    return -1;
  }

  Gizzard *toG = getGizzard(toName);
  if (toG == 0) {
    IO::en(":-( Instance: %s does not exist (1) in", toName);
    IO::en("directConnect(%s, %s, %s, %s)\n",fromName, fromPortName, toName, toPortName);
    return -1;
  }

  const ::std::vector< ProviderPortData > fromInfo = fromG->getProvidesPorts();
  ::std::vector< int > fromPIa =
     ServicesHelper::getProvidesIndexByName(fromInfo, fromPortName);

  if(fromPIa.size() > 1) {
    IO::en(":-( %s not unique in %s for connection in", 
	   fromPortName,fromName);
    IO::en("directConnect(%s, %s, %s, %s)\n",fromName, fromPortName, toName, toPortName);
    return -1;
  }
  if(fromPIa.size() == 0) {
    IO::en(":-( %s has no corresponding ProvidesPort named %s", 
	     fromName, fromPortName);
    IO::en("directConnect(%s, %s, %s, %s)\n",fromName, fromPortName, toName, toPortName);
    return -1;
  }

  ProviderPortData fromPI = fromInfo[fromPIa[0]]; // CHECKDC(fromPI);
  ccafeopq::ExceptionType gopstatus = ccafeopq::Correct;
  ccafeopq::Port* fromPort = fromG->getOpaquePort(fromPortName, gopstatus);
  if(fromPort == 0) {
    nullPortMessage(fromPortName,gopstatus);
    IO::en(";-( Unconnected port in component %s", fromName);
    return -1;
  }

  const ::std::vector< UserPortData > toInfo =
     toG->getUsesPortRegister(); // Gizzard-specific call.
  ::std::vector< int > toPIa =
     ServicesHelper::getUsesIndexByName(toInfo, toPortName);
  if(toPIa.size() == 0) {
    IO::en("Bad connection for component: %s\nNo Matching UsesPort to connect to.", toName);
    return -1;
  }
  if(toPIa.size() > 1) {
    IO::en(":-( UsesPort name not unique");
    return -1;
  }
  UserPortData toPI = toInfo[toPIa[0]]; // CHECKDC(toPI);


  if (debug || true) {
    ::std::string umess = toPI.toString();
    IO::en("userPI = %s", umess.c_str());
    ::std::string pmess = fromPI.toString();
    IO::en("provPI = %s", pmess.c_str());
  }

  /** ConnectionEventService fire events. */
  // user
  ConnectedConnectionEvent *toEvt = new ConnectedConnectionEvent(toPI);
  ccafeopq::connectionevents::ConnectionEvent_shared toEvt_shared(toEvt);
  // provider
  ConnectedConnectionEvent *fromEvt = new ConnectedConnectionEvent(fromPI);
  ccafeopq::connectionevents::ConnectionEvent_shared fromEvt_shared(fromEvt);

  toEvt->setpreChange(true);
  fromEvt->setpreChange(true);

  toG->getOCES()->fireConnectEvent(toEvt_shared);
  fromG->getOCES()->fireConnectEvent(fromEvt_shared);

  // username, provided port, providerportname, providercomponent
  toG->connectUsesPort(toPI.getPortName(), fromPort, fromPortName, fromG);

  toEvt->setpreChange(false);
  fromEvt->setpreChange(false);
  toG->getOCES()->fireConnectEvent(toEvt_shared);
  fromG->getOCES()->fireConnectEvent(fromEvt_shared);

  return 0;
}

int ConnectionFramework::disconnectAll(const char* componentInstanceName) {
  Gizzard* giz = getGizzard(componentInstanceName);
  ::std::vector< ConnectionID_ptr > cv = giz->getConnections();
  for (size_t i = cv.size(); i > 0 ; i--) {
    ConnectionID_ptr c = cv[i-1];
    if(c->isActive()) {
      std::string gupn = c->getUserPortName();
      std::string gugin =  c->getUser()->getInstanceName();
      std::string gppn =  c->getProviderPortName();
      std::string gpgin = c->getProvider()->getInstanceName();
      IO::en("Warning, disconnecting Port: %s used by Component: %s"
	     " from Port: %s provided by Component %s "
	     "that has not been released"
	     "\ndisconnecting anyway ...", 
	     gupn.c_str(),
	     gugin.c_str(),
	     gppn.c_str(),
	     gpgin.c_str()
	     );
    }
    disconnect(c->getProvider(), c->getProviderPortName(),
	             c->getUser(), c->getUserPortName()
	            );
  }
  return 0;
    
}

//======================================================================
int ConnectionFramework::disconnect(const ::ccafeopq::ComponentID_shared fromC,
                                    const ::std::string & fromPortName, 
                                    const ::ccafeopq::ComponentID_shared toC,
                                    const ::std::string & toPortName) {

  return disconnect(fromC->getInstanceName(), fromPortName,
                    toC->getInstanceName(), toPortName);

}

  //======================================================================
int ConnectionFramework::disconnect(const char* fromName, const char* fromPortName, 
                                    const char* toName,   const char* toPortName) {
  return directDisconnect(fromName, fromPortName, toName, toPortName);
}

  //======================================================================
int ConnectionFramework::disconnect( const ::std::string & fromName, const ::std::string & fromPortName, const 	::std::string & toName, const   ::std::string & toPortName) {
  return directDisconnect(fromName.c_str(), fromPortName.c_str(),
                          toName.c_str(), toPortName.c_str());
}

  //======================================================================
int  ConnectionFramework::directDisconnect(const char* fromName, const char* fromPortName, 
                                           const char* toName,   const char* toPortName)
{
  if(debug) {
    IO::en("ConnectionFramework::directDisconnect: entry fromName = %s "
	   "fromPortName = %s toName = %s toPortName = %s", 
	   fromName, fromPortName, toName, toPortName);
  }
  Gizzard *fromG = getGizzard(fromName);
  if(!fromG) {
    IO::en(":-( Instance: %s does not exist (2)\n", fromName);
    return -2;
  }
  
  if(debug) {
    IO::en("disconnect entry");
  }
  Gizzard *toG = getGizzard(toName);
  if (toG == 0) {
    IO::en(":-( Instance: %s does not exist (3)\n", toName);
    return -2;
  }

  const ::std::vector< ProviderPortData > fromInfo = fromG->getProvidesPorts();
  if (fromInfo.size() == 0) { return -1; }
  ::std::vector< int > fromPIa = 
    ServicesHelper::getProvidesIndexByName(fromInfo, fromPortName);
  if(fromPIa.size() > 1) {
    IO::en(":-( %s not unique in %s for connection", 
	   fromPortName,fromName);
    return -2;
  }
  if(fromPIa.size() == 0) {
    IO::en(":-( %s has no corresponding ProvidesPort named %s", 
	     fromName, fromPortName);
    return -2;
  }
  ProviderPortData fromPI = fromInfo[fromPIa[0]]; // CHECKDC(fromPI);

  const ::std::vector< UserPortData > toInfo =
    toG->getUsesPortRegister(); // Gizzard-specific call.
  ::std::vector< int > toPIa = 
    ServicesHelper::getUsesIndexByName(toInfo, toPortName);
  if(toPIa.size() == 0) {
    IO::en("Bad connection for component: %s\nNo Matching UsesPort to connect to.", toName);
    return -2;
  }
  if(toPIa.size() > 1) {
    IO::en(":-( UsesPort name not unique");
    return -2;
  }
  UserPortData toPI = toInfo[toPIa[0]];

  /** New ConnectionEventService fire event. */
  DisconnectingConnectionEvent *toEvt = new DisconnectingConnectionEvent(toPI);
  ccafeopq::connectionevents::ConnectionEvent_shared toEvt_shared(toEvt);

  DisconnectingConnectionEvent *fromEvt = new DisconnectingConnectionEvent(fromPI);
  ccafeopq::connectionevents::ConnectionEvent_shared fromEvt_shared(fromEvt);

  toEvt->setpreChange(true);
  fromEvt->setpreChange(true);
  toG->getOCES()->fireDisconnectEvent(toEvt_shared);
  fromG->getOCES()->fireDisconnectEvent(fromEvt_shared);

  toG->disconnectUsesPort(toPIa[0]);

  toEvt->setpreChange(false);
  fromEvt->setpreChange(false);
  toG->getOCES()->fireDisconnectEvent(toEvt_shared);
  fromG->getOCES()->fireDisconnectEvent(fromEvt_shared);
  
  return 0;
}

  //======================================================================
::std::vector< ::std::string > ConnectionFramework::instanceNames() {

  ::std::vector< ::std::string > v;
  ::std::map< ::std::string, ::ccafe::CmpBox_shared >::iterator pos;
  for ( pos = instances.begin(); pos != instances.end(); ++pos)
  {
    v.push_back(pos->first);
  }
  return v;
}

::std::map< std::string, ccafe::CmpBox_shared >
ConnectionFramework::getInstances()
{
	return instances;
}

::ccafeopq::ConnectionID_shared ConnectionFramework::getConnectionID(const char* uc, const char* up, const char* pc, const char* pp)
{
  ::ccafeopq::ConnectionID_shared connid;
  Gizzard * ug = getGizzard(uc);
  Gizzard * pg = getGizzard(pc);
  if (ug == 0 ) {
    IO_en2("getConnectionID called with unknown user component %s", uc);
    return connid;
  }
  if (pg == 0 ) {
    IO_en2("getConnectionID called with unknown provider component %s", pc);
    return connid;
  }
  const ::std::vector< UserPortData > updv = ug->getUsesPorts();
  ::std::vector< int > pi = ServicesHelper::getUsesIndexByName(updv, up);
  if (pi.size() == 1) {
    const ::std::vector< ConnectionID_ptr > cpv = 
      updv[pi[0]].getConnectionIDs();
    int loc;
    loc = ConnectionID_impl::indexOfConnection(cpv, up, pp, ug, pg);
    if (loc != -1) {
      connid = cpv[loc];
    }
  }
  return connid;
}

::std::vector < ::ccafeopq::ConnectionID_shared > ConnectionFramework::getConnectionIDs(  const ::std::string & userName, const ::std::string & usingPortName,  const ::std::string & providerName, const ::std::string & providingPortName) throw (::ccafeopq::Exception )
{
  ::std::vector< ::ccafeopq::ConnectionID_shared > connlist;
  ::ccafeopq::ConnectionID_shared connid;
  Gizzard * ug = getGizzard(userName);
  Gizzard * pg = getGizzard(providerName);
  if (ug == 0 ) {
    IO_en2("getConnectionIDs called with unknown user component %s", userName.c_str());
    return connlist;
  }
  if (pg == 0 ) {
    IO_en2("getConnectionID called with unknown provider component %s", providerName.c_str());
    return connlist;
  }
  const ::std::vector< UserPortData > updv = ug->getUsesPorts();
  ::std::vector< int > pi = ServicesHelper::getUsesIndexByName(updv, usingPortName);
  if (pi.size() == 1) {
    const ::std::vector< ConnectionID_ptr > cpv = 
      updv[pi[0]].getConnectionIDs();
    size_t loc;
    for (loc = 0; loc < cpv.size(); loc++) {
      connid = cpv[loc];
      if (!connid || ! (providingPortName == connid->getProviderPortName()) ) {
	continue;
      }
      ::ccafeopq::ComponentID_shared cid = connid->getProvider();
      if ( ! cid) { continue; }
      if (!( cid->getInstanceName() == providerName) ) { continue; }
      connlist.push_back(connid);
    }
  } // else something is really sick...
  return connlist;
}

ComponentFactory_shared ConnectionFramework::getBaseComponentFactory()
{
  return ocf;
}

/** see cca.sidl */
::ccafeopq::TypeMap_shared ConnectionFramework::getConnectionProperties( ::ccafeopq::ConnectionID_shared & conn)
{
  ::ccafeopq::TypeMap_shared tm;
  if (!conn) { return tm; }
  ConnectionID_ptr ccid = 
    ::boost::shared_dynamic_cast<ConnectionID_impl >(conn);
  if (!ccid) { return tm; }
  tm = ccid->getProperties();
  return tm;
}

void ConnectionFramework::setConnectionProperties( ::ccafeopq::ConnectionID_shared & connID,  ::ccafeopq::TypeMap_shared & map) throw ( ::ccafeopq::Exception )
{
  ::ccafeopq::TypeMap_shared tm;
  if (!connID) { return; }
  ConnectionID_ptr ccid = 
    boost::shared_dynamic_cast<ConnectionID_impl >(connID);
  if (!ccid) { return; }
  ccid->setProperties(map); 
}

void ConnectionFramework::setPortProperties( ::ccafeopq::ComponentID_shared & cid, const ::std::string & portname,  ::ccafeopq::TypeMap_shared & map) throw (::ccafeopq::Exception )
{
	if (!cid) {
		whine( "setPortProperties called with bogus ComponentID");
	}
	Gizzard *giz = getGizzard(cid->getInstanceName());
	if (giz == 0) {
		// whine( ::ccafeopq::BadComponentID, "setPortProperties called with bogus ComponentID");
		whine( "setPortProperties called with bogus ComponentID");
		// not reached
	}
	giz->setPortProperties(portname, map);
}

int ConnectionFramework::setPortProperty(const ::std::string & instanceName, const std::string & portName,
                       const std::string & key, const std::string & valueType, const std::string & value)
{
	Gizzard *giz = getGizzard(instanceName);
	if (giz == 0) {
		return -1;
	}
	::ccafeopq::TypeMap_shared tmptm = giz->createTypeMap();
	int err = ::gov::sandia::util::TypeMap::putValueByStrings(tmptm, key, valueType, value);
	if (err) { return err; }
	try {
		giz->setPortProperties(portName, tmptm);
		return 0;
	}
	catch ( std::exception &e )
	{
		return -1;
	}
}



::ccafeopq::TypeMap_shared ConnectionFramework::getPortProperties( ::ccafeopq::ComponentID_shared & cid, const ::std::string & portname) throw ( ::ccafeopq::Exception )
{
	if (!cid) {
		whine( "getPortProperties called with bogus ComponentID");
	}
	Gizzard *giz = getGizzard(cid->getInstanceName());
	if (giz == 0) {
		// whine( ::ccafeopq::BadComponentID, "getPortProperties called with bogus ComponentID");
		whine( "getPortProperties called with bogus ComponentID");
		// not reached
	}
	return giz->getPortProperties(portname);
}

::ccafeopq::TypeMap_shared ConnectionFramework::getPortProperties(  const ::std::string & cname,  const ::std::string & portname) throw ()
{
	if (cname.size() == 0) {
		whine( "getPortProperties called with bogus Component name");
	}
	::ccafeopq::TypeMap_shared res;
	Gizzard *giz = getGizzard(cname);
	if (giz == 0) {
		return res;
	}
	try {
		res = giz->getPortProperties(portname);
		return res;
	} catch (...) 
	{
		return res;
	}
}


/** see cca.sidl */
::std::vector< ::ccafeopq::ConnectionID_shared > ConnectionFramework::getConnectionIDs( ::std::vector< ::ccafeopq::ComponentID_shared> & clist)
{
  ::std::vector< ::ccafeopq::ConnectionID_shared > result;
  ::std::vector< ConnectionID_ptr > matches;
  // iterate over comps. 
  for (size_t i = 0; i < clist.size(); i++) {
    if (!clist[i] ) { continue; }
    Gizzard * g = getGizzard( clist[i]->getInstanceName() );
    if ( !g) { continue; }
	  ::std::vector< ConnectionID_ptr > complist = g->getConnections();
    // loop over conns
    for (size_t j = 0; j < complist.size(); j++) {
      if ( ConnectionID_impl::indexOfConnection(matches, complist[j]) == -1) {
        matches.push_back(complist[j]);
      }
    }
  }
  for (size_t k = 0; k < matches.size(); k++)
  {
    result.push_back(matches[k]);
  }
  return result;
}


  //======================================================================
/** Remove an already instantiated component from the Arena. */
void ConnectionFramework::removeInstantiatedComponent(const std::string & instanceName) {
	if(debug) {
		IO::en("ConnectionFramework::removeInstantiatedComponent: in");
		IO::en("instanceName = %s", instanceName.c_str());
	}
	Gizzard *giz = 0;

	giz = getGizzard(instanceName);
        if (giz == 0) {
	  IO::en("getGizzard(\"%s\") = 0. No such instance.",instanceName.c_str());
          return;
        }
	if(debug) {
	  IO::en("getGizzard(\"%s\") = 0x%x",instanceName.c_str(), giz);
	}
	// this should be the last reference to cmpbox after the erase
	::ccafe::CmpBox_shared rc = getInstance(instanceName); 

	if (rc != 0) {
		if (rc->internal == false) { return; } // insiders can't blow away outsiders
		instances.erase(instanceName);
		if (giz != 0) {
			rc->comp->setServices(0); 
		}
	}
}

  //======================================================================

/*CFREE*/ char * ConnectionFramework::getConfiguration(const char * instanceName, const char * portInstanceName) {
  
  Gizzard *g = getGizzard(instanceName);
  if (g == 0) {
    std::string sb = "!ConnectionFramework::getConfiguration: Component ";
    sb += instanceName;
    sb += " does not exist.";
    IO::en(sb);
    return STRDUP("");
  }
  
  ccafeopq::Port *p;
  ccafeopq::ExceptionType status = ccafeopq::Correct;
  p = g->getOpaquePort(portInstanceName, status);
  if (p == 0) {
    nullPortMessage(portInstanceName,status);
    IO::en(";-( Unconnected configuration port in component %s", instanceName);
    return STRDUP("");
  }

  // begine OPAQUE_PORT case
  if ( p->supportsKind(ccafeopq::OPAQUE_PORT) ) 
  {
    ::std::string prefix = instanceName;
    prefix += " ";
    prefix += portInstanceName;
    // try nonwrapped opq internal from dialog service
    StringableParameterPort *spp = 0;
    spp = dynamic_cast<StringableParameterPort *>(p);
    if (spp != 0) {
	char *ds;
	std::string sppr = spp->getConfigurationString(prefix);
	ds = STRDUP(sppr.c_str());
	return ds;
    }
    ccafeopq::ports::BasicParameterPort *bpp;
    bpp = dynamic_cast<ccafeopq::ports::BasicParameterPort *>(p);
    if (bpp != 0) {
      char *ds;
      ::ccafeopq::TypeMap_shared tm = bpp->readConfigurationMap();
      ccafe::ParameterPort_Impl ppi(tm,true);
      std::string sppr = ppi.getConfigurationString(prefix);
      ds = STRDUP(sppr.c_str());
      return ds;
    }
  }
#ifdef HAVE_CLASSIC
  // begin CLASSIC_PORT case
  if(p->getKind() == ccafeopq::CLASSIC_PORT) {
    ClassicOpaquePort * cp = dynamic_cast<ClassicOpaquePort*>(p);
    if (cp == 0) {
      IO_en3("!Opaque port doesn't wrap claimed classic port in"
        " component instance: %s and port instance: %s", 
        instanceName, portInstanceName);
      return STRDUP("");
    }
    classic::gov::cca::Port * gcp = cp->getClassicPort();
    if (gcp == 0) {
      IO_en3("!Classic ParameterPort null for"
        " component instance: %s and port instance: %s", 
        instanceName, portInstanceName);
      return STRDUP("");
    }
    ::std::string prefix = instanceName;
    prefix += " ";
    prefix += portInstanceName;
    ParameterPort * pp;
    // try classic crap
    pp = dynamic_cast<ParameterPort*>(gcp);
    if ( pp != 0 ) {
      char *result;
      result = pp->getConfigurationString(const_cast<char *>(prefix.c_str()));
      return result;
    }
    // try wrapped opq internal from dialog service
    StringableParameterPort *spp = 0;
    spp = dynamic_cast<StringableParameterPort *>(gcp);
    if (spp != 0) {
	char *ds;
	std::string sppr = spp->getConfigurationString(prefix);
	ds = STRDUP(sppr.c_str());
	return ds;
    }
    std::string sb = 
      "!Specified portName to ConnectionFramework->getConfiguration() "
      "must be of type ParameterPort or ccafeopq::ParameterPort portName: ";
    sb += portInstanceName;
    sb += " maps to type: ";
#ifdef HAVE_TYPEID
    sb += (typeid(p).name());
#else
    sb += "{typeid() unsupported.}";
#endif
    IO::en(sb);
    return STRDUP("");
  } // end classic_port case
#endif // HAVE_CLASSIC
  IO_dn3("!ParameterPort not of supported flavor (classic, babel) for"
    " component instance: %s and port instance: %s {or required binding is not configured into ccafe}", 
    instanceName, portInstanceName);
  return STRDUP("");
}

std::string ConnectionFramework::deriveConfigurationString(const std::string & prefix,
		::ccafeopq::TypeMap_shared pptm)
{
	// FIXME deriveConfigurationString(p,t);
	std::string s;
	// for type in String, Bool, Double, Float, Int, Long
	// make a tab for the set by type, if there, and total on tab
	// < 7.
	return STRDUP("");
}

std::string ConnectionFramework::deriveConfigurationString(const std::string & prefix,
		::ccafeopq::TypeMap_shared pptm, const std::string & key)
{
	// FIXME deriveConfigurationString(p,t, k);
	std::string s;
	// for type in String, Bool, Double, Float, Int, Long
	// make a tab for the set by type, if there, and total on tab
	// < 7.
	return STRDUP("");
}

// returns 0 if ok
int ConnectionFramework::insertConfigurationString( ::ccafeopq::TypeMap_shared pptm, const std::string & key, const std::string & value)
{
	// fixme insertConfigurationString
	if (!pptm) { return -1; }
	int err;
	std::string kts = ::gov::sandia::util::TypeMap::stringType(pptm, key);
	err = ::gov::sandia::util::TypeMap::putValueByStrings(pptm, key, kts, value);
	return err;
}

  //======================================================================

/*CFREE*/ char * ConnectionFramework::getConfiguration(const char * instanceName, const char * portInstanceName, const char *fieldName) {
  
  Gizzard *g = getGizzard(instanceName);
  if (g == 0) {
    std::string sb = "!ConnectionFramework::getConfiguration: Component ";
    sb += instanceName;
    sb += " does not exist.";
    IO::en(sb);
    return STRDUP("");
  }
  
  ccafeopq::Port *p;
  ccafeopq::ExceptionType status = ccafeopq::Correct;
  p = g->getOpaquePort(portInstanceName, status);
  if (p == 0) {
    nullPortMessage(portInstanceName,status);
    IO::en(";-( Unconnected configuration port in component %s", instanceName);
    return STRDUP("");
  }
  // begin opaque case . could be full or basic.
  if ( p->supportsKind(ccafeopq::OPAQUE_PORT)) 
  {
    ::std::string prefix = instanceName;
    prefix += " ";
    prefix += portInstanceName;
    // try nonwrapped opq internal from dialog service
    StringableParameterPort *spp = 0;
    spp = dynamic_cast<StringableParameterPort *>(p);
    if (spp != 0) {
      char *ds;
      std::string sppr = spp->getConfigurationString(prefix,fieldName);
      ds = STRDUP(sppr.c_str());
      return ds;
    }
    ccafeopq::ports::BasicParameterPort *bpp;
    bpp = dynamic_cast<ccafeopq::ports::BasicParameterPort *>(p);
    if (bpp != 0) {
      char *ds;
      ::ccafeopq::TypeMap_shared tm = bpp->readConfigurationMap();
      ccafe::ParameterPort_Impl ppi(tm,true);
      std::string sppr = ppi.getConfigurationString(prefix,fieldName);
      ds = STRDUP(sppr.c_str());
      return ds;
    }
  }

#ifdef HAVE_CLASSIC
  // begin classic case 
  if(p->getKind() == ccafeopq::CLASSIC_PORT) { 
    ClassicOpaquePort * cp = dynamic_cast<ClassicOpaquePort*>(p);
    if (cp == 0) {
      IO_en3("!Opaque port doesn't wrap claimed classic port in"
        " component instance: %s and port instance: %s", 
        instanceName, portInstanceName);
      return STRDUP("");
    }
    classic::gov::cca::Port * gcp = cp->getClassicPort();
    if (gcp == 0) {
      IO_en3("!Classic ParameterPort null for"
        " component instance: %s and port instance: %s", 
        instanceName, portInstanceName);
      return STRDUP("");
    }
    std::string infix = instanceName;
    infix += " ";
    infix += portInstanceName;
    // try classic crap
    ParameterPort *pp;
    pp = dynamic_cast<ParameterPort*>(gcp);
    if ( pp != 0) {
      char * result;
      result = pp->getConfigurationString(const_cast<char *>(infix.c_str()), 
                                          const_cast<char *>(fieldName));
      return result;
    }
    // try wrapped opq internal from dialog service
    StringableParameterPort *spp = 0;
    spp = dynamic_cast<StringableParameterPort *>(gcp);
    if (spp != 0) {
	char *ds;
	std::string sppr = spp->getConfigurationString(infix, fieldName);
	ds = STRDUP(sppr.c_str());
	return ds;
    }
    std::string sb = 
      "!Specified classic portName to ConnectionFramework->getConfiguration() "
      "must be of type ParameterPort or ccafeopq::ParameterPort portName: ";
    sb += portInstanceName;
    sb += " maps to type: ";
#ifdef HAVE_TYPEID
    sb += (typeid(p).name());
#else
    sb += "{typeid() unsupported.}";
#endif
    IO::en(sb);
    return STRDUP("");
  } // end classic_port case
#endif // HAVE_CLASSIC


  IO_en3("ParameterPort not of known type for"
    " component instance: %s and port instance: %s", 
   instanceName, portInstanceName);
  return STRDUP("");
}

  //======================================================================
/** Set the parameter data from a component, if it has any.
    Return the parameters if it takes any, or the empty
    string if it doesn't. */

char * ConnectionFramework::setConfiguration(const char * instanceName, const char * portInstanceName, const char *fieldName, const char * configuration) {
  
  Gizzard *g = getGizzard(instanceName);
  if (g == 0) {
    std::string sb = "!ConnectionFramework::setConfiguration: Component ";
    sb += instanceName;
    sb += " does not exist.";
    IO::en(sb);
    return (char *)"";
  }

  ccafeopq::Port *p;
  ccafeopq::ExceptionType status = ccafeopq::Correct;
  p = g->getOpaquePort(portInstanceName, status);
  if (p == 0) {
    nullPortMessage(portInstanceName,status);
    IO::en(";-( Unconnected configuration port in component %s", instanceName);
    return (char *)"";
  }

  IO_dn5("Setting-config %s %s %s = %s", instanceName, portInstanceName, fieldName, configuration);
  // begin opaque case 
  if ( p->supportsKind( ccafeopq::OPAQUE_PORT))
  {
    ::std::string prefix = instanceName;
    prefix += " ";
    prefix += portInstanceName;
    // try nonwrapped opq internal from dialog service or OPPF
    // FIXME need oppf in this branch.
    StringableParameterPort *spp = 0;
    spp = dynamic_cast<StringableParameterPort *>(p);
    if (spp != 0) {
      int err;
      IO_dn1("Setting-config-opq.");
      err = spp->setConfigurationString(fieldName, configuration);
      if (err) {
	IO_dn2("Error putting parameter encountered (%d).",err);
        return (char *)"";
      }
      return const_cast<char *>(configuration);
    }
    ccafeopq::ports::BasicParameterPort *bpp;
    bpp = dynamic_cast<ccafeopq::ports::BasicParameterPort *>(p);
    if (bpp != 0) {
      int err;
      IO_dn1("Setting-config-basic.");
      ::ccafeopq::TypeMap_shared tm = bpp->readConfigurationMap();
      ccafe::ParameterPort_Impl ppi(tm,true);
      err = ppi.setConfigurationString(fieldName, configuration);
      if (err) {
	IO_dn2("Error putting parameter encountered (%d).",err);
        return (char *)"";
      }
      bpp->writeConfigurationMap(tm);
      return const_cast<char *>(configuration);
    }
  }


#ifdef HAVE_CLASSIC
  // begin classic case
  if(p->getKind() == ccafeopq::CLASSIC_PORT) {
    ClassicOpaquePort* cp = dynamic_cast<ClassicOpaquePort*>(p);
    if (cp == 0) {
        IO_en3("!Opaque port doesn't wrap claimed classic port in"
            " component instance: %s and port instance: %s",
            instanceName, portInstanceName);
        return (char *)"";
    }
    classic::gov::cca::Port * gcp = cp->getClassicPort();
    if (gcp == 0) {
        IO_en3("!Classic ParameterPort null for"
        " component instance: %s and port instance: %s",
        instanceName, portInstanceName);
        return (char *)"";
    }

    ParameterPort *pp;
    pp = dynamic_cast<ParameterPort*>(gcp);
    if(pp != 0) {
      BaseParameter *bp;
      bp = pp->getParameter(const_cast<char *>(fieldName));
      if(bp == 0 || bp->setValue(const_cast<char *>(configuration))) {
        return (char *)"";
      }
      IO_dn1("Setting-config-classic.");
      return const_cast<char *>(configuration);
    }

    // try wrapped opq internal from dialog service or OPPF
    StringableParameterPort *spp = 0;
    spp = dynamic_cast<StringableParameterPort *>(gcp);
    if (spp != 0) {
      int err = spp->setConfigurationString(fieldName, configuration);
      IO_dn1("Setting-config-classic-as-stringable.");
      if (err) {
        return (char *)"";
      }
      return const_cast<char *>(configuration);
    }

    std::string sb =
      "!Specified classic portName to ConnectionFramework->setConfiguration() "
       "must be of type ParameterPort or ccafeopq::ParameterPort portName: ";
    sb += portInstanceName;
    sb += " maps to type: ";
#ifdef HAVE_TYPEID
    sb += (typeid(p).name());
#else
    sb += "{typeid() unsupported.}";
#endif
    IO::en(sb);
    return (char *)"";
  } // end classic case
#endif // HAVE_CLASSIC

  IO_en3("Port given not of known ParameterPort type for"
   " component instance: %s and port instance: %s", 
   instanceName, portInstanceName);
  return (char*)"";
}

  //======================================================================
/** Call go for a specific component/port */

int ConnectionFramework::goOne(const char * instanceName, const char * portInstanceName) {
  
  Gizzard *g = getGizzard(instanceName);
  if (g == 0) {
    ::std::string sb = "ConnectionFramework::goOne: no";
    sb += " component named ";
    sb += instanceName;
    IO::en(sb.c_str());
    return -1;
  }

  ccafeopq::Port *p;
  ccafeopq::ExceptionType status;
  p = g->getOpaquePort(portInstanceName, status);

  if (p == 0) {
    nullPortMessage(portInstanceName,status);
    IO::en("Named GoPort does not exist in component %s", instanceName);
    return -1;
  }
  ccafeopq::GoPort *pp;
  pp = dynamic_cast< ccafeopq::GoPort * >(p); 
  if(pp == 0) {
    ::std::string sb = "Specified portName to "
       "ConnectionFramework.goOne() "
       "must be of type ::ccafeopq::GoPort portName: ";
    sb += portInstanceName;
    sb += " maps to type: ";
#ifndef _NO_TYPEID
    sb += typeid(p).name();
#else
    sb += "{typeid() unsupported.}";
#endif
    IO::en(sb.c_str());
    return -1;
  }
  IO_dn3("GoPort for component instance: %s and port instance: %s about "
	 "to be called", instanceName, portInstanceName);
  ::ccafeopq::TypeMap_shared tm = g->getPortProperties(portInstanceName);
  std::string threaded = tm->getString("GoPort_Spawns_Thread", "");
  IO_dn2("threaded = %s", threaded.c_str());
  if(threaded != "true") {
    IO_dn1("Normal Go called");
    return pp->go();
  } else { /* It is threaded. */
    IO_dn1("The port has \"GoPort_Spawns_Thread\" set to \"true\"");
#ifdef CCAFE_THREADS
    std::string s1 = instanceName;
    std::string s2 = portInstanceName;
    std::string key = s1 + "::" + s2;
    GoThread_shared gt = goThreads[key];
    if((gt.get() != NULL) && (gt->isRunning())) {
      IO_en3("Attempt to create a thread when another thread is active"
	     " we don't allow that right now.  "
	     "Maybe it is generically a bad idea.\n"
	     " Attempted to create another GoPort thread for Component: %s "
	     "and Port: %s", instanceName, portInstanceName);
      return -1;
    }      

    GoThread_shared goth (new GoThread());
    if(goth->create_thread(pp)) {
      IO_en1(":-( GoPort thread spawn failed.");
      return -1;
    }
    goThreads[key] = goth;
    return 0;
#else
    IO_en3("Attempt to create a thread when threads disabled in ccaffeine."
     " You must configure ccaffeine --enable-threads to use threaded GoPorts."
     " Refused to create GoPort thread for Component: %s "
     "and Port: %s", instanceName, portInstanceName);
    return -1;
#endif
  }
}

  //======================================================================
/** Return the list of key/value pairs.  The vector returned should be deleted, but not its elements.
 * it takes the string values from the property map, but not those of other types.
 * */
std::vector< std::string > ConnectionFramework::getComponentProperties(const std::string & instanceName) {
  std::vector< std::string > props;
  Gizzard *g = getGizzard(instanceName);
  if (!g) { return props; }
  ::ccafeopq::TypeMap_shared pt = g->getComponentInternalPropertyMap();

  std::vector< std::string > keys = pt->getAllKeys( ::ccafeopq::String );
  std::string value;
  for (size_t i = 0; i < keys.size() ; i++) {
    props.push_back(keys[i]);
    value = pt->getString(keys[i],"");
    props.push_back(value);
  }
  return props;

}

  //======================================================================
/** Return the value corresponding to key, or NULL if key unknown. */
const std::string ConnectionFramework::getComponentProperty(const std::string & instanceName, const std::string & key) {
  Gizzard *g = getGizzard(instanceName);
  if (!g) { return ""; }
  ::ccafeopq::TypeMap_shared pt = g->getComponentInternalPropertyMap();
  if (pt->typeOf(key) != ::ccafeopq::String ) {
	  return "";
  }
  const std::string value = pt->getString(key,"");
  return value;
}

  //======================================================================
/** Set the value corresponding to key. Returns nonzero if an error occurs. */
void ConnectionFramework::setComponentProperty(const std::string & instanceName, const std::string & key, const std::string & value) {
  Gizzard *g = getGizzard(instanceName);
  if (!g) { return; }
  ::ccafeopq::TypeMap_shared pt = g->getComponentInternalPropertyMap();
  if (pt->typeOf(key) != ::ccafeopq::NoType && pt->typeOf(key) != ::ccafeopq::String) {
	  IO_en4("!Error: ConnectionFramework::setComponentProperty(%s, %s, %s) called on key which has a value type other than String.",
		instanceName.c_str(), key.c_str(), value.c_str());
	  return;
  }
  pt->putString(key,value);
}

  //======================================================================
::ccafeopq::TypeMap_shared ConnectionFramework::getComponentPropertyTypeMap(const ::std::string & instanceName)
{
  Gizzard *g = getGizzard(instanceName);
  if (g) {
    return g->getPropertyMap();
  }
  IO_en2("getComponentPropertyTypeMap: unknown instance %s given",
	  instanceName.c_str());
  ::ccafeopq::TypeMap_shared rt;
  return rt;
}
  
  //======================================================================
bool ConnectionFramework::setComponentPropertyTypeMap(const ::std::string & instanceName, ::ccafeopq::TypeMap_shared & tm)
{
  Gizzard *g = getGizzard(instanceName);
  if (g) {
    g->setPropertyMapData(tm);
    return true;
  }
  IO_en2("setComponentProperyTypeMap: unknown instance %s given",
	  instanceName.c_str());
  return false;
}

  /** =============  repository activities =============  */

/** this section makes calls on the global component factory.
The ConnectionFramework class needs to be rewritten 
as a ConnectionContainer and to take
a factory and a repository(list) as constructor arguments. */

  //======================================================================
  /** Set current module path from an argv. Input will only be read
      until argc or a null element is reached. Normal return is 0. */
int ConnectionFramework::setRepositoryPath(char **argv, int argc) {

  std::vector< std::string > cp;
  for (int i = 0; i < argc; i++) { cp.push_back(argv[i]); }
  return setRepositoryPath( cp);
}

int ConnectionFramework::setRepositoryPath(const std::vector< std::string > & p)
{
  // ComponentFactory * fwkCF = dynamic_cast<ComponentFactory *>(ocf);
  // assert(fwkCF != 0);
  ocf->setComponentPath(p);
  ocf->indexComponentPath();
  std::vector< ccafeopq::ComponentClassDescription_shared > cl =
	  ocf->getComponentClasses();
  int count = cl.size();
  IO::en("# There are allegedly %d classes in the component path", count);
  
  return 0;
}

  //======================================================================
  /** Get current component path as an argv. Path returned
      is null-terminated and has argc elements. Not yours
      to mess with the content or destroy. */
std::vector< std::string > ConnectionFramework::getRepositoryPath() {
  std::vector< std::string > result = ocf->getComponentPath();
  return result;
}
  
  //======================================================================
  /** Return the list of unloaded classes and where
      they come from. argc is an even number, as you
      get the library location following each class entry.
      Class names will be unique, whether or not component
      writers worried about that.
. */
std::vector<std::string> ConnectionFramework::getRepositoryClasses() {
  std::vector<std::string >result;
  ccafeopq::ComponentFactory *rawcf = ocf.get();
  ComponentFactory * fwkCF = dynamic_cast<ComponentFactory *>(rawcf);
  assert(fwkCF != 0);
  result = fwkCF->getUnloadedComponents();

  return result;
}
  
  //======================================================================
  /** Move a class from the repository to the
    pallet. Probably involves a dynamic load.
    returns 0 if transferred successfully.
  */
int ConnectionFramework::loadRepositoryClass(const char *className, bool global, bool lazy) {
  int result;
  ccafeopq::ComponentFactory *rawcf = ocf.get();
  ComponentFactory * fwkCF = dynamic_cast<ComponentFactory *>(rawcf);
  assert(fwkCF != 0);
  result = fwkCF->loadPalette(className, global, lazy);
  refreshPallet();
  return result;
}

int ConnectionFramework::loadPorts(const std::string & libPathName)
{
  int result;
  ccafeopq::ComponentFactory *rawcf = ocf.get();
  ComponentFactory * fwkCF = dynamic_cast<ComponentFactory *>(rawcf);
  assert(fwkCF != 0);
  result = fwkCF->loadPorts(libPathName);
  return result;
}

void ConnectionFramework::refreshPallet() {
  std::vector< std::string > ret;
  for(size_t i = 0, n = xCmptFactories.size();i < n ; i++) {
    std::vector< std::string > q = 
      xCmptFactories[i]->getComponentClassNames();
    ret.insert(ret.end(), q.begin(), q.end());
  }
  std::vector< std::string > p = ocf->getComponentClassAliases();
  ret.insert(ret.end(), p.begin(), p.end());
  pallet = ret;
}

  //======================================================================


  /** Implements ComponentChangedListener.  Signal a change in the
      Component's status. */
void ConnectionFramework::componentChanged(ComponentChangedEvent* evt) {
  // Test to see if we are in the midst of creating the component, if
  // so don't send out a bunch of events until after it is created
  // completely.
  if(!instantiatingComponent) {
    size_t nl = cmptChgLsnrs.size();
    for ( ; nl > 0; nl--) {
      ComponentChangedListener* l = cmptChgLsnrs[nl-1];
      CHECKDC(l);
      l->componentChanged(evt);
    }
  }

  if(evt->getChangeType() == ComponentChangedEvent::PORT_ADDED) {
    std::string svcType = "::ccafeopq::ComponentFactory";
    std::string pt = evt->getPortType();
    std::string pi = evt->getPortInstance();
    if ( pt == "::ccafeopq::ComponentFactory" || pt == "ccafeopq::ComponentFactory" ) {
      IO_dn1("Adding a ComponentFactory");
      ::ccafe::CmpBox_shared box = getInstance(evt->getComponentInstance());
      if (box == 0) {
	      whine("ConnFwk: componentChanged got bogus component event");
      }
      XCmptFactory_shared xs = DefaultXCmptFactory::createFactory(box->giz, pi);
      addXCmptFactory(xs);
    }
  }

  if (evt->getChangeType() == ComponentChangedEvent::PORT_REGISTERED) {
    std::string pt = evt->getPortType();
    const char * pi = evt->getPortInstance();
    const char * comp = evt->getComponentInstance();
    // service registry
    std::string svcType = "::ccafeopq::ServiceRegistry";
    if ( pt == "::ccafeopq::ServiceRegistry" || pt == "ccafeopq::ServiceRegistry") {
      IO_dn1("Connecting to FRAMEWORK.ServiceRegistry");
      connect("FRAMEWORK","ServiceRegistry", comp, pi);
      // the disconnect will occor by unregister so long as port
      // is released by caller.
    }
    // printfport
    if ( pt == "JPrintfPort" ) {
      IO_dn1("Connecting to FRAMEWORK.JPrintfPort");
      connect("FRAMEWORK","JPrintfPort", comp, pi);
    }
    // builderservices
    if ( pt == "ccafeopq::BuilderService" || pt == "::ccafeopq::BuilderService" ) {
      IO_dn1("Connecting to FRAMEWORK.BuilderService");
      connect("FRAMEWORK","BuilderService", comp, pi);
    }
    // guiservice
    if ( pt == "ccafeopq::GUIService" || pt == "::ccafeopq::GUIService" ) {
      IO_dn1("Connecting to FRAMEWORK.GUIService");
      connect("FRAMEWORK","GUIService", comp, pi);
    }
     // make it go away...
    if ( pt == "::classic::hack::BuilderService" ) {
      IO_dn1("Connecting to FRAMEWORK.fakeBuilderService");
      connect("FRAMEWORK","fakeBuilderService", comp, pi);
    }
    std::string serverName;
    std::string serverPort;
    if ( osr->serverAvailable(pt, serverName, serverPort) ) {
      IO_dn3("Connecting to %s.%s", serverName.c_str(), serverPort.c_str());
      connect(serverName.c_str(), serverPort.c_str(), comp, pi);
    }
  }

}

void  ConnectionFramework::addXCmptFactory(XCmptFactory_shared xs) {
  xCmptFactories.push_back(xs);
}

  //======================================================================
  /** Add a listener for a change in the status of a component. */
void ConnectionFramework::addComponentChangedListener(ComponentChangedListener* l)
{
  cmptChgLsnrs.push_back(l);
}

  //======================================================================
Gizzard *ConnectionFramework::getGizzard(const ::std::string & name)
{
  ::ccafe::CmpBox_shared o = getInstance(name);
  if (!o) { return 0; }
  Gizzard *g = o->giz;
  return g;
}

Gizzard *ConnectionFramework::getGizzard(const char *instanceName)
{
	return getGizzard( ::std::string(instanceName));
}

std::vector< ccafeopq::ComponentID_shared > 
ConnectionFramework::getComponentsThatUse(const std::string& portType) {
  std::vector< ccafeopq::ComponentID_shared > ret;
  ::std::map< ::std::string, ::ccafe::CmpBox_shared >::iterator pos;
  for ( pos = instances.begin(); pos != instances.end(); ++pos)
  {
    ::ccafe::CmpBox_shared b = pos->second;
    if (b->giz->usesThisPortType(portType)) {
      ret.push_back(b->giz->getComponentID());
    }
  }
  return ret;
}


std::vector< ccafeopq::ComponentID_shared > 
ConnectionFramework::getComponentsThatProvide(const std::string& portType) {
  std::vector< ccafeopq::ComponentID_shared > ret;
  ::std::map< ::std::string, ::ccafe::CmpBox_shared >::iterator pos;
  for ( pos = instances.begin(); pos != instances.end(); ++pos)
  {
    ::ccafe::CmpBox_shared b = pos->second;
    if (b->giz->providesThisPortType(portType)) {
      ret.push_back(b->giz->getComponentID());
    }
  }
  return ret;
}

  //======================================================================
void * ConnectionFramework::getFrameItem(std::string name)
{
  if (frameItems.find(name) != frameItems.end()) {
    return frameItems[name];
  }
  return 0;
}

  //======================================================================
void ConnectionFramework::putFrameItem(std::string name, void * item)
{

  // new, nonnull, store it.
  if (item != 0 && frameItems.find(name) == frameItems.end())
  {
    frameItems[name] = item;
    return;
  }

  // old item, null, remove it.
  if (item == 0 && frameItems.find(name) != frameItems.end())
  {
    frameItems.erase(name);
    return;
  }

  // old item, new value, ignore it.
  IO::en("# Attempt to reset a frame item without setting to 0 first");

}


