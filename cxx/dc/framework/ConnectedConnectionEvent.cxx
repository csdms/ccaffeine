#include "dc/export/AllExport.hh"
#include "dc/framework/ConnectionID.h"
#include "dc/framework/UserPortData.h"
#include "dc/framework/ProviderPortData.h"


#include "dc/framework/ConnectedConnectionEvent.h"
#include "util/TypeMap.h"
#include "util/IO.h"

namespace {
char id[]=
"$Id: ConnectedConnectionEvent.cxx,v 1.6 2004/10/16 05:53:20 baallan Exp $";
} ENDSEMI

ConnectedConnectionEvent::~ConnectedConnectionEvent( )
{ 
#ifdef CCAFE_AUDIT
  IO_dn3("destroying ConnectedConnectionEvent(usesport) %s {%s}", tpn.c_str(), tpt.c_str());
#endif
}

ConnectedConnectionEvent::ConnectedConnectionEvent( UserPortData & upd) 
{ 
  ctm = upd.getUserPortProperties();
  tpn = upd.getPortName();
  tpt = upd.getPortType();
#ifdef CCAFE_AUDIT
  IO_dn3("created ConnectedConnectionEvent(usesport) %s {%s}", tpn.c_str(), tpt.c_str());
#endif
}

ConnectedConnectionEvent::ConnectedConnectionEvent( ProviderPortData & ppd) 
{ 
  ctm =  ppd.getProviderPortProperties();
  tpn = ppd.getPortName();
  tpt = ppd.getPortType();
#ifdef CCAFE_AUDIT
  IO_dn3("created ConnectedConnectionEvent(providesport) %s {%s}", tpn.c_str(), tpt.c_str());
#endif
}

void ConnectedConnectionEvent::setpreChange(bool pc) {
  prechange = pc;
}

bool ConnectedConnectionEvent::preChange() {
  return prechange;
}

/** True if the event informs a connection. (always) */
int ConnectedConnectionEvent::connected() {
  return true;
}

/** True if the event informs a disconnection (never) */
int ConnectedConnectionEvent::disconnected() {
  return false;
}

std::string ConnectedConnectionEvent::getName()
{
	return tpn;
}
	
std::string ConnectedConnectionEvent::getType()
{
	return tpt;
}
	
ccafeopq::TypeMap_shared ConnectedConnectionEvent::getProperties()
{
	return ctm;
}

void * ConnectedConnectionEvent::getOpqTypeMapSharedPtrAddress()
{
	::ccafeopq::TypeMap_shared * ctm_addr = 0;
	ctm_addr = &(ctm);
	void * vpctm = static_cast<void *>(ctm_addr);
	return vpctm;
}
