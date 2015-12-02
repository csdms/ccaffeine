#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: DefaultJPrintfPort.cxx,v 1.6 2004/10/16 05:53:21 baallan Exp $";
} ENDSEMI


#include <string>
#ifdef HAVE_CLASSIC
#include <cca.h>
#include <stdPorts.h>
#endif
#include "dc/export/AllExport.hh"
#ifdef HAVE_CLASSIC
#include "dc/classic/ccafe-bind/ClassicOpaquePort.hh"
#endif
#include "dc/framework/KernelPort.h"
#ifdef HAVE_NEO
#include <neocca.hh>
#include <neoports.hh>
#include "dc/neo/ccafe-bind/NeoOpaquePort.hh"
#endif
#include "dc/port/DefaultJPrintfPort.h"
#include "util/IO.h"

#if defined(__SUNPRO_CC) | defined(__sgi)
#include <string.h>
#include <limits.h>
#else
#include <cstring>
#include <climits>
#endif // __SUNPRO_CC | __sgi

DefaultJPrintfPort::DefaultJPrintfPort(int bogon) {
	// this is just part of a test for type completeness
	// don't call it and expect anything to work.
}

DefaultJPrintfPort::DefaultJPrintfPort() {
#ifdef HAVE_NEO
	IO_dn1("DefaultJPrintfPort::DefaultJPrintfPort() adding neo");
	initNeo();
#endif // HAVE_NEO
#ifdef HAVE_CLASSIC
	IO_dn1("DefaultJPrintfPort::DefaultJPrintfPort() adding classic");
	initClassic();
#endif // HAVE_CLASSIC
	IO_dn1("DefaultJPrintfPort::DefaultJPrintfPort() adding kernel");
	initKernel();
	IO_dn1("DefaultJPrintfPort::DefaultJPrintfPort() done");
}

#ifdef HAVE_CLASSIC
classic::gov::cca::Port * DefaultJPrintfPort::getClassicPort()
{
	return this;
}
#endif // HAVE_CLASSIC

#ifdef HAVE_NEO
neo::cca::Port * DefaultJPrintfPort::getNeoPort()
{
	return this;
}
#endif // HAVE_NEO

void DefaultJPrintfPort::p(char* msg) {
  if (IO::out()==0) { return; }
  
  
  fprintf(IO::out(), msg);
  
}

void DefaultJPrintfPort::p(const char* msg) {
  if (IO::out()==0) { return; }
  
  
  fprintf(IO::out(), msg);
  
}

void DefaultJPrintfPort::pn(char * msg) {
  if (IO::out()==0) { return; }
  
  
  fprintf(IO::out(), msg);
  if (IO::getId() != -1) {
    fprintf(IO::out()," <<%d>>",IO::getId());
  }
  fprintf(IO::out(),"\n");
  
}

void DefaultJPrintfPort::pn(const char * msg) {
  if (IO::out()==0) { return; }
  
  
  fprintf(IO::out(), msg);
  if (IO::getId() != -1) {
    fprintf(IO::out()," <<%d>>",IO::getId());
  }
  fprintf(IO::out(),"\n");
  
}

void DefaultJPrintfPort::e(const char* msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg);
  
}

void DefaultJPrintfPort::e(char* msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg);
  
}

void DefaultJPrintfPort::en(char* msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg);
  if (IO::getId() != -1) {
    fprintf(IO::err()," <<%d>>",IO::getId());
  }
  fprintf(IO::err(),"\n");
  
}

void DefaultJPrintfPort::en(const char* msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg);
  if (IO::getId() != -1) {
    fprintf(IO::err()," <<%d>>",IO::getId());
  }
  fprintf(IO::err(),"\n");
  
}
/////////////////////////////////////////////////

void DefaultJPrintfPort::p(std::string& msg) {
  if (IO::out()==0) { return; }
  
  
  fprintf(IO::out(), msg.c_str());
  
}

void DefaultJPrintfPort::p(const std::string& msg) {
  if (IO::out()==0) { return; }
  
  
  fprintf(IO::out(), msg.c_str());
  
}

void DefaultJPrintfPort::pn(std::string& msg) {
  if (IO::out()==0) { return; }
  
  
  fprintf(IO::out(), msg.c_str());
  if (IO::getId() != -1) {
    fprintf(IO::out()," <<%d>>",IO::getId());
  }
  fprintf(IO::out(),"\n");
  
}

void DefaultJPrintfPort::pn(const std::string& msg) {
  if (IO::out()==0) { return; }
  
  
  fprintf(IO::out(), msg.c_str());
  if (IO::getId() != -1) {
    fprintf(IO::out()," <<%d>>",IO::getId());
  }
  fprintf(IO::out(),"\n");
  
}

void DefaultJPrintfPort::e(const std::string& msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg.c_str());
  
}

void DefaultJPrintfPort::e(std::string& msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg.c_str());
  
}

void DefaultJPrintfPort::en(std::string& msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg.c_str());
  if (IO::getId() != -1) {
    fprintf(IO::err()," <<%d>>",IO::getId());
  }
  fprintf(IO::err(),"\n");
  
}

void DefaultJPrintfPort::en(const std::string& msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg.c_str());
  if (IO::getId() != -1) {
    fprintf(IO::err()," <<%d>>",IO::getId());
  }
  fprintf(IO::err(),"\n");
  
}
////////////////////////////////////////////////
////////////////////////////////////////////////
// so we cheat and log and err are the same.
void DefaultJPrintfPort::l(const std::string& msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg.c_str());
  
}

void DefaultJPrintfPort::l(std::string& msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg.c_str());
  
}

void DefaultJPrintfPort::ln(std::string& msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg.c_str());
  if (IO::getId() != -1) {
    fprintf(IO::err()," <<%d>>",IO::getId());
  }
  fprintf(IO::err(),"\n");
  
}

void DefaultJPrintfPort::ln(const std::string& msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg.c_str());
  if (IO::getId() != -1) {
    fprintf(IO::err()," <<%d>>",IO::getId());
  }
  fprintf(IO::err(),"\n");
  
}
void DefaultJPrintfPort::l(char* msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg);
  
}

void DefaultJPrintfPort::l(const char* msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg);
  
}

void DefaultJPrintfPort::ln(char * msg) {
  if (IO::err()==0) { return; }
  
  
  fprintf(IO::err(), msg);
  fprintf(IO::err(),"\n");
  
}

void DefaultJPrintfPort::ln(const char * msg) {
  if (IO::err()==0) { return; }
  fprintf(IO::err(), msg);
  fprintf(IO::err(),"\n");
}

// call the bogon constructor so we know when compiling class
// itself that it implements all inherited methods somehow.
// in the broken python world, this may not help.
DefaultJPrintfPort DefaultJPrintfPort_djpp(0);
