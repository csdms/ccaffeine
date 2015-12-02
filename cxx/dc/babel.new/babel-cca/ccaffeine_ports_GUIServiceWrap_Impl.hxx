// 
// File:          ccaffeine_ports_GUIServiceWrap_Impl.hxx
// Symbol:        ccaffeine.ports.GUIServiceWrap-v0.3
// Symbol Type:   class
// Babel Version: 0.10.10
// Description:   Server-side implementation for ccaffeine.ports.GUIServiceWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// babel-version = 0.10.10
// 

#ifndef included_ccaffeine_ports_GUIServiceWrap_Impl_hxx
#define included_ccaffeine_ports_GUIServiceWrap_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "sidl_cxx.hxx"
#endif
#ifndef included_ccaffeine_ports_GUIServiceWrap_IOR_h
#include "ccaffeine_ports_GUIServiceWrap_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_ccaffeine_ports_GUIServiceWrap_hxx
#include "ccaffeine_ports_GUIServiceWrap.hxx"
#endif
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.GUIServiceWrap._includes)
#include "dc/export/AllExport.hh"
#include "gov_cca.hxx"
#include "dc/babel.new/babel-cca/server/ccaffeine.hxx"
#include "dc/babel.new/babel-cca/server/ccaffeine_ports.hxx"
// DO-NOT-DELETE splicer.end(ccaffeine.ports.GUIServiceWrap._includes)

namespace ccaffeine { 
  namespace ports { 

    /**
     * Symbol "ccaffeine.ports.GUIServiceWrap" (version 0.3)
     * 
     * ccaffeine implementation of GUIService 
     */
    class GUIServiceWrap_impl
    // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GUIServiceWrap._inherits)
    // Insert-Code-Here {ccaffeine.ports.GUIServiceWrap._inherits} (optional inheritance here)
    // DO-NOT-DELETE splicer.end(ccaffeine.ports.GUIServiceWrap._inherits)
    {

    private:
      // Pointer back to IOR.
      // Use this to dispatch back through IOR vtable.
      GUIServiceWrap self;

      // DO-NOT-DELETE splicer.begin(ccaffeine.ports.GUIServiceWrap._implementation)
	::ccafeopq::GUIService *cgs;
	int serial;
	static int nextNum() { genSerial++; return genSerial; }
	static int genSerial;
	void checkthrow(const char *funcName);
      // DO-NOT-DELETE splicer.end(ccaffeine.ports.GUIServiceWrap._implementation)

    private:
      // private default constructor (required)
      GUIServiceWrap_impl() 
      {} 

    public:
      // sidl constructor (required)
      // Note: alternate Skel constructor doesn't call addref()
      // (fixes bug #275)
      GUIServiceWrap_impl( struct ccaffeine_ports_GUIServiceWrap__object * s ) 
        : self(s,true) { _ctor(); }

      // user defined construction
      void _ctor();

      // virtual destructor (required)
      virtual ~GUIServiceWrap_impl() { _dtor(); }

      // user defined destruction
      void _dtor();

      // static class initializer
      static void _load();

    public:


      /**
       * passed in is a void * cast pointer of
       *  ccafeopq::ports::ParameterPortFactory *.
       */
      void
      initialize (
        /* in */ void* ccafeopq_ports_GUIService_star
      )
      throw () 
      ;


      /**
       * fetch up a pointer for static casting. if the name
       * supplied is not exactly right, returns null.
       */
      void*
      getWrapped (
        /* in */ const ::std::string& className
      )
      throw () 
      ;


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
      load (
        /* in */ const ::std::string& uicommand
      )
      throw () 
      ;

    };  // end class GUIServiceWrap_impl

  } // end namespace ports
} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.GUIServiceWrap._misc)
// Insert-Code-Here {ccaffeine.ports.GUIServiceWrap._misc} (miscellaneous things)
// DO-NOT-DELETE splicer.end(ccaffeine.ports.GUIServiceWrap._misc)

#endif
