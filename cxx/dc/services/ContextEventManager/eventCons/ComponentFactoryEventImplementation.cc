#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
ccafeopq::event::ComponentFactoryEventImplementation::ComponentFactoryEventImplementation()
{
	// dummy constructor for unit test
}

ccafeopq::event::ComponentFactoryEventImplementation::ComponentFactoryEventImplementation(enum ccafeopq::event::type::ContextEventType factoryEventType, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum, ccafeopq::ComponentID_shared factory, ccafeopq::TypeMap_shared factoryPortProperties)
: ContextEventImplementation(factoryEventType, cid, sKey, seqNum)
{
	factoryID = factory;
	fpp = factoryPortProperties;
	std::string pName = "(unknown)";
	if (fpp != 0)
	{
		pName = fpp->getString( ::ccafeopq::Keys::CCA_PORTNAME, pName);
	}
	std::string desc = "ComponentFactory ";
	desc += factory->getInstanceName();
	desc += " port ";
	desc += pName;
	setContextEventDescription(desc);
}

ccafeopq::ComponentID_shared 
ccafeopq::event::ComponentFactoryEventImplementation::getFactoryID()
{
	return factoryID;
}

ccafeopq::TypeMap_shared 
ccafeopq::event::ComponentFactoryEventImplementation::getFactoryPortProperties()
{
	return fpp;
}
  
