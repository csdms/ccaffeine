// 
// File:          ccaffeine_PortTranslator_Impl.cc
// Symbol:        ccaffeine.PortTranslator-v0.6
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.PortTranslator
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_PortTranslator_Impl.hxx"

// DO-NOT-DELETE splicer.begin(ccaffeine.PortTranslator._includes)

// DO-NOT-DELETE splicer.end(ccaffeine.PortTranslator._includes)

// user defined constructor
void ccaffeine::PortTranslator_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.PortTranslator._ctor)

  port = NULL;

  // DO-NOT-DELETE splicer.end(ccaffeine.PortTranslator._ctor)
}

// user defined destructor
void ccaffeine::PortTranslator_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.PortTranslator._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.PortTranslator._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  initialize
 */
void
ccaffeine::PortTranslator_impl::initialize (
  /*in*/ void* opaquePort ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.PortTranslator.initialize)

  if( opaquePort != NULL) {
    port = (ccafeopq::Port*)opaquePort;
  } else {
    port = NULL;
  }

  // DO-NOT-DELETE splicer.end(ccaffeine.PortTranslator.initialize)
}

/**
 * Return a classic port.  The void * returned in C++ are
 * directly castable to a C++ classic::gov::cca::Port* and only
 * that type.  Casting to the specific type must occur after. 
 */
void*
ccaffeine::PortTranslator_impl::getClassicPort () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.PortTranslator.getClassicPort)

  ClassicOpaquePort * cp = dynamic_cast< ClassicOpaquePort * >( port );
  if(cp == NULL) {
    return NULL;
  } else {
    classic::gov::cca::Port * p = cp->getClassicPort();
    return (void*)p;
  }

  // DO-NOT-DELETE splicer.end(ccaffeine.PortTranslator.getClassicPort)
}

/**
 * unimplemented, returns NULL. 
 */
void*
ccaffeine::PortTranslator_impl::getChasmPort () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.PortTranslator.getChasmPort)

  return NULL;

  // DO-NOT-DELETE splicer.end(ccaffeine.PortTranslator.getChasmPort)
}

/**
 * Return a raw OpaquePort.  The void * in C++ is directly
 * castable to a ccafeopq::Port*.  
 */
void*
ccaffeine::PortTranslator_impl::getRawPort () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.PortTranslator.getRawPort)

  return (void*)port;

  // DO-NOT-DELETE splicer.end(ccaffeine.PortTranslator.getRawPort)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.PortTranslator._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.PortTranslator._misc)

