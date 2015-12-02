#ifndef ccafeopq_event_ContextEventImplementation_hh_seen
#define ccafeopq_event_ContextEventImplementation_hh_seen
namespace ccafeopq {
namespace event {
/** Container event data mechanism. All the data accesible
    through this interface is relative to (interpretable only
    in the context of) the container in which the event belongs.
    The methods are named with ContextEvent
    so that implementors choosing to roll ContextEvent,
    ConnectionEvent, and generic std::string events ala Indiana
    into a single implementation
    will not have method naming conflicts.
    This interface is container-scoped while the ConnectionEvent
    interface is component-scoped, thus the two are not redundant.
*/
class ContextEventImplementation
: public virtual ContextEvent
{
private:

	enum ccafeopq::event::type::ContextEventType contextEventType;

	ccafeopq::ComponentID_shared sourceID ;
	int sourceKey;
	long sequenceNumber;
	std::string description ;
public:

	/** never call this constructor except for certain testing. */
	ContextEventImplementation();
	virtual ~ContextEventImplementation();

	ContextEventImplementation(enum ccafeopq::event::type::ContextEventType cet, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum);

	/** Returns the integer standard type for the event. If the
	event is not one of the standard types, then this returns
	ccafeopq::event::type::NONE. 
	*/
	virtual enum ccafeopq::event::type::ContextEventType getContextEventType();

	/** 
	Fetch the component generating the event.
	@return the componentID of the component generating the event,
	or null if the container itself generated the event.
	*/
	virtual ccafeopq::ComponentID_shared getContextEventSourceID();

	/** Within a source component, there may be more than one emitter. Key
	is the self-proclaimed serial number of the emitter, unique
	within the scope of the result from getSourceID.
	*/
	virtual int getContextEventSourceKey();

	/** For each source:key pair events are emitted in a monotonically
	increasing sequence. It is hoped 64 bits is enough to handle
	long runs.
	*/
	virtual int64_t getContextEventSequenceNumber();

	/**
	The following additional info, if present, may make the event
	interpretable in the scope of the outermost framework. This
	is handy mainly as that's where the interactive user interface
	will reside.
	<pre>
	containerFullyQualifiedInstanceName,
	componentFullyQualifiedInstanceName,
	callerComponentFullyQualifiedInstanceName,
	calleeComponentFullyQualifiedInstanceName,
	</pre>
	These and others can be included in the std::string description.
	However, the sub-class of the event is what can be guaranteed
	machine interpretable. In some frameworks this function may
	return an XML or other SGML-style string.
	*/
	virtual std::string getContextEventDescription();

	/** Set or amend the description, as determined by the implementation.
	*/
	virtual void setContextEventDescription( const  std::string & desc) ;

};  // end class ContextEventImplementationImplementation

#define ContextEventImplementation_functions \
	virtual enum ccafeopq::event::type::ContextEventType getContextEventType(); \
	virtual ccafeopq::ComponentID_shared getContextEventSourceID(); \
	virtual int getContextEventSourceKey(); \
	virtual int64_t getContextEventSequenceNumber(); \
	virtual std::string getContextEventDescription(); \
	virtual void setContextEventDescription(const std::string & desc) 

/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/services/ContextEventManager/eventCons/ContextEventImplementation.hh,v 1.2 2004/04/02 02:17:54 baallan Exp $ */

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // ContextEventImplementation_hh_seen
