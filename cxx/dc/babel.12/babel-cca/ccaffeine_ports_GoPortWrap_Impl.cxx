// 
// File:          ccaffeine_ports_GoPortWrap_Impl.cc
// Symbol:        ccaffeine.ports.GoPortWrap-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.GoPortWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ports_GoPortWrap_Impl.hxx"

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.GoPortWrap._includes)
// Put additional includes or other arbitrary code here...
#include "dc/babel.12/babel-cca/BabelCCAHelpers.hxx"
#include "dc/babel.12/ccafe-bind/AllCcafeBind.hh"

int ccaffeine::ports::GoPortWrap_impl::genSerial = 0;
// DO-NOT-DELETE splicer.end(ccaffeine.ports.GoPortWrap._includes)

// user defined constructor
void ccaffeine::ports::GoPortWrap_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GoPortWrap._ctor)
    gp = 0;
#ifdef CCAFE_AUDIT
    serial = nextNum();
    IO_dn2("ccaffeine::ports::GoPortWrap_impl _ctor %d", serial);
#endif
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.GoPortWrap._ctor)
}

// user defined destructor
void ccaffeine::ports::GoPortWrap_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GoPortWrap._dtor)

#ifdef CCAFE_AUDIT
	serial = -serial;
	IO_dn2("ccaffeine::ports::GoPortWrap_impl _dtor %d", serial);
#endif
	gp = 0;
  
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.GoPortWrap._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * passed in is a void * cast pointer of
 *  ccafeopq::GoPort *.
 */
void
ccaffeine::ports::GoPortWrap_impl::initialize (
  /*in*/ void* ccafeopq_GoPort_star ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GoPortWrap.initialize)

#ifdef CCAFE_AUDIT
	IO_dn2("ccaffeine::ports::GoPortWrap_impl init %d", serial);
	if (ccafeopq_GoPort_star == 0) {
		IO_dn1("ccaffeine::ports::GoPortWrap_impl init given null.");
	}
#endif
	gp = static_cast< ::ccafeopq::GoPort *>(ccafeopq_GoPort_star);

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.GoPortWrap.initialize)
}

/**
 * fetch up a pointer for static casting. if the name
 * supplied is not exactly right, returns null.
 */
void*
ccaffeine::ports::GoPortWrap_impl::getWrapped (
  /*in*/ const ::std::string& className ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GoPortWrap.getWrapped)
	if (className == "::ccafeopq::GoPort")
	{
		return gp;
	}
	return 0;

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.GoPortWrap.getWrapped)
}

/**
 * Execute some encapsulated functionality on the component. 
 * Return 0 if ok, -1 if internal error but component may be 
 * used further, and -2 if error so severe that component cannot
 * be further used safely.
 */
int32_t
ccaffeine::ports::GoPortWrap_impl::go () 
throw () 

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GoPortWrap.go)
  int result = gp->go();
  return result;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.GoPortWrap.go)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.GoPortWrap._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.ports.GoPortWrap._misc)

