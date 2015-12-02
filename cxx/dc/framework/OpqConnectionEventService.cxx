#include <assert.h>


#include <string>
#include <map>
#include <iostream>
using namespace std;
#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_support.hh"
#include "dc/framework/Check.h"
#include "dc/framework/KernelPort.h"
#include "dc/framework/dc_fwkStar.h"


#include "util/TypeMap.h"
#include "util/IO.h"

class SIO {
public:
static void e(const std::string & s) {
  IO::e("%s",s.c_str());
}
static void en(const std::string & s) {
  IO::en("%s",s.c_str());
}
};

namespace {
char id[]=
"$Id: OpqConnectionEventService.cxx,v 1.1 2004/10/16 05:53:20 baallan Exp $";
} ENDSEMI

using ::ccafeopq::Keys;

OpqConnectionEventService::OpqConnectionEventService()
{
  initKernel();
  IO_dn1("  OpqConnectionEventService CTOR done.");
}

OpqConnectionEventService::~OpqConnectionEventService() {
  size_t nl;

  ccafeopq::connectionevents::ConnectionEventListener_shared dummy;

  nl = connectListeners.size() ;
  for ( ; nl > 0; nl--) { connectListeners[nl-1] = dummy; }
  connectListeners.clear();

  nl = disconnectListeners.size() ;
  for ( ; nl > 0; nl--) { disconnectListeners[nl-1] = dummy; }
  disconnectListeners.clear();

  IO_dn1("  OpqConnectionEventService DTOR done.");
}

int OpqConnectionEventService::nextSerial()
{
  serial++;
  return serial;
}

void OpqConnectionEventService::addConnectEventListener(ccafeopq::connectionevents::ConnectionEventListener_shared l) {
  IO_dn1("  OpqConnectionEventService::addConnectEventListener done.");
  connectListeners.push_back(l);
}
void OpqConnectionEventService::addDisconnectEventListener(ccafeopq::connectionevents::ConnectionEventListener_shared l) {
  IO_dn1("  OpqConnectionEventService::addDisconnectEventListener done.");
  disconnectListeners.push_back(l);
}

void OpqConnectionEventService::removeConnectEventListener(ccafeopq::connectionevents::ConnectionEventListener_shared l){
  IO_dn1("  OpqConnectionEventService::removeConnectEventListener done.");
  connectListeners.erase(remove(connectListeners.begin(),
                         connectListeners.end(),
                         l),
                         connectListeners.end());
}

void OpqConnectionEventService::removeDisconnectEventListener(ccafeopq::connectionevents::ConnectionEventListener_shared l) {
  IO_dn1("  OpqConnectionEventService::removeDisconnectEventListener done.");
  disconnectListeners.erase(remove(disconnectListeners.begin(),
                            disconnectListeners.end(),
                            l),
                            disconnectListeners.end());
}

void OpqConnectionEventService::fireConnectEvent(ccafeopq::connectionevents::ConnectionEvent_shared evt) {
  std::string ename = evt->getName();
  IO_dn2("  OpqConnectionEventService::fireConnectEvent start. %s", ename.c_str());
  size_t nl = connectListeners.size() ;
  IO_dn2("  OpqConnectionEventService::fireConnectEvent %d listeners.", (int)nl);
  for( ; nl > 0; nl--) {
    ccafeopq::connectionevents::ConnectionEventListener_shared l = connectListeners[nl-1];
    if (l != 0) {
      l->connectionActivity(evt);
    } else { // FIXME whine
    }
  }
}
void OpqConnectionEventService::fireDisconnectEvent(ccafeopq::connectionevents::ConnectionEvent_shared evt) {
  IO_dn1("  OpqConnectionEventService::fireDisconnectEvent start.");
  size_t nl = disconnectListeners.size() ;
  IO_dn2("  OpqConnectionEventService::fireConnectEvent %d listeners.", (int)nl);
  for(; nl > 0; nl--) {
    ccafeopq::connectionevents::ConnectionEventListener_shared l = disconnectListeners[nl-1];
    if (l != 0) {
      l->connectionActivity(evt);
    } else { // FIXME whine
    }
  }
}

