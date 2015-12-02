#ifndef ccafeopq_event_EventProcessor_hh
#define ccafeopq_event_EventProcessor_hh
namespace ccafeopq {
namespace event {
/** Derivatives of this interface are registered in ContextEventManager. */
class EventProcessor
{
  /** Fire the event, appropriately cast, to some group of listeners.
      If the event is of the wrong type, do nothing.
   */
public:
	virtual ~EventProcessor(){}
	virtual void process(ContextEvent_shared eData) = 0;

};
} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // end ccafeopq_event_EventProcessor_hh
