#include "dc/export/AllExport.hh"
#include "dc/framework/ConnectionID.h"
#include "dc/framework/UserPortData.h"
#include "dc/framework/ProviderPortData.h"
#include "dc/framework/DisconnectingConnectionEvent.h"
#include "util/TypeMap.h"

namespace {
char id[]=
"$Id: DisconnectingConnectionEvent.cxx,v 1.6 2004/10/16 05:53:20 baallan Exp $";
} ENDSEMI

DisconnectingConnectionEvent::DisconnectingConnectionEvent( UserPortData & upd)
{
  ::ccafeopq::TypeMap_shared tm1 = upd.getUserPortProperties();
  // pi = new OpqPortInfo(upd.getPortName(), upd.getPortType(), tm1);
  ctm = upd.getUserPortProperties();
  tpn = upd.getPortName();
  tpt = upd.getPortType();
}

DisconnectingConnectionEvent::DisconnectingConnectionEvent( ProviderPortData & ppd)
{
  ::ccafeopq::TypeMap_shared tm1 = ppd.getProviderPortProperties();
  // pi = new OpqPortInfo(ppd.getPortName(), ppd.getPortType(), tm1);
  ctm = ppd.getProviderPortProperties();
  tpn = ppd.getPortName();
  tpt = ppd.getPortType();
}

DisconnectingConnectionEvent::~DisconnectingConnectionEvent() 
{ 
  // pi = 0;
}

/** True if the event informs a connection. (never) */
int DisconnectingConnectionEvent::connected()
{
  return false;
}

/** True if the event informs a disconnection (always) */
int DisconnectingConnectionEvent::disconnected()
{
  return true;
}

std::string DisconnectingConnectionEvent::getName()
{
	return tpn;
}
	
std::string DisconnectingConnectionEvent::getType()
{
	return tpt;
}
	
ccafeopq::TypeMap_shared DisconnectingConnectionEvent::getProperties()
{
	return ctm;
}


void * DisconnectingConnectionEvent::getOpqTypeMapSharedPtrAddress()
{
	::ccafeopq::TypeMap_shared * ctm_addr = 0;
	ctm_addr = &(ctm);
	void * vpctm = static_cast<void *>(ctm_addr);
	return vpctm;
}

void DisconnectingConnectionEvent::setpreChange(bool pc) {
  prechange = pc;
}

bool DisconnectingConnectionEvent::preChange() {
  return prechange;
}
