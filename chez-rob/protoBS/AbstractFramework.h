#ifndef __ABSTRACTFRAMEWORK_H__
#define __ABSTRACTFRAMEWORK_H__

#include <cca.h>

/** The CCA framework model: the interface that all CCA frameworks
    may implement to accomodate "main-oriented" drivers.
    Provides a way for main() to get its hands on a Services and
    treat itself henceforth as a component. Not required of a framework.
    <p>
    Authors unable to relinquish the definition of main() to
    a generic framework will need an interface like this
    if they want to easily try out their code in different frameworks or
    embed a cca-compliant framework in a larger application in order
    to use cca components. It turns out this is also a nice sane way
    to build nested frameworks.
    </p>

    <p>
    It is assumed that an implementation class of AbstractFramework
    is chosen in the main(). The idea is to allow a complete swap
    of framework choice by changing a single-line framework declaration
    in main. E.G.
    </p>

    <code><pre>
    main(argc,argv) {
      ccaffeine.Framework fwkimpl = new ccaffeine.Framework();
        // change above to use different cca implementations.
      gov.cca.AbstractFramework fwk = (gov.cca.AbstractFramework)fwkimpl;
      Services svc = fwk.getBootstrapServices(argv[1]);
        // From here on, access all services, components, etc
        // through ports.
      fwk.releaseBootstrapServices(svc);
      fwk.shutdownFramework();
    }
    </pre></code>

    <p>
    Once someone has used this approach
    to write their main, it is a short trip further to
    convert that main to a normal setServices() function if the
    implementation language supports OO programming as Java/C++ do.
    </p>

    <p>If one uses interfaces other than this on an instance
       of a framework, one is hardwiring a dependence on that
       particular framework implementation and should not expect 
       easy portability of the application main().
    </p>

  */

namespace gov {

  namespace cca {


    class AbstractFramework {

    public:

      /** Obtain Services handle, which noone can set on us as there
	  is no "main()" "this" pointer in some languages and this scope
	  is "higher" than the framework instance. Cannot be called 
	  twice on the same fwk instance without an intervening 
	  releaseBootstrapServices. (Is there a real threaded counterexample of this?)
	  @param selfInstanceName The name of the component instance the 
	  calling code wishes to appear as in the framework. 
	  If there is a name collision with an already
	  existing component, the name will be appended to be made
	  unambiguous. This should be checked by examining the
	  result of getComponentID.getLocalName() from the returned
	  Services.
	  @param selfClassName The name of the component instance the 
	  calling code wishes to appear as in the framework. 
	  This may, but is not required, to correspond to any
	  actual class name.
	  @param selfProperties An array of strings that is arranged
	  key, value, key, value  for as many keys as needed.

	  @return  A normal Services object of the sort normally passed
	  in Component.setServices(). 
      */
      virtual Services* getBootstrapServices(char* selfInstanceName, char* selfClassName, 
				     char** selfProperties) throw (CCAException) = 0;

      /** Release Services obtained earlier. This will have the
	  side effect of disconnecting any remaining connections that have
	  been made between the 'main' component and others in the
	  framework.
	  @param svc The result of getBootstrapServices earlier obtained.
      */
      virtual void releaseBootstrapServices(Services* svc) throw (CCAException) = 0;

      /** After releaseBootstrapServices, attempt an orderly shutdown.
	  This constitutes setting Services null on all the components.
	  Well written components will-
	  <pre>
	  possibly checkpoint themselves, and
	  drop connections, and 
	  unregister or remove ports in an orderly fashion, and 
	  release any other system resources
	  during the setServices(null) call on them.
	  </pre>
	  In languages supporting a delete call, it is reasonable to call 
	  delete on the framework instance after this is called.
      */  
      virtual void shutdownFramework() = 0;

      /** Creates a new framework instance based on the
	  same underlying framework implementation. This way, a main()
	  building several containers (possibly nesting them) can
	  pick the implementation class of the framework once and then
	  everywhere else clone new instances without hard-coding the framework type.
	  The clone is shallow, i.e. it does not create
	  copies of any components within the original framework.
      */
      virtual AbstractFramework* createFramework() throw (CCAException) = 0;
    };




  }; //namespace cca
}; //namespace gov

#endif //__ABSTRACTFRAMEWORK_H__
