#include <vector>
#include <string>

#include "dc/export/AllExport.hh"

#define CmdLineCommonInternal_dependent
#include "dc/user_iface/CmdLineCommonInternal.h"
#include <string.h> // strncmp

#include "util/TypeMap.h"

#include <vector>
#include <string>

#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "parameters/parametersStar.h"

#include "dc/framework/dc_fwkPublic.h"
#include "port/portInterfaces.h"

#include "dc/user_iface/BuilderModel.h"
#include "dc/user_iface/DefaultBuilderModel.h"

#include "util/IO.h"
#include "util/freefree.h"
#include "dc/user_iface/CmdLineBuilderViewForGUI.h"

#ifndef lint
static char id[]=
"$Id: CmdLineBuilderViewForGUI.cxx,v 1.30 2005/11/16 03:21:28 baallan Exp $";
#endif

/** Everything in this puppy has to do things exactly as the Java
    class does or Colin's GUI won't work. */


CmdLineBuilderViewForGUI::CmdLineBuilderViewForGUI() {
  promptString = 
      "\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n";
  setOutputStream(stdout);  // may not make much sense.
  bm = 0;
}

CmdLineBuilderViewForGUI::~CmdLineBuilderViewForGUI() {
}

/**  Implements ComponentChangedListener.  Signal a change in the
       Component's status. */
void CmdLineBuilderViewForGUI::componentChanged(ComponentChangedEvent* evt) {
  if(out != 0) {
    fprintf(out, "revalidate %s\n", evt->getComponentInstance());
  }
}


void CmdLineBuilderViewForGUI::setOutputStream(FILE* out) {
  this->out = out;
}

void CmdLineBuilderViewForGUI::setBuilderModel(BuilderModel* bm) {
  this->bm = bm;
  (this->bm)->addComponentChangedListener(this);
}

void CmdLineBuilderViewForGUI::displayPallet() {
  std::vector< std::string > pal = bm->getPallet();
  for(int i = 0;i < (int)pal.size();i++) {
    p("addClass ");
    pn(pal[i]);
  }
}

void CmdLineBuilderViewForGUI::displayInstantiatedComponents() {
  if(bm == 0) {
    pn("!no instantiated builder");
    return;
  }
  ::std::map< ::std::string, ComponentInfo_shared > arena = bm->getArena();
  ::std::map< ::std::string, ComponentInfo_shared >::iterator pos;
  ::std::string sb = "\n";
  bool shown = false;
  for (pos = arena.begin(); pos != arena.end(); pos++) {
    ComponentInfo_shared ci = pos->second;
    if (ci == 0) {
      pn("!corrupted arena!!");
        assert(ci!=0);
      exit(1);
    }
    sb += "instantiate ";
    sb += ci->getClassName();
    sb += " ";
    sb += ci->getInstanceName();
    sb += "\n";
    shown = true;
  }
  
  if (shown) {
    pn(sb);
  } else {
    pn("!no instantiated components available");
  }
}

void CmdLineBuilderViewForGUI::displayComponentInfo(const char* instanceName)
{
  ::std::map< ::std::string, ComponentInfo_shared  > arena = bm->getArena();
  ::std::map< ::std::string, ComponentInfo_shared  >::iterator pos;
  size_t i;
  pos = arena.find(instanceName);
  if (pos == arena.end()) {
    return; // fixme should whine.
  }
  ComponentInfo_shared ci = pos->second;

  if ( ci == 0) {
    pn("!corrupted arena!!");
    assert(ci!=0);
    exit(1);
  }

  ::std::string sb = "addProvidesPorts ";;
  const ::std::vector< ProviderPortData > pi = ci->getProvidesPorts();
  sb += instanceName;
  sb += " ";
  if(pi.size() != 0) {
    for(i = 0;i < pi.size(); i++) {
        sb += pi[i].getPortName();
        sb += " ";
        sb += pi[i].getPortType();
        sb += " ";
    }
  }
  pn(sb);

  ::std::vector< UserPortData > upi = ci->getUsesPortRegister();
  sb = "addUsesPorts ";
  sb += instanceName;
  sb += " ";
  if(upi.size() != 0) {
    for(i = 0; i < upi.size(); i++) {
        sb += upi[i].getPortName();
        sb += " ";
        sb += upi[i].getPortType();
        sb += " ";
    }
  }
  pn(sb);
  // Properties display
  ::ccafeopq::TypeMap_shared tm = ci->getComponentPropertyTypeMap();
  std::vector< std::string > keys = tm->getAllKeys(::ccafeopq::String);
  for(size_t i = 0;i < keys.size();i++) {
    std::string key = keys[i];
    std::string value = tm->getString(key,"");
    p("property ");
    p(instanceName);
    p(" ");
    p(key);
    p(" ");
    p(value);
    pn("");
  }  
  for(size_t i = 0; i < pi.size();i++) {
    std::string portname = pi[i].getPortName();
    tm = ci->getPortPropertyTypeMap(portname);
    displayPortProperties(instanceName, portname, tm, "");
  }
  for(size_t i = 0; i < upi.size();i++) {
    std::string portname = upi[i].getPortName();
    tm = ci->getPortPropertyTypeMap(portname);
    displayPortProperties(instanceName, portname, tm, "");
  }
}

void CmdLineBuilderViewForGUI::connect(const char* fromInstance, const char* providesInstance, const char* toInstance, const char* usesInstance) {
  p("connect ");
  p(toInstance);
  p(" ");
  p(usesInstance);
  p(" ");
  p(fromInstance);
  p(" ");
  pn(providesInstance);
}

void CmdLineBuilderViewForGUI::disconnect(const char* fromInstance,const  char* providesInstance,const  char* toInstance,const  char* usesInstance) {
  p("disconnect ");
  p(toInstance);
  p(" ");
  p(usesInstance);
  p(" ");
  p(fromInstance);
  p(" ");
  pn(providesInstance);
}

void CmdLineBuilderViewForGUI::pullDownComponent(const char* className, const char* instanceName) {
  p("pulldown ");
  p(className);
  p(" ");
  p(instanceName);
//   std::vector< std::string > prop = bm->getComponentProperties(instanceName);
//   if(prop.size() >= 2) { // There are some properties
//     std::string sb = prop[0];
//     if(prop.size() % 2) {
//       IO_en(2, ":-( numberof properties should be even, actual number is: %d"
// 	    " doing nothing ...", prop.size());
//     }
//     for(int i = 1;i < prop.size();i++) {
//       sb += "_";
//       sb += prop[i];
//     }
//     p(sb);
//   }
  pn("");
}

void CmdLineBuilderViewForGUI::displayDisconnectionFailed(const char *msg) {
  error("CmdLineBuilderViewForGUI::displayDisconnectionFailed: Disconnection unsuccessful.");
  error(msg);
}

void CmdLineBuilderViewForGUI::displayConnectionFailed(const char *msg) {
  error("CmdLineBuilderViewForGUI::displayConnectionFailed: Connection unsuccessful.");
  error(msg);
}

void CmdLineBuilderViewForGUI::displayChain() {
  if(bm == 0) {
    pn("!no instances available");
    return;
  }

  ::std::map< ::std::string, ComponentInfo_shared > arena = bm->getArena();
  ::std::map< ::std::string, ComponentInfo_shared >::iterator pos;


  for (pos = arena.begin(); pos != arena.end(); pos++) {
    ComponentInfo_shared ci = pos->second;
    displayChain(ci);
  }
}

/** Only displays the Uses connections for the given Link */
void CmdLineBuilderViewForGUI::displayChain(ComponentInfo_shared ci) {
  ::std::vector< ConnectionID_ptr > conns = ci->getUsesConnections();
  for (size_t i=0; i < conns.size(); i++) {
    ::std::string sb = "connect ";
    ConnectionID_ptr c = conns[i];
    if(!c->isFrameworkConnection()) {
      sb += c->getUser()->getInstanceName();
      sb += " ";
      sb += c->getUserPortName();
      sb += " ";
      sb += c->getProvider()->getInstanceName();
      sb += " ";
      sb += c->getProviderPortName();
      
      pn(sb);
    }
  }
}

void CmdLineBuilderViewForGUI::error(const std::string msg) {
	error(msg.c_str());
}

void CmdLineBuilderViewForGUI::error(const char* msg) {
	(void)msg;
  // Per Ben's suggestion: this does nothing.
  // the gui probably can't cope with us dying.
} 

void CmdLineBuilderViewForGUI::errorFatal(const char * msg) {
	(void)msg;
  // Per Ben's suggestion: this does nothing.
  // the gui probably can't cope with us dying.
}

void CmdLineBuilderViewForGUI::pn( const std::string & s) {
  fprintf(out,"%s\n",s.c_str());
  fflush(out);
}

void CmdLineBuilderViewForGUI::p( const std::string & s) {
  if(strncmp(s.c_str(), "\ncca>", 5) == 0) {
    return;
  }
  fprintf(out,"%s",s.c_str());
  fflush(out);
}

void CmdLineBuilderViewForGUI::pn(const char* s) {
  fprintf(out,"%s\n",s);
  fflush(out);
}

void CmdLineBuilderViewForGUI::p(const char* s) {
  if(strncmp(s, "\ncca>", 5) == 0) {
    return;
  }
  fprintf(out,"%s",s);
  fflush(out);
}

void CmdLineBuilderViewForGUI::pn(const char c) {
  fputc(c,out);
  fputc('\n',out);
  fflush(out);
}

void CmdLineBuilderViewForGUI::p(const char c) {
  fputc(c,out);
  fflush(out);
}

void CmdLineBuilderViewForGUI::displayConfiguration(const char * instanceName, const char * portName, const char * data) {
	(void)portName;
	(void)instanceName;
  pn(data);
};

void CmdLineBuilderViewForGUI::setConfiguration(const char * instanceName, const char * portName, const char * fieldName, const char * data) {
	(void)portName;
	(void)instanceName;
	(void)data;
	(void)fieldName;
}

void CmdLineBuilderViewForGUI::displayComponentProperties(const char * instanceName, std::vector< std::string > & props)
{
  if (instanceName == 0) { return; }
  int r = props.size();
  for (int i=0; i < r; i+=2) {
    std::string key = props[i];
    std::string value = props[i+1];
    p("setProperty ");
    p(instanceName);
    p(" ");
    p(key);
    p(" ");
    pn(value);
  }
}

void CmdLineBuilderViewForGUI::displayComponentProperty(const char * instanceName, const char * key, const char * value) {
  if (value != NULL) {
    p("ComponentProperty ");
    p(instanceName);
    p(" ");
    p(key);
    p(" ");
    pn(value);
  }
}

void CmdLineBuilderViewForGUI::setComponentProperty(const char * instanceName, const char * key, const char * value, int err) {
  if (err != 0) {
    return;
  }
  p("SetComponentProperty ");
  p(instanceName);
  p(" ");
  p(key);
  p(" ");
  pn(value);

}

void CmdLineBuilderViewForGUI::displayPortProperties(const std::string & iname, const std::string & pname, ::ccafeopq::TypeMap_shared t, const std::string & key)
{
	if (!(!t) && key.size() != 0 ) {
		p("PortProperty ");
		p(iname);
		p(" ");
		p(pname);
		p(" ");
		p(key);
		const std::string & stype = ::gov::sandia::util::TypeMap::stringType(t, key);
		p(" ");
		p(stype);
		const std::string & sval = ::gov::sandia::util::TypeMap::stringValue(t, key);
		p(" ");
		pn(sval);
	}
	if (!(!t) && key.size() == 0 ) {
		std::vector<std::string> keys = t->getAllKeys(::ccafeopq::NoType);
		for (size_t i = 0 ; i < keys.size(); i++)
	  	{
			p("PortProperty ");
			p(iname);
			p(" ");
			p(pname);
			p(" ");
			p(keys[i]);
			const std::string & stype = ::gov::sandia::util::TypeMap::stringType(t, keys[i]);
			p(" ");
			p(stype);
			const std::string & sval = ::gov::sandia::util::TypeMap::stringValue(t, keys[i]);
			p(" ");
			pn(sval);
	  	}
	}
}

void CmdLineBuilderViewForGUI::setPortProperty(const std::string & iName, const std::string & pName, const std::string & key, const std::string & stype, const std::string & sval, int err)
{
  if (err != 0) {
    return ;
  }
  p("setPortProperty ");
  p(iName);
  p(" ");
  p(pName);
  p(" ");
  p(key);
  p(" ");
  p(stype);
  p(" ");
  pn(sval);
}

