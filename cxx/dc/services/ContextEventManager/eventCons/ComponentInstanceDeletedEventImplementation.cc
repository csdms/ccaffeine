#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#define NS ccafeopq::event::ComponentInstanceDeletedEventImplementation
NS::ComponentInstanceDeletedEventImplementation( const std::string & dClass, const std::string & dInstance, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum)
: ContextEventImplementation(ccafeopq::event::type::ComponentInstanceDeleted, cid, sKey, seqNum)
{
	deadClass = dClass;
	deadInstance = dInstance;
}

NS::~ComponentInstanceDeletedEventImplementation()
{
	deadClass += ".reallyDead";
	deadInstance += ".reallyDead";
}
NS::ComponentInstanceDeletedEventImplementation()
{
// dummy constructor for unit test
}


const std::string 
NS::getDeadComponentClassName()
{
	return deadClass;
}

const std::string 
NS::getDeadComponentInstanceName()
{
	return deadInstance;
}
