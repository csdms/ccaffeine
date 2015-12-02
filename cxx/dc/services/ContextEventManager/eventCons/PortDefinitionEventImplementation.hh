#ifndef ccafeopq_event_PortDefinitionEventImplementation_hh_seen
#define ccafeopq_event_PortDefinitionEventImplementation_hh_seen
namespace ccafeopq {
namespace event {
/** 
   This interface lets components be notified about ports
   coming and going on other components.
   For PortDefinitionEvent, the type is one of subset
      PortAddPending,
      PortAdded,
      PortRemovePending,
      PortRemoved,
      PortRegisterPending,
      PortRegistered,
      PortUnregisterPending,
      PortUnregistered.
   Special notes:
   PortAddPending events do not guarantee that a PortAdded
   event will follow. The port addition may fail if there
   is a port naming conflict yet to be discovered.
*/
class PortDefinitionEventImplementation
: public virtual ContextEventImplementation
, public virtual PortDefinitionEvent
{
private:
	ccafeopq::ComponentID_shared portCID ;
	ccafeopq::TypeMap_shared prop ;
	std::string pName;
	std::string pType;
public:

	PortDefinitionEventImplementation(enum ccafeopq::event::type::ContextEventType cet, const std::string & name, const std::string & type, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum, ccafeopq::ComponentID_shared  portSource, ccafeopq::TypeMap_shared portProps);

	/** never call this constructor except for certain testing. */
	PortDefinitionEventImplementation();

	
	virtual ~PortDefinitionEventImplementation();

	/** @return id of component now providing or registering a port. */
	ccafeopq::ComponentID_shared getComponent();

	/** @return properties of the port being provided or registered. */
	ccafeopq::TypeMap_shared getPortProperties();

	const std::string getPortName();
	const std::string getPortType();
  
	//ContextEventImplementation_functions;

};  // end class PortDefinitionEventImplementation



/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/services/ContextEventManager/eventCons/PortDefinitionEventImplementation.hh,v 1.2 2004/04/02 02:17:54 baallan Exp $ */

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // PortDefinitionEventImplementation_hh_seen
