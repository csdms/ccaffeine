/* GENERATED FILE. Do not edit. DATAEventProcessor.cc.sed */
#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#include "dc/services/ContextEventManager/ContextEventManager.hh"
//#include "dc/services/ContextEventManager/eventCons/ComponentInstanceAddedEventProcessor.hh"


ccafeopq::event::ComponentInstanceAddedEventProcessor::~ComponentInstanceAddedEventProcessor()
{
	cem = 0;
}

ccafeopq::event::ComponentInstanceAddedEventProcessor::ComponentInstanceAddedEventProcessor()
{
	cem = 0;
}

ccafeopq::event::ComponentInstanceAddedEventProcessor::ComponentInstanceAddedEventProcessor(ContextEventManager * source)
{
	cem = source;
}

void 
ccafeopq::event::ComponentInstanceAddedEventProcessor::process(ContextEvent_shared eData)
{
	ComponentInstanceAddedEvent_shared event;
	event = boost::shared_dynamic_cast< ComponentInstanceAddedEvent >(eData);
	if ( !event ) { return; }
	ComponentInstanceAddedEventListenerList ell = cem->getComponentInstanceAddedEventListeners();
	for (size_t i = 0, n = ell.size(); i < n; i++)
	{
		ComponentInstanceAddedEventListener_shared el = ell[i];
		el->doComponentInstanceAdded(event);
	}

}


