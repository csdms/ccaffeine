#include "dc/export/AllExport.hh"
#include "dc/framework/ConnectionID.h"
#include "dc/framework/UserPortData.h"

#include "util/IO.h"
#include "util/TypeMap.h"

namespace {
char id[]=
"$Id: UserPortData.cxx,v 1.5 2004/01/21 06:21:55 baallan Exp $";
} ENDSEMI

using ::std::vector;
using ::std::string;
using ::ccafeopq::Keys;

/** turns on spew to cerr in constructors if defined. */
#define DEBUG_CONS
#undef DEBUG_CONS
namespace {
	void conslog(const char *f, const string & name, const string & type) {

		::std::cerr << f << name << " : " << type << ::std::endl;
	}
} ENDSEMI // end namespace anonymous

void UserPortData::shutdown()
{
  //pp = 0;
  type += ".DEAD";
  name += ".DEAD";
  isActive = false;
  serial = -serial;
}

UserPortData::~UserPortData()
{
  shutdown();
}

UserPortData::UserPortData()
{
#ifdef DEBUG_CONS
  conslog("    UserPortData-DFLT-CONS " ,name ,type);
#endif
  // tm = 0;
  name = "UNINIT"; 
  type = "UNINIT";
  serial = 0;
  isActive = false;
  isSelfConnected = false;
}

#if UserPortData_USEEXPLICIT_COPYCTOR
UserPortData::UserPortData(const UserPortData & src)
{
#ifdef DEBUG_CONS
  conslog("    UserPortData-COPY-CONS ", src.name, src.type);
#endif
  tm = src.tm;
  name = src.name;
  type = src.type;
  serial = src.serial;
  isActive = src.isActive;
  isSelfConnected = src.isSelfConnected;
  for (size_t i = 0; i < src.conns.size(); i++)
  {
	  conns.push_back(src.conns[i]);
  }
}
#endif

UserPortData::UserPortData(const ::std::string & name_, const ::std::string & type_, ::ccafeopq::TypeMap_shared & tm_, int serial_)
{
  if ( !tm_ || !tm_->getBool("UserPortData::initDefaultProperties",false)) {
	throw ::ccafeopq::Exception("UserPortData::UserPortData(n, t, tm, ser) called with bad tm");	
  }
#ifdef DEBUG_CONS
  conslog("    UserPortData-REAL-CONS " ,name_ , type_);
#endif
  name = name_;
  type = type_;
  tm = tm_;
  serial = serial_;
  isActive = false;
  isSelfConnected = false;
}

::ccafeopq::TypeMap_shared UserPortData::getUserPortProperties()
{
  return tm->cloneData();
}

void UserPortData::setUserPortProperties( ::ccafeopq::TypeMap_shared tm_)
{
  ::gov::sandia::util::TypeMap::copyInData(tm_, tm);
}

::std::string UserPortData::getPortName() const
{
  return name;
}
::std::string UserPortData::getPortType() const
{
  return type;
}
bool UserPortData::getIsActive()
{
  return isActive;
}
bool UserPortData::getIsConnected()
{
  if ( conns.size() > 0 ) { return true; }
  return false;
}

const ::std::vector< ConnectionID_ptr > & UserPortData::getConnectionIDs() const
{
  return conns;
}

ConnectionID_ptr UserPortData::addConnection(Gizzard *user, const ::std::string & uname, Gizzard *provider, const ::std::string & pname, ::ccafeopq::Port *p)
{
  ConnectionID_impl *cimpl = new ConnectionID_impl( provider, pname, user, uname, p);
  ConnectionID_ptr c(cimpl);
  conns.push_back(c); 
  // std::cerr << toString() << std::endl; // FIXME
  return c;
}

ConnectionID_ptr UserPortData::addSelfConnection(Gizzard *user, const ::std::string & uname, ::ccafeopq::Port *p)
{
  isSelfConnected = true;
  ConnectionID_impl *cimpl = new ConnectionID_impl( user, uname , p);
  ConnectionID_ptr c(cimpl);
  conns.push_back(c);
  // std::cerr << toString() << std::endl; // FIXME
  return c;
}

/** return number of active connections broken in process */
int UserPortData::removeConnection(ConnectionID_ptr & cp)
{
  int i = 0;
  int ret = 0;
  i = ConnectionID_impl::indexOfConnection(conns,cp);
  if (i < 0) {
    return ret;
  }
  if ( conns[i]->isActive()) {
    ret++;
  }
  conns.erase(conns.begin()+i);
  return ret;
}

/** return number of active connections broken in process */
int UserPortData::removeConnections()
{
  int ret = 0;
  for (size_t i = conns.size(); i > 0 ; i--) {
    if ( conns[i]->isActive()) {
      ret++;
    }
    conns.erase(conns.begin()+(i-1));
  }
  return ret;
}

int UserPortData::getNumberOfConnections()
{
  return int(conns.size());
}
int UserPortData::getMaxConnections()
{
  return tm->getInt(Keys::CCA_MAXCONNECT, 2000000001);
}
int UserPortData::getMinConnections()
{
  return tm->getInt(Keys::CCA_MINCONNECT, 0);
}

// updates isActive.
::ccafeopq::Port *UserPortData::getProvided()
{
  if (conns.size() == 1) {
    isActive = true;
    return conns[0]->getCachedPort();
  }
  return 0;
}

void UserPortData::releaseProvided()
{
  isActive = false;
}

::std::vector< ::ccafeopq::Port * > UserPortData::getAllProvided()
{
  ::std::vector< ::ccafeopq::Port * > ret(conns.size(),0);
  for (size_t i = conns.size(); i > 0; i--)
  {
    isActive = true;
    ret[i-1] = conns[i-1]->getCachedPort();
  }
  return ret;
}

void UserPortData::releaseAllProvided()
{
  isActive = false;
}

::std::string UserPortData::toString() const
{
  string ret = "name = ";
  ret += name;
  std::string uname = tm->getString( Keys::CCA_PORTNAME,"noname?");
  ret += ", tm.portname= ";
  ret += uname;
  ret += ", type = ";
  ret += type;
  ret += ", active=";
  ret += (isActive) ? "true" : "false";
  ret += ", selfConnected=";
  ret += (isSelfConnected) ? "true" : "false";
  ret += ", conns.size()";
  ret += (conns.size() > 0) ? ">=1" : "=0";
  ret += "\n";
  return ret;
  
}

#define DECRUFT(T,NAME,TYPE, X) \
if (T->hasKey(NAME) && T->typeOf(NAME) != ::ccafeopq::TYPE) { T->remove(NAME); } \
if (! T->hasKey(NAME)) X
void UserPortData::initDefaultProperties( ::ccafeopq::TypeMap_shared t,
	       	const std::string & name, const std::string & type)
{
	if (!t) {
		IO_en3("UserPortData::initDefaultProperties(t,%s,%s) null t.",
			name.c_str(), type.c_str());
		exit(2);
	}
	if (t->getBool("UserPortData::initDefaultProperties",false)) {
		return; // don't do it twice
	}
	t->remove("UserPortData::initDefaultProperties");
	t->putBool("UserPortData::initDefaultProperties",true);
  
	DECRUFT(t,Keys::CCA_PORTNAME,String, t->putString(Keys::CCA_PORTNAME, name) );
	DECRUFT(t,Keys::CCA_PORTTYPE,String, t->putString(Keys::CCA_PORTTYPE, type) );
	DECRUFT(t,Keys::CCA_PROXYABLE,Bool, t->putBool(Keys::CCA_PROXYABLE, false) );
	DECRUFT(t,Keys::CCAFE_VISIBLE,Bool, t->putBool(Keys::CCAFE_VISIBLE, true) );
	DECRUFT(t,Keys::CCA_MAXCONNECT,Int, t->putInt(Keys::CCA_MAXCONNECT, 1) );
	DECRUFT(t,Keys::CCA_MINCONNECT,Int, t->putInt(Keys::CCA_MINCONNECT, 0) );
}

