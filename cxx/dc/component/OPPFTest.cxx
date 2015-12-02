/**
For testing purposes only. Do NOT copy the code
used to implement this class -- it depends on internal
framework interfaces that are highly subject to change
and will NOT be supported in future versions.

REPEAT:
Don't do anything like this component when writing
your own. This service (PPF) is not yet ported to 
classic space.
*/
//
// ABANDON ALL HOPE, YE WHO ENTER HERE
//
#include <cca.h>
#include <stdPorts.h>
#include <ports/StringConsumerPort.h>
#include "dc/framework/Check.h"
#include "dc/export/AllExport.hh"
#include "dc/classic/ccafe-bind/AllCcafeBind.hh"
#include "dc/component/OPPFTest.h"

#ifndef lint
namespace {
char id[] =
"$Id: OPPFTest.cxx,v 1.4 2007/10/17 17:19:33 baallan Exp $";
} ENDSEMI
#endif

using std::string;

OPPFTest::OPPFTest(){ 
myCore = 0; numtests = 0;
	std::cout << "OPPFTEST:  CTOR" << std::endl;
}

OPPFTest::~OPPFTest(){
myCore = 0;
	std::cout << "OPPFTEST:  DTOR" << std::endl;
}

void OPPFTest::setServices(classic::gov::cca::Services *cc) {
	std::cout << "OPPFTEST:  SET_SERVICES" << std::endl;
	if (myCore != 0 && cc == 0) {
		std::cout << "OPPFTEST:  shutdown"  << std::endl;
		myCore = cc;
		::classic::gov::cca::Port * port;
		port = myCore->getPort("ppf");
		if (port != 0) {
			std::cout << "OPPFTEST: ppf fetched in setservices. " << std::endl;
			ppf = dynamic_cast< ::ccafeopq::ports::ParameterPortFactory *>(port);
			if (!ppf == 0) {
				ClassicServices * cs = dynamic_cast<ClassicServices *>(myCore);
				::ccafeopq::Services * os = 0;
				os = cs->unwrapServices();
				for (size_t i = 0; i < pplist.size(); i++)
				{
					::ccafeopq::TypeMap_shared tm = pplist[i];
					ppf->removeParameterPort(tm, os);
				}
			}
			myCore->releasePort("ppf");
		} else {
			std::cout << "OPPFTEST: ppf fetch failed in setServices. " << std::endl;
		}
		myCore->unregisterUsesPort("ppf");
		myCore->removeProvidesPort("go");
		myCore = 0;
		return;
	}
	if (myCore != 0 && cc != 0)
	{
		return; // fwk is hosed. ignore it.
		std::cout << "OPPFTEST: setservices !=0 twice. " << std::endl;
	}

	std::cout << "OPPFTEST:  startup"  << std::endl;
  myCore = cc;

  // Contact the PrintfService
  classic::gov::cca::PortInfo* pinfo = myCore->createPortInfo("pSvc", "gov.cca.JPrintfService", 0);
  myCore->registerUsesPort(pinfo);
  pinfo = 0;
  ::classic::gov::cca::Port * np;
  np = myCore->getPort("pSvc");
  pfp = dynamic_cast< classic::gov::cca::JPrintfPort * >(np);
  CHECKDC(pfp);
  if (pfp == 0) {
    classic::gov::cca::PortInfo* dpinfo = myCore->createPortInfo("DEAD=NoJPrintf", "classic::gov::cca::GoPort", 0);
    myCore->addProvidesPort(this, dpinfo);
    ::printf("!!! No JPrintfService available from framework.");
    dpinfo = 0;
    return;
  }

  pinfo = myCore->createPortInfo("ppf", "::ccafeopq::ports::ParameterPortFactory",0);
  myCore->registerUsesPort(pinfo);
  pinfo = 0;

  pinfo = myCore->createPortInfo("go", "::classic::gov::cca::GoPort",0);
  myCore->addProvidesPort(this, pinfo);
  pinfo = 0;
	std::cout << "OPPFTEST:  startup done"  << std::endl;
}

int OPPFTest::go()
{
  char buf[40];
  numtests++;
  sprintf(buf,"%d",numtests);
  classic::gov::cca::Port * port= 0;

  ClassicServices * cs = dynamic_cast< ClassicServices * >(myCore);
  ::ccafeopq::Services * os = 0;
  os = cs->unwrapServices();

  ::ccafeopq::TypeMap_shared tm = os->createTypeMap();

  pplist.push_back(tm);
  std::string pname = "PP_";
  pname += buf;


  std::cout << "OPPFTEST:  getting ppf." << std::endl;
  port = myCore->getPort("ppf");
  if (port == 0) {
	   return -1;
  }
  std::cout << "OPPFTEST:  got ppf." << std::endl;
  ppf = dynamic_cast< ::ccafeopq::ports::ParameterPortFactory *>(port);
  ppf->createParameterPort(tm, pname);

  ::std::string title = "Test PPF for port ";
  title += pname;
  ppf->setBatchTitle(tm, title);
  ppf->addRequestBoolean(tm,"noName","var to test if default group gets used","anon group",true);
  ppf->setGroupName(tm,"Named Set1");
  ppf->addRequestInt(tm,"iVar","a ranged test integer","int test", 5, 0 ,10);
  ppf->addRequestLong(tm,"jVar","a deranged test long","long test", -50, 0 , -100);
  ppf->setGroupName(tm,"Named Set2");
  ppf->setGroupNameAndTitle(tm,"Named Set2","Pretty title");
  ppf->addRequestDouble(tm,"dVar","a ranged test double","double test", -50, 0 , -100);
  ppf->addRequestFloat(tm,"fVar","a ranged test float","float test", 50, -1000 , 1000);
  ppf->setGroupName(tm,"Named Set3");
  ppf->addRequestString(tm,"sVar","a free test string","string any test", "some value");
  ppf->addRequestString(tm,"sList","a choice test string","string list test", "some value");
  ppf->addRequestStringChoice(tm,"sList","choice 1");
  ppf->addRequestStringChoice(tm,"sList","choice 3");
  ppf->addRequestStringChoice(tm,"sList","choice 2");
  std::vector< std::string > moreStrings;
  moreStrings.push_back("fred");
  moreStrings.push_back("barney");
  ppf->addStringChoices(tm,"sList", moreStrings);
  int itest[3] = { 3, 5, 7 };
  ppf->addRequestInt(tm,"icVar","a choiced test integer","int-choice test", 5, 5 ,5);
  ppf->addIntChoices(tm,"icVar", itest, 3);
  
  
  ppf->addParameterPort(tm, os);
  std::cout << "OPPFTEST:  configured tm." << std::endl;
// FIXME enable this
#if 0
  // cycle through a remove just in case we don't get through
  // a destructor protocol due to bugs elsewhere.
  ppf->removeParameterPort(tm, os);
  ppf->addParameterPort(tm, os);
#endif
  ppf = 0;

  myCore->releasePort("ppf");
  ccafeopq::ports::ParameterPort *pp;
  ccafeopq::Port *op = 0;
  classic::gov::cca::Port * cpp = 0;
  cpp = myCore->getPort(pname.c_str());
  if (cpp == 0) {
    std::cout << "OPPFTEST: getport(" << pname << ") failed." << std::endl;
  }
  pp = dynamic_cast< ccafeopq::ports::ParameterPort *>(cpp);
  if (pp == 0) {
    pfp->en("OPPFTest trying opq pp because classic cast failed.");
    ccafeopq::ExceptionType status = ccafeopq::Correct;
    op = os->getPort(pname,status);
    if (op == 0) {
       pfp->en("OPPFTest opq pp get failed.");
       return 0;
    }
    ccafeopq::ports::ParameterPort *pp = 
      dynamic_cast< ccafeopq::ports::ParameterPort*>(op);
    if (pp == 0) {
      pfp->en("OPPFTest opq pp cast failed.");
      os->releasePort(pname.c_str());
    }
    ccafeopq::TypeMap_shared ptm = pp->readConfigurationMap();
    std::string svar = ptm->getString("sVar","failed svar fetch");
    std::cout << "OPPFTEST:  sVar = " << svar << std::endl;
    os->releasePort(pname.c_str());
  } else {
    pfp->en("OPPFTest got classicopq pp");
    ccafeopq::TypeMap_shared ptm2 = pp->readConfigurationMap();
    myCore->releasePort(pname.c_str());
    std::string svar2 = ptm2->getString("sVar","failed svar fetch");
    std::cout << "OPPFTEST:  sVar = " << svar2 << std::endl;
  }
  
  return 0;
}


