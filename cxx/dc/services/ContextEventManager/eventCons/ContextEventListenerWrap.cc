#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons/ContextEventListenerWrap.hh"
ccafeopq::event::ContextEventListenerWrap::ContextEventListenerWrap() {}
ccafeopq::event::ContextEventListenerWrap::~ContextEventListenerWrap() {}

const int ccafeopq::event::ContextEventListenerWrap::numEventTypes = CONTEXTEVENT_LISTENER_WRAP_NUM_EVENT_TYPES;

ccafeopq::event::ContextEventListenerWrap::ContextEventListenerWrap(enum ccafeopq::event::type::ContextEventType cet, ContextEventListener_shared l)
{
	listener = l;

	for (int i = 0; i < numEventTypes; i++)
	{
		listenFor[i] = false;
	}
	includeEventType(cet);
}

/** Fire the wrapped event, if its type list matches. */
void 
ccafeopq::event::ContextEventListenerWrap::fire(enum ccafeopq::event::type::ContextEventType type, ContextEvent_shared ce)
{
	if (listenFor[type])
	{
		listener->contextActivity(ce);
	}
}

/** Include cet in the events listened for.  */
void 
ccafeopq::event::ContextEventListenerWrap::includeEventType(enum ccafeopq::event::type::ContextEventType cet)
{
	if (cet < 0 || cet >= numEventTypes )
	{
		return;
	}

	if (cet == ccafeopq::event::type::ALL) // fixme enum
	{
		for (int i = 0; i < numEventTypes; i++)
		{
			listenFor[i] = true;
		}
	}

	listenFor[cet] = true;
}

/** Remove cet in the events listened for.  */
void 
ccafeopq::event::ContextEventListenerWrap::omitEventType(enum ccafeopq::event::type::ContextEventType cet)
{
	// fixme omitEventType
}
