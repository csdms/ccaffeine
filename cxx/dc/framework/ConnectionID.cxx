#include "dc/export/ccafeopq.hh"
#include "dc/export/AllExport.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <ports/AllEvents.h>
#endif // HAVE_CLASSIC
#ifdef HAVE_NEO
#include <neocca.hh>
#endif // HAVE_NEO
#include "dc/export/ccafeopq_support.hh"
#include "dc/framework/ComponentChangedEvent.h"
#include "dc/framework/ComponentChangedListener.h"
#include "dc/framework/ComponentID.h"
#include "dc/framework/ConnectionID.h"
#include "dc/framework/UserPortData.h"
#include "dc/framework/ProviderPortData.h"
#include "dc/framework/KernelPort.h"
#include "dc/framework/OpqConnectionEventService.h"
#include "dc/framework/Gizzard.h"
#include "util/TypeMap.h"

namespace {
char id[]=
"$Id: ConnectionID.cxx,v 1.8 2004/10/16 05:53:20 baallan Exp $";
} ENDSEMI

ConnectionID_impl::ConnectionID_impl(Gizzard *provider, const ::std::string & providerPortName, Gizzard *user, const ::std::string & userPortName , ::ccafeopq::Port *p_)
{
  if (provider == 0 || user == 0 || providerPortName == "" || userPortName == "" || p_ == 0)
  {
    dead = true;
    inUse = false;
    p = u = 0;
    selfConnection = false;
    // could whine here, but above should have done so before getting here.
    return;
  }
  dead  = false;
  inUse = false;
  pPortName = providerPortName;
  uPortName = userPortName;
  p = provider;
  u = user;
  pp = p_;
  selfConnection = false;
  tm = user->createTypeMap();
}

ConnectionID_impl::ConnectionID_impl(Gizzard *user, const ::std::string & userPortName, ::ccafeopq::Port *p_)
{
  if ( user == 0 || userPortName == "" || p_ == 0) {
    dead = true;
    inUse = false;
    p = u = 0;
    selfConnection = false;
    // could whine here, but above should have done so before getting here.
    return;
  }
  dead  = false;
  inUse = false;
  pPortName = userPortName;
  uPortName = userPortName;
  p = 0;
  u = user;
  selfConnection = true;
  tm = user->createTypeMap();
  pp = p_;
}

/** required destructor */
ConnectionID_impl::~ConnectionID_impl()
{
  p = u = 0;
  pPortName += ".DEAD";
  uPortName += ".DEAD";
  dead = true;
  inUse = selfConnection = false;
  pp = 0;
}

::ccafeopq::ComponentID_shared ConnectionID_impl::getProvider() throw ( ::ccafeopq::Exception )
{
  if (dead) {
    ::ccafeopq::ComponentID_shared ncid;
    return ncid;
  }
  return p->getComponentID();
}

  /** Recall that ComponentID is also a shared_ptr type.
     @throws a Exception if the underlying connection is no longer valid.
   */
::ccafeopq::ComponentID_shared ConnectionID_impl::getUser() throw ( ::ccafeopq::Exception )
{
  if (dead) {
    ::ccafeopq::ComponentID_shared ncid;
    return ncid;
  }
  return u->getComponentID();
}

::std::string ConnectionID_impl::getProviderPortName() throw ( ::ccafeopq::Exception )
{
  if (dead) {
    return "";
  }
  return pPortName;
}

::std::string ConnectionID_impl::getUserPortName() throw ( ::ccafeopq::Exception )
{
  if (dead) {
    return "";
  }
  return uPortName;
}

bool ConnectionID_impl::isSameAs(  ConnectionID_ptr cp )
{
  if (dead) { return false; }
  if (cp.get() == this) {
    return true; // same object wrapped in another boost ptr.
  }
  return false;
  
}

bool ConnectionID_impl::isSameAs( ::ccafeopq::ConnectionID_shared & fcp )
{
  if (dead) { return false; }
  ConnectionID_ptr cp = ::boost::shared_dynamic_cast<ConnectionID_impl>(fcp);
  if (cp != 0 && cp.get() == this) {
    return true;
  }
  return false;
  
}

/** Returns true if the connection is currently being used, i.e. the
component has called getPort() but has not yet called
releasePort(). */
int ConnectionID_impl::isActive()
{
  if (dead) {
    return false;
  }
  return inUse;
}

  /** Is this connected to the framework internally? */
int ConnectionID_impl::isFrameworkConnection()
{
  if (dead) { return false; }
  return selfConnection;
}

::ccafeopq::TypeMap_shared ConnectionID_impl::getProperties()
{
  if (dead) {
    ::ccafeopq::TypeMap_shared ntm;
    return ntm;
  }
  return tm->cloneData();
}

void ConnectionID_impl::setProperties( ::ccafeopq::TypeMap_shared tm_)
{
  if (dead) {
    return;
  }
  ::gov::sandia::util::TypeMap::copyInData(tm_, tm);
}

Gizzard *ConnectionID_impl::getProviderGizzard()
{
  if (dead) {
    return 0;
  }
  return p;
}

Gizzard *ConnectionID_impl::getUserGizzard()
{
  if (dead) {
    return 0;
  }
  return u;
}

::ccafeopq::Port * ConnectionID_impl::getCachedPort()
{
  if (dead) {
    return 0;
  }
  return pp;
}

int ConnectionID_impl::indexOfConnection(
                const ::std::vector< ConnectionID_ptr > & conns,
                                         ConnectionID_ptr c)
{
  size_t i;
  for (i = 0; i < conns.size(); i++) {
    if (conns[i]->isSameAs(c)) {
      return i;
    }
  }
  return -1;
}

int ConnectionID_impl::indexOfConnection( 
		            const ::std::vector< ConnectionID_ptr > & conns,
                                         const ::std::string & upname,
                                         const ::std::string & ppname, 
                                         Gizzard *ug, Gizzard *pg)
{
  size_t i;
  for (i = 0; i < conns.size(); i++) {
    if (conns[i]->getUserPortName() == upname && 
        conns[i]->getProviderPortName() == ppname && 
        conns[i]->getUserGizzard() == ug &&
        conns[i]->getProviderGizzard() == pg)
    { return int(i); }
  }
  return -1;
}
