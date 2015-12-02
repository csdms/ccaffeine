// 
// File:          ccaffeine_ports_ConnectionEvent_Impl.cc
// Symbol:        ccaffeine.ports.ConnectionEvent-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.ConnectionEvent
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ports_ConnectionEvent_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEvent._includes)
// Put additional includes or other arbitrary code here...
int ccaffeine::ports::ConnectionEvent_impl::genSerial = 0;
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEvent._includes)

// user defined constructor
void ccaffeine::ports::ConnectionEvent_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEvent._ctor)
  // add construction details here
#ifdef CCAFE_AUDIT
  serial = nextNum();
  IO_dn2("ccaffeine::ConnectionEvent_impl _ctor %d", serial);
#endif
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEvent._ctor)
}

// user defined destructor
void ccaffeine::ports::ConnectionEvent_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEvent._dtor)
  // add destruction details here
#ifdef CCAFE_AUDIT
  serial = -serial;
  IO_dn2("ccaffeine::ConnectionEvent_impl _dtor %d", serial);
#endif
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEvent._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  initialize[]
 */
void
ccaffeine::ports::ConnectionEvent_impl::initialize (
  /*in*/ ::gov::cca::ports::EventType eventType,
  /*in*/ ::gov::cca::TypeMap portProperties ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEvent.initialize)
  portInfo = portProperties;
  e = eventType;
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ConnectionEvent_impl init %d", serial);
#endif
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEvent.initialize)
}

/**
 * <p>Returns the integer from those enumerated that describes the event.</p>
 * 
 * <p>
 * The semantics are noted before
 * each member of the enum/static constant. We can add in different
 * types of connect/disconnect as multiports and
 * explicit local/global/sync/async semantics are agreed to in the future.
 * At present we assume that:
 * <ul>
 * <li> All instances in a component cohort (often thought of as a single
 *   "parallel component") receive all the events
 *   and in the same order, but not necessarily globally synchronously.
 * 
 * <li> For disconnections, within a process the events are delivered first
 *   to the using component then (if necessary) to the providing
 *   component.
 * 
 * <li> For connections, within a process the events are delivered first
 *   to the providing component then (if necessary) to the using
 *   component.
 * </ul>
 * </p>
 * 
 * <p>
 * Clearly some of the assumptions above may not suit a component
 * instance in which multiple execution threads act on a
 * single instance of the <code>cca.Services</code> object (SMP). The Services
 * specification is ambiguous as to whether such a component is even
 * allowed.
 * </p>
 * <p>
 * When this is clarified, additional members of the enum may arise,
 * in which case the assumptions here apply only to
 * <code>ConnectPending</code>, <code>Connected</code>, <code>DisconnectPending</code>, 
 * <code>Disconnected</code> types.
 */
::gov::cca::ports::EventType
ccaffeine::ports::ConnectionEvent_impl::getEventType () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEvent.getEventType)
  return e;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEvent.getEventType)
}

/**
 * Get Properties of the affected Port.
 * Among the standard properties are the name and type info.
 */
::gov::cca::TypeMap
ccaffeine::ports::ConnectionEvent_impl::getPortInfo () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEvent.getPortInfo)
  return portInfo;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEvent.getPortInfo)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ConnectionEvent._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ConnectionEvent._misc)

