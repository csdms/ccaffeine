#include <cca.h>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/classic/ccafe-bind/ClassicPortInfo.hh"

#define CHECKDEAD(f) \
if (dead) IO::en("ClassicPortInfo::%s called on deleted instance", f)

ClassicPortInfo::ClassicPortInfo(ccafeopq::PortInfo *pi_)
{
  dead = false;
  pi = pi_;
  IO_dn1("ClassicPortInfo created");
}

ClassicPortInfo::~ClassicPortInfo()
{
  CHECKDEAD("~ClassicPortInfo");
  if (pi) {
    delete pi;
  }
  pi = 0;
  dead = true;
  IO_dn1("ClassicPortInfo destroyed");

}

CONST char* ClassicPortInfo::getType() CONST
{
  CHECKDEAD("getType");
  if (pi == 0) { return 0; }
  std::string st = pi->getType();
  return const_cast<char *>(st.c_str() );
}

CONST char* ClassicPortInfo::getName() CONST
{
  CHECKDEAD("getName");
  if (pi == 0) { return 0; }
  std::string st = pi->getName();
  return const_cast<char *>(st.c_str() );
}

CONST char* ClassicPortInfo::getProperty(char* name)
{
  CHECKDEAD("getProperty");
  if (pi == 0) { return 0; }
  ::std::string v = pi->getProperty(name);
  return const_cast<char *>( v.c_str() );
}

ccafeopq::PortInfo *ClassicPortInfo::getpi()
{
  CHECKDEAD("getpi");
  return pi;
}

void ClassicPortInfo::resetPortInfo()
{
  CHECKDEAD("resetPortInfo");
  pi = 0;
}

void ClassicPortInfo::addSupportsKind( const char * portKind)
{
	std::string s = portKind;
	supportsKind.push_back(s);
}

const std::vector< std::string > & ClassicPortInfo::getSupportsKind()
{
	return supportsKind;
}
