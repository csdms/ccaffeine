// 
// File:          ccaffeine_ports_PortTranslator_Impl.cc
// Symbol:        ccaffeine.ports.PortTranslator-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.PortTranslator
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ports_PortTranslator_Impl.hxx"

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.PortTranslator._includes)

#include "util/IO.h"

// DO-NOT-DELETE splicer.end(ccaffeine.ports.PortTranslator._includes)

// user defined constructor
void ccaffeine::ports::PortTranslator_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.PortTranslator._ctor)

  port = NULL;
  IO_dn1("ccaffeine::PortTranslator_impl::_ctor");

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.PortTranslator._ctor)
}

// user defined destructor
void ccaffeine::ports::PortTranslator_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.PortTranslator._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.PortTranslator._dtor)
}

// user defined static methods:
/**
 * Create a new PortTranslator wrapper with a
 * classic::gov::cca::Port*. If the type does not match this
 * specifically, unexpected results may occur, or more likely,
 * all get methods will return NULL.
 */
::ccaffeine::ports::PortTranslator
ccaffeine::ports::PortTranslator_impl::createFromClassic (
  /*in*/ void* classic_Port_ptr ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.PortTranslator.createFromClassic)
  ccaffeine::ports::PortTranslator px = 
    ccaffeine::ports::PortTranslator::_create();
#ifdef HAVE_CLASSIC

  classic::gov::cca::Port * p = 
    static_cast< classic::gov::cca::Port * >(classic_Port_ptr);
  if(p == NULL) {
    return px;
  }
  ::ccafeopq::Port * op = new ClassicOpaquePort(p);
  px.initialize(op);
  return px;
#else
  IO_en1("ccaffeine::ports::PortTranslator_impl::createFromClassic() called without classic configured during framework build.");
  return px;
#endif // HAVE_CLASSIC

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.PortTranslator.createFromClassic)
}

/**
 * Create a new PortTranslator wrapper with a ::ccafeopq::Port*.
 * If the type does not match this specifically, unexpected
 * results may occur, or more likely, all get methods will return
 * NULL. 
 */
::ccaffeine::ports::PortTranslator
ccaffeine::ports::PortTranslator_impl::createFromRaw (
  /*in*/ void* ccafeopq_Port_ptr ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.PortTranslator.createFromRaw)

  ::ccafeopq::Port * p = 
    static_cast< ::ccafeopq::Port * >(ccafeopq_Port_ptr);
  if(p == NULL) {
    return ccaffeine::ports::PortTranslator::_create(); // nil object
  }
  ccaffeine::ports::PortTranslator px;
  px.initialize(p);
  return px;

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.PortTranslator.createFromRaw)
}


// user defined non-static methods:
/**
 * Must be initialized with a ::ccafeopq::Port* 
 */
void
ccaffeine::ports::PortTranslator_impl::initialize (
  /*in*/ void* opaquePort ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.PortTranslator.initialize)

  IO_dn1("ccaffeine::PortTranslator_impl::initialize");

  if(opaquePort != NULL) {
    port = static_cast< ccafeopq::Port* >(opaquePort);
    IO_dn3("opaquePort = 0x%x, port = 0x%x", opaquePort, port);
  } else {
    port = NULL;
  }

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.PortTranslator.initialize)
}

/**
 * Return a classic port.  The void * returned in C++ are
 * directly castable to a C++ classic::gov::cca::Port* and only
 * that type.  Casting to the specific type must occur after. 
 */
void*
ccaffeine::ports::PortTranslator_impl::getClassicPort () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.PortTranslator.getClassicPort)

#ifdef HAVE_CLASSIC
  ClassicOpaquePort * cp = dynamic_cast< ClassicOpaquePort * >( port );
  IO_dn1("ccaffeine::PortTranslator_impl::getClassicPort () entry");
  if(cp == NULL) {
     IO_dn2("classic::gov::cca::Port * p = 0x%x", NULL);
    return NULL;
  } else {
    classic::gov::cca::Port * p = cp->getClassicPort();
    void * vp = static_cast< void*>(p);
    IO_dn3("classic::gov::cca::Port * p = 0x%x, vp = 0x%x", p, vp);
    return vp;
  }
#else
  IO_en1("ccaffeine::ports::PortTranslator_impl::getClassicPort() called without classic configured during framework build.");
  return 0;
#endif // HAVE_CLASSIC

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.PortTranslator.getClassicPort)
}

/**
 * unimplemented, returns NULL. 
 */
void*
ccaffeine::ports::PortTranslator_impl::getChasmPort () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.PortTranslator.getChasmPort)

  IO_en1("ccaffeine::ports::PortTranslator_impl::getChasmPort() never implemented.");
  return NULL;

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.PortTranslator.getChasmPort)
}

/**
 * Return a raw OpaquePort.  The void * in C++ is directly
 * castable to a ccafeopq::Port*.  
 */
void*
ccaffeine::ports::PortTranslator_impl::getRawPort () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.PortTranslator.getRawPort)

  return (void*)port;

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.PortTranslator.getRawPort)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.PortTranslator._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.ports.PortTranslator._misc)

