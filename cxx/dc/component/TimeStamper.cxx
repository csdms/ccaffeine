#include <stdio.h>
#include <cca.h>
#include <ports/StringConsumerPort.h>
#include <ports/TimeProducerPort.h>
#include "parameters/parametersStar.h"
#include "port/portInterfaces.h"
#include "port/supportInterfaces.h"
#include "dc/component/TimeStamper.h"
#include <string>
#include <iostream>
#include "dc/framework/Check.h"
		   
#ifndef lint
namespace {
char id[] = 
"$Id: TimeStamper.cxx,v 1.19 2003/10/07 08:04:17 baallan Exp $";
} ENDSEMI
#endif

void TimeStamper::setupParameters(ConfigurableParameterFactory *cpf){
  pp = cpf->createConfigurableParameterPort();
  ParameterGetListener *pgl;
  pgl = dynamic_cast<ParameterGetListener *>(this);
  pp->setUpdater(pgl);
  prefix = new StringParameter("prefix",
    "The time stamper suffixes time strings with the zone","US zones","PST");
  commie = new BoolParameter("commie","pointless checkbutton test","Upload Starr report",false);
  utest = new BoolParameter("utest","this tests the updateParameterPort","update called successfully",true);
  dtest = new DoubleParameter("dtest","pointless double test","double value",-5.0,-100.0,100.0);
  anything = new StringParameter("anything","allow any input","free form string","hi there!");

  prefix->addChoice("PST");
  prefix->addChoice("MST");
  prefix->addChoice("CST");
  prefix->addChoice("EST");

  pp->setBatchTitle("Time Stamper Configuration");
  pp->setGroupName("Time Zone");
  pp->addRequest(prefix);
  pp->addRequest(commie);
  pp->setGroupName("idiot page");
  pp->addRequest(dtest);
  pp->addRequest(anything);
}

TimeStamper::TimeStamper(){
  utestdone = false;
}

TimeStamper::~TimeStamper() {
  delete pp; 
  pp = 0;
  delete prefix;
  prefix = 0;
}

bool TimeStamper::updateParameterPort(ConfigurableParameterPort *opp)  {
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

void TimeStamper::setServices(classic::gov::cca::Services *cc){
  if(!cc) {
    return;
  }
  core = cc;

  // Contact the ParameterPortFactoryService
  classic::gov::cca::PortInfo* pinfo = core->createPortInfo("cSvc", "gov.cca.ParameterPortFactoryService", 0);
  core->registerUsesPort(pinfo);
	::classic::gov::cca::Port *rp = core->getPort("cSvc");
  if(rp == 0) {
    core->addProvidesPort(this, core->createPortInfo("DEAD=NoParamService", "Port", 0));
    return;
  }
  ConfigurableParameterFactory *cpf = 
    dynamic_cast<ConfigurableParameterFactory *>(rp);
  if(cpf == 0) {
    core->addProvidesPort(this, core->createPortInfo("DEAD=NoParamService-cast", "Port", 0));
    return;
  }
  setupParameters(cpf);
  core->releasePort("cSvc");
  core->unregisterUsesPort("cSvc");

  core->addProvidesPort(this, 
    core->createPortInfo("in_port", "StringConsumerPort", 0 ));

  core->addProvidesPort(pp, 
    core->createPortInfo("configure_port", "ParameterPort", 0));


  core->registerUsesPort(core->createPortInfo("out0", "StringConsumerPort", 0));

  core->registerUsesPort(core->createPortInfo("time0", "TimeProducerPort", 0));
}


void TimeStamper::setString(const char* s){

  ::classic::gov::cca::Port *tp = 0;
  tp = core->getPort("out0");
  if (tp == 0) {
    std::cerr << "TimeStamper::setString port out0 not connected!" << std::endl;
    return;
  }
  classic::gov::cca::StringConsumerPort* output = 
    dynamic_cast<classic::gov::cca::StringConsumerPort*> (tp);
  CHECKDC(output);


  tp = core->getPort("time0");
  if (tp == 0) {
    std::cerr << "TimeStamper::setString port time0 not connected!" << std::endl;
    return;
  }
  classic::gov::cca::TimeProducerPort* timer = 
    dynamic_cast <classic::gov::cca::TimeProducerPort*> (tp);
  CHECKDC(timer);
  tp = 0;


  char* t = timer->getTime();
  char valstring[40];

  std::string sb = s;
  sb += "@";
  sb += t;
  sb += "--";
  sb += prefix->value;
  sb += "--";
  sb += commie->getValueString();
  sb += "--";
  sprintf(valstring,"%23.19g",dtest->value);
  sb += valstring;
  sb += "--";
  sb += anything->value;

  output->setString(sb.c_str());
  core->releasePort("out0");
  core->releasePort("time0");
}
