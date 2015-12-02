#ifndef ccafeopq_event_PortActivityEventImplementation_hh_seen
#define ccafeopq_event_PortActivityEventImplementation_hh_seen
namespace ccafeopq {
namespace event {

/** 
      For PortActivityEvent, the type is one of subset
      PortFetchPending,
      PortFetched,
      PortReleasePending,
      PortReleased.
      Special notes:
      PortFetchPending does not guarantee a PortFetched event, as
      the defined connection may prove bogus. 
      For ArrayUses ports, a separate event occurs for connection.
*/
class PortActivityEventImplementation
: public virtual ContextEventImplementation
, public virtual PortActivityEvent
{

private:
	ccafeopq::ConnectionID_shared connID ;
	std::string userPortName ;
	std::string userPortType ;
	ccafeopq::ComponentID_shared user ;
public:

	PortActivityEventImplementation(enum ccafeopq::event::type::ContextEventType portActivityEventType, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum, ccafeopq::ConnectionID_shared  conn, const std::string & pName, const std::string & pType, ccafeopq::ComponentID_shared userid);

	/** never call this constructor except for certain testing. */
	PortActivityEventImplementation();

	virtual ~PortActivityEventImplementation();

	///// PortActivityEvent_sharedspecific functions
	/** @return connection changing. */
	virtual ccafeopq::ConnectionID_shared getConnection() ;

	/** @return the component getting/releasing one of its port. */
	virtual ccafeopq::ComponentID_shared getComponent();

	/** @return name of port user component is getting/releasing. */
	virtual	const std::string getPortName();

	/** @return type of port being affected. */
	virtual const std::string getPortType();

	//ContextEventImplementation_functions;

};  // end interface PortActivityEventImplementation


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/services/ContextEventManager/eventCons/PortActivityEventImplementation.hh,v 1.2 2004/04/02 02:17:54 baallan Exp $ */

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // PortActivityEventImplementation_hh_seen
