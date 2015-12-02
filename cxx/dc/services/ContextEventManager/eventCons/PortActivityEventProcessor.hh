/* GENERATED FILE. Do not edit. DATAEventProcessor.hh.sed */
#ifndef ccafeopq_event_PortActivityEventProcessor_hh
#define ccafeopq_event_PortActivityEventProcessor_hh

namespace ccafeopq {
namespace event {

/** Handles processing of PortActivityEvents for the ContextEventManager (generated code).
 */
class PortActivityEventProcessor : public virtual EventProcessor
{

private:
	ContextEventManager *cem;

public:

	/** unit test only*/
	PortActivityEventProcessor();
	virtual ~PortActivityEventProcessor();

	/** create an event processor tied to the source.
	The processor uses the matching listener list
	data item from the source.
	*/
	PortActivityEventProcessor(ContextEventManager * source);

	/** process the events */
	virtual void process(ContextEvent_shared eData);

};

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // ccafeopq_event_PortActivityEventProcessor_hh
