#ifndef ccafeopq_event_ComponentInstanceAddRequestEventImplementation_hh_seen
#define ccafeopq_event_ComponentInstanceAddRequestEventImplementation_hh_seen
namespace ccafeopq {
namespace event {
/** 
    Special notes:
    The ComponentAddPending means a request with the data
    available in this interface was made; it does not
    guarantee that the data is consistent or that the
    creation process will succeed.
*/
class ComponentInstanceAddRequestEventImplementation
: public virtual  ContextEventImplementation
, public virtual ComponentInstanceAddRequestEvent
{

private:
	std::string className ;
	std::string instanceName ;
public:

	ComponentInstanceAddRequestEventImplementation( const std::string & cName, const std::string & iName, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum);

	/** never call this constructor except for certain testing. */
	ComponentInstanceAddRequestEventImplementation();
	virtual ~ComponentInstanceAddRequestEventImplementation() {}

	/////// ComponentInstanceAddRequestEvent_sharedspecific functions
	/** class name of requested instance. */
	virtual const std::string getComponentClassName();

	/** name of requested instance. */
	virtual const std::string getComponentInstanceName();

	// ContextEventImplementation_functions;

};  // end interface ComponentInstanceAddRequestEvent

/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/services/ContextEventManager/eventCons/ComponentInstanceAddRequestEventImplementation.hh,v 1.2 2004/04/02 02:17:54 baallan Exp $ */

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // ComponentInstanceAddRequestEventImplementation_hh_seen
