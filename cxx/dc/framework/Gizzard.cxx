#include <assert.h>


#include <string>
#include <map>
#include <iostream>
using namespace std;
#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_support.hh"

#ifdef HAVE_CLASSIC
#include <cca.h>
#include <stdPorts.h>
#endif // HAVE_CLASSIC

#ifdef HAVE_NEO
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/NeoOpaquePort.hh"
#endif // HAVE_NEO

#include "dc/framework/Check.h"
#include "dc/framework/KernelPort.h"

#ifdef HAVE_CLASSIC
#include "dc/classic/ccafe-bind/ClassicOpaquePort.hh"
#endif // HAVE_CLASSIC

// #include "dc/port/DefaultJPrintfPort.h"
#include "dc/framework/dc_fwkStar.h"
#include "dc/port/StringableParameterPort.h"
#include "dc/port/OpqParameterPort.h"
#include "dc/port/OpqParameterPortFactory.h"

#include "dc/framework/ComponentChangedEvent.h"
#include "dc/framework/GizzardComponentChangedEvent.h"
#include "dc/framework/ComponentChangedListener.h"

#include "util/TypeMap.h"
#include "util/IO.h"
#ifdef HAVE_CLASSIC
#include "dc/classic/ccafe-bind/AllCcafeBind.hh"
#endif // HAVE_CLASSIC
#include <cstring>

class SIO {
public:
static void e(const std::string & s) {
  IO::e("%s",s.c_str());
}
static void en(const std::string & s) {
  IO::en("%s",s.c_str());
}
};

namespace {
char id[]=
"$Id: Gizzard.cxx,v 1.62 2008/12/24 19:38:41 baallan Exp $";
} ENDSEMI

using ::ccafeopq::Keys;

void Gizzard::destroyComponentID( ::ccafeopq::ComponentID_shared cid_)
{ (void) cid_; }

::ccafeopq::PortInfo* 
Gizzard::createPortInfo(const std::string & name, 
			const std::string & type, 
			const std::map<std::string, std::string> &  properties)  
  throw (ccafeopq::Exception) 
{
  return new OpqPortInfo(name, type, properties);
}

/** destroy a previously created PortInfo */
void Gizzard::destroyPortInfo( ::ccafeopq::PortInfo * pi) {
  delete pi;
}

::ccafeopq::ComponentID_shared Gizzard::getComponentID() {
  return cid;
}


int Gizzard::findIndex( ::std::vector< ProviderPortData > & info, const std::string & name)
{
  ::std::vector< int > res = ServicesHelper::getProvidesIndexByName(info,name);
  if (res.size() == 1) {
    return res[0];
  }
  return -1;
}

int Gizzard::findIndex( ::std::vector< UserPortData > & info, const std::string & name)
{
  ::std::vector< int > res = ServicesHelper::getUsesIndexByName(info,name);
  if (res.size() == 1) {
    return res[0];
  }
  return -1;
}



bool Gizzard::countInitDone = false;
int Gizzard::pnameCount = -1;
/* a source of unique id numbers, at least
 * the first 4 billion times.
 */
int Gizzard::getNextCount() {
  pnameCount++;
  return pnameCount;
}

Gizzard::Gizzard(const std::string & instanceName, int64_t fComm, bool useComm) {

  serial = 0;
  IO_dn3("Gizzard::Gizzard(%s, %d)",instanceName.c_str(),(int)fComm);
  if (useComm) {
    fortranMPIComm = fComm;
  }
  hasComm = useComm;
  if (!countInitDone) {
    pnameCount = 0;
  }
  /* set the initial debug value from flag if present, or false if not present. */
#ifdef CCAFE_SPEW
#if CCAFE_SPEW 
  debug = true;
#else
  debug = false;
#endif
#else
  debug = false;
#endif
  frame = 0;
  ::std::string ser = "CCAFFEINE.";
  ::std::string iname = instanceName;
  ser += instanceName;
  ComponentID_impl * cidi = new ComponentID_impl(iname,ser);
  ComponentID cid_impl(cidi); // boost pointer in our local namespace. ugh.
  cid = ::boost::shared_dynamic_cast< ::ccafeopq::ComponentID_Interface > (cid_impl);

  compPropertyMap = createTypeMap();
  IO_dn1("  Gizzard properties created");

  oppf = new OpqParameterPortFactory();
  IO_dn1("  Gizzard OPPF created");

  oces = new OpqConnectionEventService();
  IO_dn1("  Gizzard OCES created");

  opaqueDelegates["::ccafeopq::ports::ConnectionEventService"] = oces;
  opaqueDelegates["::ccafeopq::ports::ParameterPortFactory"] = oppf;

  initKernel();
  IO_dn1("  Gizzard CTOR done.");
}

Gizzard::~Gizzard() {
  // jpfp->en("Gizzard::~Gizzard: dropping all the memory on the floor");
  frame = 0;
  delete oppf; oppf = 0;
  opaqueDelegates["::ccafeopq::ports::ParameterPortFactory"] = 0;
  opaqueDelegates["::ccafeopq::ports::ConnectionEventService"] = 0;
  compPropertyMap.reset();
  size_t nl;
  nl = cmptChgLsnrs.size() ;
  for ( ; nl > 0; nl--) { cmptChgLsnrs[nl-1] = 0; }
  cmptChgLsnrs.clear();
  cid.reset();
  fortranMPIComm = -1;
  hasComm = false;
}

void Gizzard::registerUsesPort( ::ccafeopq::PortInfo *name_and_type) throw (ccafeopq::Exception)
{
  ::ccafeopq::TypeMap_shared tm_ = createTypeMap();
  UserPortData::initDefaultProperties(tm_, name_and_type->getName(), name_and_type->getType());
  registerUsesPort(name_and_type->getName(), name_and_type->getType(), tm_);
  // fixme registerUsesPort :copy properties we care about from name_and_type
  // there's a function for this in util/TypeMap.h
  delete name_and_type;
}

void Gizzard::registerUsesPort(const ::std::string & pName, const ::std::string & pType, ccafeopq::TypeMap_shared tm_) throw ( ::ccafeopq::Exception )
{
  IO_dn3("Gizzard::registerUsesPort called for %s of type %s", 
	  pName.c_str(), pType.c_str());
  
  // if we're going to have one namespace, enforce that.
  int idx = findIndex(uData, pName);
  if(idx != -1) {
    IO::e("A uses port of type ");  SIO::e(pType);
    IO::e(" already has the name: ");  SIO::en(pName);
    char * x =
    IO_sn3("A uses port of type %s already has the name: %s",
	  pType.c_str(), pName.c_str());
    string msg = x;
    free(x);
    throw ccafeopq::Exception(msg);
  }
  idx = findIndex(pData, pName);
  if(idx != -1) {
    IO::e("A provides port of type ");  SIO::e(pType);
    IO::e(" already has the name: ");  SIO::en(pName);
    char * x = IO_sn3("A provides port of type %s already has the name: %s",
		  pType.c_str(), pName.c_str() );
    string msg = x;
    throw ccafeopq::Exception(msg);
  }
  if (!tm_) {
	  tm_ = createTypeMap();
  } 
  UserPortData::initDefaultProperties(tm_, pName, pType);

  int ins = nextSerial();
  UserPortData newuses(pName, pType, tm_, ins);
  uData.push_back(newuses);

  IO_dn1("checkInternalServices being called");
  checkInternalServices(pName, pType);
  GizzardComponentChangedEvent* gevt = new 
    GizzardComponentChangedEvent(ComponentChangedEvent::PORT_REGISTERED,
				 cid->getInstanceName(),
				 pName, pType
				 );
  ComponentChangedEvent* evt =  gevt;
  fireComponentChangedEvent(evt);
  delete gevt;

  return;
}


/** Inform Ccaffeine that you no longer intend to use this
    Port. Returns -1 if error. 0 otherwise.  */
int Gizzard::unregisterUsesPort(const char * name) 
{
  return unregisterUsesPort((char*) name);
}

void Gizzard::unregisterUsesPort(const std::string & name)  throw (ccafeopq::Exception)
{
  unregisterUsesPort(name.c_str());
  return;
}


int Gizzard::unregisterUsesPort(char *name) 
{
  // this functions assumes a singleton uses, not array uses.

  ::std::vector< int > rmPIa =
    ServicesHelper::getUsesIndexByName(uData, name);

  if(rmPIa.size() > 1) {
    char tmps[40];
    sprintf(tmps,"%d",int(rmPIa.size()));
    IO::e("Gizzard::unregisterUsesPort: More than 1 ("); IO::e(tmps); IO::e(") ");
    IO::e("uses Port in Services for name: "); IO::en(name);
    // delete rmPIa;
    return -1;
  }

  if (rmPIa.size() <= 0) { // This may be undefined or already unregistered.
    IO::e(":-( Gizzard::unregisterUsesPort error ("); IO::e(name);
    IO::en(") {never registered or already unregistered?}\n");
    return -1;
  }
  if (rmPIa.size() == 1) { // This may be currently connected.
    // blow the connection if not in use and remove registration.
    int idx = rmPIa[0];
    int err;
    err = disconnectUsesPort(idx);
    if (err) {
      IO::e("Cannot unregister port connected and in use: "); IO::en(name);
      return err;
    }
    UserPortData rmPI = uData[idx];
    uData.erase(uData.begin()+idx);
    GizzardComponentChangedEvent* gevt = new 
        GizzardComponentChangedEvent(ComponentChangedEvent::PORT_UNREGISTERED,
				   cid->getInstanceName(),
				   rmPI.getPortName(),
           rmPI.getPortType()
				   );
    ComponentChangedEvent* evt = gevt;
    fireComponentChangedEvent(evt);
    if(debug) {
      IO::e("Called Gizzard::unregisterUsesPort ");
      IO::en(name);
    }
    delete gevt;
    gevt = 0;
    evt = 0;
  }
  return 0;
}

int Gizzard::nextSerial()
{
  serial++;
  return serial;
}

void Gizzard::addProvidesPort(ccafeopq::Port* p, const std::string& pName, const std::string& pType) throw ( ::ccafeopq::Exception )
{
  IO_dn3("Gizzard::addProvidesPort(o,n,t) called for %s of type %s", 
	  pName.c_str(), pType.c_str());
  ::ccafeopq::TypeMap_shared tm_ = createTypeMap();
  ProviderPortData::initDefaultProperties(tm_, pName, pType);
  addProvidesPort(p, pName, pType, tm_);
}

void Gizzard::addProvidesPort( ::ccafeopq::Port * inPort, 
			     ::ccafeopq::PortInfo * name) throw (ccafeopq::Exception)
{
  std::string gn = name->getName();
  std::string gt = name->getType();
  IO_dn3("Gizzard::addProvidesPort(o,pi) called for %s of type %s", 
	  gn.c_str(), gt.c_str());

  ::ccafeopq::TypeMap_shared tm_ = createTypeMap();
  ProviderPortData::initDefaultProperties(tm_, gn, gt);
  
  ::gov::sandia::util::TypeMap::pi2typemap(name, tm_);
  addProvidesPort(inPort, gn, gt, tm_);
  delete name;

}

void Gizzard::addProvidesPort(ccafeopq::Port* inPort, const std::string& pName, const std::string& pType, ::ccafeopq::TypeMap_shared tm_) throw ( ::ccafeopq::Exception )
{
  IO_dn3("Gizzard::addProvidesPort(o,n,t,tm) called for %s of type %s", 
	  pName.c_str(), pType.c_str());
  // if we're going to have one namespace, enforce that.
  int idx = findIndex(pData, pName);
  if(idx != -1) {
    IO::e("A provides port of type "); SIO::e(pType); IO::e(" already has the name: ");
    SIO::en(pName);
    char * x =
      IO_sn3("A provides port of type %s already has the name: %s",
      pType.c_str() , pName.c_str());
    string msg = x;
    throw ccafeopq::Exception(msg);
  }
  idx = findIndex(uData, pName);
  if(idx != -1) {
    IO::e("A uses port of type "); SIO::e(pType); IO::e(" already has the name: ");
    SIO::en(pName);
    char * x =
      IO_sn3( "A uses port of type %s already has the name: %s", 
	      pType.c_str() , pName.c_str());
    string msg = x;
    throw ccafeopq::Exception(msg);
  }


  serial++;
  if (!tm_) {
	  tm_ = createTypeMap();
  }
  ProviderPortData::initDefaultProperties(tm_,pName, pType);
  int ins = nextSerial();
  ProviderPortData pp(inPort, pName, pType, tm_, ins);
  pData.push_back(pp);

  GizzardComponentChangedEvent* gevt = new 
    GizzardComponentChangedEvent(ComponentChangedEvent::PORT_ADDED,
				 cid->getInstanceName(),
				 pName, pType
				 );
  ComponentChangedEvent* evt = gevt;
  fireComponentChangedEvent(evt);
  delete gevt;
  evt = 0;
  gevt = 0;
  return;
}

::ccafeopq::Port * Gizzard::removeProvidesPort(const std::string & name)   throw (ccafeopq::Exception)
{
  return removeProvidesPort(name.c_str());
}

::ccafeopq::Port * Gizzard::removeProvidesPort(const char *name) 
{

  ::std::vector< int > rmPIa = 
    ServicesHelper::getProvidesIndexByName(pData, name);

  char tmps[40];
  if(rmPIa.size() > 1) {
    sprintf(tmps,"%d",int(rmPIa.size()));
    IO::e("Gizzard::removeProvidesPort: More than 1 (");
    IO::e(tmps); IO::e(") provides Port in Services for name: "); IO::en(name);
  }
  if(rmPIa.size() < 1) {
    sprintf(tmps,"%d",int(rmPIa.size()));
    IO::e("Gizzard::removeProvidesPort: Less than 1 (");
    IO::e(tmps); IO::e(") provides Port in Services for name: "); IO::en(name);
    return 0;
  }
  int idx = rmPIa[0];
  ProviderPortData rmPI = pData[idx];
  pData.erase(pData.begin()+idx);
  ::ccafeopq::Port * oldPort = 0;
  oldPort = rmPI.getPortInterface();
  
  GizzardComponentChangedEvent* gevt = new 
    GizzardComponentChangedEvent(ComponentChangedEvent::PORT_REMOVED,
				 cid->getInstanceName(),
				 rmPI.getPortName(), rmPI.getPortType()
				 );
  ComponentChangedEvent* evt =  gevt;
  fireComponentChangedEvent(evt);
  if(debug) {
    IO::e("Called Gizzard::removeProvidesPort ");
    IO::en(name);
  }
 
  delete gevt;

  return oldPort;
}

bool 
Gizzard::usesThisPortType(const string& typeToTest)
{
  int n = uData.size();

  for (int i = 0; i < n; i++)
  {
    if(uData[i].getPortType() == typeToTest)
      {
	return true;
      }
  }
  return false;
}

bool 
Gizzard::providesThisPortType(const string& typeToTest)
{
  int n = pData.size();

  for (int i = 0; i < n; i++)
  {
    if(pData[i].getPortType() == typeToTest)
      {
	return true;
      }
  }
  return false;
}


::std::vector< ::std::string > 
Gizzard::getUsesPortTypes()
{
	::std::vector< ::std::string > names;
  int n = uData.size();

  for (int i = 0; i < n; i++)
  {
    names.push_back(uData[i].getPortType());
  }
  return names;
}

::std::vector< ::std::string > 
Gizzard::getUsesPortNames()
{
	::std::vector< ::std::string > names;
  int n = uData.size();

  for (int i = 0; i < n; i++)
  {
    names.push_back(uData[i].getPortName());
  }
  return names;
}

::std::vector< ::std::string > 
Gizzard::getProvidesPortTypes()
{
  ::std::vector< ::std::string > names;

  int n = pData.size();
  for (int i = 0; i < n; i++)
  {
    names.push_back( pData[i].getPortType() );
  }
  return names;
}

::std::vector< ::std::string > Gizzard::getProvidesPortNames()
{
	::std::vector< ::std::string > names;
  int n = pData.size();
  for (int i = 0; i < n; i++)
  {
    names.push_back( pData[i].getPortName() );
  }
  return names;
}

::ccafeopq::Port * Gizzard::getOpaquePort(const ::std::string & name,enum ccafeopq::ExceptionType &status) {
  return getOpaquePort(name.c_str(), status);
}

::ccafeopq::Port * Gizzard::getOpaquePort(const char * name, enum ccafeopq::ExceptionType &status) {
	// FIXME -- must reject duplicate getPort calls,
	// or the reference management contract is not followed.
  // see if it's a connected uses port. 
  // returns null if defined uses, but  misconnected.
  ::ccafeopq::Port *op = 0;
  int idx = findIndex(uData, name);
  if(idx != -1) {
    if ( uData[idx].getIsConnected() &&
         uData[idx].getNumberOfConnections() == 1) {

      // This getPort can only return classic Port's. If getClassicPort
      // is called on an OpaquePort of type BABEL_PORT, it will return
      // NULL.
      op = uData[idx].getProvided();
      status = ccafeopq::Correct;
      return op;
    }
    ::std::string im = "!Info: Requested uses port ";
    im += name;
    im += " in component ";
    ::std::string gin = cid->getInstanceName();
    im += gin.c_str();
    im += " is not connected.";
    std::string es = im;
    IO::en(im.c_str());
    im = uData[idx].toString();
    IO::en(im.c_str());
    status = ccafeopq::PortNotConnected;
    return 0;
  }

  // we can always find stuff we currently provide, connected or not.
  idx = findIndex(pData, name);
  if (idx != -1) {
    op = pData[idx].getPortInterface();
    status = ccafeopq::Correct;
    return op;
  }

  // Didn't find anything provided connected or provided.
  IO::e("!Info: Requested port "); IO::e(name);
  ::std::string gin = cid->getInstanceName();
  IO::e(" in component "); IO::e(gin.c_str());
  IO::en(" is not defined as provide or uses.");
  status = ccafeopq::PortNotDefined;
  return 0;
}

::ccafeopq::Port * Gizzard::getPort(const std::string & name, enum ccafeopq::ExceptionType &status)   throw (ccafeopq::Exception){
  return getOpaquePort(name.c_str(), status);
}


void Gizzard::releasePort(char *name) {
  releasePort((const char *) name);
}

void Gizzard::releasePort(const char *name) {
  int idx = findIndex(uData, name);
  if(idx >= 0) {
    if ( uData[idx].getNumberOfConnections() == 1) {
      uData[idx].releaseProvided();
      return;
    } 
    // fixme--spew about releasePort on multiple connection.
    return;
  }
  idx = findIndex(pData, name);
  if (idx != -1) {
    if (pData[idx].getNumberOfUsers() < 1) {
      // fixme--spew about extra releaseport
    }
    pData[idx].releasePortInterface();
  }
}

void Gizzard::releasePort(const std::string & name)  throw (ccafeopq::Exception){
  releasePort(name.c_str());
}


/** This is how the framework adds a UsesPort.  Note that this is
    completely inaccessible from the component. */
int Gizzard::connectUsesPort( ::ccafeopq::PortInfo *info,  ::ccafeopq::Port *up, ::ccafeopq::PortInfo *fromPI, Gizzard *fromG) {
   int ret = 0;
   ret = connectUsesPort( info->getName(), up, fromPI->getName(), fromG);
   return ret;
}

// the internal service connection version
int Gizzard::connectUsesPort(const ::std::string & usesPortName,  ::ccafeopq::Port *up)
{
  std::string s = "";
  return connectUsesPort(usesPortName, up, s, 0);
}

// username, provided port, providerportname, providercomponent
int Gizzard::connectUsesPort(const ::std::string & usesPortName,  ::ccafeopq::Port *up, const ::std::string & fromName, Gizzard *fromG)
{
  int idx = findIndex(uData, usesPortName);
  if (idx < 0) {
    return -1;
  }
  if ( fromG ) {
    ConnectionID_ptr conn =
      uData[idx].addConnection(this, usesPortName, fromG, fromName, up);
      fromG->connectProvidesPort(conn);
    // cout << uData[idx].toString() <<endl; //FIXME
  } else {
    ConnectionID_ptr conn =
      uData[idx].addSelfConnection(this, usesPortName, up);
    // cout << uData[idx].toString() <<endl; //FIXME
  }
  // fixme--probably should either return or store conn somewhere.
  return 0;
}

/** Tell the Gizzard that this connection is no longer in effect. */
int Gizzard::disconnectProvidesPort(ConnectionID_ptr c) {
  int n;
  int erased = 0;
  while ( (n = ConnectionID_impl::indexOfConnection(cData, c) ) != -1) 
  {
    if (n >= 0 && n < int(cData.size())) {
      cData.erase(cData.begin()+n);
      erased++;
    }
  }
  if (!erased) {
    return -1;
  }
  return 0;
}

/** Tell the Gizzard that its providesPort is participating in the
    given connection. 
  */
int Gizzard::connectProvidesPort(ConnectionID_ptr c) {
  cData.push_back(c);
  return 0;
}


::std::vector< ConnectionID_ptr > Gizzard::getConnections()
{
  ::std::vector< ConnectionID_ptr > result;
  result = getUsesConnections();
  for (size_t i = 0; i < cData.size(); i++)
  {
    if ( ConnectionID_impl::indexOfConnection(result, cData[i]) == -1) 
    {
      result.push_back(cData[i]);
    }
  }
  return result;
}  

::std::vector< ConnectionID_ptr > Gizzard::getUsesConnections()
{
  ::std::vector< ConnectionID_ptr > result;
  for (size_t i = 0; i < uData.size(); i++)
  {
    ::std::vector< ConnectionID_ptr > upconns = uData[i].getConnectionIDs();
    for (size_t j = 0; j < upconns.size(); j++)
    {
      result.push_back(upconns[j]);
    }
  }
  return result;
}  

const char* Gizzard::getComponentInstanceName() {
  ::std::string gin = cid->getInstanceName();
  return gin.c_str();
}

::std::vector< std::string > Gizzard::getConnectionStrings()
{
  ::std::vector< std::string > v;
  ::std::string sb;
#if 0
  // fixme getConnectionStrings (not currently called, so not ported yet).
  char *s = 0;
  OpaquePortInfo *upi;
  int err;
  for(int i = 0;i < uPortStatus->size(); i++) {
    // UPortStatus *ups = dynamic_cast<UPortStatus *>(uPortStatus->elementAt(i));
    CHECKDC(ups);
    sb->setLength(0,err);
    if (!ups->selfConnection) {
      if (!ups->isReleased) {
        ::std::string gin = cid->getInstanceName();
        sb->append(gin.c_str());
        sb->append((char *)" ",1);
        upi = dynamic_cast<OpaquePortInfo *>(uName->elementAt(i));
        CHECKDC(upi);
        sb->append(upi->getName());
        sb->append((char *)" " ,1);
        sb->append(ups->providerGizzard->getComponentInstanceName());
        sb->append((char *)" ",1);
        sb->append(ups->providedPortInfo->getName());
      } else {
        ::std::string gin = cid->getInstanceName();
        sb->append(gin.c_str());
        sb->append((char *)" ",1);
        upi = dynamic_cast<OpaquePortInfo *>(uName->elementAt(i));
        CHECKDC(upi);
        sb->append(upi->getName());
        sb->append((char *)" " ,1);
        sb->append(ups->providerGizzard->getComponentInstanceName());
        sb->append((char *)" ",1);
        sb->append(ups->providedPortInfo->getName());
        sb->append((char *)" ACTIVE",7);
      }
    } else {
      if (!ups->isReleased) {
        ::std::string gin = cid->getInstanceName();
        sb->append(gin.c_str());
        sb->append((char *)" ",1);
        upi = dynamic_cast<OpaquePortInfo *>(uName->elementAt(i));
        CHECKDC(upi);
        sb->append(upi->getName());
        sb->append((char *)" FRAMEWORK ",11);
        sb->append(upi->getName());
      } else {
        ::std::string gin = cid->getInstanceName();
        sb->append(gin.c_str());
        sb->append((char *)" ",1);
        upi = dynamic_cast<OpaquePortInfo *>(uName->elementAt(i));
        CHECKDC(upi);
        sb->append(upi->getName());
        sb->append((char *)" FRAMEWORK ",11);
        sb->append(upi->getName());
        sb->append((char *)" ACTIVE",7);
      }
    }
    s = sb->toString();
    v->add(s);
  }
#endif
  return v;
}


// apparently unused function anyway...
// return 0 if we didn't force-destroy any connections.
int Gizzard::disconnectAllUsesPorts() {
  // fixme--disconnectAllUsesPorts -- needs events generated?
  // should we object about disconnects of items in use?
  int n;
  n = uData.size();
  int sum = 0;
  for ( ; n > 0; n--) {
    sum += uData[n-1].removeConnections();
  }
  return sum;

}

// int Gizzard::disconnectUsesPort( ::ccafeopq::PortInfo *info, ::ccafeopq::PortInfo *fromPI, Gizzard *fromG) {
int Gizzard::disconnectUsesPort( int idx)
{ 
              
  // int idx = findIndex(uData, info->getName());
  if(idx < 0 || idx > (int)uData.size()) {
    return 0;
  }
  ::std::string uname = uData[idx].getPortName();
  if (uData[idx].getIsActive()) {
    IO::e("Cannot disconnect active port "); SIO::e(uname); 
    IO::en(" connected to another component.");
    return -1;
  }
  ::std::vector< ConnectionID_ptr > connlist = uData[idx].getConnectionIDs();
  for ( int n = connlist.size(); n > 0; n--) {
    uData[idx].removeConnection(connlist[n-1]);
    // to inform provider here.
    if ( ! (connlist[n-1] -> isFrameworkConnection() ) ){
      Gizzard * pg = connlist[n-1] -> getProviderGizzard();
      pg->disconnectProvidesPort(connlist[n-1]);
    }
  }
  return 0; // well, nothing to do. could spew.

}


const ::std::vector< UserPortData > & Gizzard::getUsesPortRegister()
{
  return uData;
}

const ::std::vector< UserPortData > & Gizzard::getUsesPorts() {
  return uData;
}

const ::std::vector< ProviderPortData > & Gizzard::getProvidesPorts() {
  return pData;
}

/** Must use the Servicefactory Standard and return an  ::ccafeopq::Port. */
void Gizzard::checkInternalServices( const ::std::string & uName, const ::std::string & uType) {

  int err = 0;

  // check bindings for special ports.
  IO_dn2("!checkInternalServices: %d helpers registered.", (int)helpers.size());
  for (size_t ih = 0; ih < helpers.size(); ih++)
  {
    ::ccafeopq::ServicesHelper *sh = 0;
    sh = helpers[ih];
    ::ccafeopq::Port * op = 0;
    IO_dn2("!checkInternalServices: trying helper %d.", (int)ih);
    op  = sh->checkSupport(uName, uType, opaqueDelegates);
    if (op) {
      err = connectUsesPort(uName, op);
      IO_dn2("!Uses Port: %s is connected as a service", uName.c_str());
      if (err != 0) {
        IO_en3("!Uses Port: %s service connect returned %d", uName.c_str(), err);
      }
      return;
    }
  }

  // check kernel supported services.
  // really, these shouldn't be here.
  // for bindings we need to use the PC lookup-adapter approach

  if(strcmp("::ccafeopq::ports::ConnectionEventService", uType.c_str()) == 0||
     strcmp("ccafeopq::ports::ConnectionEventService", uType.c_str()) == 0) {
	// don't need a wrapper. oces is port and wrapper all in one
    err = connectUsesPort(uName, oces);
    IO_dn2("!Uses Port: %s connect as a service attempted", uName.c_str());
    IO_en3("!Uses Port: %s service connect returned %d (0=ok)", uName.c_str(), err);
    return;
  }
  if(strcmp("::ccafeopq::ports::ParameterPortFactory", uType.c_str()) == 0||
     strcmp("ccafeopq::ports::ParameterPortFactory", uType.c_str()) == 0) {
	// don't need a wrapper. oppf is port and wrapper all in one
    err = connectUsesPort(uName, oppf);
    IO_dn2("!Uses Port: %s connect as a service attempted", uName.c_str());
    IO_en3("!Uses Port: %s service connect returned %d (0=ok)", uName.c_str(), err);
    return;
  }
  IO_dn3("!Uses Port: %s (%s) unmatched in internal services.", uName.c_str(),uType.c_str());
}

::ccafeopq::TypeMap_shared 
Gizzard::createTypeMapStatic() throw ( ::ccafeopq::Exception )
{
  ::gov::sandia::util::TypeMap * ntm = new ::gov::sandia::util::TypeMap();
  ::ccafeopq::TypeMap_Interface * otmi = ntm;
  ::ccafeopq::TypeMap_shared otm(otmi);
  return otm;
}


::ccafeopq::TypeMap_shared Gizzard::createTypeMap() throw ( ::ccafeopq::Exception )
{
  return createTypeMapStatic();
}

::ccafeopq::TypeMap_shared Gizzard::getPortProperties(const ::std::string & name) throw ( ::ccafeopq::Exception )
{
  // ::ccafeopq::PortInfo* opi = 0;
  int idx = -1;
  idx = findIndex(uData, name);
  if (idx != -1) {
    
    return uData[idx].getUserPortProperties();
  }
  idx = findIndex(pData, name);
  if (idx != -1) {
    return pData[idx].getProviderPortProperties();
    
  }
  throw ::ccafeopq::Exception( ::ccafeopq::BadPortName,"Gizzard::getPortProperties port not found");
}

void Gizzard::setPortProperties(const ::std::string& name, ::ccafeopq::TypeMap_shared tm_) throw ( ::ccafeopq::Exception )
{
  // ::ccafeopq::PortInfo* opi = 0;
  int idx = -1;
  idx = findIndex(uData, name);
  if (idx != -1) {
   
    uData[idx].setUserPortProperties(tm_);
    return;
  }
  idx = findIndex(pData, name);
  if (idx != -1) {
    pData[idx].setProviderPortProperties(tm_);
    return;
  }
  throw ::ccafeopq::Exception( ::ccafeopq::BadPortName,"Gizzard::setPortProperties port not found");
}

::std::string Gizzard::genUniquePortName(const ::std::string& baseName) throw ( ::ccafeopq::Exception )
{
/** on a long enough run, this will be buggy. fixme--longterm. */
  ::std::string s = baseName;
  s += "_";
  char buf[40];
  int c = getNextCount();
  sprintf(buf,"%d",c);
  s += buf;
  return s;
}

::ccafeopq::TypeMap_shared Gizzard::getPropertyMap()
{
	return compPropertyMap->cloneData();
}

void Gizzard::setPropertyMapData( ::ccafeopq::TypeMap_shared tm )
{
	::gov::sandia::util::TypeMap::copyInData(tm, compPropertyMap);
}


void Gizzard::initDelegates() {

}

#if HAVE_CLASSIC
// connection event stuff was here. now oces-> ...
#endif // HAVE_CLASSIC

void Gizzard::addComponentChangedListener(ComponentChangedListener* l) {
  cmptChgLsnrs.push_back(l);
}

void Gizzard::fireComponentChangedEvent(ComponentChangedEvent* evt) {
  size_t nl = cmptChgLsnrs.size() ;
  for(; nl > 0; nl--) {
    ComponentChangedListener* ccl = cmptChgLsnrs[nl-1];
    if (ccl != 0) {
      ccl->componentChanged(evt);
    } else { // FIXME whine
    }
  }
}

OpqConnectionEventService * Gizzard::getOCES()
{
	return oces;
}

void Gizzard::setFrameData( std::map<std::string, void *> *v)
{
  frame = v;
}

bool Gizzard::hasMPIComm(int64_t & fortranBorrowComm) 
{
	if (hasComm) {
		fortranBorrowComm = fortranMPIComm;
		IO_dn1("Gizzard::hasMPIComm returning true.");
	} else {
		IO_dn1("Gizzard::hasMPIComm returning false.");
	}
	return hasComm;
}

/* basically this is only here for ServicesHelper implementations. */
::ccafeopq::TypeMap_shared Gizzard::getComponentInternalPropertyMap()
{
  return compPropertyMap;
}

void Gizzard::addServicesHelper( ::ccafeopq::ServicesHelper *sh)
{
  if (sh != 0) {
    helpers.push_back(sh);
  }
}
