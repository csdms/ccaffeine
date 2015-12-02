#ifndef ccafeopq_event_ContextConnectionEventImplementation_hh_seen
#define ccafeopq_event_ContextConnectionEventImplementation_hh_seen
namespace ccafeopq {
namespace event {
/** 
    This interface is container-scoped while the ConnectionEvent
    interface is component-scoped, thus the two are not redundant.
    Special notes:
    The ConnectPending means a request with the data
    available in this interface was made; it does not
    guarantee that the data is consistent or that the
    connection process will succeed.
*/
class ContextConnectionEventImplementation
: public virtual  ContextEventImplementation
, public virtual ccafeopq::event::ContextConnectionEvent
{
private:
	ccafeopq::ComponentID_shared userCID ;
	ccafeopq::ComponentID_shared providerCID ;
	ccafeopq::TypeMap_shared userProps ;
	ccafeopq::TypeMap_shared providerProps ;
	std::string userPortName ;
	std::string providerPortName ;
public:
	/** never call this constructor except for certain testing. */
	ContextConnectionEventImplementation();
	virtual ~ContextConnectionEventImplementation();

	ContextConnectionEventImplementation(enum ccafeopq::event::type::ContextEventType connectionEventType, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum, ccafeopq::ComponentID_shared user, const std::string & upName, ccafeopq::TypeMap_shared userPortProperties,  ccafeopq::ComponentID_shared provider, const std::string & ppName, ccafeopq::TypeMap_shared providerPortProperties);

	/////// ContextConnectionEvent_sharedspecific functions
	virtual /** @return the providing component id. */
	ccafeopq::ComponentID_shared getProvider();

	/** @return the using component id. */
	virtual ccafeopq::ComponentID_shared getUser() ;

	/** @return the properties of the providing port. */
	virtual ccafeopq::TypeMap_shared getProviderPortProperties() ;

	/** @return the properties of the using port. */
	virtual ccafeopq::TypeMap_shared getUserPortProperties() ;

	/** Provider port instance name.
	@return the name of the providing port.
	*/
	virtual const std::string getProviderPortName() ;

	/** User port instance name.
	@return the name of the using port.
	*/
	virtual const std::string getUserPortName() ;

	//ContextEventImplementation_functions;

};  // end interface ContextConnectionEventImplementation

/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/services/ContextEventManager/eventCons/ContextConnectionEventImplementation.hh,v 1.2 2004/04/02 02:17:54 baallan Exp $ */

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // ContextConnectionEventImplementation_hh_seen
