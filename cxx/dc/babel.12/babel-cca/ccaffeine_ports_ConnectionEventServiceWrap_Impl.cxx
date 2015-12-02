// 
// File:          ccaffeine_ports_ConnectionEventServiceWrap_Impl.cxx
// Symbol:        ccaffeine.ports.ConnectionEventServiceWrap-v0.3
// Symbol Type:   class
// Babel Version: 1.4.0 (Revision: 6607 release-1-4-0-branch)
// Description:   Server-side implementation for ccaffeine.ports.ConnectionEventServiceWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ports_ConnectionEventServiceWrap_Impl.hxx"

// 
// Includes for all method dependencies.
// 
#ifndef included_gov_cca_ports_ConnectionEventListener_hxx
#include "gov_cca_ports_ConnectionEventListener.hxx"
#endif
#ifndef included_gov_cca_ports_EventType_hxx
#include "gov_cca_ports_EventType.hxx"
#endif
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif
#ifndef included_sidl_NotImplementedException_hxx
#include "sidl_NotImplementedException.hxx"
#endif
// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap._includes)
#include "dc/babel.12/babel-cca/BblConnectionEventListener.h"

int ccaffeine::ports::ConnectionEventServiceWrap_impl::genSerial = 0;
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap._includes)

// special constructor, used for data wrapping(required).  Do not put code here unless you really know what you're doing!
ccaffeine::ports::ConnectionEventServiceWrap_impl::ConnectionEventServiceWrap_impl
  () : StubBase(reinterpret_cast< void*>(
  ::ccaffeine::ports::ConnectionEventServiceWrap::_wrapObj(reinterpret_cast< 
  void*>(this))),false) , _wrapped(true){ 
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap._ctor2)
  // Insert-Code-Here {ccaffeine.ports.ConnectionEventServiceWrap._ctor2} (ctor2)
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap._ctor2)
}

// user defined constructor
void ccaffeine::ports::ConnectionEventServiceWrap_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap._ctor)
  oces = 0;
#ifdef CCAFE_AUDIT
  serial = nextNum();
  IO_dn2("ccaffeine::ports::ConnectionEventServiceWrap_impl _ctor %d", serial);
#endif
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap._ctor)
}

// user defined destructor
void ccaffeine::ports::ConnectionEventServiceWrap_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap._dtor)
#ifdef CCAFE_AUDIT
  serial = -serial;
  IO_dn2("ccaffeine::ports::ConnectionEventServiceWrap_impl _dtor %d", serial);
#endif
  oces = 0;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap._dtor)
}

// static class initializer
void ccaffeine::ports::ConnectionEventServiceWrap_impl::_load() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap._load)
  // Insert-Code-Here {ccaffeine.ports.ConnectionEventServiceWrap._load} (class initialization)
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap._load)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 *  passed in is a void  cast pointer of
 * ccafeopq::ports::ConnectionEventService .
 */
void
ccaffeine::ports::ConnectionEventServiceWrap_impl::initialize_impl (
  /* in */void* co_p_ConnEvtSvc_star ) 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap.initialize)
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ports::ConnectionEventServiceWrap_impl init %d", serial);
  if (co_p_ConnEvtSvc_star == 0) {
    IO_dn1("ccaffeine::ports::ConnectionEventServiceWrap_impl init given null.");
  }
#endif
  oces =
    static_cast< ::ccafeopq::ports::ConnectionEventService *>(co_p_ConnEvtSvc_star);
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap.initialize)
}

/**
 *  fetch up a pointer for static casting. if the name
 * supplied is not exactly right, returns null.
 */
void*
ccaffeine::ports::ConnectionEventServiceWrap_impl::getWrapped_impl (
  /* in */const ::std::string& className ) 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap.getWrapped)
  if (className == "::ccafeopq::ports::ConnectionEventService")
  {
    return oces;
  } 
  return 0;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap.getWrapped)
}

/**
 *  
 * Sign up to be told about connection activity.
 * connectionEventType must be one of the integer 
 * values defined iN ConnectionEvent. 
 */
void
ccaffeine::ports::ConnectionEventServiceWrap_impl::addConnectionEventListener_impl
  (
  /* in */::gov::cca::ports::EventType et,
  /* in */::gov::cca::ports::ConnectionEventListener& cel ) 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap.addConnectionEventListener)
  ccafeopq::connectionevents::ConnectionEventListener * l = 
    new BblConnectionEventListener(et, cel);
  ccafeopq::connectionevents::ConnectionEventListener_shared lptr(l);
  listeners[et] = lptr;
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ports::ConnectionEventServiceWrap_impl::addConnectionEventListener_impl %d", (int)et);
#endif
  if(et == gov::cca::ports::EventType_Connected || 
     et == gov::cca::ports::EventType_ALL ||
     et == gov::cca::ports::EventType_ConnectPending) {
    oces->addConnectEventListener(lptr);
  }
  if (et == gov::cca::ports::EventType_Disconnected || 
      et == gov::cca::ports::EventType_DisconnectPending ||
      et == gov::cca::ports::EventType_ALL) {
    oces->addDisconnectEventListener(lptr);
  }
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap.addConnectionEventListener)
}

/**
 *  
 * Ignore future ConnectionEvents of the given type.
 * connectionEventType must be one of the integer values 
 * defined in ConnectionEvent. 
 */
void
ccaffeine::ports::ConnectionEventServiceWrap_impl::removeConnectionEventListener_impl
  (
  /* in */::gov::cca::ports::EventType et,
  /* in */::gov::cca::ports::ConnectionEventListener& cel ) 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap.removeConnectionEventListener)
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ports::ConnectionEventServiceWrap_impl::removeConnectionEventListener_impl %d", (int)et);
#endif
  ccafeopq::connectionevents::ConnectionEventListener_shared lptr = 
    listeners[et];
  if(et == gov::cca::ports::EventType_Connected || 
     et == gov::cca::ports::EventType_ConnectPending ||
     et == gov::cca::ports::EventType_ALL) {
    oces->removeConnectEventListener(lptr);
  }
  if (et == gov::cca::ports::EventType_Disconnected || 
      et == gov::cca::ports::EventType_DisconnectPending ||
      et == gov::cca::ports::EventType_ALL) {
    oces->removeDisconnectEventListener(lptr);
  }
  if(listeners.erase(et) != 1) {
    fprintf(stderr, 
            ":-( ccaffeine::Services_impl::removeConnectionEventListener:"
            "Attempt to delete a listener that was not there: "
            "this should not happen");
  }
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap.removeConnectionEventListener)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEventServiceWrap._misc)
// Insert-Code-Here {ccaffeine.ports.ConnectionEventServiceWrap._misc} (miscellaneous code)
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEventServiceWrap._misc)

