#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#define NS ccafeopq::event::ComponentInstanceAddRequestEventImplementation

NS::ComponentInstanceAddRequestEventImplementation(const std::string & cName, const std::string & iName, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum)
: ContextEventImplementation( ccafeopq::event::type::ComponentInstanceAddPending,cid, sKey, seqNum)
{
	className = cName;
	instanceName = iName;
}

NS::ComponentInstanceAddRequestEventImplementation()
{
// dummy constructor for unit test
}

const std::string 
NS::getComponentClassName()
{
	return className;
}

const std::string 
NS::getComponentInstanceName()
{
	return instanceName;
}
