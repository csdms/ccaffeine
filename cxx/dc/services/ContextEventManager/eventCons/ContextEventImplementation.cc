#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#include "dc/services/ContextEventManager/ContextEventManager.hh"

#define NS ccafeopq::event::ContextEventImplementation

NS::~ContextEventImplementation()
{
// fixme
}

NS::ContextEventImplementation()
{
// dummy constructor for unit test
}

NS::ContextEventImplementation(enum ccafeopq::event::type::ContextEventType cet, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum)
{
	contextEventType = cet;
	sourceID = cid; // not null? FIXME
	sourceKey = sKey;
	sequenceNumber = seqNum;
	description = ccafeopq::event::ContextEventManager::stringFromEnum(cet);
}

/** Returns the integer standard type for the event. If the
event is not one of the standard types, then this returns
ContextEventType.NONE. 
*/
enum ccafeopq::event::type::ContextEventType
NS::getContextEventType()
{
	return contextEventType;
}

/** 
Fetch the component generating the event.
@return the componentID of the component generating the event,
or null if the container itself generated the event.
*/
ccafeopq::ComponentID_shared 
NS::getContextEventSourceID()
{
	return sourceID;
}

/** Within a source component, there may be more than one emitter. Key
is the self-proclaimed serial number of the emitter, unique
within the scope of the result from getSourceID.
*/
int 
NS::getContextEventSourceKey()
{
	return sourceKey;
}

/** For each source:key pair events are emitted in a monotonically
increasing sequence. It is hoped 64 bits is enough to handle
long runs.
*/
int64_t
NS::getContextEventSequenceNumber()
{
	return sequenceNumber;
}

std::string
NS::getContextEventDescription()
{
	return description;
}

void 
NS::setContextEventDescription( const std::string & desc) 
{
	description = desc + "{was " + description + "}";
}
