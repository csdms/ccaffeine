// 
// File:          ccaffeine_ConnectionEventService_Impl.cc
// Symbol:        ccaffeine.ConnectionEventService-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ConnectionEventService
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ConnectionEventService_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionEventService._includes)

#include "dc/babel/babel-cca/BblConnectionEventListener.h"

// DO-NOT-DELETE splicer.end(ccaffeine.ConnectionEventService._includes)

// user defined constructor
void ccaffeine::ConnectionEventService_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionEventService._ctor)
  // add construction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionEventService._ctor)
}

// user defined destructor
void ccaffeine::ConnectionEventService_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionEventService._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionEventService._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  initialize[]
 */
void
ccaffeine::ConnectionEventService_impl::initialize (
  /*in*/ void* gizzard ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionEventService.initialize)

  giz = (Gizzard*) gizzard;

  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionEventService.initialize)
}

/**
 * Sign up to be told about connection activity.
 * connectionEventType must be one of the integer 
 * values defined iN ConnectionEvent. 
 */
void
ccaffeine::ConnectionEventService_impl::addConnectionEventListener (
  /*in*/ ::gov::cca::ports::EventType et,
  /*in*/ ::gov::cca::ports::ConnectionEventListener cel ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionEventService.addConnectionEventListener)

  ccafeopq::connectionevents::ConnectionEventListener * l = 
    new BblConnectionEventListener(et, cel);
  ccafeopq::connectionevents::ConnectionEventListener_shared lptr(l);
  listeners[et] = lptr;
  if(et == gov::cca::ports::EventType_Connected || et == gov::cca::ports::EventType_ALL) {
    giz->getOCES()->addConnectEventListener(lptr);
  }
  if (et == gov::cca::ports::EventType_Disconnected || et == gov::cca::ports::EventType_ALL) {
    giz->getOCES()->addDisconnectEventListener(lptr);
  }


  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionEventService.addConnectionEventListener)
}

/**
 * Ignore future ConnectionEvents of the given type.
 * connectionEventType must be one of the integer values 
 * defined in ConnectionEvent. 
 */
void
ccaffeine::ConnectionEventService_impl::removeConnectionEventListener (
  /*in*/ ::gov::cca::ports::EventType et,
  /*in*/ ::gov::cca::ports::ConnectionEventListener cel ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionEventService.removeConnectionEventListener)

  ccafeopq::connectionevents::ConnectionEventListener_shared lptr = 
    listeners[et];
  if(et == gov::cca::ports::EventType_Connected || et == gov::cca::ports::EventType_ALL) {
    giz->getOCES()->removeConnectEventListener(lptr);
  }
  if (et == gov::cca::ports::EventType_Disconnected || et == gov::cca::ports::EventType_ALL) {
    giz->getOCES()->removeDisconnectEventListener(lptr);
  }
  if(listeners.erase(et) != 1) {
    fprintf(stderr, 
	    ":-( ccaffeine::Services_impl::removeConnectionEventListener:"
	    "Attempt to delete a listener that was not there: "
	    "this should not happen");
  }

  // DO-NOT-DELETE splicer.end(ccaffeine.ConnectionEventService.removeConnectionEventListener)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ConnectionEventService._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.ConnectionEventService._misc)

