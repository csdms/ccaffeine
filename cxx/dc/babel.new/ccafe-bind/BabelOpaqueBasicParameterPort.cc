#include "gov_cca.hxx"
#include "gov_cca_ports.hxx"
// #include "gov_cca_CCAExceptionType.hxx"
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/framework/KernelPort.h"
#include "dc/babel.new/ccafe-bind/BabelOpaqueTypeMap.hh"
#include "dc/babel.new/ccafe-bind/BabelOpaquePort.hh"
#include "dc/babel.new/ccafe-bind/BabelOpaqueBasicParameterPort.hh"
#include "dc/babel.new/babel-cca/ccaffeine_TypeMap_Impl.hxx"

BabelOpaqueBasicParameterPort::BabelOpaqueBasicParameterPort(gov::cca::ports::BasicParameterPort bpp_) 
{
  bpp = bpp_; 
  setPort(bpp); 
#ifdef CCAFE_AUDIT
  IO_dn1(" BabelOpaqueBasicParameterPort created");
#endif
  initBabel();
#ifdef CCAFE_AUDIT
  IO_dn1("BabelOpaqueBasicParameterPort::BabelOpaqueBasicParameterPort(bpp): done initBabel");
#endif
  initKernel();
#ifdef CCAFE_AUDIT
  IO_dn1("BabelOpaqueBasicParameterPort::BabelOpaqueBasicParameterPort(bpp): done initKernel");
#endif

}

BabelOpaqueBasicParameterPort::~BabelOpaqueBasicParameterPort()
{
#ifdef CCAFE_AUDIT
  IO_dn1(" BabelOpaqueBasicParameterPort destroyed");
#endif
}

ccafeopq::TypeMap_shared 
BabelOpaqueBasicParameterPort::readConfigurationMap()
{
  ::ccafeopq::TypeMap_shared otm;
  if(bpp._not_nil()) {
    gov::cca::TypeMap btm;
    btm = bpp.readConfigurationMap();
    otm = BabelOpaqueTypeMap_Interface::opaqueWrap(btm);
  } else {
    IO_en1((char *)"! :-( BasicParameter port is nil");
  }
  return otm;
}

void 
BabelOpaqueBasicParameterPort::writeConfigurationMap( ccafeopq::TypeMap_shared map )
{
  if(bpp._not_nil()) {
    ccaffeine::TypeMap btm = ccaffeine::TypeMap_impl::babelWrap(map);
    bpp.writeConfigurationMap(btm); 
  } else {
    IO_en1((char *)"! :-( BasicParameter port is nil");
  }
}

::std::vector< ::std::string> 
BabelOpaqueBasicParameterPort::readConfigurationKeys () {

  std::vector< ::std::string> result;
  if(bpp._not_nil()) {
    gov::cca::TypeMap btm = bpp.readConfigurationMap();
    ccafeopq::TypeMap_shared otm = BabelOpaqueTypeMap_Interface::opaqueWrap(btm);
    result = otm->getAllKeys(ccafeopq::NoType);
  } else {
    IO_en1((char *)"! :-( BasicParameter port is nil");
  }
  return result;
}

