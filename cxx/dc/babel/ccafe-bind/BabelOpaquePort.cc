
#include <AllCCA.hh>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/babel/ccafe-bind/BabelOpaquePort.hh"


BabelOpaquePort::~BabelOpaquePort()
{
}

BabelOpaquePort::BabelOpaquePort(gov::cca::Port p_)
{
  p = p_;
  initBabel();
}
  
void
BabelOpaquePort::setPort(gov::cca::Port p_)
{
  p = p_;
}
  
BabelOpaquePort::BabelOpaquePort()
{
	// call only when inherited.
	// for example by goport
}
  
void
BabelOpaquePort::initBabel()
{
  addSupportedKind(ccafeopq::BABEL_PORT);
}

gov::cca::Port BabelOpaquePort::getBabelPort() {
  return p;
}

