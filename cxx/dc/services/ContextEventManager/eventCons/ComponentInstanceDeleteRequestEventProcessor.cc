/* GENERATED FILE. Do not edit. DATAEventProcessor.cc.sed */
#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#include "dc/services/ContextEventManager/ContextEventManager.hh"
//#include "dc/services/ContextEventManager/eventCons/ComponentInstanceDeleteRequestEventProcessor.hh"


ccafeopq::event::ComponentInstanceDeleteRequestEventProcessor::~ComponentInstanceDeleteRequestEventProcessor()
{
	cem = 0;
}

ccafeopq::event::ComponentInstanceDeleteRequestEventProcessor::ComponentInstanceDeleteRequestEventProcessor()
{
	cem = 0;
}

ccafeopq::event::ComponentInstanceDeleteRequestEventProcessor::ComponentInstanceDeleteRequestEventProcessor(ContextEventManager * source)
{
	cem = source;
}

void 
ccafeopq::event::ComponentInstanceDeleteRequestEventProcessor::process(ContextEvent_shared eData)
{
	ComponentInstanceDeleteRequestEvent_shared event;
	event = boost::shared_dynamic_cast< ComponentInstanceDeleteRequestEvent >(eData);
	if ( !event ) { return; }
	ComponentInstanceDeleteRequestEventListenerList ell = cem->getComponentInstanceDeleteRequestEventListeners();
	for (size_t i = 0, n = ell.size(); i < n; i++)
	{
		ComponentInstanceDeleteRequestEventListener_shared el = ell[i];
		el->doComponentInstanceDeleteRequest(event);
	}

}


