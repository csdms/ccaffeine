#include "dc/export/AllExport.hh"
namespace ccafeopq {
namespace event {
class ContextEventManager;
} ENDSEMI
} ENDSEMI
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"

#include "dc/services/ContextEventManager/ContextEventManager.hh"


int64_t
ccafeopq::event::ContextEventManager::nextNum() 
{
	seqNumGenerator++;
	return seqNumGenerator;
}

void
ccafeopq::event::ContextEventManager::initProcessorList()
{
	addProcessor(&cfep);
	addProcessor(&ciarep);
	addProcessor(&ciaep);
	addProcessor(&cidrep);
	addProcessor(&cidep);
	addProcessor(&ccep);
	addProcessor(&paep);
	addProcessor(&pdep);
}
  
void 
ccafeopq::event::ContextEventManager::addProcessor(ccafeopq::event::EventProcessor *ep)
{
	processors.push_back(ep);
}

#define no_semicolon

#define GETLIST(T)  \
ccafeopq::event::T##EventListenerList \
ccafeopq::event::ContextEventManager::get##T##EventListeners() \
{ \
	return the##T##EventListeners; \
} \

GETLIST(ComponentFactory) no_semicolon
GETLIST(ComponentInstanceAddRequest) no_semicolon
GETLIST(ComponentInstanceAdded) no_semicolon
GETLIST(ComponentInstanceDeleteRequest) no_semicolon
GETLIST(ComponentInstanceDeleted) no_semicolon
GETLIST(ContextConnection) no_semicolon
GETLIST(PortActivity) no_semicolon
GETLIST(PortDefinition) no_semicolon


ccafeopq::event::ContextEventManager::~ContextEventManager() 
{
	processors.clear();
}

ccafeopq::event::ContextEventManager::ContextEventManager() 
{
	initProcessorList();
	seqNumGenerator = 0;
	debug = true;
	initDone = false;
}

void 
ccafeopq::event::ContextEventManager::log(std::string s)
{
	if (!debug)
	{
		return;
	}
	std::cerr << "ContextEventManager." << s << std::endl;
}

#if 0
Services svc;
/** cca componentness */
void setServices(Services s)
{
// all the logic determining the value of svc is in this function.
// all the port actions are in private functions, because
// we don't want to obscure svc management logic with port logic.
if (svc == null) {
svc = s;
setUpPorts();
} else {
// svc != null
if (s != null) {
 // rant and rave about double call of setServices.
return; // fixme -- throw exception.
}
tearDownPorts();
svc = null;
}
}

/** pairwise listing of the ports we use.
// use componentProperties service?
*/
String[] usesPorts =
{
"ContextExceptionService", "gov.ccafe.ports.ContextExceptionService",
"ListFactory",             "gov.ccafe.ports.ListFactory"
};

/** pairwise listing of ports we provide directly. */
String[] providesPorts =
{
"ContextEventPublisherService", "gov.ccafe.ports.ContextEventPublisherService", 
"ContextEventSubscriberService", "gov.ccafe.ports.ContextEventSubscriberService"
};

void tearDownPorts() throws CCAException
{
for (int i = 0; i < usesPorts.length; i = i+2)
{
try {
svc.unregisterUsesPort(usesPorts[i]);
} catch (CCAException e) {
log("tearDownPorts: "+e);
}
}
for (int i = 0; i < providesPorts.length; i = i+2)
{
try {
svc.removeProvidesPort(providesPorts[i]);
} catch (CCAException e) {
log("tearDownPorts: "+e);
}
}
}

void setUpPorts() throws CCAException
{
for (int i = 0; i < providesPorts.length; i = i+2)
{
svc.addProvidesPort((Port)this,providesPorts[i], providesPorts[i+1], null);
}
for (int i = 0; i < usesPorts.length; i = i+2)
{
svc.registerUsesPort(usesPorts[i], usesPorts[i+1], null);
}
// if we delegate anything, it must be here.
}

bool initDone = false;
int CCAFE_start()
{
if (initDone)
{
return 0;
}
initDone = true;
ces = (ContextExceptionService)svc.getPort("ContextExceptionService");
ListFactory lf = (ListFactory)svc.getPort("ListFactory");

cell = (ContextEventListenerList)lf.createList("ContextEventListenerList");
theComponentFactoryEventListeners = (ComponentFactoryEventListenerList)
lf.createList( "ComponentFactoryEventListenerList" );
theComponentInstanceAddRequestEventListeners = (ComponentInstanceAddRequestEventListenerList)
lf.createList( "ComponentInstanceAddRequestEventListenerList" );
theComponentInstanceAddedEventListeners  = (ComponentInstanceAddedEventListenerList)
lf.createList( "ComponentInstanceAddedEventListenerList" );
theComponentInstanceDeleteRequestEventListeners = (ComponentInstanceDeleteRequestEventListenerList)
lf.createList( "ComponentInstanceDeleteRequestEventListenerList" );
theComponentInstanceDeletedEventListeners = (ComponentInstanceDeletedEventListenerList)
lf.createList( "ComponentInstanceDeletedEventListenerList" );
theContextConnectionEventListeners = (ContextConnectionEventListenerList)
lf.createList( "ContextConnectionEventListenerList" );
thePortActivityEventListeners = (PortActivityEventListenerList)
lf.createList( "PortActivityEventListenerList" );
thePortDefinitionEventListeners = (PortDefinitionEventListenerList)
lf.createList( "PortDefinitionEventListenerList" );
lf = null;
svc.releasePort("ListFactory");
return 0;

}

void CCAFE_finish()
{
for (int i = 0; i < usesPorts.length; i = i+2)
{
try {
svc.releasePort(usesPorts[i]);
} catch (CCAException e) {
log("CCAFE_finish: "+e);
}
}
}

#endif // 0

//////////////////////////////////////////////////////////////
// ContextEventPublisherService multi-client port interface
//////////////////////////////////////////////////////////////

int 
ccafeopq::event::ContextEventManager::fireEvent( ContextEvent_shared eData)
{
	if (!eData)
	{
		return -1;
	}
	size_t i;
	// log("fireEvent###: "+eData.getContextEventDescription());
	// fixme range check eData type
	for (i = 0; i < cell.size(); i++)
	{
		ContextEventListener_shared l = cell[i];
		l->contextActivity(eData);
	}

	for (i = 0; i < processors.size(); i++)
	{
		EventProcessor * ep = processors[i];
		ep->process(eData);
	}
	return 0;
}

ccafeopq::event::ContextEvent_shared
ccafeopq::event::ContextEventManager::createContextEvent( enum ccafeopq::event::type::ContextEventType ceType, ccafeopq::ComponentID_shared source, int sourceKey) 
{
	ContextEventImplementation * e =
		new ContextEventImplementation(ceType, source, sourceKey, nextNum());
	ContextEvent_shared x(e);
	return x;
}

ccafeopq::event::ComponentFactoryEvent_shared
ccafeopq::event::ContextEventManager::createComponentFactoryEvent( ccafeopq::ComponentID_shared factoryID, ccafeopq::TypeMap_shared factoryPortProperties, enum ccafeopq::event::type::ContextEventType cet, ccafeopq::ComponentID_shared source, int sourceKey)
{
	ComponentFactoryEventImplementation *e =
		new ComponentFactoryEventImplementation(cet, source, sourceKey, nextNum(), 
	 		factoryID, factoryPortProperties);
	ComponentFactoryEvent_shared x(e);
	return x;
}

ccafeopq::event::ComponentInstanceAddRequestEvent_shared
ccafeopq::event::ContextEventManager::createComponentInstanceAddRequestEvent( std::string & componentClassName, std::string & componentInstanceName, ccafeopq::ComponentID_shared source, int sourceKey)
{
	ComponentInstanceAddRequestEventImplementation * e = 
		new ComponentInstanceAddRequestEventImplementation(
	 		componentClassName, componentInstanceName, 
	 		source, sourceKey, nextNum());
	ComponentInstanceAddRequestEvent_shared x(e);
	return x;
}

ccafeopq::event::ComponentInstanceAddedEvent_shared 
ccafeopq::event::ContextEventManager::createComponentInstanceAddedEvent( std::string & componentClassName, ccafeopq::ComponentID_shared cid, ccafeopq::ComponentID_shared source, int sourceKey)
{

	ComponentInstanceAddedEventImplementation * e =
	new ComponentInstanceAddedEventImplementation(
		source, sourceKey, nextNum(),
		componentClassName, cid);
	ComponentInstanceAddedEvent_shared x(e);
	return x;
}

ccafeopq::event::ComponentInstanceDeleteRequestEvent_shared
ccafeopq::event::ContextEventManager::createComponentInstanceDeleteRequestEvent( std::string & componentClassName, ccafeopq::ComponentID_shared cid, ccafeopq::ComponentID_shared source, int sourceKey)
{
	ComponentInstanceDeleteRequestEventImplementation *e =
		new ComponentInstanceDeleteRequestEventImplementation(
			componentClassName, cid,
			source,sourceKey,nextNum());
	ComponentInstanceDeleteRequestEvent_shared x(e);
	return x;
}

ccafeopq::event::ComponentInstanceDeletedEvent_shared
ccafeopq::event::ContextEventManager::createComponentInstanceDeletedEvent( std::string & deadComponentClassName, std::string & deadComponentInstanceName, ccafeopq::ComponentID_shared source, int sourceKey)
{
	ComponentInstanceDeletedEventImplementation * e =
		new ComponentInstanceDeletedEventImplementation(
			deadComponentClassName, deadComponentInstanceName,
			source, sourceKey, nextNum());
	ComponentInstanceDeletedEvent_shared x(e);
	return x;
}

ccafeopq::event::ContextConnectionEvent_shared
ccafeopq::event::ContextEventManager::createContextConnectionEvent( ccafeopq::ComponentID_shared user, std::string & userPortName, ccafeopq::TypeMap_shared userPortProperties, ccafeopq::ComponentID_shared provider, std::string & providerPortName,ccafeopq::TypeMap_shared providerPortProperties, enum ccafeopq::event::type::ContextEventType cet, ccafeopq::ComponentID_shared source, int sourceKey)
{
	ContextConnectionEventImplementation *e =
		new ContextConnectionEventImplementation(
			cet, source, sourceKey, nextNum(),
			user, userPortName, userPortProperties, 
			provider, providerPortName, providerPortProperties);
	ContextConnectionEvent_shared x(e);
	return x;
}

ccafeopq::event::PortActivityEvent_shared
ccafeopq::event::ContextEventManager::createPortActivityEvent( ccafeopq::ConnectionID_shared connID, std::string & portType, enum ccafeopq::event::type::ContextEventType cet, ccafeopq::ComponentID_shared source, int sourceKey)
{
// log("createPortActivityEvent(connid, "+ cet+", "+source.getInstanceName());
	PortActivityEventImplementation * e =
		new PortActivityEventImplementation(
			cet, source, sourceKey, nextNum(), connID,
		       	connID->getUserPortName(), portType, connID->getUser());
	PortActivityEvent_shared x(e);
	return x;
}

ccafeopq::event::PortActivityEvent_shared
ccafeopq::event::ContextEventManager::createPortActivityEvent( std::string & portName, std::string & portType, enum ccafeopq::event::type::ContextEventType cet, ccafeopq::ComponentID_shared source, int sourceKey)
{
// log("createPortActivityEvent(."+portName+",type,"+ cet+", "+source.getInstanceName());
	ccafeopq::ConnectionID_shared oconnid;
	PortActivityEventImplementation * e =
		new PortActivityEventImplementation(
			cet, source, sourceKey, nextNum(),
			oconnid, portName, portType, source);
	PortActivityEvent_shared x(e);
	return x;
}

ccafeopq::event::PortDefinitionEvent_shared
ccafeopq::event::ContextEventManager::createPortDefinitionEvent( ccafeopq::ComponentID_shared component, std::string & name, std::string & type, ccafeopq::TypeMap_shared portProperties, enum ccafeopq::event::type::ContextEventType cet, ccafeopq::ComponentID_shared source, int sourceKey)
{
	PortDefinitionEventImplementation *e =
		new PortDefinitionEventImplementation( cet, name, type, 
			source, sourceKey, nextNum(), component, portProperties);
	PortDefinitionEvent_shared x(e);
	return x;
}

//////////////////////////////////////////////////////////////
// end ContextEventPublisherService multi-client port interface
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
// ContextEventSubscriberService multi-client port interface
//////////////////////////////////////////////////////////////

void 
ccafeopq::event::ContextEventManager::addContextEventListener(ContextEventListener_shared l,  enum ccafeopq::event::type::ContextEventType ceType)
{
	// fixme addContextEventListener
}

void 
ccafeopq::event::ContextEventManager::removeContextEventListener( ContextEventListener_shared l, enum ccafeopq::event::type::ContextEventType ceType) 
{
	// fixme removeContextEventListener
}

#define ADDLISTENER(T) \
void  \
ccafeopq::event::ContextEventManager::add##T##EventListener( T##EventListener_shared l) \
{ \
	if (l != 0) \
	{ \
		log("add##T##EventListener###."); \
		the##T##EventListeners.push_back(l); \
	} \
}
ADDLISTENER(ComponentFactory) no_semicolon
ADDLISTENER(ComponentInstanceAddRequest) no_semicolon
ADDLISTENER(ComponentInstanceAdded) no_semicolon
ADDLISTENER(ComponentInstanceDeleteRequest) no_semicolon
ADDLISTENER(ComponentInstanceDeleted) no_semicolon
ADDLISTENER(ContextConnection) no_semicolon
ADDLISTENER(PortActivity) no_semicolon
ADDLISTENER(PortDefinition) no_semicolon

#define REMOVELISTENER(T) \
void  \
ccafeopq::event::ContextEventManager::remove##T##EventListener( T##EventListener_shared l) \
{ \
}

REMOVELISTENER(ComponentFactory) no_semicolon
REMOVELISTENER(ComponentInstanceAddRequest) no_semicolon
REMOVELISTENER(ComponentInstanceAdded) no_semicolon
REMOVELISTENER(ComponentInstanceDeleteRequest) no_semicolon
REMOVELISTENER(ComponentInstanceDeleted) no_semicolon
REMOVELISTENER(ContextConnection) no_semicolon
REMOVELISTENER(PortActivity) no_semicolon
REMOVELISTENER(PortDefinition) no_semicolon

const std::string 
ccafeopq::event::ContextEventManager::getStringFromEnum( enum ccafeopq::event::type::ContextEventType ceType) 
{
	return stringFromEnum(ceType);
}

enum ccafeopq::event::type::ContextEventType 
ccafeopq::event::ContextEventManager::getEnumFromString(const std::string & type) 
{
	return enumFromString(type );
}

//////////////////////////////////////////////////////////////
// end ContextEventSubscriberService multi-client port interface
//////////////////////////////////////////////////////////////
/* on the off chance that efficiency matters, we could make
 * the lookup faster with a map. but noone has a bottleneck at
 * this function.
 */
ccafeopq::event::type::ContextEventType 
ccafeopq::event::ContextEventManager::enumFromString( const std::string & t)
{
#define OCET(k,st) if (t == st) return ccafeopq::event::type::k
	OCET(NONE,"NONE");
	OCET(Error,"Error");
	OCET(ALL,"ALL");
	OCET(ConnectPending,"ConnectPending");
	OCET(Connected,"Connected");
	OCET(DisconnectPending,"DisconnectPending");
	OCET(Disconnected,"Disconnected");
	OCET(ComponentInstanceAddPending,"ComponentInstanceAddPending");
	OCET(ComponentInstanceAdded,"ComponentInstanceAdded");
	OCET(ComponentInstanceDeletePending,"ComponentInstanceDeletePending");
	OCET(ComponentInstanceDeleted,"ComponentInstanceDeleted");
	OCET(PortAddPending,"PortAddPending");
	OCET(PortAdded,"PortAdded");
	OCET(PortRemovePending,"PortRemovePending");
	OCET(PortRemoved,"PortRemoved");
	OCET(PortRegisterPending,"PortRegisterPending");
	OCET(PortRegistered,"PortRegistered");
	OCET(PortUnregisterPending,"PortUnregisterPending");
	OCET(PortUnregistered,"PortUnregistered");
	OCET(PortFetchPending,"PortFetchPending");
	OCET(PortFetched,"PortFetched");
	OCET(PortReleasePending,"PortReleasePending");
	OCET(PortReleased,"PortReleased");
	OCET(FactoryOpened,"FactoryOpened");
	OCET(FactoryClosed,"FactoryClosed");
	OCET(ContextClosing,"ContextClosing");
	return ccafeopq::event::type::NONE;
#undef OCET
}

const std::string 
ccafeopq::event::ContextEventManager::stringFromEnum( enum ccafeopq::event::type::ContextEventType ceType) 
{
#define OCET(k,st) case ccafeopq::event::type::k: s = st; break
	std::string s = "NONE";
	switch(ceType)
	{
	OCET(NONE,"NONE");
	OCET(Error,"Error");
	OCET(ALL,"ALL");
	OCET(ConnectPending,"ConnectPending");
	OCET(Connected,"Connected");
	OCET(DisconnectPending,"DisconnectPending");
	OCET(Disconnected,"Disconnected");
	OCET(ComponentInstanceAddPending,"ComponentInstanceAddPending");
	OCET(ComponentInstanceAdded,"ComponentInstanceAdded");
	OCET(ComponentInstanceDeletePending,"ComponentInstanceDeletePending");
	OCET(ComponentInstanceDeleted,"ComponentInstanceDeleted");
	OCET(PortAddPending,"PortAddPending");
	OCET(PortAdded,"PortAdded");
	OCET(PortRemovePending,"PortRemovePending");
	OCET(PortRemoved,"PortRemoved");
	OCET(PortRegisterPending,"PortRegisterPending");
	OCET(PortRegistered,"PortRegistered");
	OCET(PortUnregisterPending,"PortUnregisterPending");
	OCET(PortUnregistered,"PortUnregistered");
	OCET(PortFetchPending,"PortFetchPending");
	OCET(PortFetched,"PortFetched");
	OCET(PortReleasePending,"PortReleasePending");
	OCET(PortReleased,"PortReleased");
	OCET(FactoryOpened,"FactoryOpened");
	OCET(FactoryClosed,"FactoryClosed");
	OCET(ContextClosing,"ContextClosing");
	default:
		break;
	}
	return s;
#undef OCET
}

