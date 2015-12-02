
#include "dc/export/config.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <ports/AllEvents.h>
#endif // HAVE_CLASSIC

#include "dc/export/AllExport.hh"
#include "dc/export/ccafeopq_support.hh"
#include "dc/framework/ComponentChangedEvent.h"
#include "dc/framework/ComponentChangedListener.h"
#include "dc/framework/ConnectionID.h"
#include "dc/framework/ComponentID.h"
#include "dc/framework/UserPortData.h"
#include "dc/framework/ProviderPortData.h"
#include "dc/framework/KernelPort.h"
#include "dc/framework/OpqConnectionEventService.h"
#include "dc/framework/Gizzard.h"
#include "ServicesHelper.h"
#include <cstring>

namespace {
char id[]=
"$Id: ServicesHelper.cxx,v 1.14 2008/12/24 19:38:41 baallan Exp $";
} ENDSEMI


::std::vector< int > ServicesHelper::getProvidesIndexByName( const ::std::vector< ProviderPortData > & pData, const ::std::string & name)
{
  ::std::vector< int > ret;
  for (size_t i = 0; i < pData.size(); i++)
  {
    if ( pData[i].getPortName() == name )
    {
      ret.push_back(int(i));
    }
  }
  return ret;
}

::std::vector< int > ServicesHelper::getUsesIndexByName( const ::std::vector< UserPortData > & pData, const std::string & name)
{
  ::std::vector< int > ret;
  for (size_t i = 0; i < pData.size(); i++)
  {
    if ( pData[i].getPortName() == name )
    {
      ret.push_back(int(i));
    }
  }
  return ret;
}


::std::string ServicesHelper::toStringUserPortData(const UserPortData & pi)
{
  ::std::string ret = pi.toString();
  return ret;
}

::std::string ServicesHelper::toStringProviderPortData(const ProviderPortData & pi)
{
  std::string ret = "name = ";
  ret += pi.getPortName();
  ret += ", type = ";
  ret += pi.getPortType();
  ret += "\n";
  return ret;
}


/* CFREE */ char* ServicesHelper::toStringPortInfo(ccafeopq::PortInfo * opi){
  char *str = 0;

  ::std::string s ="name = ";
  s += opi->getName();
  s += ", type = ";
  s += opi->getType();
  s += "\n";

  str = strdup(s.c_str());
  return str;
}

