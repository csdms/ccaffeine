/* GENERATED FILE. Do not edit. DATAEventProcessor.cc.sed */
#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#include "dc/services/ContextEventManager/ContextEventManager.hh"
//#include "dc/services/ContextEventManager/eventCons/ComponentFactoryEventProcessor.hh"


ccafeopq::event::ComponentFactoryEventProcessor::~ComponentFactoryEventProcessor()
{
	cem = 0;
}

ccafeopq::event::ComponentFactoryEventProcessor::ComponentFactoryEventProcessor()
{
	cem = 0;
}

ccafeopq::event::ComponentFactoryEventProcessor::ComponentFactoryEventProcessor(ContextEventManager * source)
{
	cem = source;
}

void 
ccafeopq::event::ComponentFactoryEventProcessor::process(ContextEvent_shared eData)
{
	ComponentFactoryEvent_shared event;
	event = boost::shared_dynamic_cast< ComponentFactoryEvent >(eData);
	if ( !event ) { return; }
	ComponentFactoryEventListenerList ell = cem->getComponentFactoryEventListeners();
	for (size_t i = 0, n = ell.size(); i < n; i++)
	{
		ComponentFactoryEventListener_shared el = ell[i];
		el->doComponentFactory(event);
	}

}


