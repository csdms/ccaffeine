#ifndef ccafeopq_event_ComponentInstanceDeletedEventImplementation_hh_seen
#define ccafeopq_event_ComponentInstanceDeletedEventImplementation_hh_seen
namespace ccafeopq {
namespace event {
/** 
   Advise others that a component is gone.
*/
class ComponentInstanceDeletedEventImplementation
: public virtual ContextEventImplementation
, public virtual ComponentInstanceDeletedEvent
{
private:
	std::string deadClass;
	std::string deadInstance;
public:
	ComponentInstanceDeletedEventImplementation( const std::string & dClass,  const std::string & dInstance, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum);

	/** never call this constructor except for certain testing. */
	ComponentInstanceDeletedEventImplementation();
	virtual ~ComponentInstanceDeletedEventImplementation();


	/////// ComponentInstanceDeletedEvent_sharedspecific functions
	/** @return class of deleted component. */
	virtual const std::string getDeadComponentClassName();

	/** @return name of deleted component. */
	virtual const std::string getDeadComponentInstanceName();

	//ContextEventImplementation_functions;

};  // end interface ComponentInstanceDeletedEventImplementation

/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/services/ContextEventManager/eventCons/ComponentInstanceDeletedEventImplementation.hh,v 1.2 2004/04/02 02:17:54 baallan Exp $ */

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // ComponentInstanceDeletedEventImplementation_hh_seen
