// 
// File:          ccaffeine_ports_GUIServiceWrap_Impl.cc
// Symbol:        ccaffeine.ports.GUIServiceWrap-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.GUIServiceWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ports_GUIServiceWrap_Impl.hxx"

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.GUIServiceWrap._includes)

// Put additional includes or other arbitrary code here...
#include "dc/babel.12/babel-cca/BabelCCAHelpers.hxx"
#include "dc/babel.12/ccafe-bind/AllCcafeBind.hh"
                                                                                
int ccaffeine::ports::GUIServiceWrap_impl::genSerial = 0;

// DO-NOT-DELETE splicer.end(ccaffeine.ports.GUIServiceWrap._includes)

// user-defined constructor.
void ccaffeine::ports::GUIServiceWrap_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GUIServiceWrap._ctor)
  
	cgs = 0;
#ifdef CCAFE_AUDIT
	serial = nextNum();
	IO_dn2("ccaffeine::ports::GUIServiceWrap_impl _ctor %d", serial);
#endif

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.GUIServiceWrap._ctor)
}

// user-defined destructor.
void ccaffeine::ports::GUIServiceWrap_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GUIServiceWrap._dtor)
#ifdef CCAFE_AUDIT
        serial = -serial;
        IO_dn2("ccaffeine::ports::GUIServiceWrap_impl _dtor %d", serial);
#endif
        cgs = 0;

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.GUIServiceWrap._dtor)
}

// static class initializer.
void ccaffeine::ports::GUIServiceWrap_impl::_load() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GUIServiceWrap._load)
  // Insert-Code-Here {ccaffeine.ports.GUIServiceWrap._load} (class initialization)
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.GUIServiceWrap._load)
}

// user-defined static methods: (none)

// user-defined non-static methods:
/**
 * passed in is a void * cast pointer of
 *  ccafeopq::ports::ParameterPortFactory *.
 */
void
ccaffeine::ports::GUIServiceWrap_impl::initialize (
  /* in */ void* ccafeopq_GUIService_star ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GUIServiceWrap.initialize)
  
#ifdef CCAFE_AUDIT
        IO_dn2("ccaffeine::ports::GUIServiceWrap_impl init %d", serial);
        if (ccafeopq_GUIService_star == 0) {
                IO_dn1("ccaffeine::ports::GUIServiceWrap_impl init given null.");
        }
#endif
        cgs = static_cast< ::ccafeopq::GUIService *>(ccafeopq_GUIService_star);
                                                                                
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.GUIServiceWrap.initialize)
}

/**
 * fetch up a pointer for static casting. if the name
 * supplied is not exactly right, returns null.
 */
void*
ccaffeine::ports::GUIServiceWrap_impl::getWrapped (
  /* in */ const ::std::string& className ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GUIServiceWrap.getWrapped)
  
	if (className == "::ccafeopq::GUIService")
        {
                return cgs;
        }
        return 0;

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.GUIServiceWrap.getWrapped)
}

/**
 * send a string to the ccaffeine UI.
 * e.g. "gov.cca.anl.norris.UIMain arg1 arg2 arg3"
 * @param uicommand string routed to the ccaffeine ui.
 * if that ui happens to be the ccaffeine GUI, a load
 * event is generated that is handled by ./user_iface/gui/guicmd/Gui.java
 * in the following way.
 * - uicommand is broken up into words.
 * - the first word is a java classname.
 * - An instance of the classname is created (null constructor).
 * - If widget is a CcaffeineGUIWidget 
 * (see user_iface/gui/CcaffeineGUIWidget.java)
 * the rest of the words are delivered as a String[].
 * - If widget is a Runnable, gui starts it in a new thread.
 * - If widget is a javax.swing.JInternalFrame,JApplet,JFrame,
 * then it gets added to ccaffeine gui hierarchy.
 * - In the above steps, anything exceptional just gets ignored.
 * - If the classname is not a CcaffeineGUIWidget, the
 * - extra words in the uicommand are ignored.
 */
void
ccaffeine::ports::GUIServiceWrap_impl::load (
  /* in */ const ::std::string& uicommand ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GUIServiceWrap.load)
	cgs->load(uicommand); 
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.GUIServiceWrap.load)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.GUIServiceWrap._misc)
// Insert-Code-Here {ccaffeine.ports.GUIServiceWrap._misc} (miscellaneous code)
// DO-NOT-DELETE splicer.end(ccaffeine.ports.GUIServiceWrap._misc)

