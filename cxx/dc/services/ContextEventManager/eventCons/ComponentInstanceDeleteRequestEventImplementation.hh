#ifndef ccafeopq_event_ComponentInstanceDeleteRequestEventImplementation_hh_seen
#define ccafeopq_event_ComponentInstanceDeleteRequestEventImplementation_hh_seen
namespace ccafeopq {
namespace event {
/** 
   Advise others that a component is going away soon.
*/
class ComponentInstanceDeleteRequestEventImplementation
: public virtual ContextEventImplementation
, public virtual ComponentInstanceDeleteRequestEvent
{
private:
	std::string className ;
	ccafeopq::ComponentID_shared dyingCID ;
public:

	ComponentInstanceDeleteRequestEventImplementation( const std::string & deadClassName, ccafeopq::ComponentID_shared dying, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum);

	/** never call this constructor except for certain testing. */
	ComponentInstanceDeleteRequestEventImplementation();
	virtual ~ComponentInstanceDeleteRequestEventImplementation();

	/////// ComponentInstanceDeleteRequestEvent_sharedspecific functions
	/** @return class name of component instance to be deleted. */
	virtual const std::string getComponentClassName();

	/** @return id of component instance to be deleted. */
	virtual ccafeopq::ComponentID_shared getComponentID();
  
	//ContextEventImplementation_functions;

};  // end interface ComponentInstanceDeleteRequestEventImplementation

/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/services/ContextEventManager/eventCons/ComponentInstanceDeleteRequestEventImplementation.hh,v 1.2 2004/04/02 02:17:54 baallan Exp $ */

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // ComponentInstanceDeleteRequestEventImplementation_hh_seen
