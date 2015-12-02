/* GENERATED FILE. Do not edit. DATAEventProcessor.cc.sed */
#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#include "dc/services/ContextEventManager/ContextEventManager.hh"
//#include "dc/services/ContextEventManager/eventCons/ComponentInstanceAddRequestEventProcessor.hh"


ccafeopq::event::ComponentInstanceAddRequestEventProcessor::~ComponentInstanceAddRequestEventProcessor()
{
	cem = 0;
}

ccafeopq::event::ComponentInstanceAddRequestEventProcessor::ComponentInstanceAddRequestEventProcessor()
{
	cem = 0;
}

ccafeopq::event::ComponentInstanceAddRequestEventProcessor::ComponentInstanceAddRequestEventProcessor(ContextEventManager * source)
{
	cem = source;
}

void 
ccafeopq::event::ComponentInstanceAddRequestEventProcessor::process(ContextEvent_shared eData)
{
	ComponentInstanceAddRequestEvent_shared event;
	event = boost::shared_dynamic_cast< ComponentInstanceAddRequestEvent >(eData);
	if ( !event ) { return; }
	ComponentInstanceAddRequestEventListenerList ell = cem->getComponentInstanceAddRequestEventListeners();
	for (size_t i = 0, n = ell.size(); i < n; i++)
	{
		ComponentInstanceAddRequestEventListener_shared el = ell[i];
		el->doComponentInstanceAddRequest(event);
	}

}


