#include "dc/export/AllExport.hh"
#include "dc/framework/ConnectionID.h"
#include "dc/framework/ProviderPortData.h"

#include "util/TypeMap.h"
#include "util/IO.h"
#include <string>
#include <iostream>

using ::ccafeopq::Keys;

namespace {
char id[]=
"$Id: ProviderPortData.cxx,v 1.6 2004/12/06 23:07:52 baallan Exp $";
} ENDSEMI

/** turns on spew to cerr in constructors if defined. */
#define DEBUG_CONS
#undef DEBUG_CONS
namespace {
	void conslog(const char *f, const std::string & name, const std::string & type) {

					std::cerr << f << name << " : " << type << std::endl;
	}
} ENDSEMI // end namespace anonymous

::ccafeopq::Port *ProviderPortData::getPortInterface()
{
  // in stlland, this probably doesn't do the right thing.
  numberOfUsers++; 
  return pp;
}

void ProviderPortData::releasePortInterface()
{
  numberOfUsers--;
}

void ProviderPortData::shutdown()
{
  pp = 0;
  type += ".DEAD";
  name += ".DEAD";
  numberOfUsers = -numberOfUsers;
  serial = -serial;
}

ProviderPortData::~ProviderPortData( )
{
  shutdown();
}

/** create a provides port record. the typemap pushed in
    must be already created, not just an empty shared ptr.
    serial must be a unique int.
 */
ProviderPortData::ProviderPortData( ::ccafeopq::Port *p, const ::std::string & name_, const ::std::string & type_, ::ccafeopq::TypeMap_shared & tm_, int serial_)
{
  if ( !tm_ || !tm_->getBool("ProviderPortData::initDefaultProperties",false)) {
    throw ::ccafeopq::Exception("ProviderPortData::ProviderPortData(n, t, tm, ser) called with bad tm");
  }
#ifdef DEBUG_CONS
  conslog("    ProviderPortData-REAL-CONS ",name_,type_);
#endif
  pp = p;
  name = name_;
  type = type_;
  tm = tm_->cloneData();
#ifdef DEBUG_CONS
  gov::sandia::util::TypeMap::dump(tm);
#endif
  serial = serial_;
  numberOfUsers = 0;
}

ProviderPortData::ProviderPortData()
{
  // tm = static_cast< ::ccafeopq::TypeMap_Interface * >(0);
  name="UNINIT";
  type="UNINIT";
#ifdef DEBUG_CONS
  conslog("    ProviderPortData-DFLT-CONS ",name,type);
#endif
  pp = 0;
  serial = 0;
  numberOfUsers = 0;
}

#if ProviderPortData_USEEXPLICIT_COPYCTOR
ProviderPortData::ProviderPortData(const ProviderPortData & src)
{
  pp = src.pp;
  tm = src.tm;
  name = src.name;
  type = src.type;
#ifdef DEBUG_CONS
  conslog("    ProviderPortData-COPY-CONS ",name,type);
#endif
  serial = src.serial;
  numberOfUsers = src.numberOfUsers;
}
#endif

::ccafeopq::TypeMap_shared ProviderPortData::getProviderPortProperties()
{
#ifdef DEBUG_CONS
  conslog("    ProviderPortData-getPPP",name,type);
#endif
  return tm->cloneData();
}

void ProviderPortData::setProviderPortProperties( ::ccafeopq::TypeMap_shared tm_)
{
#ifdef DEBUG_CONS
  conslog("    ProviderPortData-setPPP",name,type);
#endif
  ::gov::sandia::util::TypeMap::copyInData(tm_, tm);
}

::std::string ProviderPortData::getPortName() const
{
  return name;
}

::std::string ProviderPortData::getPortType() const
{
  return type;
}

int ProviderPortData::getMaxConnections()
{
  if (!pp) { return -1; }
  return tm->getInt(Keys::CCA_MAXCONNECT, 2000000001);
}
int ProviderPortData::getMinConnections()
{
  if (!pp) { return -1; }
  return tm->getInt(Keys::CCA_MINCONNECT, 0);
}

int ProviderPortData::getNumberOfUsers()
{
  if (!pp) { return -1; }
  return numberOfUsers;
} 

// X needs to be a single statement less trailing ;
#define DECRUFT(T,NAME,TYPE, X) \
if (T->hasKey(NAME) && T->typeOf(NAME) != ::ccafeopq::TYPE) { T->remove(NAME); } \
if (! T->hasKey(NAME)) X

void ProviderPortData::initDefaultProperties( ::ccafeopq::TypeMap_shared t,
	const std::string & name, const std::string & type)
{
	if (!t) {
		IO_en3("ProviderPortData::initDefaultProperties(t,%s,%s) null t.",
			name.c_str(), type.c_str());
		exit(2);
	}

	if (t->getBool("ProviderPortData::initDefaultProperties",false)) {
		return; // don't do it twice
	}
#ifdef DEBUG_CONS
  conslog("    ProviderPortData-IDF",name,type);
#endif
	t->remove("ProviderPortData::initDefaultProperties");
	t->putBool("ProviderPortData::initDefaultProperties",true);

	// DECRUFT(t,Keys::CCA_PORTNAME,String, t->putString(Keys::CCA_PORTNAME, name) );
        if (t->hasKey(Keys::CCA_PORTNAME) && 
            t->typeOf(Keys::CCA_PORTNAME) != ::ccafeopq::String) {
		t->remove(Keys::CCA_PORTNAME);
	}
	if (!t->hasKey(Keys::CCA_PORTNAME)) {
           t->putString(Keys::CCA_PORTTYPE, type);
        }
	DECRUFT(t,Keys::CCA_PORTTYPE,String, t->putString(Keys::CCA_PORTTYPE, type) );
	DECRUFT(t,Keys::CCA_PROXYABLE,Bool, t->putBool(Keys::CCA_PROXYABLE, false) );
	DECRUFT(t,Keys::CCA_MAXCONNECT,Int, t->putInt(Keys::CCA_MAXCONNECT, 2000000000) );
	DECRUFT(t,Keys::CCA_MINCONNECT,Int, t->putInt(Keys::CCA_MINCONNECT, 0) );
	DECRUFT(t,Keys::CCAFE_VISIBLE,Bool, t->putBool(Keys::CCAFE_VISIBLE, true) );

}

::std::string ProviderPortData::toString() const
{ 
    std::string ret = "name = ";
    ret += name;
    std::string pname = tm->getString( Keys::CCA_PORTNAME,"noname?");
    ret += ", tm.portname= ";
    ret += pname;
    ret += ", type = ";
    ret += type;
    ret += "\n";
    return ret;
}
