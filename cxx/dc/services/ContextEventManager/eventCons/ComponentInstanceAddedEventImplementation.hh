#ifndef ccafeopq_event_ComponentInstanceAddedEventImplementation_hh_seen
#define ccafeopq_event_ComponentInstanceAddedEventImplementation_hh_seen
namespace ccafeopq {
namespace event {
/** 
    This interface is container-scoped while the ConnectionEvent
    interface is component-scoped, thus the two are not redundant.
    Special notes:
    The ComponentAddPending means a request with the data
    available in this interface was made; it does not
    guarantee that the data is consistent or that the
    creation process will succeed.
*/
class ComponentInstanceAddedEventImplementation
: public virtual ContextEventImplementation
, public virtual ComponentInstanceAddedEvent
{
private:
	std::string componentClassName ;
	ccafeopq::ComponentID_shared newComponentID ;
public:

	/** never call this constructor except for certain testing. */
	ComponentInstanceAddedEventImplementation();
	virtual ~ComponentInstanceAddedEventImplementation(){};

	ComponentInstanceAddedEventImplementation(ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum, std::string className, ccafeopq::ComponentID_shared newID);

	/////// ComponentInstanceAddedEvent specific functions
	/** @return classname of component added. */
	virtual const std::string getComponentClassName();

	/** @return id of component added. */
	virtual ccafeopq::ComponentID_shared getComponentID();

	// ContextEventImplementation_functions;

};  // end interface ComponentInstanceAddedEventImplementation



/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/services/ContextEventManager/eventCons/ComponentInstanceAddedEventImplementation.hh,v 1.2 2004/04/02 02:17:54 baallan Exp $ */

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // ComponentInstanceAddedEventImplementation_hh_seen
