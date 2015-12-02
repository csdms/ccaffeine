/* GENERATED FILE. Do not edit. DATAEventProcessor.cc.sed */
#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#include "dc/services/ContextEventManager/ContextEventManager.hh"
//#include "dc/services/ContextEventManager/eventCons/PortDefinitionEventProcessor.hh"


ccafeopq::event::PortDefinitionEventProcessor::~PortDefinitionEventProcessor()
{
	cem = 0;
}

ccafeopq::event::PortDefinitionEventProcessor::PortDefinitionEventProcessor()
{
	cem = 0;
}

ccafeopq::event::PortDefinitionEventProcessor::PortDefinitionEventProcessor(ContextEventManager * source)
{
	cem = source;
}

void 
ccafeopq::event::PortDefinitionEventProcessor::process(ContextEvent_shared eData)
{
	PortDefinitionEvent_shared event;
	event = boost::shared_dynamic_cast< PortDefinitionEvent >(eData);
	if ( !event ) { return; }
	PortDefinitionEventListenerList ell = cem->getPortDefinitionEventListeners();
	for (size_t i = 0, n = ell.size(); i < n; i++)
	{
		PortDefinitionEventListener_shared el = ell[i];
		el->doPortDefinition(event);
	}

}


