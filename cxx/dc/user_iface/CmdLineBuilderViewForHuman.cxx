#ifndef lint
static char id[]=
"$Id: CmdLineBuilderViewForHuman.cxx,v 1.25 2005/11/16 03:21:28 baallan Exp $";
#endif



#include <stdlib.h>

#include <vector>
#include <string>

#include "dc/export/AllExport.hh"

#define CmdLineCommonInternal_dependent
#include "dc/user_iface/CmdLineCommonInternal.h"
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"

#include "dc/user_iface/CmdLineBuilderViewForHuman.h"
#include "util/freefree.h"

#include "util/TypeMap.h"

CDELETE CmdLineBuilderViewForHuman::CmdLineBuilderViewForHuman() {
  out = IO::out();
}

CmdLineBuilderViewForHuman::~CmdLineBuilderViewForHuman() {
  out = NULL;
  bm = NULL;
}

/** Implements ComponentChangedListener.  Signal a change in the
      Component's status. */
void CmdLineBuilderViewForHuman::componentChanged(ComponentChangedEvent* evt) {
  if(out != 0) {
    fprintf(out, "revalidate \"%s\"\n", evt->getComponentInstance());
  }
}

void CmdLineBuilderViewForHuman::setOutputStream(FILE *out_) {
  out = out_;
}

void CmdLineBuilderViewForHuman::setBuilderModel(BuilderModel *bm_) {
  bm = bm_;
  bm->addComponentChangedListener(this);
}

void CmdLineBuilderViewForHuman::displayPallet() {


  if(bm == 0) {
    pn("!no pallet available");
    return;
  }

  std::vector< std::string > pal = bm->getPallet();
  pn("Components available:");
  for(int i = 0;i < (int)pal.size();i++) {
    pn(pal[i]);
  }

}

void CmdLineBuilderViewForHuman::displayInstantiatedComponents() {

  if (bm == 0) {
    pn("!No instantiated builder.");
    return;
  }
  ::std::map< ::std::string, ComponentInfo_shared > arena = bm->getArena();
  boolean shown = false;

  ::std::map< ::std::string, ComponentInfo_shared >::iterator pos;
  for ( pos = arena.begin(); pos != arena.end(); pos++) {
    ComponentInfo_shared ci = pos->second;
    if (ci == 0) {
      pn("!corrupted arena!!");
      assert(ci!=0);
      exit(1);
    }
    p(ci->getInstanceName());
    p(" of type ");
    pn(ci->getClassName());
    shown = true;
  }

  if (!shown) {
    pn("!no instantiated components available");
  }

}

void CmdLineBuilderViewForHuman::displayComponentInfo(const char *instanceName)
{

  ::std::map< ::std::string, ComponentInfo_shared > arena = bm->getArena();
  ::std::map< ::std::string, ComponentInfo_shared >::iterator pos;
  pos = arena.find(instanceName);
  if (pos == arena.end()) {
    pn("!displayComponentInfo component instance not found");
    return;
  }
  ComponentInfo_shared ci = arena[instanceName];
  if (ci == 0) {
    pn("!corrupted arena!!");
    assert(ci!=0);
    exit(1);
  }

  pn("------------------------------------");
  p("Instance name: ");
  pn(ci->getInstanceName());
  p("Class name: ");
  pn(ci->getClassName());

  pn("------------------------------------");
  p("UsesPorts registered for ");
  pn(ci->getInstanceName());
  pn("");
  ::std::vector< UserPortData > pi =
    ci->getUsesPortRegister();
  size_t i;
  if (pi.size() != 0) {
    char tmp[40];
    for(i = 0; i < pi.size(); i++) {
        sprintf(tmp,"%d. Instance Name: ",int(i));
        p(tmp); 
        p(pi[i].getPortName());
        p(" Class Name: ");
        pn(pi[i].getPortType());
    }
  } else {
    p("!No UsesPorts in ");
    pn(ci->getInstanceName());
  }

  pn("------------------------------------");
  p("ProvidesPorts registered for ");
  pn(ci->getInstanceName());
  pn("");
  const ::std::vector< ProviderPortData > ppi = ci->getProvidesPorts();
  if (ppi.size() != 0) {
    for(i = 0; i < ppi.size(); i++) {
      p("Instance Name: ");
      p(ppi[i].getPortName()); 
      p(" Class Name: "); 
      pn(ppi[i].getPortType());
    }
  } else {
    p("!No ProvidesPorts in ");
    pn(ci->getInstanceName());
  }
  pn("------------------------------------");
}

void CmdLineBuilderViewForHuman::pullDownComponent(const char *className, const char *instanceName) {
  p(instanceName);
  p(" of type ");
  p(className);
  pn(" \nsuccessfully instantiated");
}

void CmdLineBuilderViewForHuman::connect(const char *fromInstance, const char *providesInstance, const char *toInstance, const char *usesInstance) {
  p(toInstance);
  p("))))");
  p(usesInstance);
  p("---->");
  p(providesInstance);
  p("((((");
  pn(fromInstance);
  pn("connection made successfully");
}

void CmdLineBuilderViewForHuman::disconnect( const char *fromInstance,  const char *providesInstance, const  char *toInstance, const  char *usesInstance) {
  p(toInstance);
  p("))))");
  p(usesInstance);
  p("-\\ \\-");
  p(providesInstance);
  p("((((");
  pn(fromInstance);
  pn("connection broken successfully");
}

void CmdLineBuilderViewForHuman::displayConnectionFailed(const char *msg) {
  error("CmdLineBuilderViewForHuman::displayConnectionFailed: Connection unsuccessful.");
  error(msg);
}

void CmdLineBuilderViewForHuman::displayDisconnectionFailed(const char *msg) {
  error("CmdLineBuilderViewForHuman::displayDisconnectionFailed: Disconnection unsuccessful.");
  error(msg);
}


void CmdLineBuilderViewForHuman::displayChain() {
  if(bm == 0) {
    pn("no instances available");
    return;
  }
  ::std::map< ::std::string, ComponentInfo_shared > arena = bm->getArena();
  ::std::map< ::std::string, ComponentInfo_shared >::iterator pos;
  int shown = 0;
  for ( pos = arena.begin(); pos != arena.end(); pos++) {
    ComponentInfo_shared ci = pos->second;
    p("Component ");
    p(ci->getInstanceName());
    p(" of type ");
    pn(ci->getClassName());
    shown = true;
    ::std::vector< ConnectionID_ptr > conns = ci->getUsesConnections();
    for(size_t i = 0;i < conns.size();i++) {
      ConnectionID_ptr c = conns[i];
      ::std::string sb = " is using ";
      sb += c->getUserPortName();
      sb += " connected to Port: ";
      if (!c->isFrameworkConnection()) {
        sb += c->getProviderPortName();
        sb += " provided by component ";
        sb += c->getProvider()->getInstanceName();
      } else {
        sb += c->getUserPortName();
        sb += " provided by FRAMEWORK";
      }
      if (c->isActive()) {
        sb +=" ACTIVE";
      }
      pn(sb);
    }
  }

  if(!shown) {
    pn("No instantiated components available");
    return;
  }
}

// this seems to be broken: for loop not dependent on i.
// needs to do like java which perhaps implicitly calls
// toString.
void CmdLineBuilderViewForHuman::displayChain(ComponentInfo_shared ci) {
  p("))))");
  p("{l->provides}"); // fixme
  p("> ");
  p(ci->getInstanceName());
  p("))))");
  p("{l->uses}"); // fixme
  pn("> ");
}

void CmdLineBuilderViewForHuman::error(const char *msg) {
  pn(msg);
} 

void CmdLineBuilderViewForHuman::error(const std::string msg) {
	error(msg.c_str());
}

void CmdLineBuilderViewForHuman::errorFatal(const char * msg) {
  error("CmdLineBuilderViewForHuman::errorFatal:");
  error(msg);
  exit(2);
}

void CmdLineBuilderViewForHuman::pn(const  std::string & s) {
  fprintf(out,"%s\n",s.c_str());
  fflush(out);
}

void CmdLineBuilderViewForHuman::p(const  std::string & s) {
  fprintf(out,"%s",s.c_str());
  fflush(out);
}

void CmdLineBuilderViewForHuman::pn(const char *s) {
  fprintf(out,"%s\n",s);
  fflush(out);
}

void CmdLineBuilderViewForHuman::p(const char *s) {
  fprintf(out,"%s",s);
  fflush(out);
}

void CmdLineBuilderViewForHuman::pn(const char c) {
  fputc(c,out);
  fputc('\n',out);
  fflush(out);
}

void CmdLineBuilderViewForHuman::p(const char c) {
  fputc(c,out);
  fflush(out);
}

void CmdLineBuilderViewForHuman::displayConfiguration(const char * instanceName, const char * portName, const char * configuration){

  pn("CmdLineBuilderViewForHuman.cxx:displayConfiguration");
  pn(configuration);

  JCPN(StringTokenizer) *wintokens = new JCPN(StringTokenizer)(const_cast<char *>(configuration),":");
  char * title = wintokens->nextToken();
  p("Instance name: ");
  pn(instanceName);
  p("Port name: ");
  pn(portName);
  pn("------------------------------------");
  p(title);
  pn(":");
  while (wintokens->hasMoreTokens()) {
    JCPN(StringTokenizer) *tabs = new JCPN(StringTokenizer)(wintokens->nextToken(),"@");
    char * tabtitle = tabs->nextToken();
    p("Group ");
    p(tabtitle);
    pn(":");
    while (tabs->hasMoreTokens()) {
      JCPN(StringTokenizer) *itemtokens = 
          new JCPN(StringTokenizer)(tabs->nextToken(),"&",true);
      char * itype = itemtokens->nextToken();
      char * amp0 = itemtokens->nextToken(); (void)amp0;
      char * iname = itemtokens->nextToken();
      char * amp1 = itemtokens->nextToken(); (void)amp1;
      char * ival = itemtokens->nextToken();
      if (JString::compareTo(ival,"&") == 0) {
        ival = "UNDEFINED";
      } else {
        char * amp2 = itemtokens->nextToken(); (void)amp2;
      }
      char * help = itemtokens->nextToken(); (void)help;
      char * amp3 = itemtokens->nextToken(); (void)amp3;
      char * prmpt = itemtokens->nextToken();
      p(iname);
      p("(");
      p(itype);
      p(")");
      p(" : ");
      p(prmpt);
      p(" = ");
      pn(ival);
    }
  }
        
  pn("------------------------------------");
}

void CmdLineBuilderViewForHuman::setConfiguration(const char * instanceName, const char * portName, const char *fieldName, const char * configuration){
  (void) fieldName;
  pn("------------------------------------");
  p("Instance name: ");
  pn(instanceName);
  p("Port name: ");
  pn(portName);
  pn("------------------------------------");
  pn("New parameters:");
  pn(configuration);
  pn("------------------------------------");
}

void CmdLineBuilderViewForHuman::displayComponentProperties(const char * instanceName, std::vector< std::string > & props)
{
  if (!instanceName ) {
    pn("!ComponentPropertyList NULL. framework error.");
    return;
  }
  int r = props.size();
  for (int i=0; i < r; i+=2) {
    std::string key = props[i];
    std::string value = props[i+1];
    p("ComponentPropertyList ");
    p(instanceName);
    p(" ");
    p(key);
    p(" ");
    pn(value);
  }
  if (r >0) { pn("EndComponentPropertyList"); }

}

void CmdLineBuilderViewForHuman::displayComponentProperty(const char * instanceName, const char * key, const char * value) {
  if (value == NULL) {
    p("!ComponentProperty ");
    p(instanceName);
    p(" ");
    p(key);
    pn(" does not exist.");
  } else {
    p("ComponentProperty ");
    p(instanceName);
    p(" ");
    p(key);
    p(" ");
    pn(value);
  }
}

void CmdLineBuilderViewForHuman::setComponentProperty(const char * instanceName, const char * key, const char * value, int err) {
  if (err == -1) {
    pn("!SetComponentProperty: error in framework finding KeyValuePort.");
  }
  if (err == 0) {
    p("SetComponentProperty ");
    p(instanceName);
    p(" ");
    p(key);
    p(" ");
    pn(value);
  }
  if (err == 1) {
    pn("!SetComponentProperty: got NULL key or value.");
  }
  if (err == 2) {
    p("!SetComponentProperty: got key containing illegal = (");
    p(key);
    pn(").");
  }
  if (err == 3) {
    p("!SetComponentProperty got key containing illegal whitespace (");
    p(key);
    pn(").");
  }
}

void CmdLineBuilderViewForHuman::displayPortProperties(const std::string & iname, const std::string & pname, ::ccafeopq::TypeMap_shared t, const std::string & key)
{
	if (!t || iname == "" || pname == "") {
		pn("!PortPropertyList NULL. framework error.");
		return;
	}
	if ( key.size() == 0 ) {
		std::vector<std::string> keys = t->getAllKeys(::ccafeopq::NoType);
		for (size_t i = 0 ; i < keys.size(); i++)
		{
			p("PortPropertyList ");
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
		pn("EndPortPropertyList");
	  	return;
  	}
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

void CmdLineBuilderViewForHuman::setPortProperty(const std::string & instanceName, const std::string & portName, const std::string & key, const std::string & vType, const std::string & value, int err)
{
  if (err == -1) {
    pn("!SetPortProperty: error in framework setting value.");
  }
  if (err == 0) {
    p("SetPortProperty ");
    p(instanceName);
    p(" ");
    p(portName);
    p(" ");
    p(key);
    p(" ");
    p(vType);
    p(" ");
    pn(value);
  }
}

