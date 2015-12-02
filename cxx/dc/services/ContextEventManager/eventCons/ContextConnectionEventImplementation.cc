#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_events.hh"
#include "dc/services/ContextEventManager/eventCons.hh"
#define NS ccafeopq::event::ContextConnectionEventImplementation


NS::~ContextConnectionEventImplementation()
{
	// fixme ContextConnectionEventImplementation dtor?
}

NS::ContextConnectionEventImplementation()
{
// dummy constructor for unit test
}

NS::ContextConnectionEventImplementation( enum ccafeopq::event::type::ContextEventType connectionEventType, ccafeopq::ComponentID_shared cid, int sKey, int64_t seqNum, ccafeopq::ComponentID_shared user, const std::string & upName, ccafeopq::TypeMap_shared userPortProperties,  ccafeopq::ComponentID_shared provider, const std::string & ppName, ccafeopq::TypeMap_shared providerPortProperties)
: ContextEventImplementation(connectionEventType, cid, sKey, seqNum)
{
	userCID = user;
	providerCID = provider;
	userPortName = upName;
	providerPortName = ppName;
	userProps = userPortProperties;
	providerProps = providerPortProperties;
}

ccafeopq::ComponentID_shared 
NS::getProvider()
{
	return providerCID;
}

ccafeopq::ComponentID_shared 
NS::getUser() 
{
	return userCID;
}

ccafeopq::TypeMap_shared 
NS::getProviderPortProperties() 
{
	return providerProps;
}

ccafeopq::TypeMap_shared 
NS::getUserPortProperties() 
{
	return userProps;
}

const std::string 
NS::getProviderPortName() 
{
	return providerPortName;
}

const std::string 
NS::getUserPortName() 
{
	return userPortName;
}
