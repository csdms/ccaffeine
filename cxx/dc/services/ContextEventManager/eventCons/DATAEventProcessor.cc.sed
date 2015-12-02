#include "dc/export/ccafeopq.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#include "dc/services/ContextEventManager/ContextEventManager.hh"
//#include "dc/services/ContextEventManager/eventCons/DATAEventProcessor.hh"


ccafeopq::event::DATAEventProcessor::~DATAEventProcessor()
{
	cem = 0;
}

ccafeopq::event::DATAEventProcessor::DATAEventProcessor()
{
	cem = 0;
}

ccafeopq::event::DATAEventProcessor::DATAEventProcessor(ContextEventManager * source)
{
	cem = source;
}

void 
ccafeopq::event::DATAEventProcessor::process(ContextEvent_shared eData)
{
	DATAEvent_shared event;
	event = boost::shared_dynamic_cast< DATAEvent >(eData);
	if ( !event ) { return; }
	DATAEventListenerList ell = cem->getDATAEventListeners();
	for (size_t i = 0, n = ell.size(); i < n; i++)
	{
		DATAEventListener_shared el = ell[i];
		el->doDATA(event);
	}

}


