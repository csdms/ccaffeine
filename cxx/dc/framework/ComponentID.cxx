#include "dc/export/ccafeopq.hh"
#include "dc/framework/ComponentID.h"

namespace {
char id[]=
"$Id: ComponentID.cxx,v 1.4 2003/07/07 19:08:39 baallan Exp $";
} ENDSEMI

ComponentID_impl::ComponentID_impl(const ::std::string & iName, const ::std::string & s)
// : instanceName(iName), serialization(s)
{
	instanceName = iName;
	serialization = s;
       	dead = false;
}


ComponentID_impl::~ComponentID_impl()
{
	serialization += "dead";
	instanceName += "dead";
	dead = true;
}


const ::std::string ComponentID_impl::getInstanceName() throw ( ::ccafeopq::Exception)
{
	if (!dead) {
		return instanceName;
	}
	throw ccafeopq::Exception(ccafeopq::Nonstandard, "getInstanceName called on dead component");
}


const ::std::string ComponentID_impl::getSerialization() throw ( ::ccafeopq::Exception)
{
	if (!dead) {
		return serialization;
	}
	throw ccafeopq::Exception( ::ccafeopq::Nonstandard, "getSerialization called on dead component");
}


bool ComponentID_impl::isSameAs( ::ccafeopq::ComponentID_shared &  cid)
{
  if (dead) { return false; }
  ComponentID cp = ::boost::shared_dynamic_cast<ComponentID_impl>(cid);
  if (cp != 0 && cp.get() == this) {
    return true;
  }
  return false;
}
