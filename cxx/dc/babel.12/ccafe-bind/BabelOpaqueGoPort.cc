#include <AllCCA.hh>
#include "util/IO.h"
#include "dc/export/AllExport.hh"
#include "dc/framework/KernelPort.h"
#include "dc/babel.12/ccafe-bind/BabelOpaquePort.hh"
#include "dc/babel.12/ccafe-bind/BabelOpaqueGoPort.hh"
#include "gov_cca_CCAExceptionType.hxx"

BabelOpaqueGoPort::BabelOpaqueGoPort(gov::cca::ports::GoPort gp_) 
// : BabelOpaquePort(gp)
{
  gp = gp_; 
  setPort(gp); 
  lastresult = 0;
#ifdef CCAFE_AUDIT
  IO_dn1(" BabelOpaqueGoPort created");
#endif
  initBabel();
#ifdef CCAFE_AUDIT
  IO_dn1("BabelOpaqueGoPort::BabelOpaqueGoPort(gp): done initBabel");
#endif
    initKernel();
#ifdef CCAFE_AUDIT
    IO_dn1("BabelOpaqueGoPort::BabelOpaqueGoPort(gp): done initKernel");
#endif

}

BabelOpaqueGoPort::~BabelOpaqueGoPort()
{
#ifdef CCAFE_AUDIT
  IO_dn1(" BabelOpaqueGoPort destroyed");
#endif
  lastresult = -3;
}

int
BabelOpaqueGoPort::BabelOpaqueGoPort::go() {
  // we trap out all babel exceptions and others that we can and return 1, 2 if possible.
  if(gp._not_nil()) {
    if (lastresult == -2) {
       IO_en1("Request made for GoPort that previously returned 2 or failed to catch its own exceptions.");
       IO_en1("Call will not be dispatched to this port.");
       return lastresult;
    }
    try {
      lastresult = gp.go();
    }
    catch (gov::cca::CCAException ex) {
      std::string msg  = ex.getNote();
      const char *s = msg.c_str();
      IO_en1((char *)s);
      if (ex.getCCAExceptionType() == gov::cca::CCAExceptionType_PortNotConnected) {
        lastresult = -1;
      } else {
        lastresult = -2;
      }
    }
    catch (sidl::BaseException ex) {
      IO_en1((char *)"Go threw non-CCA SIDL exception:");
      std::string msg  = ex.getNote();
      const char *s = msg.c_str();
      IO_en1(s);
      IO_en1((char *)"Returning 2 to executive.");
      IO_en1((char *)"Stack trace was: -------------------------");
      msg  = ex.getTrace();
      s = msg.c_str();
      IO_en1(s);
      IO_en1((char *)"------------------------------------------");
      lastresult = -2;
    }
    catch (std::exception & ex) {
      IO_en1((char *)"Go threw standard c++ exception:");
      const char *s = ex.what();
      IO_en1(s);
      IO_en1((char *)"Returning 2 to executive.");
      lastresult = -2;
    }
    catch (...) {
      IO_en1((char *)"Go threw obscure exception with no message");
      IO_en1((char *)"Returning 2 to executive.");
      lastresult = -2;
    }
  } else {
    IO_en1((char *)"! :-( Go port is nil, not doing anything. Ever.");
    lastresult = -2;
  }
  return lastresult;
}

