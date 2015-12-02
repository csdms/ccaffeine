#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#define NS ccafeopq::event::ComponentInstanceDeleteRequestEventImplementation

NS::ComponentInstanceDeleteRequestEventImplementation( const std::string & deadClassName, ccafeopq::ComponentID_shared dying, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum)
: ContextEventImplementation( ccafeopq::event::type::ComponentInstanceDeletePending, cid, sKey, seqNum)
{
	className = deadClassName;
	dyingCID = dying;
}

NS::~ComponentInstanceDeleteRequestEventImplementation()
{
	className += "reallyDead";
}

NS::ComponentInstanceDeleteRequestEventImplementation()
{
// dummy constructor for unit test
}

const std::string 
NS::getComponentClassName()
{
	return className;
}

ccafeopq::ComponentID_shared 
NS::getComponentID()
{
	return dyingCID;
}
