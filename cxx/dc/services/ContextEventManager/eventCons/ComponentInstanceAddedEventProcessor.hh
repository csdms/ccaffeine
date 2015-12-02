/* GENERATED FILE. Do not edit. DATAEventProcessor.hh.sed */
#ifndef ccafeopq_event_ComponentInstanceAddedEventProcessor_hh
#define ccafeopq_event_ComponentInstanceAddedEventProcessor_hh

namespace ccafeopq {
namespace event {

/** Handles processing of ComponentInstanceAddedEvents for the ContextEventManager (generated code).
 */
class ComponentInstanceAddedEventProcessor : public virtual EventProcessor
{

private:
	ContextEventManager *cem;

public:

	/** unit test only*/
	ComponentInstanceAddedEventProcessor();
	virtual ~ComponentInstanceAddedEventProcessor();

	/** create an event processor tied to the source.
	The processor uses the matching listener list
	data item from the source.
	*/
	ComponentInstanceAddedEventProcessor(ContextEventManager * source);

	/** process the events */
	virtual void process(ContextEvent_shared eData);

};

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // ccafeopq_event_ComponentInstanceAddedEventProcessor_hh
