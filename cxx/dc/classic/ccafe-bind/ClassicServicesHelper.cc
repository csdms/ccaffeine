#ifndef lint
static char id[] = 
"$Id: ClassicServicesHelper.cc,v 1.15 2005/08/31 23:59:31 baallan Exp $";
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
#include <cca.h>
#ifdef HAVE_NEO
#include <neocca.hh>
#include <neoports.hh>
#endif
#include <stdPorts.h>
#include "dc/export/AllExport.hh"

#include "util/IO.h"
#ifdef _CCAMPI
#include <ports/MPIBorrow.h>
#include <ports/MPIService.h>
#include "dc/port/DefaultMPIBorrow.h"
#include "dc/port/DefaultMPIService.h"
#endif // _CCAMPI

#include "parameters/parametersStar.h"
#include "port/supportInterfaces.h"
#include "dc/port/DefaultPrintfPort.h"
#include "dc/port/DefaultKeyValuePort.h"
#include "dc/port/DefaultConfigurableParameterFactory.h"
#include "dc/port/DefaultGUIService.h"

#include "dc/framework/dc_fwkPublic.h"

#include "dc/classic/ccafe-bind/AllCcafeBind.hh"
#include "dc/classic/ccafe-bind/ClassicServicesHelper.hh"

#include "dc/port/DefaultJPrintfPort.h"

#include "dc/classic/ccafe-bind/ClassicGoPortPC.hh"
using ::ccafeopq::Keys;

//////////////////////////////////////////////////////////////////////
// all the crap here shouldn't be exposed to the ccafeopq kernel
class ClassicServicesHelperPrivate {

private:
	DefaultPrintfPort *pfp;
	DefaultJPrintfPort *jpfp;
	ConfigurableParameterFactory *cpf;
	DefaultGUIService *gsp;
	::classic::gov::cca::Port *mpis;
	::classic::gov::cca::Port *mpib;

	bool isInit;
	bool isInitComm;

public:
	ClassicServicesHelperPrivate();
	~ClassicServicesHelperPrivate();

	void init( );
	void initComm(int64_t fComm );
	void destroy();

	::classic::gov::cca::Port *get_mpis();
	::classic::gov::cca::Port *get_mpib();
	DefaultPrintfPort *get_pfp();
	DefaultJPrintfPort *get_jpfp();
	ConfigurableParameterFactory *get_cpf();
	DefaultGUIService *get_gsp();
};

void ClassicServicesHelperPrivate::init( )
{
	if (isInit) { return; }
	IO_dn1("ClassicServicesHelperPrivate::init enter");
// from new
	jpfp = new DefaultJPrintfPort(); 
	IO_dn1("ClassicServicesHelperPrivate::init created jpfp");
	pfp = new DefaultPrintfPort(); 
	IO_dn1("ClassicServicesHelperPrivate::init created pfp");
	cpf = new DefaultConfigurableParameterFactory();
	IO_dn1("ClassicServicesHelperPrivate::init created cpf");
	gsp = new DefaultGUIService();
	IO_dn1("ClassicServicesHelperPrivate::init created gsp");

	isInit = true;
	IO_dn1("ClassicServicesHelperPrivate::init exit");
}

void ClassicServicesHelperPrivate::initComm(int64_t fComm )
{
	if (isInitComm) { return; }
	IO_dn1("ClassicServicesHelperPrivate::initComm enter");
#ifdef _CCAMPI
	DefaultMPIService *m;
	m = new DefaultMPIService(fComm);
	IO_dn1("ClassicServicesHelperPrivate::init created m");
	mpis = dynamic_cast< classic::gov::cca::Port *>(m);

	DefaultMPIBorrow *mb;
	mb = new DefaultMPIBorrow(fComm);
	IO_dn1("ClassicServicesHelperPrivate::init created mb");
	mpib = dynamic_cast< classic::gov::cca::Port *>(mb);
#else 
	mpis = 0;
	mpib = 0;
#endif // _CCAMPI

	isInitComm = true;
	IO_dn1("ClassicServicesHelperPrivate::initComm exit");
}


void ClassicServicesHelperPrivate::destroy()
{
	delete jpfp; jpfp = 0;
	delete pfp; pfp = 0;
	delete cpf; cpf = 0;
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

ClassicServicesHelperPrivate::~ClassicServicesHelperPrivate()
{
	destroy();
	isInit = false;
	isInitComm = false;
}

ClassicServicesHelperPrivate::ClassicServicesHelperPrivate()
{
	isInit = false;
	isInitComm = false;
	jpfp = 0;
	pfp = 0;
	cpf = 0;
	gsp = 0;
	mpis = 0;
	mpib = 0;
}

DefaultJPrintfPort *ClassicServicesHelperPrivate::get_jpfp()
{
	init();
	return jpfp;
}
DefaultPrintfPort *ClassicServicesHelperPrivate::get_pfp()
{
	init();
	return pfp;
}

ConfigurableParameterFactory *ClassicServicesHelperPrivate::get_cpf()
{
	init();
	return cpf;
}


DefaultGUIService *ClassicServicesHelperPrivate::get_gsp()
{
	init();
	return gsp;
}

::classic::gov::cca::Port *ClassicServicesHelperPrivate::get_mpis()
{
	return mpis;
}

::classic::gov::cca::Port *ClassicServicesHelperPrivate::get_mpib()
{
	return mpib;
}


//////////////////////////////////////////////////////////////////////

ClassicServicesHelper::ClassicServicesHelper()
{
	hp = new ClassicServicesHelperPrivate();
}

void ClassicServicesHelper::initComm(int64_t fComm)
{
	// FIXME setup mpi services based on comm.
	hp->initComm(fComm);
}

ClassicServicesHelper::~ClassicServicesHelper()
{
	delete hp;
	hp = 0;
}

void ClassicServicesHelper::destroy()
{
	 // fixme?
	// probably should record wrappers created in checkSupport and delete them.
}

using ::ccafeopq::Keys;

void ClassicServicesHelper::addBindingDelegates( ::ccafeopq::Services *os )
{
}

::ccafeopq::Port * ClassicServicesHelper::checkSupport(const std::string & uName, const std::string & uType, ::ccafeopq::SvcPortMap &gpm)
{
  hp->init();
  IO_dn3("!ClassicServicesHelper::checkSupport(%s, %s) entered",uName.c_str(),uType.c_str());
#if 0 // fixme
  if(uType == "gov.cca.ConnectionEventService") {
    classic::gov::cca::Port* uses = 
      dynamic_cast<classic::gov::cca::Port* >(this);
    CHECKDC(uses);
    connectUsesPort(uName, new ClassicOpaquePort(uses));
    return;
  }
#endif // 0

  if( uType == "gov.cca.JPrintfService") {
	  // we know something special about jprintf implementation
	  // that makes thiks cast possible.
    classic::gov::cca::Port* uses = dynamic_cast<classic::gov::cca::Port*>(hp->get_jpfp());

    if (uses == 0) {
	    IO_en2("ClassicServicesHelper::checkSupport cast fail unexpected for %s",uType.c_str());
	    return 0;
    }
    ClassicOpaquePort * cop = new ClassicOpaquePort(uses);
    IO_dn1("ClassicServicesHelper::checkSupport using hp_jpfp");
    return cop;
  }

  if(uType == "GUIService") {
    classic::gov::cca::Port* uses = dynamic_cast<classic::gov::cca::Port*>(hp->get_gsp());
    if (uses == 0) {
	    IO_en2("ClassicServicesHelper::checkSupport cast fail unexpected for %s",uType.c_str());
	    return 0;
    }
    ClassicOpaquePort * cop = new ClassicOpaquePort(uses);
    IO_dn1("ClassicServicesHelper::checkSupport using hp_gsp]");
    return cop;
  }
  if(uType == "gov.cca.PrintfService") {
    classic::gov::cca::Port* uses = dynamic_cast<classic::gov::cca::Port*>(hp->get_pfp());
    if (uses == 0) {
	    IO_en2("ClassicServicesHelper::checkSupport cast fail unexpected for %s",uType.c_str());
	    return 0;
    }
    ClassicOpaquePort * cop = new ClassicOpaquePort(uses);
    IO_dn1("ClassicServicesHelper::checkSupport using hp_pfp]");
    return cop;
  }
  if (uType == "gov.cca.ParameterPortFactoryService") {
    classic::gov::cca::Port* uses = dynamic_cast<classic::gov::cca::Port*>(hp->get_cpf());
    if (uses == 0) {
	    IO_en2("ClassicServicesHelper::checkSupport cast fail unexpected for %s",uType.c_str());
	    return 0;
    }
    ClassicOpaquePort * cop = new ClassicOpaquePort(uses);
    IO_dn1("ClassicServicesHelper::checkSupport using hp_cpf]");
    return cop;
  }

#ifdef _CCAMPI
  if (uType == "gov.cca.MPIService") {
    classic::gov::cca::Port* uses = dynamic_cast<classic::gov::cca::Port*>(hp->get_mpis());
    if (uses == 0) {
	    IO_en2("ClassicServicesHelper::checkSupport cast fail unexpected for %s",uType.c_str());
	    return 0;
    }
    ClassicOpaquePort * cop = new ClassicOpaquePort(uses);
    IO_dn1("ClassicServicesHelper::checkSupport using hp_mpis]");
    return cop;
  }
  if( uType == "gov.cca.MPIBorrow") {
    classic::gov::cca::Port* uses = dynamic_cast<classic::gov::cca::Port*>(hp->get_mpib());
    if (uses == 0) {
	    IO_en2("ClassicServicesHelper::checkSupport cast fail unexpected for %s",uType.c_str());
	    return 0;
    }
    ClassicOpaquePort * cop = new ClassicOpaquePort(uses);
    IO_dn1("ClassicServicesHelper::checkSupport using hp_mpib]");
    return cop;
  }
#endif // _CCAMPI

  IO_dn3("!No ClassicServicesHelper support for %s(%s).",uName.c_str(),uType.c_str());
  return 0;
}

#ifdef HAVE_NEO
#include "dc/neo/ccafe-bind/NeoOpaquePort.hh"
#endif // HAVE_NEO
classic::gov::cca::Port * 
ClassicServicesHelper::translate(const std::string name, ::ccafeopq::Port * op)
{

#ifdef HAVE_NEO
        NeoOpaquePort *nop = dynamic_cast< NeoOpaquePort * >(op);
        if (nop) {
                neo::cca::Port * np = nop->getNeoPort();
                if (np == 0) { // rather unexpected!
                        IO_en2("ClassicServicesHelper::translate getNeoPort %s failed.",name.c_str());
                        return 0;
                }
		classic::gov::cca::Port *cp = dynamic_cast< classic::gov::cca::Port * >(np);
                if (cp ==0) {
                        IO_en2("ClassicServicesHelper::translate cast to neo of %s failed unexpectedly.",name.c_str());
                }
                return cp;
        }
#endif // HAVE_NEO

        // other bindings?
        return 0;

}

#if 0
ClassicPortConverter_shared
ClassicServicesHelper::findConversion( ccafeopq::Port *op)
{
	IO_dn1("!ClassicServicesHelper::findConversion: make it go away!.");
	ClassicPortConverter_shared npc;

	// FIXME -- or don't. this requires dynamic_cast case testing
	// and we should just not do it. 
	// unfortunately, we need an event model to replace it.
	
	if (op == 0) {
#ifdef CCAFE_AUDIT
		IO_dn1("ClassicServicesHelper::convert called on null");
#endif
		return npc;
	}
	ccafeopq::ports::ParameterPort * opp =
		dynamic_cast< ccafeopq::ports::ParameterPort * >(op);
	if (opp != 0) {
		ClassicParameterPortPC *pppc = new ClassicParameterPortPC();
		ClassicPortConverter_shared pppc_ptr(pppc);
		return pppc_ptr;
	}

	ccafeopq::ports::BasicParameterPort * obpp =
		dynamic_cast< ccafeopq::ports::BasicParameterPort * >(op);
	if (obpp != 0) {
		ClassicBasicParameterPortPC *bpppc = new ClassicBasicParameterPortPC();
		ClassicPortConverter_shared bpppc_ptr(bpppc);
		return bpppc_ptr;
	}

	return npc; 
}
#endif

std::string 
ClassicServicesHelper::registerForConversionType(ccafeopq::ComponentID_shared me, std::string portName, std::string portType, std::map< std::string, ClassicPortConverter_shared > & portConversions)
{
#define WHINGE \
IO_dn4("ClassicServicesHelper::registerForConversionType: %s --> %s at %d", \
portType.c_str(), ntype.c_str(), __LINE__)

	string ntype = portType;
	IO_dn3("Entering ClassicServicesHelper::registerForConversionType: %s at %d", portType.c_str(),  __LINE__);
	// check goport alii
	if (portType == "classic::gov::cca::GoPort" ||
		portType == "::classic::gov::cca::GoPort" ||
		portType == "GoPort" ||
		portType == "gov.cca.GoPort" ||
		portType == "classic.gov.cca.GoPort")
       	{
		ntype = "::ccafeopq::GoPort";
		ClassicGoPortPC *gppc = new ClassicGoPortPC();
		ClassicPortConverter_shared gppc_ptr(gppc);
		portConversions[portName] = gppc_ptr;
		WHINGE;
	}

#if 0
	// check builderservice alii
	if (portType == "classic::gov::cca::ports::BuilderService" ||
		portType == "::classic::gov::cca::ports::BuilderService" ||
		portType == "classic.gov.cca.ports.BuilderService")
       	{
		ntype = "::ccafeopq::BuilderService";
		ClassicBuilderServicePC *bspc = new ClassicBuilderServicePC();
		ClassicPortConverter_shared bspc_ptr(bspc);
		portConversions[portName] = bspc_ptr;
		WHINGE;
	}

	// check parameter port alii
	if (portType == "classic.gov.cca.ports.ParameterPort" ||
		portType == "classic::gov::cca::ports::ParameterPort" ||
		portType == "::classic::gov::cca::ports::ParameterPort")
       	{
		ntype = "::ccafeopq::ports::ParameterPort";
		ClassicParameterPortPC *pppc = new ClassicParameterPortPC();
		ClassicPortConverter_shared pppc_ptr(pppc);
		portConversions[portName] = pppc_ptr;
		WHINGE;
	}

	// check parameter portfactory alii
	if (portType == "classic.gov.cca.ports.ParameterPortFactory" ||
		portType == "classic::gov::cca::ports::ParameterPortFactory" ||
		portType == "::classic::gov::cca::ports::ParameterPortFactory")
       	{
		ntype = "::ccafeopq::ports::ParameterPortFactory";
		ClassicParameterPortFactoryPC *ppfpc = new ClassicParameterPortFactoryPC();
		ClassicPortConverter_shared ppfpc_ptr(ppfpc);
		portConversions[portName] = ppfpc_ptr;
		WHINGE;
	}

	// check basic parameter port alii
	if (portType == "classic.gov.cca.ports.BasicParameterPort" ||
		portType == "classic::gov::cca::ports::BasicParameterPort" ||
		portType == "::classic::gov::cca::ports::BasicParameterPort")
       	{
		ntype = "::ccafeopq::ports::BasicParameterPort";
		ClassicBasicParameterPortPC *bpppc = new ClassicBasicParameterPortPC();
		ClassicPortConverter_shared bpppc_ptr(bpppc);
		portConversions[portName] = bpppc_ptr;
		WHINGE;
	}

	// check serviceregistry port alii
	if (portType == "classic.gov.cca.ports.ServiceRegistry" ||
		portType == "classic::gov::cca::ports::ServiceRegistry" ||
		portType == "::classic::gov::cca::ports::ServiceRegistry")
       	{
		ntype = "::ccafeopq::ServiceRegistry";
		ClassicServiceRegistryPC *srpc = new ClassicServiceRegistryPC(me);
		ClassicPortConverter_shared srpc_ptr(srpc);
		portConversions[portName] = srpc_ptr;
		WHINGE;
	}

	// check loader port alii
	if (portType == "classic.gov.cca.ports.Loader" ||
		portType == "classic::gov::cca::ports::Loader" ||
		portType == "::classic::gov::cca::ports::Loader")
       	{
		ntype = "::ccafeopq::Loader";
		ClassicLoaderPC *lpc = new ClassicLoaderPC();
		ClassicPortConverter_shared lpc_ptr(lpc);
		portConversions[portName] = lpc_ptr;
		WHINGE;
	}
#endif

	return ntype;
#undef WHINGE
}

void 
ClassicServicesHelper::checkthrow(const char * className, const char * memberName, void * member, const char *funcName)
{
	if (! member ) {
		std::string mess = className;
		mess += " ";
		mess += memberName;
		mess += " uninit in ";
		mess += funcName;
		std::cout << mess << std::endl;
		exit(1);
	}
}

#if 0

::ccafeopq::Port * 
ClassicServicesHelper::createSpecialProvider( classic::gov::cca::Port * inPort, const std::string & name, const std::string & type, ccafeopq::TypeMap_shared portProperties, std::string & supportedType)
{
	// assume input is good, as it comes from ClassicServices.
	supportedType = type; //may want to morph this sometimes?
	ccafeopq::Port * wrapper = 0;

#define WHINE_TYPE_MISMATCH(t, ct) else IO_en3("You seem to have classified a non-%s as a %s by mistake.", ct.c_str(), type.c_str())

	// The rules are: check for string matches, then check for cast.
	// Switching based on dynamic cast will give wrong result for
	// components that implement multiple ports by inheritance.

//// GO PORT section //////////////////////////////////////
	if (
		type == "::classic::gov::cca::ports::GoPort" ||
		type == "classic.gov.cca.ports.GoPort" ||
		type == "classic::gov::cca::ports::GoPort"||
		type == "gov.cca.ports.GoPort" ||
		type == "GoPort" ||
		type == "gov.cca.GoPort"
	) 
	{
		supportedType = "::ccafeopq::GoPort";
		IO_dn3("Adding an apparent GoPort of type: %s and named: %s",
			 type.c_str(), name.c_str());

		classic::gov::cca::ports::GoPort * gp =
			dynamic_cast< classic::gov::cca::ports::GoPort* >(inPort);
		if (gp) {
			ClassicOpaqueGoPort * cop = new ClassicOpaqueGoPort(gp);
			wrapper = cop;
			return wrapper;
		} 
		WHINE_TYPE_MISMATCH(type, supportedType);
	}

//// ComponentFactory section //////////////////////////////////////
	if (
		type == "::classic::gov::cca::ports::ComponentFactory" ||
		type == "classic::gov::cca::ports::ComponentFactory" ||
		type == "classic.gov.cca.ports.ComponentFactory" ||
		type == "ComponentFactory" 
	)
	{
		supportedType = "::ccafeopq::ComponentFactory";
		IO_dn3("Adding an apparent Factory of type: %s and named: %s",
			 type.c_str(), name.c_str());

		classic::gov::cca::ports::ComponentFactory * cf =
			dynamic_cast< classic::gov::cca::ports::ComponentFactory * >(inPort);
		if (cf) {
			ClassicOpaqueComponentFactory * cop = new ClassicOpaqueComponentFactory(cf);
			wrapper = cop;
			return wrapper;
		} 
		WHINE_TYPE_MISMATCH(type, supportedType);
	}
	return 0;
	
#undef WHINE_TYPE_MISMATCH
}

#endif

