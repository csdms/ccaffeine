#include <unistd.h>
#include "dc/export/AllExport.hh"
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoBuilderServicePC.hh"
#include "dc/neo/ccafe-bind/NeoBuilderServiceWrap.hh"
#include "util/IO.h"



NeoBuilderServicePC::NeoBuilderServicePC(int bogon)
{
}

NeoBuilderServicePC::NeoBuilderServicePC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("NeoBuilderServicePC CTOR");
#endif
}

NeoBuilderServicePC::~NeoBuilderServicePC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("NeoBuilderServicePC DTOR");
#endif
}

neo::cca::Port *
NeoBuilderServicePC::convert(::ccafeopq::Port * op)
{
  if ( op->supportsKind( ccafeopq::OPAQUE_PORT) ) {
    ccafeopq::BuilderService *bsp = dynamic_cast< ccafeopq::BuilderService * >(op);
    if (!bsp) {
      IO_en1("BuilderService: fails to cast ::ccafeopq::Port * "
             "to a ::ccafeopq::BuilderService *, returning null");
      return  0;
    }
    NeoBuilderServiceWrap *nbsPort = new NeoBuilderServiceWrap( bsp );
    neo::cca::Port *p = nbsPort; 
    return p;
  } else {
    std::string pkind = op->getKind();
    IO_en3("ccafeopq::Port of kind: %s not %s, returning a null port", 
           pkind.c_str(),
           ::ccafeopq::OPAQUE_PORT.c_str());
    return 0;
  }
}

NeoBuilderServicePC NeoBuilderServicePC_test(1);
