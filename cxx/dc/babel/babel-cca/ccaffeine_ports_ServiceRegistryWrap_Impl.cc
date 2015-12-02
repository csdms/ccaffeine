// 
// File:          ccaffeine_ports_ServiceRegistryWrap_Impl.cc
// Symbol:        ccaffeine.ports.ServiceRegistryWrap-v0.3
// Symbol Type:   class
// Description:   Server-side implementation for ccaffeine.ports.ServiceRegistryWrap
// 
// WARNING: Automatically generated; only changes within splicers preserved
// 
// 
#include "ccaffeine_ports_ServiceRegistryWrap_Impl.hh"

// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap._includes)
// Put additional includes or other arbitrary code here...
#include "dc/babel/babel-cca/BabelCCAHelpers.hh"
#include "dc/babel/ccafe-bind/AllCcafeBind.hh"

int ccaffeine::ports::ServiceRegistryWrap_impl::genSerial = 0;
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap._includes)

// user defined constructor
void ccaffeine::ports::ServiceRegistryWrap_impl::_ctor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap._ctor)
    sr = 0;
#ifdef CCAFE_AUDIT
    serial = nextNum();
    IO_dn2("ccaffeine::ports::ServiceRegistryWrap_impl _ctor %d", serial);
#endif
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap._ctor)
}

// user defined destructor
void ccaffeine::ports::ServiceRegistryWrap_impl::_dtor() {
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap._dtor)

#ifdef CCAFE_AUDIT
	serial = -serial;
	IO_dn2("ccaffeine::ports::ServiceRegistryWrap_impl _dtor %d", serial);
#endif
	sr = 0;
  
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap._dtor)
}

// user defined static methods: (none)

// user defined non-static methods:
/**
 * Method:  initialize[]
 */
void
ccaffeine::ports::ServiceRegistryWrap_impl::initialize (
  /*in*/ void* ccafeopq_ServiceRegistry_star,
  /*in*/ void* opaque_ComponentID_addr ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap.initialize)

#ifdef CCAFE_AUDIT
	IO_dn2("ccaffeine::ports::ServiceRegistryWrap_impl init %d", serial);
	if (ccafeopq_ServiceRegistry_star == 0) {
		IO_dn1("ccaffeine::ports::ServiceRegistryWrap_impl init given null.");
	}
#endif
	if (opaque_ComponentID_addr == 0) {
#ifdef CCAFE_AUDIT
		IO_dn2("ServiceRegistryWrap_impl init %d called with null", serial);
#endif
		return;
	}
	sr = static_cast< ::ccafeopq::ServiceRegistry *>(ccafeopq_ServiceRegistry_star);

	::ccafeopq::ComponentID_shared *ocid_addr = 0;
	ocid_addr =
	static_cast< ::ccafeopq::ComponentID_shared * >(opaque_ComponentID_addr);
	cid = *ocid_addr;
  
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap.initialize)
}

/**
 * fetch up a pointer for static casting. if the name
 * supplied is not exactly right, returns null.
 */
void*
ccaffeine::ports::ServiceRegistryWrap_impl::getWrapped (
  /*in*/ const ::std::string& className ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap.getWrapped)
	if (className == "::ccafeopq::ServiceRegistry")
	{
		return sr;
	}
	return 0;

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap.getWrapped)
}

/**
 * return opq cidshared. 
 */
void
ccaffeine::ports::ServiceRegistryWrap_impl::getProviderID (
  /*in*/ void* opaque_ComponentID_addr ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap.getProviderID)
	if (opaque_ComponentID_addr == 0) {
#ifdef CCAFE_AUDIT
		IO_dn2("ServiceRegistryWrap_impl getProviderID called with null", serial);
#endif
		return;
	}
	::ccafeopq::ComponentID_shared *ocid_addr = 0;
	ocid_addr =
	static_cast< ::ccafeopq::ComponentID_shared * >(opaque_ComponentID_addr);
	*ocid_addr = cid;
  
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap.getProviderID)
}

/**
 * Add a ServiceProvider that can be asked to produce service Port's
 * for other components to use subsequently.
 * True means success. False means that for some reason, the
 * provider isn't going to function. Possibly another server is doing
 * the job.
 */
bool
ccaffeine::ports::ServiceRegistryWrap_impl::addService (
  /*in*/ const ::std::string& serviceType,
  /*in*/ ::ccaffeine::ports::ServiceProvider portProvider ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap.addService)
	if (portProvider._is_nil()) {
		return false;
	}
	ccafeopq::ServiceProvider_shared osp = BabelOpaqueServiceProvider::createWrap(portProvider, cid);
	bool result = sr->addService(serviceType, osp);
	return result;
  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap.addService)
}

/**
 * Add a "reusable" service gov.cca.Port for other components to use 
 * subsequently.
 */
bool
ccaffeine::ports::ServiceRegistryWrap_impl::addSingletonService (
  /*in*/ const ::std::string& serviceType,
  /*in*/ ::gov::cca::Port server ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap.addSingletonService)
  
        std::string canonicalType = serviceType;
        ccafeopq::TypeMap_shared dummy;
        std::string dname = "SINGLETON_SERVICE";
        ccafeopq::Port * cop =
                ccafe::BabelCCAHelpers::createSpecialProvider(server, dname, serviceType, dummy, canonicalType);
        if (cop == 0) {
                cop = new BabelOpaquePort(server);
#ifdef CCAFE_AUDIT
                IO_dn2("Adding singleton service of type: %s ", serviceType.c_str());
#endif
        } else {
#ifdef CCAFE_AUDIT
                IO_dn3("Adding singleton service type: %s, canonical type %s", serviceType.c_str(), canonicalType.c_str());
#endif
        }

        bool result = sr->addSingletonService(canonicalType, cop);
        if ( !result)
        {
                delete cop;
        } else {
                opqSingletons[serviceType] = cop;
                opqSingletonCanonical[serviceType] = canonicalType;
        }

        return result;

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap.addSingletonService)
}

/**
 * Inform the framework that this service Port is no longer to
 * be used, subsequent to this call. This is likely to
 * cause an exception unless all the ports obtained from the
 * previously added services have been released and disconnected.
 */
void
ccaffeine::ports::ServiceRegistryWrap_impl::removeService (
  /*in*/ const ::std::string& serviceType ) 
throw () 
{
  // DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap.removeService)
        std::map< std::string, std::string  >::const_iterator si;
        si = opqSingletonCanonical.find(serviceType);
        if (si != opqSingletonCanonical.end())
        {
                std::string ctype = opqSingletonCanonical[serviceType];
                ccafeopq::Port *cop = opqSingletons[serviceType];
                sr->removeService(ctype);
                delete cop;
                opqSingletonCanonical.erase(serviceType);
                opqSingletons.erase(serviceType);
                return;
        }
        sr->removeService(serviceType);

  // DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap.removeService)
}


// DO-NOT-DELETE splicer.begin(ccaffeine.ports.ServiceRegistryWrap._misc)
// Put miscellaneous code here
// DO-NOT-DELETE splicer.end(ccaffeine.ports.ServiceRegistryWrap._misc)

