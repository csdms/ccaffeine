// 
// File:          ccaffeine_AbstractFramework_Impl.cxx
// Symbol:        ccaffeine.AbstractFramework-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.AbstractFramework
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_AbstractFramework_Impl.hxx"

// 
// Includes for all method dependencies.
// 
#ifndef included_ccaffeine_BabelMain_hxx
#include "ccaffeine_BabelMain.hxx"
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
#ifndef included_sidl_BaseInterface_hxx
#include "sidl_BaseInterface.hxx"
#endif
#ifndef included_sidl_ClassInfo_hxx
#include "sidl_ClassInfo.hxx"
#endif
#ifndef included_sidl_RuntimeException_hxx
#include "sidl_RuntimeException.hxx"
#endif
#ifndef included_sidl_NotImplementedException_hxx
#include "sidl_NotImplementedException.hxx"
#endif
// DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework._includes)

#include "babel_compat.hh"

#ifdef _CCAMPI
#include "util/noSeekMPI.h"
#include <mpi.h>
#endif

// DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework._includes)

// speical constructor, used for data wrapping(required).  Do not put code here unless you really know what you're doing!
ccaffeine::AbstractFramework_impl::AbstractFramework_impl() : 
  StubBase(reinterpret_cast< 
  void*>(::ccaffeine::AbstractFramework::_wrapObj(this)),false) ,
  _wrapped(true){ 
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework._ctor2)
  // Insert-Code-Here {ccaffeine.AbstractFramework._ctor2} (ctor2)
  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework._ctor2)
}

// user defined constructor
void ccaffeine::AbstractFramework_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework._ctor)

  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework._ctor)
}

// user defined destructor
void ccaffeine::AbstractFramework_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework._dtor)
  // add destruction details here
  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework._dtor)
}

// static class initializer
void ccaffeine::AbstractFramework_impl::_load() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework._load)
  // Insert-Code-Here {ccaffeine.AbstractFramework._load} (class initialization)
  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework._load)
}

// user defined static methods:
/**
 *  fetches the fortran form of MPI_COMM_WORLD.
 * The primary utility of this method is that python and
 * java drivers may not otherwise be able to find the mpi
 * argument needed to initialize().
 * @return false if mpi not available (and fComm unchanged), true
 * if mpi is available and fComm will be set.
 */
bool
ccaffeine::AbstractFramework_impl::getMPICommWorld_impl (
  /* inout */int64_t& fComm ) 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework.getMPICommWorld)
#ifdef _CCAMPI 
	MPI_Fint fc = MPI_Comm_c2f(MPI_COMM_WORLD);
	int64_t result = fc;
	fComm = result;
	return true;
#endif
        return false;
  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework.getMPICommWorld)
}


// user defined non-static methods:
/**
 *  
 * @param args Meant to be something like a commandline arguments for the
 * this Ccaffeine framework object.  Currently supported:
 * 
 * --path /a/place/for/components:another/place/for/components:...
 * Ccaffeine will discover the components in the path.
 * --load a:colon-separated:list:of:components 
 * load specified components into the pallet.
 * @param fComm an mpi communicator in fortran or 0 if mpi not
 * in use.
 * @param useComm true if fComm is a valid mpi fortran comm (
 * which is obtained from MPI_Comm_c2f if you are in c).
 */
void
ccaffeine::AbstractFramework_impl::initialize_impl (
  /* in */const ::std::string& args,
  /* in */int64_t fComm,
  /* in */bool useComm ) 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework.initialize)

  int ignore = 0;
  bm = new DefaultBuilderModel(ignore,0,fComm,useComm);
  bm -> initScript();


  std::vector< std::string > v = StringTools::split(args);
  //  const char ** loadCmpt = 0;
  for(unsigned int i = 0;i < v.size();i++) {
    if(v[i] == "--path") {
      std::string path = v[++i];
      std::vector< std::string > p = StringTools::split(path,':');
      IO_dn1("Component search path being set to:");
      for(size_t i = 0;i < p.size();i++) {
	IO_dn2("Component path element: %s", p[i].c_str());
      }
      IO_dn1("into ComponentFactory");
      bm->setRepositoryPath(p);
      IO_dn1("returned from ComponentFactory");
      continue;
    }
    if(v[i] == "--load") {
      std::string c = v[++i];
      std::vector< std::string > cmpts = StringTools::split(c, ':');
      for(unsigned int i = 0;i < cmpts.size();i++) {
	if(bm->loadRepositoryClass(cmpts[i].c_str(), true, true)) {
	  IO_en2("Error in ComponentFactory::loadPallet for %s", 
		 cmpts[i].c_str());
	  continue;
	}
	IO_dn2("Loaded %s into pallet", cmpts[i].c_str());
      }
      continue;
    }
  }


  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework.initialize)
}

/**
 * @param driver: any implementation of the driver interface.
 * driver.DriverBody will be appropriately invoked.
 */
void
ccaffeine::AbstractFramework_impl::run_impl (
  /* inout */::ccaffeine::BabelMain& driver ) 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework.run)
	 gov::cca::AbstractFramework baf = *this;
	 driver.driverBody(baf);
	//driver.driverBody(this);
  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework.run)
}

/**
 * Method:  getFrameMPIComm[]
 */
bool
ccaffeine::AbstractFramework_impl::getFrameMPIComm_impl (
  /* inout */int64_t& fCommFwk ) 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework.getFrameMPIComm)
  // Insert-Code-Here {ccaffeine.AbstractFramework.getFrameMPIComm} (getFrameMPIComm method)
  // 
  // This method has not been implemented
  // get comm from bm object or cf inside. 
    ::sidl::NotImplementedException ex = ::sidl::NotImplementedException::_create();
    ex.setNote("too deep");
    ex.add(__FILE__, __LINE__, "This method has not been implemented");
    throw ex;
  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework.getFrameMPIComm)
}

/**
 *  
 * Create an empty TypeMap. Presumably this would be used in 
 * an ensuing call to <code>getServices()</code>. The "normal" method of
 * creating typemaps is found in the <code>Services</code> interface. It
 * is duplicated here to break the "chicken and egg" problem.
 */
::gov::cca::TypeMap
ccaffeine::AbstractFramework_impl::createTypeMap_impl () 
// throws:
//     ::gov::cca::CCAException
//     ::sidl::RuntimeException

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework.createTypeMap)

  ::ccafeopq::TypeMap_shared tm = Gizzard::createTypeMapStatic();
  if(! tm) {
    IO_en1(":-( nil Typmap from Gizzard::createTypeMapStatic()");
    return ::gov::cca::TypeMap();
  }
  return ccaffeine::TypeMap_impl::babelWrap(tm);

  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework.createTypeMap)
}

/**
 *  
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
 * image of the this component. This is identical
 * to the object passed into Component.setServices() 
 * when a component is created.
 */
::gov::cca::Services
ccaffeine::AbstractFramework_impl::getServices_impl (
  /* in */const ::std::string& selfInstanceName,
  /* in */const ::std::string& selfClassName,
  /* in */::gov::cca::TypeMap selfProperties ) 
// throws:
//     ::gov::cca::CCAException
//     ::sidl::RuntimeException
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework.getServices)

  if(proxyServices.find(selfInstanceName) != proxyServices.end()) {
    char* msg =
      IO_sn2(":-( InstanceName: %s already exists for this AbstractFramework"
	     " Currently we do not allow different components with the "
	     "same instance name", selfInstanceName.c_str());
    gov::cca::CCAException ex = ccaffeine::CCAException::_create();
    ex. SIDL_EXCEPTION_setMessage(msg);
    free(msg);
    throw ex;
  }

  if(proxies.find(selfClassName) == proxies.end()) { // new type
    IO_dn2("type: %s is new, creating a new factory...", 
	   selfClassName.c_str());
    SelfProxyFactory * spfStar = new SelfProxyFactory(selfClassName);
    SelfProxyFactory_ptr spf(spfStar);
    proxies[selfClassName] = spf;
    XCmptFactory_shared xcf = 
      boost::shared_dynamic_cast< XCmptFactory >(spf);
    if(spf == NULL) {
      char * msg = IO_sn1("Failed shared_dynamic_cast");
      gov::cca::CCAException ex = ccaffeine::CCAException::_create();
      ex.SIDL_EXCEPTION_setMessage(msg);
      free(msg);
      throw ex;
    }
    bm->getFramework()->addXCmptFactory(xcf);
    IO_dn1("factory added");
  }

  std::string instName = bm->pullDownFromPallet(selfClassName,
					  selfInstanceName);
  if(instName == "") {
    gov::cca::CCAException ex = ccaffeine::CCAException::_create();
    char * msg = IO_sn3(":-( Could not create %s with instance name %s",
		       selfInstanceName.c_str(), selfClassName.c_str());
    ex. SIDL_EXCEPTION_setMessage(msg);
    free(msg);
    throw ex;
  }
  SelfProxyFactory_ptr prx = proxies[selfClassName];
  prx->setLastInstanceToName(instName);
  ccafeopq::Services * svc = prx->getServicesFor(instName);
   ccaffeine::Services csvc = ccaffeine::Services::_create();
   csvc.initialize(svc);
   gov::cca::Services serv = csvc;
   proxyServices[instName] = serv;
   return serv;

  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework.getServices)
}

/**
 *  
 * Inform framework that the <code>Services</code> handle is no longer needed by the 
 * caller and that the reference to its component image is to be
 * deleted from the context of the underlying framework. This invalidates
 * any <code>ComponentID</code>'s or <code>ConnectionID</code>'s associated 
 * with the given <code>Services</code>' component image. 
 * 
 * @param services The result of getServices earlier obtained.
 * 
 * @throws CCAException if the <code>Services</code>
 * handle has already been released or is otherwise rendered invalid 
 * or was not obtained from <code>getServices()</code>.
 */
void
ccaffeine::AbstractFramework_impl::releaseServices_impl (
  /* in */::gov::cca::Services services ) 
// throws:
//     ::gov::cca::CCAException
//     ::sidl::RuntimeException
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework.releaseServices)

  std::string found = "";
  std::map< std::string, gov::cca::Services >::iterator pos;
  for(pos = proxyServices.begin();pos != proxyServices.end();++pos) {
    gov::cca::Services mySvc = pos->second;
    if(mySvc.isSame(services)) {
      found = pos->first;
      break;
    }
  }
  if(found == "") {
    IO_en1("Service not found, gov::cca::Services not released");
    return;
  }
  bm->removeInstantiatedComponent(found);
  proxyServices.erase(found);

  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework.releaseServices)
}

/**
 *  
 * Tell the framework it is no longer needed and to clean up after itself. 
 * @throws CCAException if the framework has already been shutdown.
 */
void
ccaffeine::AbstractFramework_impl::shutdownFramework_impl () 
// throws:
//     ::gov::cca::CCAException
//     ::sidl::RuntimeException

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework.shutdownFramework)

  delete bm;

  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework.shutdownFramework)
}

/**
 *  
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
ccaffeine::AbstractFramework_impl::createEmptyFramework_impl () 
// throws:
//     ::gov::cca::CCAException
//     ::sidl::RuntimeException

{
  // DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework.createEmptyFramework)

  return ccaffeine::AbstractFramework::_create();


  // DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework.createEmptyFramework)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.AbstractFramework._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.AbstractFramework._misc)

