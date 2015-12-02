#include "dc/export/AllExport.hh"
 #ifdef HAVE_CLASSIC
#include <cca.h>
#include "stdPorts.h"
#endif
//#include "jc++/jc++.h"
//#include "jc++/lang/jc++lang.h"
//#include "jc++/util/jc++util.h"
#include "dc/port/DefaultKeyValuePort.h"


DefaultKeyValuePort::DefaultKeyValuePort( ::ccafeopq::TypeMap_shared tm_) {
  tm = tm_;
}

DefaultKeyValuePort::DefaultKeyValuePort() {
}

void DefaultKeyValuePort::setMap( ::ccafeopq::TypeMap_shared tm_) {
  tm = tm_;
}

DefaultKeyValuePort::~DefaultKeyValuePort() { 
}

const std::string DefaultKeyValuePort::getValue(const std::string & key) { 
  return tm->getString(key,"");
}

void DefaultKeyValuePort::setValue( const std::string & key, const std::string & value){
  tm->putString(key,value); 
} 

const std::string DefaultKeyValuePort::remove( const std::string & key ) { 
  std::string out = tm->getString(key,"");
  tm->remove(key);
  return out;
}

/** Return all known keys of string type.  May be the empty list.  */
std::vector< std::string > DefaultKeyValuePort::getKeys(){ 
  std::vector< std::string > s = tm->getAllKeys( ::ccafeopq::String );
  return s;
}

