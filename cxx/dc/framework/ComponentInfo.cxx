
#include <string>
#include <map>

#include "util/IO.h"
#include "dc/export/AllExport.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <ports/AllEvents.h>
#endif
#include "dc/framework/ComponentChangedEvent.h"
#include "dc/framework/ComponentChangedListener.h"
#include "dc/framework/ConnectionID.h"
#include "dc/framework/ComponentID.h"
#include "dc/framework/UserPortData.h"
#include "dc/framework/ProviderPortData.h"
#include "dc/framework/KernelPort.h"
#include "dc/framework/OpqConnectionEventService.h"
#include "dc/framework/Gizzard.h"
#include "dc/framework/CmpBox.h"
#include "dc/framework/ServicesHelper.h"

#include "ComponentInfo.h"

#include "util/freefree.h"

namespace {
char id[]=
"$Id: ComponentInfo.cxx,v 1.28 2004/11/24 00:47:43 baallan Exp $";
} ENDSEMI

ComponentInfo::ComponentInfo(ccafe::CmpBox_shared b) {
  box = b;
}

ComponentInfo_shared 
ComponentInfo::wrapCmpBox( boost::shared_ptr< ::ccafe::CmpBox > b)
{
	ComponentInfo *x = new ComponentInfo(b);
	ComponentInfo_shared y(x);
	return y;
}

std::vector < ComponentInfo_shared > 
ComponentInfo::wrapCmpBoxVector( std::vector< ccafe::CmpBox_shared > & bvec)
{
	size_t i,n;
	std::vector < ComponentInfo_shared > result;
	for (i = 0, n= bvec.size(); i < n; i++)
       	{
		ccafe::CmpBox_shared y = bvec[i];
		ComponentInfo_shared x = ComponentInfo::wrapCmpBox(y);
		result.push_back(x);
	}
	return result;
}

std::map < std::string, ComponentInfo_shared > 
ComponentInfo::wrapCmpBoxMap( std::map< std::string, ccafe::CmpBox_shared > & bmap)
{
	std::map < std::string, ComponentInfo_shared > result;
	::std::map< ::std::string, ccafe::CmpBox_shared >::iterator pos;
	for ( pos = bmap.begin(); pos != bmap.end(); pos++) {
		ccafe::CmpBox_shared cb = pos->second;
		ComponentInfo_shared x = ComponentInfo::wrapCmpBox(cb);
		result[pos->first] = x;
	}
	return result;
}

std::string
ComponentInfo::toString() {

  char val[40];
  ::std::string result = "Component instance name: ";

  result += box->cname; 
  result += " of type: "; 
  result += box->ctype; 
  result += "\n"; 

  size_t i = 0;
  result += "Uses Ports:\n";
  const ::std::vector< UserPortData > updv = box->giz->getUsesPortRegister();
  for (i = 0; i < updv.size(); i++) {
    sprintf(val,"Port#%d ",int(i));
    result += val; 
    ::std::string c = ServicesHelper::toStringUserPortData(updv[i]);
    result += c; 
    result += "\n"; 
  }

  result += "Provides Ports:\n";
  const ::std::vector< ProviderPortData > ppdv = box->giz->getProvidesPorts();
  for ( i = 0; i < ppdv.size(); i++) {
    sprintf(val,"Port#%d ",int(i));
    result += val;
    ::std::string c = ServicesHelper::toStringProviderPortData(ppdv[i]);
    result += c;
    result += "\n"; 
  }

  return result;
}



const std::string
ComponentInfo::getClassName()
{
  return box->ctype;
}

ComponentInfo::~ComponentInfo()
{
}

const std::string
ComponentInfo::getInstanceName() { 
  return box->cname;
}

const ::std::vector< UserPortData > & ComponentInfo::getUsesPortRegister()
{
  return box->giz->getUsesPortRegister();
}

const ::std::vector< ProviderPortData > & ComponentInfo::getProvidesPorts()
{
  return box->giz->getProvidesPorts();
}

::std::vector< ConnectionID_ptr > ComponentInfo::getUsesConnections()
{
  return box->giz->getUsesConnections();
}

  /** Properties for this component */
::ccafeopq::TypeMap_shared ComponentInfo::getComponentPropertyTypeMap() {
  return box->giz->getPropertyMap();
}

  /** Properties for this component */
void ComponentInfo::setComponentPropertyTypeMap(::ccafeopq::TypeMap_shared tm) {
  box->giz->setPropertyMapData(tm);
}


  /** Properties for this component */
::ccafeopq::TypeMap_shared 
ComponentInfo::getPortPropertyTypeMap(const std::string & portname) {
  return box->giz->getPortProperties(portname);
}

  /** Properties for this component */
void ComponentInfo::setPortPropertyTypeMap(const std::string & portname, 
					   ::ccafeopq::TypeMap_shared tm) {
  box->giz->setPortProperties(portname, tm);
}

