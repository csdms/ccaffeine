
#include <assert.h>
#include <stdlib.h>

#include "dc/export/AllExport.hh"

#include "ComponentChangedEvent.h"
#include "GizzardComponentChangedEvent.h"

namespace {
char id[]=
"$Id: GizzardComponentChangedEvent.cxx,v 1.8 2004/04/02 02:17:53 baallan Exp $";
} ENDSEMI

GizzardComponentChangedEvent::GizzardComponentChangedEvent(
			 const int type_, 
			 const char * componentInstanceName,
			 ccafeopq::PortInfo * opi)
{
  type = type_;
  componentName = componentInstanceName;
  portName = opi->getName();
  portType = opi->getType();
}

GizzardComponentChangedEvent::GizzardComponentChangedEvent(
			 const int type_, 
			 const ::std::string & componentInstanceName,
       const ::std::string & pName,
       const ::std::string & pType
			 )
{
  type = type_;
  componentName = componentInstanceName;
  portName = pName;
  portType = pType;
}

GizzardComponentChangedEvent::~GizzardComponentChangedEvent() {
  type = ComponentChangedEvent::PORT_ERROR;
  componentName += ".DEAD";
  portType += ".DEAD";
  portName += ".DEAD";
}

int GizzardComponentChangedEvent::getChangeType() {
  return type;
}

const char * GizzardComponentChangedEvent::getComponentInstance() {
  return componentName.c_str();
}

const char * GizzardComponentChangedEvent::getPortInstance() {
  return portName.c_str();
}

const char * GizzardComponentChangedEvent::getPortType() {
  return portType.c_str();
}
