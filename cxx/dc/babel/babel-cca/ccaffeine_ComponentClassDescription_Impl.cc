// 
// File:          ccaffeine_ComponentClassDescription_Impl.cc
// Symbol:        ccaffeine.ComponentClassDescription-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ComponentClassDescription
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ComponentClassDescription_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccaffeine.ComponentClassDescription._includes)
// Put additional includes or other arbitrary code here...
// int ::ccaffeine::ComponentClassDescription_impl::genSerial = 0;
#include "babel_compat.hh"
int ccaffeine::ComponentClassDescription_impl::genSerial = 0;
// DO-NOT-DELETE splicer.end(ccaffeine.ComponentClassDescription._includes)

// user defined constructor
void ccaffeine::ComponentClassDescription_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ComponentClassDescription._ctor)
#ifdef CCAFE_AUDIT
  serial = nextNum();
  IO_dn2("ccaffeine::ComponentClassDescription_impl _ctor %d", serial);
#endif
  // add construction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.ComponentClassDescription._ctor)
}

// user defined destructor
void ccaffeine::ComponentClassDescription_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ComponentClassDescription._dtor)
#ifdef CCAFE_AUDIT
  IO_dn2("ccaffeine::ComponentClassDescription_impl _dtor %d", serial);
  serial = -serial;
#endif
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.ComponentClassDescription._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  initialize[]
 */
void
ccaffeine::ComponentClassDescription_impl::initialize (
  /*in*/ void* opaque_ComponentClassDescription_addr ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ComponentClassDescription.initialize)
  // insert implementation here
#ifdef CCAFE_AUDIT
  IO_dn2("ComponentClassDescription_impl init %d", serial);
#endif
    if (opaque_ComponentClassDescription_addr == 0) {
#ifdef CCAFE_AUDIT
      IO_dn2("ComponentClassDescription_impl init %d called with null", serial);
#endif
    return;
  }
  ::ccafeopq::ComponentClassDescription_shared *occd_addr = 0;
  occd_addr = 
    static_cast< ::ccafeopq::ComponentClassDescription_shared * >(opaque_ComponentClassDescription_addr);
  occd = *occd_addr;

  // DO-NOT-DELETE splicer.end(ccaffeine.ComponentClassDescription.initialize)
}

/**
 *  Returns the class name provided in 
 *   <code>BuilderService.createInstance()</code>
 *   or in
 *   <code>AbstractFramework.getServices()</code>.
 *  <p>
 *  Throws <code>CCAException</code> if <code>ComponentClassDescription</code> is invalid.
 */
::std::string
ccaffeine::ComponentClassDescription_impl::getComponentClassName () 
throw ( 
  ::gov::cca::CCAException
)
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ComponentClassDescription.getComponentClassName)
  if (! occd) {
    ::ccaffeine::CCAException ex = ::ccaffeine::CCAException::_create(); 
    ex.setCCAExceptionType( ::gov::cca::CCAExceptionType_Nonstandard );
    ex.SIDL_EXCEPTION_setMessage("occd uninitialized"); 
    ex.SIDL_EXCEPTION_addToTrace( __FILE__, __LINE__, "getComponentClassName"); 
    ::gov::cca::CCAException gex = ex; // cast
    throw gex;
  } else {
    return occd->getComponentClassName();
  }
  // insert implementation here
  // DO-NOT-DELETE splicer.end(ccaffeine.ComponentClassDescription.getComponentClassName)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ComponentClassDescription._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.ComponentClassDescription._misc)

