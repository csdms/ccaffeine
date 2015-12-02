/* GENERATED FILE. Do not edit. DATAEventProcessor.hh.sed */
#ifndef ccafeopq_event_ComponentInstanceDeleteRequestEventProcessor_hh
#define ccafeopq_event_ComponentInstanceDeleteRequestEventProcessor_hh

namespace ccafeopq {
namespace event {

/** Handles processing of ComponentInstanceDeleteRequestEvents for the ContextEventManager (generated code).
 */
class ComponentInstanceDeleteRequestEventProcessor : public virtual EventProcessor
{

private:
	ContextEventManager *cem;

public:

	/** unit test only*/
	ComponentInstanceDeleteRequestEventProcessor();
	virtual ~ComponentInstanceDeleteRequestEventProcessor();

	/** create an event processor tied to the source.
	The processor uses the matching listener list
	data item from the source.
	*/
	ComponentInstanceDeleteRequestEventProcessor(ContextEventManager * source);

	/** process the events */
	virtual void process(ContextEvent_shared eData);

};

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // ccafeopq_event_ComponentInstanceDeleteRequestEventProcessor_hh
