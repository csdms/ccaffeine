#ifndef lint
static char id[] = 
"$Id: NeoServicesHelper.cc,v 1.20 2005/08/31 23:59:32 baallan Exp $";
#endif
#include <assert.h>

#ifdef _CCAMPI
#include "util/noSeekMPI.h"
#include <mpi.h>
#endif
#include <string>
#include <map>
#include <iostream>
using namespace std;
#include "dc/export/config.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#endif
#include <neocca.hh>
#ifdef HAVE_CLASSIC
#include <stdPorts.h>
#endif
#include <neoports.hh>
#include "dc/export/AllExport.hh"
#include "dc/framework/KernelPort.h"

#include "util/IO.h"

#include "port/GUIService.h"
#include "dc/port/DefaultPrintfPort.h"



#include "dc/port/DefaultGUIService.h"

#ifdef _CCAMPI
#ifdef HAVE_CLASSIC
#include <ports/MPIBorrow.h>
#include <ports/MPIService.h>
#endif
#include "dc/port/DefaultMPIBorrow.h"
#include "dc/port/DefaultMPIService.h"
#endif // _CCAMPI

//#include "dc/framework/dc_fwkStar.h"

#include "dc/framework/ComponentChangedEvent.h"
#include "dc/framework/GizzardComponentChangedEvent.h"
#include "dc/framework/ComponentChangedListener.h"

#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoServicesHelper.hh"
#include "dc/neo/ccafe-bind/NeoOpaquePort.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueGoPort.hh"
#include "dc/neo/ccafe-bind/NeoOpaqueComponentFactory.hh"
#include "dc/neo/ccafe-bind/NeoBasicParameterPortPC.hh"
#include "dc/neo/ccafe-bind/NeoParameterPortPC.hh"
#include "dc/neo/ccafe-bind/NeoParameterPortFactoryPC.hh"
#include "dc/neo/ccafe-bind/NeoBuilderServicePC.hh"
#include "dc/neo/ccafe-bind/NeoServiceRegistryPC.hh"
#include "dc/neo/ccafe-bind/NeoLoaderPC.hh"
#include "dc/neo/ccafe-bind/NeoGoPortPC.hh"

using ::ccafeopq::Keys;

//////////////////////////////////////////////////////////////////////
// all the crap here shouldn't be exposed to the ccafeopq kernel
class NeoServicesHelperPrivate {

private:
	DefaultPrintfPort *pfp;
	DefaultGUIService *gsp;

	bool isInit;
	bool isInitComm;

public:
	::neo::cca::Port *mpis;
	::neo::cca::Port *mpib;
	NeoServicesHelperPrivate();
	~NeoServicesHelperPrivate();

	void init( );
	void initComm( int64_t fComm);
	void destroy();

	DefaultPrintfPort *get_pfp();
	DefaultGUIService *get_gsp();
	::neo::cca::Port *get_mpis();
	::neo::cca::Port *get_mpib();
};

void NeoServicesHelperPrivate::initComm(int64_t fComm )
{
	if (isInitComm) { return; }
#ifdef _CCAMPI
	DefaultMPIService *m;
	m = new DefaultMPIService(fComm);
	mpis = dynamic_cast<neo::cca::Port *>(m);

	DefaultMPIBorrow *mb;
	mb = new DefaultMPIBorrow(fComm);
	mpib = dynamic_cast<neo::cca::Port *>(mb);
#else 
	mpis = 0;
	mpib = 0;
#endif // _CCAMPI
	isInitComm = true;
}

void NeoServicesHelperPrivate::init( )
{
	if (isInit) { return; }
// from new
	pfp = new DefaultPrintfPort(); 
	gsp = new DefaultGUIService();

	isInit = true;
}

void NeoServicesHelperPrivate::destroy()
{
	delete pfp; pfp = 0;
	delete gsp; gsp = 0;
#ifdef _CCAMPI
	if (mpis != 0) {
		DefaultMPIService *m;
		m = dynamic_cast<DefaultMPIService *>(mpis);
		delete m; m = 0;
	}
	if (mpib != 0) {
		DefaultMPIBorrow *mb;
		mb = dynamic_cast<DefaultMPIBorrow *>(mpib);
		delete mb; mb = 0;
	}
#endif

}

NeoServicesHelperPrivate::~NeoServicesHelperPrivate()
{
	destroy();
	isInit = false;
}
NeoServicesHelperPrivate::NeoServicesHelperPrivate()
{
	isInit = false;
	pfp = 0;
	gsp = 0;
        mpis = 0;
	mpib = 0;
}

DefaultPrintfPort *NeoServicesHelperPrivate::get_pfp()
{
	init();
	return pfp;
}

DefaultGUIService *NeoServicesHelperPrivate::get_gsp()
{
	init();
	return gsp;
}

::neo::cca::Port *NeoServicesHelperPrivate::get_mpis()
{
	init();
	return mpis;
}

::neo::cca::Port *NeoServicesHelperPrivate::get_mpib()
{
	init();
	return mpib;
}


//////////////////////////////////////////////////////////////////////

NeoServicesHelper::NeoServicesHelper()
{
	hp = new NeoServicesHelperPrivate();
}

NeoServicesHelper::NeoServicesHelper(int bogon)
{
	hp = new NeoServicesHelperPrivate();
}

NeoServicesHelper::~NeoServicesHelper()
{
	delete hp;
}

void NeoServicesHelper::destroy()
{
	 // fixme?
	// probably should record wrappers created in checkSupport and delete them.
}

using ::ccafeopq::Keys;

void NeoServicesHelper::addBindingDelegates( ::ccafeopq::Services *os )
{
}

void NeoServicesHelper::initComm(int64_t fComm)
{
	hp->initComm(fComm);
}

::ccafeopq::Port * NeoServicesHelper::checkSupport(const std::string & uName, const std::string & uType, ::ccafeopq::SvcPortMap &gpm)
{
  hp->init();
  IO_dn3("!NeoServicesHelper::checkSupport(%s, %s) entered",uName.c_str(),uType.c_str());
#if 0 // fixme
  if(uType == "gov.cca.ConnectionEventService") {
    neo::cca::Port* uses = 
      dynamic_cast<neo::cca::Port* >(this);
    CHECKDC(uses);
    connectUsesPort(uName, new NeoOpaquePort(uses));
    return;
  }
#endif // 0
  if( uType == "neo.cca.ports.JPrintfPort") {
	  // we know something special about jprintf implementation
	  // that makes this cast possible.
    neo::cca::Port* uses = dynamic_cast<neo::cca::Port*>(gpm["JPrintfPort"]);

    if (uses == 0) {
	    IO_en2("NeoServicesHelper::checkSupport cast fail unexpected for %s",uType.c_str());
	    return 0;
    }
    NeoOpaquePort * cop = new NeoOpaquePort(uses);
    return cop;
  }

  if(uType == "GUIService") {
    neo::cca::Port* uses = dynamic_cast<neo::cca::Port*>(hp->get_gsp());
    if (uses == 0) {
	    IO_en2("NeoServicesHelper::checkSupport cast fail unexpected for %s",uType.c_str());
	    return 0;
    }
    NeoOpaquePort * cop = new NeoOpaquePort(uses);
    return cop;
  }

#if 0 // stdarg virtual printf insanity not supported while gcc is broken.
  if(uType == "gov.cca.PrintfService") {
    neo::cca::Port* uses = dynamic_cast<neo::cca::Port*>(hp->get_pfp());
    if (uses == 0) {
	    IO_en2("NeoServicesHelper::checkSupport cast fail unexpected for %s",uType.c_str());
	    return 0;
    }
    NeoOpaquePort * cop = new NeoOpaquePort(uses);
    return cop;
  }
#endif

  if (uType == "neo.cca.ports.ParameterPortFactory" ||
      uType == "::neo::cca::ports::ParameterPortFactory" ||
      uType == "neo::cca::ports::ParameterPortFactory") {
	  // we happen to know this is a core service bound directly.
    ccafeopq::Port *uses = gpm["::ccafeopq::ports::ParameterPortFactory"];
    if (uses == 0) {
      IO_en2("NeoServicesHelper::checkSupport cast fail unexpected for %s",uType.c_str());
      return 0;
    }
    neo::cca::ports::ParameterPortFactory * nppf;
    nppf = dynamic_cast< neo::cca::ports::ParameterPortFactory * >(uses);
    if ( nppf != 0) {
      NeoOpaquePort * cop = dynamic_cast< NeoOpaquePort *>(nppf);
      return cop;
    } 
    return 0;
  }

#ifdef _CCAMPI
  if (uType == "gov.cca.MPIService") {
    neo::cca::Port* uses = dynamic_cast<neo::cca::Port*>(hp->mpis);
    if (uses == 0) {
	    IO_en2("NeoServicesHelper::checkSupport cast fail unexpected for %s",uType.c_str());
	    return 0;
    }
    NeoOpaquePort * cop = new NeoOpaquePort(uses);
    return cop;
  }
  if( uType == "gov.cca.MPIBorrow") {
    neo::cca::Port* uses = dynamic_cast<neo::cca::Port*>(hp->mpib);
    if (uses == 0) {
	    IO_en2("NeoServicesHelper::checkSupport cast fail unexpected for %s",uType.c_str());
	    return 0;
    }
    NeoOpaquePort * cop = new NeoOpaquePort(uses);
    return cop;
  }
#endif // _CCAMPI

  IO_dn3("!No NeoServicesHelper support for %s(%s).",uName.c_str(),uType.c_str());
  return 0;
}

NeoPortConverter_shared
NeoServicesHelper::findConversion( ccafeopq::Port *op)
{
	IO_dn1("!NeoServicesHelper::findConversion: make it go away!.");
	NeoPortConverter_shared npc;

	// FIXME -- or don't. this requires dynamic_cast case testing
	// and we should just not do it. 
	// unfortunately, we need an event model to replace it.
	
	if (op == 0) {
#ifdef CCAFE_AUDIT
		IO_dn1("NeoServicesHelper::convert called on null");
#endif
		return npc;
	}

	ccafeopq::ports::ParameterPort * opp =
		dynamic_cast< ccafeopq::ports::ParameterPort * >(op);
	if (opp != 0) {
		NeoParameterPortPC *pppc = new NeoParameterPortPC();
		NeoPortConverter_shared pppc_ptr(pppc);
		return pppc_ptr;
	}

	ccafeopq::ports::BasicParameterPort * obpp =
		dynamic_cast< ccafeopq::ports::BasicParameterPort * >(op);
	if (obpp != 0) {
		NeoBasicParameterPortPC *bpppc = new NeoBasicParameterPortPC();
		NeoPortConverter_shared bpppc_ptr(bpppc);
		return bpppc_ptr;
	}

	return npc; 
}

std::string 
NeoServicesHelper::registerForConversionType(ccafeopq::ComponentID_shared me, std::string portName, std::string portType, std::map< std::string, NeoPortConverter_shared > & portConversions)
{
#define WHINGE \
IO_dn4("NeoServicesHelper::registerForConversionType: %s --> %s at %d", \
portType.c_str(), ntype.c_str(), __LINE__)

	string ntype = portType;
	// check goport alii
	if (portType == "neo::cca::ports::GoPort" ||
		portType == "::neo::cca::ports::GoPort" ||
		portType == "neo.cca.ports.GoPort")
       	{
		ntype = "::ccafeopq::GoPort";
		NeoGoPortPC *gppc = new NeoGoPortPC();
		NeoPortConverter_shared gppc_ptr(gppc);
		portConversions[portName] = gppc_ptr;
		WHINGE;
	}

	// check builderservice alii
	if (portType == "neo::cca::ports::BuilderService" ||
		portType == "::neo::cca::ports::BuilderService" ||
		portType == "neo.cca.ports.BuilderService")
       	{
		ntype = "::ccafeopq::BuilderService";
		NeoBuilderServicePC *bspc = new NeoBuilderServicePC();
		NeoPortConverter_shared bspc_ptr(bspc);
		portConversions[portName] = bspc_ptr;
		WHINGE;
	}

	// check parameter port alii
	if (portType == "neo.cca.ports.ParameterPort" ||
		portType == "neo::cca::ports::ParameterPort" ||
		portType == "::neo::cca::ports::ParameterPort")
       	{
		ntype = "::ccafeopq::ports::ParameterPort";
		NeoParameterPortPC *pppc = new NeoParameterPortPC();
		NeoPortConverter_shared pppc_ptr(pppc);
		portConversions[portName] = pppc_ptr;
		WHINGE;
	}

	// check parameter portfactory alii
	if (portType == "neo.cca.ports.ParameterPortFactory" ||
		portType == "neo::cca::ports::ParameterPortFactory" ||
		portType == "::neo::cca::ports::ParameterPortFactory")
       	{
		ntype = "::ccafeopq::ports::ParameterPortFactory";
		NeoParameterPortFactoryPC *ppfpc = new NeoParameterPortFactoryPC();
		NeoPortConverter_shared ppfpc_ptr(ppfpc);
		portConversions[portName] = ppfpc_ptr;
		WHINGE;
	}

	// check basic parameter port alii
	if (portType == "neo.cca.ports.BasicParameterPort" ||
		portType == "neo::cca::ports::BasicParameterPort" ||
		portType == "::neo::cca::ports::BasicParameterPort")
       	{
		ntype = "::ccafeopq::ports::BasicParameterPort";
		NeoBasicParameterPortPC *bpppc = new NeoBasicParameterPortPC();
		NeoPortConverter_shared bpppc_ptr(bpppc);
		portConversions[portName] = bpppc_ptr;
		WHINGE;
	}

	// check serviceregistry port alii
	if (portType == "neo.cca.ports.ServiceRegistry" ||
		portType == "neo::cca::ports::ServiceRegistry" ||
		portType == "::neo::cca::ports::ServiceRegistry")
       	{
		ntype = "::ccafeopq::ServiceRegistry";
		NeoServiceRegistryPC *srpc = new NeoServiceRegistryPC(me);
		NeoPortConverter_shared srpc_ptr(srpc);
		portConversions[portName] = srpc_ptr;
		WHINGE;
	}

	// check loader port alii
	if (portType == "neo.cca.ports.Loader" ||
		portType == "neo::cca::ports::Loader" ||
		portType == "::neo::cca::ports::Loader")
       	{
		ntype = "::ccafeopq::Loader";
		NeoLoaderPC *lpc = new NeoLoaderPC();
		NeoPortConverter_shared lpc_ptr(lpc);
		portConversions[portName] = lpc_ptr;
		WHINGE;
	}

	return ntype;
#undef WHINGE
}

void 
NeoServicesHelper::checkthrow(const char * className, const char * memberName, void * member, const char *funcName)
{
	if (! member ) {
		::neo::cca::Exception ex;
		std::string mess = className;
		mess += " ";
		mess += memberName;
		mess += " uninit in ";
		mess += funcName;
		ex.setMessage(mess);
		throw ex;
	}
}


::ccafeopq::Port * 
NeoServicesHelper::createSpecialProvider( neo::cca::Port * inPort, const std::string & name, const std::string & type, ccafeopq::TypeMap_shared portProperties, std::string & supportedType)
{
	// assume input is good, as it comes from NeoServices.
	supportedType = type; //may want to morph this sometimes?
	ccafeopq::Port * wrapper = 0;

#define WHINE_TYPE_MISMATCH(t, ct) else IO_en3("You seem to have classified a non-%s as a %s by mistake.", ct.c_str(), type.c_str())

	// The rules are: check for string matches, then check for cast.
	// Switching based on dynamic cast will give wrong result for
	// components that implement multiple ports by inheritance.

//// GO PORT section //////////////////////////////////////
	if (
		type == "::neo::cca::ports::GoPort" ||
		type == "neo.cca.ports.GoPort" ||
		type == "neo::cca::ports::GoPort"||
		type == "gov.cca.ports.GoPort" ||
		type == "GoPort" ||
		type == "gov.cca.GoPort"
	) 
	{
		supportedType = "::ccafeopq::GoPort";
		IO_dn3("Adding an apparent GoPort of type: %s and named: %s",
			 type.c_str(), name.c_str());

		neo::cca::ports::GoPort * gp =
			dynamic_cast< neo::cca::ports::GoPort* >(inPort);
		if (gp) {
			NeoOpaqueGoPort * cop = new NeoOpaqueGoPort(gp);
			wrapper = cop;
			return wrapper;
		} 
		WHINE_TYPE_MISMATCH(type, supportedType);
	}

//// ComponentFactory section //////////////////////////////////////
	if (
		type == "::neo::cca::ports::ComponentFactory" ||
		type == "neo::cca::ports::ComponentFactory" ||
		type == "neo.cca.ports.ComponentFactory" ||
		type == "ComponentFactory" 
	)
	{
		supportedType = "::ccafeopq::ComponentFactory";
		IO_dn3("Adding an apparent Factory of type: %s and named: %s",
			 type.c_str(), name.c_str());

		neo::cca::ports::ComponentFactory * cf =
			dynamic_cast< neo::cca::ports::ComponentFactory * >(inPort);
		if (cf) {
			NeoOpaqueComponentFactory * cop = new NeoOpaqueComponentFactory(cf);
			wrapper = cop;
			return wrapper;
		} 
		WHINE_TYPE_MISMATCH(type, supportedType);
	}
	return 0;
	
#undef WHINE_TYPE_MISMATCH
}

#ifdef HAVE_CLASSIC
#include "dc/classic/ccafe-bind/ClassicOpaquePort.hh"
#endif
neo::cca::Port * 
NeoServicesHelper::translate(const std::string name, ::ccafeopq::Port * op)
{
	IO_en2("NeoServicesHelper::translate trying on port ",name.c_str());
#ifdef HAVE_CLASSIC
	if ( op->supportsKind(ccafeopq::CLASSIC_PORT) ) {
		IO_en1("NeoServicesHelper::translate seems to have a classic.");
		ClassicOpaquePort *cop = dynamic_cast< ClassicOpaquePort * >(op);
		if (cop) {
			classic::gov::cca::Port * cp = cop->getClassicPort();
			if (cp == 0) { // rather unexpected!
				IO_en2("NeoServicesHelper::translate getClassicPort %s failed.",name.c_str());
				return 0;
			}
			neo::cca::Port *np = dynamic_cast< neo::cca::Port * >(cp);
			if (np == 0) {
				IO_en2("NeoServicesHelper::translate cast to neo of %s failed unexpectedly.",name.c_str());
			}
			return np;
		}
	}
#endif // HAVE_CLASSIC

	// other bindings?
	return 0;
	
}
