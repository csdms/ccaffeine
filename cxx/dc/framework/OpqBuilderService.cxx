#include <unistd.h>

#ifdef HAVE_NEO
#include <neocca.hh>
#endif // HAVE_NEO
#include "dc/framework/dc_fwkStar.h"
#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/BuilderView.h"
#include "dc/user_iface/DefaultBuilderModel.h"
#include "dc/user_iface/CmdLineBuilderView.h"
#include "dc/user_iface/CmdLineBuilderViewMux.h"
#include "dc/framework/dc_fwkStar.h"

#include "dc/export/ccafeopq.hh"
#include "dc/framework/KernelPort.h"
#include "dc/framework/OpqBuilderService.h"

namespace {
char id[]=
"$Id: OpqBuilderService.cxx,v 1.13 2005/10/28 19:20:49 baallan Exp $";
} ENDSEMI

using ::std::vector;
using ::std::string;

//---------------------------------------------------
//
namespace {
  void unimplemented( const char * fname ) {
    string s = "Unimplemented OpqBuilderService::";
    s += fname;
    throw ::ccafeopq::Exception( ::ccafeopq::Nonstandard, s);
  }

  void whine( const char * fname ) {
    string s = "OpqBuilderService::";
    s += fname;
    throw ::ccafeopq::Exception( ::ccafeopq::Nonstandard, s);
  }

  void whine( const string m ) {
    string s = "OpqBuilderService::";
    s += m;
    throw ::ccafeopq::Exception( ::ccafeopq::Nonstandard, s);
  }

  void throwAndFree(char * s) {
    ::ccafeopq::Exception ex = 
	::ccafeopq::Exception( ::ccafeopq::Nonstandard, s);
    free(s);
    throw ex;
  }
}

DefaultBuilderModel * 
OpqBuilderService::getDefaultBuilderModel() {
  void *bmv = 0;
  DefaultBuilderModel *bm = 0;
  if((*frame).find("DefaultBuilderModel") == (*frame).end()) {
    char * s = 
      IO_sn1(":-( No BuilderModel found in frame");
    throwAndFree(s);
  }
  bmv = (*frame)["DefaultBuilderModel"];
  bm = static_cast< DefaultBuilderModel *>(bmv);
  return bm;
}

CmdLineBuilderView *
OpqBuilderService::getCmdLineBuilderView() {
  void *bvv = 0;
  CmdLineBuilderView *bv = 0;
  if((*frame).find("CmdLineBuilderView") == (*frame).end()) {
    if(nullBV == 0) {
      // CmdLineBuilderViewMux is basically null with nothing in it.
      nullBV = new CmdLineBuilderViewMux();
    }
      return nullBV;
  }
  bvv = (*frame)["CmdLineBuilderView"];
  bv = static_cast< CmdLineBuilderView *>(bvv);
  return bv;    
}
ConnectionFramework *
OpqBuilderService::getConnectionFramework() {
  return getDefaultBuilderModel()->getFramework();
}

//---------------------------------------------------
//
OpqBuilderService::OpqBuilderService()
{
  frame = 0;
  nullBV = 0;
  initKernel();
}

//---------------------------------------------------
//
OpqBuilderService::~OpqBuilderService()
{
  frame = 0;
  if(nullBV) {
    delete nullBV;
    nullBV = 0;
  }
}

//---------------------------------------------------
//
::ccafeopq::ComponentID_shared OpqBuilderService::createInstance(const string & instanceName, const string & className, ::ccafeopq::TypeMap_shared & properties) throw (::ccafeopq::Exception ) 
{
#if 0
  // this is what we would like, but absent a full event model as in
  // ben's new framework this doesn't ensure that all the
  // usual stuff happens so things show up in the gui. ugh.
  ConnectionFramework * cf = getConnectionFramework();
  ComponentInfo_shared ci ;
  ci = cf->instantiate( className.c_str(), instanceName.c_str(), properties);
  if (ci == 0) {
    string s = "createInstance";
    s+= instanceName;
    s+= ", ";
    s+=className;
    s+="):  error creating instance.";
    whine(s);
    // not reached
  }
#else
  CmdLineBuilderView * bv = getCmdLineBuilderView();
  DefaultBuilderModel * bm = getDefaultBuilderModel();
  ConnectionFramework * cf = getConnectionFramework();
  
  if (!className.size()) { whine("createInstance: bad classname"); }
  if (!instanceName.size()) { whine("createInstance: bad instancename"); }
  string iname ;
  Gizzard *g = cf->getGizzard(instanceName);
  if (g) {
    whine("createInstance: instanceName already used.");
  }
  iname = bm->pullDownFromPallet(className,instanceName, properties);
  if (iname.size() == 0) {
    bv->error("instantiation unsuccessful");
    whine("createInstance: instantiation unsuccessful");
  }
  bv->pullDownComponent(className.c_str(), iname.c_str());
  return getComponentID( iname);
#endif
}

//---------------------------------------------------
//
::ccafeopq::ComponentID_shared OpqBuilderService::getComponentID( const string & componentInstanceName) throw (::ccafeopq::Exception )
{
  ConnectionFramework * cf = getConnectionFramework();

  Gizzard *g = cf->getGizzard(componentInstanceName.c_str());
  if (g) {
    return g->getComponentID();
  }
  string s = "getComponentID(";
  s += componentInstanceName;
  s += "): unknown instance name";
  whine(s);
  // not reached
  ::ccafeopq::ComponentID_shared nullid;
  return nullid;
}

//---------------------------------------------------
//
vector< ::ccafeopq::ComponentID_shared > OpqBuilderService::getComponentIDs() throw (::ccafeopq::Exception ) 
{
  ConnectionFramework * cf = getConnectionFramework();

  vector< string > s = cf->instanceNames();
  int imax = s.size();
  vector< ::ccafeopq::ComponentID_shared > ids;
  for (int i = 0; i < imax; i++ )
    {
      ::ccafeopq::ComponentID_shared cid = getComponentID(s[i]);
      ids.push_back(cid);
    }
  return ids;

}

//---------------------------------------------------
//
::ccafeopq::TypeMap_shared OpqBuilderService::getComponentProperties( ::ccafeopq::ComponentID_shared & cid) throw (::ccafeopq::Exception )
{
  ConnectionFramework * cf = getConnectionFramework();

  ::ccafeopq::TypeMap_shared rt;
  rt = cf->getComponentPropertyTypeMap(cid->getInstanceName());
  if (!rt) {
    whine("getComponentProperties: unknown ComponentID given");
  }
  return rt;
}

//---------------------------------------------------
//
void OpqBuilderService::setComponentProperties( ::ccafeopq::ComponentID_shared & cid,  ::ccafeopq::TypeMap_shared & map) throw (::ccafeopq::Exception )
{
  ConnectionFramework * cf = getConnectionFramework();

  bool ok;
  ok = cf->setComponentPropertyTypeMap(cid->getInstanceName(), map);
  if (!ok) {
    whine("setComponentProperties: unknown ComponentID given");
  }
}

//---------------------------------------------------
//
::ccafeopq::ComponentID_shared OpqBuilderService::getDeserialization( const string & s) throw (::ccafeopq::Exception )
{
  unimplemented("getDeserialization"); // fixme getDeserialization
  // notreached
  ::ccafeopq::ComponentID_shared dummy;
  return dummy;
}

//---------------------------------------------------
//
void OpqBuilderService::destroyInstance( ::ccafeopq::ComponentID_shared & toDie,  float timeout ) throw (::ccafeopq::Exception )
{
  CmdLineBuilderView * bv = getCmdLineBuilderView();

  DefaultBuilderModel * bm = getDefaultBuilderModel();

  std::string ins = toDie->getInstanceName();
  const char * instanceName = ins.c_str();
  bm->removeInstantiatedComponent(instanceName);
  bv->p("remove "); 
  bv->pn(instanceName);
}

//---------------------------------------------------
//
vector< string > OpqBuilderService::getProvidedPortNames( ::ccafeopq::ComponentID_shared & cid) throw (::ccafeopq::Exception ) 
{
  ConnectionFramework * cf = getConnectionFramework();

  std::string gin = cid->getInstanceName();
  Gizzard *g = cf->getGizzard(gin.c_str());
  if (g) {
    return g->getProvidesPortNames();
  }
  whine("getProvidedPortNames: unknown ComponentID given");
  // not reached
  vector< string > v;
  return v;
}

//---------------------------------------------------
//
vector< string > OpqBuilderService::getUsedPortNames( ::ccafeopq::ComponentID_shared & cid) throw (::ccafeopq::Exception ) 
{
  ConnectionFramework * cf = getConnectionFramework();

  std::string gin = cid->getInstanceName();
  Gizzard *g = cf->getGizzard(gin.c_str());
  if (g) {
    return g->getUsesPortNames();
  }
  whine("getUsedPortNames: unknown ComponentID given");
  // not reached
  vector< string > v;
  return v;
}

//---------------------------------------------------
//
::ccafeopq::TypeMap_shared OpqBuilderService::getPortProperties( ::ccafeopq::ComponentID_shared & cid, const string & portname) throw (::ccafeopq::Exception )
{
  ConnectionFramework * cf = getConnectionFramework();

  return cf->getPortProperties(cid, portname);
}

//---------------------------------------------------
//
void OpqBuilderService::setPortProperties( ::ccafeopq::ComponentID_shared & cid, const string & portname,  ::ccafeopq::TypeMap_shared & map) throw (::ccafeopq::Exception )
{
  ConnectionFramework * cf = getConnectionFramework();
  cf->setPortProperties(cid, portname, map);
}

//---------------------------------------------------
//
::ccafeopq::ConnectionID_shared OpqBuilderService::connect( ::ccafeopq::ComponentID_shared & user, const string & usingPortName,  ::ccafeopq::ComponentID_shared & provider, const string & providingPortName) throw (::ccafeopq::Exception ) 
{
  CmdLineBuilderView * bv = getCmdLineBuilderView();

  DefaultBuilderModel * bm = getDefaultBuilderModel();

  ConnectionFramework * cf = getConnectionFramework();

  string toInstanceC;
  string fromInstanceC;
  toInstanceC = user->getInstanceName();
  fromInstanceC = provider->getInstanceName();

  char *toInstance = const_cast<char *>(toInstanceC.c_str()); // userc
  char *fromInstance = const_cast<char *>(fromInstanceC.c_str()); // provc
  char *usesInstance = const_cast<char *>(usingPortName.c_str()); // userp
  char *providesInstance = const_cast<char *>(providingPortName.c_str()); // provp
  IO_dn5("Attempting connect for: fromInstance = %s,providesInstance = %s, "
	 "toInstance = %s, usesInstance = %s",fromInstance, 
	 providesInstance, toInstance, usesInstance); 
  int err = 0;
  err =  bm->connect( fromInstance, providesInstance, toInstance, usesInstance);

  IO_dn2("out of bm->connect: err = %d", err);
  if (err) {
    bv->displayConnectionFailed("bm->connect failed");
    IO_dn5("Connect failed for fromInstance = %s,providesInstance = %s, "
	   "toInstance = %s, usesInstance = %s",fromInstance, 
	   providesInstance, toInstance, usesInstance); 
    whine("connect failed");
  }
  bv->connect(fromInstance, providesInstance, toInstance, usesInstance);
  return cf->getConnectionID(toInstance, usesInstance, fromInstance, providesInstance);
  // userc, userp, provc, provp

}

//---------------------------------------------------
//
vector < ::ccafeopq::ConnectionID_shared > OpqBuilderService::getConnectionIDs( vector< ::ccafeopq::ComponentID_shared > & componentList) throw (::ccafeopq::Exception ) 
{
  ConnectionFramework * cf = getConnectionFramework();

  return cf->getConnectionIDs(componentList);
}

//---------------------------------------------------
//
vector < ::ccafeopq::ConnectionID_shared > OpqBuilderService::getConnectionIDs(  const string & userName, const string & usingPortName,  const string & providerName, const string & providingPortName) throw (::ccafeopq::Exception )
{
  ConnectionFramework * cf = getConnectionFramework();

  return cf->getConnectionIDs(userName, usingPortName, providerName, providingPortName);
}

//---------------------------------------------------
//
::ccafeopq::TypeMap_shared OpqBuilderService::getConnectionProperties( ::ccafeopq::ConnectionID_shared & connID) throw (::ccafeopq::Exception )
{
  ConnectionFramework * cf = getConnectionFramework();

  return cf->getConnectionProperties(connID);
}

//---------------------------------------------------
//
void OpqBuilderService::setConnectionProperties( ::ccafeopq::ConnectionID_shared & connID, ::ccafeopq::TypeMap_shared & map) throw (::ccafeopq::Exception )
{
  ConnectionFramework * cf = getConnectionFramework();

  cf->setConnectionProperties(connID, map);
}

//---------------------------------------------------
//
void OpqBuilderService::disconnect( ::ccafeopq::ConnectionID_shared & connID,  float timeout) throw (::ccafeopq::Exception ) 
{

  DefaultBuilderModel * bm = getDefaultBuilderModel();

  CmdLineBuilderView * bv = getCmdLineBuilderView();

  char *fromInstance = 0;
  char *providesInstance = 0;
  char *toInstance = 0;
  char *usesInstance = 0;

  ::ccafeopq::ComponentID_shared pc = connID->getProvider();
  ::ccafeopq::ComponentID_shared uc = connID->getUser();
  string pport = connID->getProviderPortName();
  string uport = connID->getUserPortName();
  string pcname = pc->getInstanceName();
  string ucname = uc->getInstanceName();

  toInstance = const_cast<char *>(ucname.c_str());
  usesInstance = const_cast<char *>(uport.c_str());
  fromInstance = const_cast<char *>(pcname.c_str()); 
  providesInstance = const_cast<char *>(pport.c_str());

  int err = 0;
  err = bm->disconnect(fromInstance, providesInstance, toInstance, usesInstance);
  if (err) {
    bv->displayDisconnectionFailed("cca->bm->disconnect failed");
    whine("disconnect: disconnect failed");
    // notreached
  }
  bv->disconnect(fromInstance, providesInstance, toInstance, usesInstance);
}

//---------------------------------------------------
//
void 
OpqBuilderService::disconnectAll( ::ccafeopq::ComponentID_shared & id1,  
				  ::ccafeopq::ComponentID_shared & id2,  
				  float timeout) 
  throw (::ccafeopq::Exception ) 
{
  unimplemented(""); // fixme disconnectAll
}

std::vector< ::ccafeopq::ComponentID_shared >
OpqBuilderService::getComponentsThatUse(const std::string& portType) {
  ConnectionFramework * cf = getConnectionFramework();
  return cf->getComponentsThatUse(portType);
}
std::vector< ::ccafeopq::ComponentID_shared >
OpqBuilderService::getComponentsThatProvide(const std::string& portType) {
  ConnectionFramework * cf = getConnectionFramework();
  return cf->getComponentsThatProvide(portType);
}

void 
OpqBuilderService::appendRepositoryPath ( const ::std::string& dirPathElement )
{
	DefaultBuilderModel * bm = getDefaultBuilderModel();
	std::vector< std::string > pathlist = bm->getRepositoryPath();
        pathlist.push_back(dirPathElement);
        bm->setRepositoryPath(pathlist);
}

void
OpqBuilderService::loadRepositoryClass (const ::std::string& className, bool loadGlobal, bool loadLazy )
{
	DefaultBuilderModel * bm = getDefaultBuilderModel();
	bm->loadRepositoryClass(className.c_str(), loadGlobal,loadLazy);
}
//---------------------------------------------------
//
void OpqBuilderService::setFrameData( std::map<std::string, void *> *v)
{
  frame = v;
}

//---------------------------------------------------
