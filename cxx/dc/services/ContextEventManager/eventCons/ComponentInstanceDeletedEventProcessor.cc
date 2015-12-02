/* GENERATED FILE. Do not edit. DATAEventProcessor.cc.sed */
#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#include "dc/services/ContextEventManager/ContextEventManager.hh"
//#include "dc/services/ContextEventManager/eventCons/ComponentInstanceDeletedEventProcessor.hh"


ccafeopq::event::ComponentInstanceDeletedEventProcessor::~ComponentInstanceDeletedEventProcessor()
{
	cem = 0;
}

ccafeopq::event::ComponentInstanceDeletedEventProcessor::ComponentInstanceDeletedEventProcessor()
{
	cem = 0;
}

ccafeopq::event::ComponentInstanceDeletedEventProcessor::ComponentInstanceDeletedEventProcessor(ContextEventManager * source)
{
	cem = source;
}

void 
ccafeopq::event::ComponentInstanceDeletedEventProcessor::process(ContextEvent_shared eData)
{
	ComponentInstanceDeletedEvent_shared event;
	event = boost::shared_dynamic_cast< ComponentInstanceDeletedEvent >(eData);
	if ( !event ) { return; }
	ComponentInstanceDeletedEventListenerList ell = cem->getComponentInstanceDeletedEventListeners();
	for (size_t i = 0, n = ell.size(); i < n; i++)
	{
		ComponentInstanceDeletedEventListener_shared el = ell[i];
		el->doComponentInstanceDeleted(event);
	}

}


