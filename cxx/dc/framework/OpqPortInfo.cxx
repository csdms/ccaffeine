#include "dc/export/AllExport.hh"
#include "util/IO.h"
#include "util/TypeMap.h"


namespace {
char id[]=
"$Id: OpqPortInfo.cxx,v 1.9 2005/11/08 00:38:55 baallan Exp $";
} ENDSEMI

namespace {
  static int numopi = 0;
  int note() {
      numopi++;
      IO_dn2("OpqPortInfo created %d", numopi);
      return numopi;
  }
};

OpqPortInfo::~OpqPortInfo()
{
  IO_dn2("OpqPortInfo deleted %d", serial);
  serial = -serial;
}

OpqPortInfo::OpqPortInfo(const std::string & name_, const std::string & type_, 
            const std::map<std::string, std::string> & properties)
{
  serial = note();
  name = name_;
  type = type_;
  std::map<std::string, std::string>::const_iterator it;
  ::ccafeopq::TypeMap_shared tmap(new ::gov::sandia::util::TypeMap());
  for(it = properties.begin();it != properties.end();++it) {
    tmap->putString(it->first, it->second);
  }
  tm = tmap;
}

OpqPortInfo::OpqPortInfo(const std::string & name_, const std::string & type_, 
            ::ccafeopq::TypeMap_shared & t)
{
  serial = note();
  name = name_;
  type = type_;
  tm = t;
}


std::string OpqPortInfo::getType() {
  return type;
}

void OpqPortInfo::setType(std::string newType) {
  type = newType;
}

std::string OpqPortInfo::getName() {
  return name;
}

std::string OpqPortInfo::getProperty(const std::string & propertyKey) {
  return ::gov::sandia::util::TypeMap::stringValue(tm, propertyKey);
}

std::string OpqPortInfo::toString() {
  return std::string("type="+type+" name="+name);
}

::std::vector< ::std::string > OpqPortInfo::getKeys()
{
  return tm->getAllKeys( ::ccafeopq::NoType );
}

::ccafeopq::TypeMap_shared OpqPortInfo::getPropertiesTypeMap() {
  return tm;
}

