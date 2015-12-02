#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"

#define NS ccafeopq::event::ComponentInstanceAddedEventImplementation

NS::ComponentInstanceAddedEventImplementation()
{
// dummy constructor for unit test
}

NS::ComponentInstanceAddedEventImplementation(ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum, std::string className, ccafeopq::ComponentID_shared newID)
: ContextEventImplementation(ccafeopq::event::type::ComponentInstanceAdded, cid, sKey, seqNum)
{
	componentClassName = className;
	newComponentID = newID;
}

const std::string 
NS::getComponentClassName()
{
	return componentClassName;
}

ccafeopq::ComponentID_shared 
NS::getComponentID()
{
	return newComponentID;
}

