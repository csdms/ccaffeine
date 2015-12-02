#include <unistd.h>
#include "dc/export/AllExport.hh"
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/NeoPortConverter.hh"
#include "dc/neo/ccafe-bind/NeoGoPortPC.hh"
#include "dc/neo/ccafe-bind/NeoGoPortWrap.hh"
#include "util/IO.h"



NeoGoPortPC::NeoGoPortPC(int bogon)
{
}

NeoGoPortPC::NeoGoPortPC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("NeoGoPortPC CTOR");
#endif
}

NeoGoPortPC::~NeoGoPortPC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("NeoGoPortPC DTOR");
#endif
}

neo::cca::Port *
NeoGoPortPC::convert(::ccafeopq::Port * op)
{
  if ( op->supportsKind( ccafeopq::OPAQUE_PORT) ) {
    ccafeopq::GoPort *gpp = dynamic_cast< ccafeopq::GoPort * >(op);
    if (!gpp) {
      IO_en1("GoPort: fails to cast ::ccafeopq::Port * "
             "to a ::ccafeopq::GoPort *, returning null");
      return  0;
    }
    NeoGoPortWrap *ngpPort = new NeoGoPortWrap( gpp );
    neo::cca::Port *p = ngpPort; 
    return p;
  } else {
    std::string pkind = op->getKind();
    IO_en3("ccafeopq::Port of kind: %s not %s, returning a null port", 
           pkind.c_str(),
           ::ccafeopq::OPAQUE_PORT.c_str());
    return 0;
  }
}

NeoGoPortPC NeoGoPortPC_test(1);
