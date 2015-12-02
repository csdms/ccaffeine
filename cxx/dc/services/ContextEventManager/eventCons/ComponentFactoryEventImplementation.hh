#ifndef ccafeopq_event_ComponentFactoryEventImplementation_hh_seen
#define ccafeopq_event_ComponentFactoryEventImplementation_hh_seen
namespace ccafeopq {
namespace event {

/** 
   Notice to interested parties that a new component factory 
   is in play or an old one is going away.
      For ComponentFactoryEvent, the type is
      FactoryPortAdded
      FactoryPortRemovePending
*/
class ComponentFactoryEventImplementation 
: public virtual ContextEventImplementation
, public virtual ComponentFactoryEvent
{
private:
	ccafeopq::ComponentID_shared factoryID ;
	ccafeopq::TypeMap_shared fpp ;

public:
	/** never call this constructor except for certain testing. */
	ComponentFactoryEventImplementation();
	virtual ~ComponentFactoryEventImplementation() {}

	ComponentFactoryEventImplementation(enum ccafeopq::event::type::ContextEventType factoryEventType, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum, ccafeopq::ComponentID_shared factory, ccafeopq::TypeMap_shared factoryPortProperties);

	/////// ComponentFactoryEvent_sharedspecific functions
	/** @return the componentid of the factory being mentioned. */
	virtual ccafeopq::ComponentID_shared getFactoryID();

	/** @return the properties of the port that provides the factory function */
	virtual ccafeopq::TypeMap_shared getFactoryPortProperties();
  
	 // ContextEventImplementation_functions;

};  // end class ComponentFactoryEventImplementation

/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/services/ContextEventManager/eventCons/ComponentFactoryEventImplementation.hh,v 1.2 2004/04/02 02:17:54 baallan Exp $ */

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // ComponentFactoryEventImplementation_hh_seen
