
#include <cca.h>
#include <stdPorts.h>
#include <ports/StringConsumerPort.h>
#include <ports/TimeProducerPort.h>
#include "dc/framework/Check.h"
#include "parameters/parametersStar.h"
#include "port/portInterfaces.h"
#include "port/supportInterfaces.h"
#include "dc/component/RevalidateTest.h"
#include <cstring>
#ifndef lint
namespace {
char id[]= 
"$Id: RevalidateTest.cxx,v 1.21 2008/12/24 19:38:41 baallan Exp $";
} ENDSEMI
#endif
		   
void RevalidateTest::setupParameters(ConfigurableParameterFactory *cpf){
  pp = cpf->createConfigurableParameterPort();
  ParameterGetListener *pgl;
  pgl = dynamic_cast<ParameterGetListener *>(this);
  pp->setUpdater(pgl);
  pp->setBatchTitle("Time Stamper Configuration");
  pp->setGroupName("Time Zone");
  pp->addRequest(prefix);
  pp->addRequest(commie);
  pp->setGroupName("idiot page");
  pp->addRequest(dtest);
  pp->addRequest(anything);
}

RevalidateTest::RevalidateTest(){
  pfp = 0;
  prefix = new StringParameter("prefix",
    "The time stamper suffixes time strings with the zone","US zones","PST");
  commie = new BoolParameter("commie","pointless checkbutton test","Upload spy report",false);
  utest = new BoolParameter("utest","this tests the updateParameterPort","update called successfully",true);
  dtest = new DoubleParameter("dtest","pointless double test","double value",-5.0,-100.0,100.0);
  anything = new StringParameter("anything","allow any input","free form string","hi there!");

  prefix->addChoice("PST");
  prefix->addChoice("MST");
  prefix->addChoice("CST");
  prefix->addChoice("EST");

  utestdone = false;

  alreadyRemoved = false;
  eSvc = 0;
}

RevalidateTest::~RevalidateTest(){
  delete pp; 
  pp = 0;
  delete prefix;
  prefix = 0;
  pfp = 0;
  core = 0;
}

/** Implements ConnectionEventListener for the
    ConnectionEventService. If either of the StringConsumer Ports are
    connected the configure port will disappear. */
void RevalidateTest::connectionActivity(classic::gov::cca::ConnectionEvent* evt) {
  if(alreadyRemoved) {
    return;
  }
  classic::gov::cca::PortInfo* pi = evt->getPortInfo();
  if(strcmp(pi->getName(), "out0") == 0) {
    core->removeProvidesPort("configure_port");
    core->unregisterUsesPort("mangle");
    alreadyRemoved = true;
  }
  if(strcmp(pi->getName(), "in_port") == 0) {
    core->removeProvidesPort("configure_port");
    core->unregisterUsesPort("mangle");
    alreadyRemoved = true;
  }
}


bool RevalidateTest::updateParameterPort(ConfigurableParameterPort *opp)  {
  if (!(pp == opp)) {
    return false;
  }
  if (!utestdone) {
    pp->addRequest(utest);
    utestdone = true;
    return true;
  }
  return false;
}

void RevalidateTest::setServices(classic::gov::cca::Services *cc){
  if(!cc) {
    return;
  }
  core = cc;

  // Contact the PrintfService
  classic::gov::cca::PortInfo* pinfo = cc->createPortInfo("pSvc", "gov.cca.JPrintfService", 0);
  cc->registerUsesPort(pinfo);
  pfp = dynamic_cast<classic::gov::cca::JPrintfPort*>(cc->getPort("pSvc"));
  CHECKDC(pfp);
  if(pfp == 0) {
    cc->addProvidesPort(this, cc->createPortInfo("DEAD=NoJPrintf", "Port", 0));
    printf("!!! No JPrintfService available from framework.");
    return;
  }

  // Contact the ParameterPortFactoryService
  pinfo = core->createPortInfo("cSvc", "gov.cca.ParameterPortFactoryService", 0);
  core->registerUsesPort(pinfo);
  ConfigurableParameterFactory *cpf =
    dynamic_cast<ConfigurableParameterFactory*>(core->getPort("cSvc"));
  CHECKDC(cpf);
  if(cpf == 0) {
    core->addProvidesPort(this, core->createPortInfo("DEAD=NoParamService", "Port", 0));
    pfp->en("!!! RevalidateTest dead. Framework supplies no ParameterPortFactoryService");
    return;
  }
  setupParameters(cpf);
  core->releasePort("cSvc");
  core->unregisterUsesPort("cSvc");


  // Contact the ConnectionEventService
  classic::gov::cca::PortInfo* info = core->createPortInfo("eSvc", "gov.cca.ConnectionEventService", 0);
  core->registerUsesPort(info);
  eSvc = dynamic_cast<classic::gov::cca::ConnectionEventService*>(core->getPort("eSvc"));
  CHECKDC(eSvc);
  if(eSvc == 0) {
    pfp->en("No ConnectionEventService available");
    return;
  }

  core->addProvidesPort(this, 
    core->createPortInfo("in_port", "StringConsumerPort", 0 ));

  core->addProvidesPort(pp, 
    core->createPortInfo("configure_port", "ParameterPort", 0));


  core->registerUsesPort(core->createPortInfo("out0", "StringConsumerPort", 0));

  core->registerUsesPort(core->createPortInfo("mangle", "Parameter", 0));

  core->registerUsesPort(core->createPortInfo("time0", "TimeProducerUsesPort", 0));

  eSvc->addConnectEventListener(this);
}

void RevalidateTest::setString(const char* s){

  classic::gov::cca::StringConsumerPort* output = 
    dynamic_cast<classic::gov::cca::StringConsumerPort*> (core->getPort("out0"));
  CHECKDC(output);


  classic::gov::cca::TimeProducerPort* timer = 
    dynamic_cast <classic::gov::cca::TimeProducerPort*> (core->getPort("time0"));
  CHECKDC(timer);


  char* t = timer->getTime();

  std::string sb = s;
  char valstring[40];
  sb += "@";
  sb += t;
  sb += "--";
  sb += prefix->value;
  sb += "--";
  sb += commie->value;
  sb += "--";
  sprintf(valstring,"%23.19g",dtest->value);
  sb += valstring;
  sb += "--";
  sb += anything->value;

  output->setString(sb.c_str());
  core->releasePort("out0");
  core->releasePort("time0");
}
