#ifndef ccafeopq_event_DATAEventProcessor_hh
#define ccafeopq_event_DATAEventProcessor_hh

namespace ccafeopq {
namespace event {

/** Handles processing of DATAEvents for the ContextEventManager (generated code).
 */
class DATAEventProcessor : public virtual EventProcessor
{

private:
	ContextEventManager *cem;

public:

	/** unit test only*/
	DATAEventProcessor();
	virtual ~DATAEventProcessor();

	/** create an event processor tied to the source.
	The processor uses the matching listener list
	data item from the source.
	*/
	DATAEventProcessor(ContextEventManager * source);

	/** process the events */
	virtual void process(ContextEvent_shared eData);

};

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // ccafeopq_event_DATAEventProcessor_hh
