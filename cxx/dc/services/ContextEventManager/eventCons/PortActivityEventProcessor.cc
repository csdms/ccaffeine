/* GENERATED FILE. Do not edit. DATAEventProcessor.cc.sed */
#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#include "dc/services/ContextEventManager/ContextEventManager.hh"
//#include "dc/services/ContextEventManager/eventCons/PortActivityEventProcessor.hh"


ccafeopq::event::PortActivityEventProcessor::~PortActivityEventProcessor()
{
	cem = 0;
}

ccafeopq::event::PortActivityEventProcessor::PortActivityEventProcessor()
{
	cem = 0;
}

ccafeopq::event::PortActivityEventProcessor::PortActivityEventProcessor(ContextEventManager * source)
{
	cem = source;
}

void 
ccafeopq::event::PortActivityEventProcessor::process(ContextEvent_shared eData)
{
	PortActivityEvent_shared event;
	event = boost::shared_dynamic_cast< PortActivityEvent >(eData);
	if ( !event ) { return; }
	PortActivityEventListenerList ell = cem->getPortActivityEventListeners();
	for (size_t i = 0, n = ell.size(); i < n; i++)
	{
		PortActivityEventListener_shared el = ell[i];
		el->doPortActivity(event);
	}

}


