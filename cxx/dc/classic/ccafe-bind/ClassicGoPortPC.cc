#include <unistd.h>
#include "dc/export/AllExport.hh"
#include <cca.h>
#include <stdPorts.h>
#include "dc/classic/ccafe-bind/ClassicPortConverter.hh"
#include "dc/classic/ccafe-bind/ClassicGoPortPC.hh"
#include "dc/classic/ccafe-bind/ClassicGoPortWrap.hh"
#include "util/IO.h"



ClassicGoPortPC::ClassicGoPortPC(int bogon)
{
}

ClassicGoPortPC::ClassicGoPortPC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("ClassicGoPortPC CTOR");
#endif
}

ClassicGoPortPC::~ClassicGoPortPC()
{
#ifdef CCAFE_AUDIT
	IO_dn1("ClassicGoPortPC DTOR");
#endif
}

classic::gov::cca::Port *
ClassicGoPortPC::convert(::ccafeopq::Port * op)
{
  if ( op->supportsKind( ccafeopq::OPAQUE_PORT) ) {
    ccafeopq::GoPort *gpp = dynamic_cast< ccafeopq::GoPort * >(op);
    if (!gpp) {
      IO_en1("GoPort: fails to cast ::ccafeopq::Port * "
             "to a ::ccafeopq::GoPort *, returning null");
      return  0;
    }
    ClassicGoPortWrap *ngpPort = new ClassicGoPortWrap( gpp );
    classic::gov::cca::Port *p = ngpPort; 
    return p;
  } else {
    ::std::string ogk =  op->getKind();
    IO_en3("ccafeopq::Port of kind: %s not %s, returning a null port", 
           ogk.c_str(),
           ::ccafeopq::OPAQUE_PORT.c_str());
    return 0;
  }
}

ClassicGoPortPC ClassicGoPortPC_test(1);
