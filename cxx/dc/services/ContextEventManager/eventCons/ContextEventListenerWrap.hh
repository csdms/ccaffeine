#ifndef ccafeopq_event_ContextEventListenerWrap_hh
#define ccafeopq_event_ContextEventListenerWrap_hh

namespace ccafeopq {
namespace event {
#define CONTEXTEVENT_LISTENER_WRAP_NUM_EVENT_TYPES 24
class ContextEventListenerWrap
{
private:
	ContextEventListener_shared listener;
	/** array indexed by event type. */
	bool listenFor[CONTEXTEVENT_LISTENER_WRAP_NUM_EVENT_TYPES];


public:
  /** testing only constructor */
	ContextEventListenerWrap();
	~ContextEventListenerWrap();

	/** see ContextEventType for the proper value of this. */
	static const int numEventTypes;

	ContextEventListenerWrap(enum ccafeopq::event::type::ContextEventType cet, ContextEventListener_shared l);

	/** Fire the wrapped event, if its type list matches. */
	void fire(enum ccafeopq::event::type::ContextEventType type, ContextEvent_shared ce);

	/** Include cet in the events listened for.  */
	void includeEventType(enum ccafeopq::event::type::ContextEventType cet);

	/** Remove cet in the events listened for.  */
	void omitEventType(enum ccafeopq::event::type::ContextEventType cet);

};

} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq
#endif // ccafeopq_event_ContextEventListenerWrap_hh
