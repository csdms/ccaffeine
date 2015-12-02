/* GENERATED FILE. Do not edit. DATAEventProcessor.cc.sed */
#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#include "dc/services/ContextEventManager/ContextEventManager.hh"
//#include "dc/services/ContextEventManager/eventCons/ContextConnectionEventProcessor.hh"


ccafeopq::event::ContextConnectionEventProcessor::~ContextConnectionEventProcessor()
{
	cem = 0;
}

ccafeopq::event::ContextConnectionEventProcessor::ContextConnectionEventProcessor()
{
	cem = 0;
}

ccafeopq::event::ContextConnectionEventProcessor::ContextConnectionEventProcessor(ContextEventManager * source)
{
	cem = source;
}

void 
ccafeopq::event::ContextConnectionEventProcessor::process(ContextEvent_shared eData)
{
	ContextConnectionEvent_shared event;
	event = boost::shared_dynamic_cast< ContextConnectionEvent >(eData);
	if ( !event ) { return; }
	ContextConnectionEventListenerList ell = cem->getContextConnectionEventListeners();
	for (size_t i = 0, n = ell.size(); i < n; i++)
	{
		ContextConnectionEventListener_shared el = ell[i];
		el->doContextConnection(event);
	}

}


