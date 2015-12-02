// 
// File:          ccaffeine_AbstractFramework_Impl.hxx
// Symbol:        ccaffeine.AbstractFramework-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.AbstractFramework
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 

#ifndef included_ccaffeine_AbstractFramework_Impl_hxx
#define included_ccaffeine_AbstractFramework_Impl_hxx

#ifndef included_sidl_cxx_hxx
#include "SIDL_cxx.hh"
#endif
#ifndef included_ccaffeine_AbstractFramework_IOR_h
#include "ccaffeine_AbstractFramework_IOR.h"
#endif
// 
// Includes for all method dependencies.
// 
#ifndef included_sidl_BaseInterface_hxx
#include "SIDL_BaseInterface.hh"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "SIDL_ClassInfo.hh"
#endif
#ifndef included_ccaffeine_AbstractFramework_hxx
#include "ccaffeine_AbstractFramework.hxx"
#endif
#ifndef included_gov_cca_AbstractFramework_hxx
#include "gov_cca_AbstractFramework.hxx"
#endif
#ifndef included_gov_cca_CCAException_hxx
#include "gov_cca_CCAException.hxx"
#endif
#ifndef included_gov_cca_Services_hxx
#include "gov_cca_Services.hxx"
#endif
#ifndef included_gov_cca_TypeMap_hxx
#include "gov_cca_TypeMap.hxx"
#endif


// DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework._hincludes)

#include <vector>
#include <map>
#include <string>
#include <unistd.h>
#include "dc/export/ccafeopq.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <stdPorts.h>
#endif // HAVE_CLASSIC


#include "dc/framework/dc_fwkStar.h"
#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/BuilderView.h"
#include "dc/user_iface/DefaultBuilderModel.h"
#include "dc/user_iface/CmdLineBuilderView.h"
#include "dc/framework/dc_fwkStar.h"

#include "dc/framework/KernelPort.h"
#include "dc/framework/OpqBuilderService.h"
#include "dc/babel.12/babel-cca/SelfProxyFactory.hxx"
#include "dc/babel.12/babel-cca/ccaffeine_TypeMap_Impl.hxx"
#include "dc/babel.12/babel-cca/server/ccaffeine_Services.hxx"
#include "util/StringTools.hh"

// DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework._hincludes)

namespace ccaffeine { 

  /**
   * Symbol "ccaffeine.AbstractFramework" (version 0.3)
   * 
   * NOTE: the BuilderServices should be treated
   * as a port with the get/release BuilderService functions.
   * Mixing this with gov.cca.AbstractFramework presents
   * implementation problems.
   */
  class AbstractFramework_impl
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework._inherits)
  // Put additional inheritance here...
  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework._inherits)
  {

  private:
    // Pointer back to IOR.
    // Use this to dispatch back through IOR vtable.
    AbstractFramework self;

    // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework._implementation)

    DefaultBuilderModel * bm;
    std::map< std::string, gov::cca::Services > proxyServices;

    // A container of proxies that are a keyed by type.  Each type has
    // a single proxy.  There is nothing that prevents a user of this
    // class to grab a Services of multiple different types.
    std::map< std::string, SelfProxyFactory_ptr > proxies;

    // true if fortran comm was given.
    bool hasComm;
    // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework._implementation)

  private:
    // private default constructor (required)
    AbstractFramework_impl() {} 

  public:
    // SIDL constructor (required)
    // Note: alternate Skel constructor doesn't call addref()
    // (fixes bug #275)
    AbstractFramework_impl( struct ccaffeine_AbstractFramework__object * s ) : 
      self(s,true) { _ctor(); }

    // user defined construction
    void _ctor();

    // virtual destructor (required)
    virtual ~AbstractFramework_impl() { _dtor(); }

    // user defined destruction
    void _dtor();

  public:


    /**
     * Meant to be something like a commandline arguments for the
     * this Ccaffeine framework object.  Currently supported:
     * 
     * --path /a/place/for/components:another/place/for/components:...
     *        Ccaffeine will discover the components in the path.
     * --load a:colon-separated:list:of:components 
     *        load specified components into the pallet.
     */
    void
    initialize (
      /*in*/ const ::std::string& args
    )
    throw () 
    ;


    /**
     *  Create an empty TypeMap. Presumably this would be used in 
     *  an ensuing call to <code>getServices()</code>. The "normal" method of
     *  creating typemaps is found in the <code>Services</code> interface. It
     *  is duplicated here to break the "chicken and egg" problem.
     */
    ::gov::cca::TypeMap
    createTypeMap() throw ( 
      ::gov::cca::CCAException
    );

    /**
     * Retrieve a Services handle to the underlying framework. 
     * This interface effectively causes the calling program to 
     * appear as the image of a component inside the framework.
     * This method may be called any number of times
     * with different arguments, creating a new component image 
     * each time. 
     * The only proper method to destroy a Services obtained 
     * from this interface is to pass it to releaseServices.
     * 
     * @param selfInstanceName the Component instance name,
     * as it will appear in the framework.
     * 
     * @param selfClassName the Component type of the 
     * calling program, as it will appear in the framework. 
     * 
     * @param selfProperties (which can be null) the properties 
     * of the component image to appear. 
     * 
     * @throws CCAException in the event that selfInstanceName 
     * is already in use by another component.
     * 
     * @return  A Services object that pertains to the
     * 	    image of the this component. This is identical
     * 	    to the object passed into Component.setServices() 
     * 	    when a component is created.
     */
    ::gov::cca::Services
    getServices (
      /*in*/ const ::std::string& selfInstanceName,
      /*in*/ const ::std::string& selfClassName,
      /*in*/ ::gov::cca::TypeMap selfProperties
    )
    throw ( 
      ::gov::cca::CCAException
    );


    /**
     * Inform framework that the <code>Services</code> handle is no longer needed by the 
     * caller and that the reference to its component image is to be
     * deleted from the context of the underlying framework. This invalidates
     * any <code>ComponentID</code>'s or <code>ConnectionID</code>'s associated 
     * with the given <code>Services</code>' component image. 
     * 
     * @param svc The result of getServices earlier obtained.
     * 
     * @throws CCAException if the <code>Services</code>
     *         handle has already been released or is otherwise rendered invalid 
     *         or was not obtained from <code>getServices()</code>.
     */
    void
    releaseServices (
      /*in*/ ::gov::cca::Services svc
    )
    throw ( 
      ::gov::cca::CCAException
    );


    /**
     * Tell the framework it is no longer needed and to clean up after itself. 
     *  @throws CCAException if the framework has already been shutdown.
     */
    void
    shutdownFramework() throw ( 
      ::gov::cca::CCAException
    );

    /**
     * Creates a new framework instance based on the same underlying 
     * framework implementation. This does not copy the existing 
     * framework, nor are any of the user-instantiated components in
     * the original framework available in the newly created 
     * <code>AbstractFramework</code>. 
     * 
     * @throws CCAException when one of the following conditions occur:
     * 
     * (1)the AbstractFramework previously had shutdownFramework() called on it, or 
     * (2)the underlying framework implementation does not permit creation 
     * of another instance.	 
     */
    ::gov::cca::AbstractFramework
    createEmptyFramework() throw ( 
      ::gov::cca::CCAException
    );
  };  // end class AbstractFramework_impl

} // end namespace ccaffeine

// DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework._hmisc)
// Put miscellaneous things here...
// DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework._hmisc)

#endif
