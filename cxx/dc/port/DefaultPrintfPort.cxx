#include "dc/export/config.hh"
namespace {
char id[]=
"$Id: DefaultPrintfPort.cxx,v 1.9 2004/10/16 05:53:21 baallan Exp $";
} ENDSEMI

#ifdef HAVE_CLASSIC
#include <cca.h>
#include <stdPorts.h>
#endif
#include "dc/port/DefaultPrintfPort.h"
#include "util/IO.h"

#if defined(__SUNPRO_CC) | defined(__sgi)
#include <string.h>
#include <limits.h>
#else
#include <cstring>
#include <climits>
#endif // __SUNPRO_CC | __sgi

DefaultPrintfPort::DefaultPrintfPort() {}

#if HAVE_PRINTFPORT

void DefaultPrintfPort::p(char* fmt, ...) {
  if (IO::out()==0) { return; }
  va_list ap;
  va_start(ap, fmt);
  vfprintf(IO::out(), fmt, ap);
  va_end(ap);
}

void DefaultPrintfPort::p(const char* fmt, ...) {
  if (IO::out()==0) { return; }
  va_list ap;
  va_start(ap, fmt);
  vfprintf(IO::out(), fmt, ap);
  va_end(ap);
}

void DefaultPrintfPort::pn(char * fmt, ...) {
  if (IO::out()==0) { return; }
  va_list ap;
  va_start(ap, fmt);
  vfprintf(IO::out(), fmt, ap);
  if (IO::getId() != -1) {
    fprintf(IO::out()," <<%d>>",IO::getId());
  }
  fprintf(IO::out(),"\n");
  va_end(ap);
}

void DefaultPrintfPort::pn(const char * fmt, ...) {
  if (IO::out()==0) { return; }
  va_list ap;
  va_start(ap, fmt);
  vfprintf(IO::out(), fmt, ap);
  if (IO::getId() != -1) {
    fprintf(IO::out()," <<%d>>",IO::getId());
  }
  fprintf(IO::out(),"\n");
  va_end(ap);
}

void DefaultPrintfPort::e(const char* fmt, ...) {
  if (IO::err()==0) { return; }
  va_list ap;
  va_start(ap, fmt);
  vfprintf(IO::err(), fmt, ap);
  va_end(ap);
}

void DefaultPrintfPort::e(char* fmt, ...) {
  if (IO::err()==0) { return; }
  va_list ap;
  va_start(ap, fmt);
  vfprintf(IO::err(), fmt, ap);
  va_end(ap);
}

void DefaultPrintfPort::en(char* fmt, ...) {
  if (IO::err()==0) { return; }
  va_list ap;
  va_start(ap, fmt);
  vfprintf(IO::err(), fmt, ap);
  if (IO::getId() != -1) {
    fprintf(IO::err()," <<%d>>",IO::getId());
  }
  fprintf(IO::err(),"\n");
  va_end(ap);
}

void DefaultPrintfPort::en(const char* fmt, ...) {
  if (IO::err()==0) { return; }
  va_list ap;
  va_start(ap, fmt);
  vfprintf(IO::err(), fmt, ap);
  if (IO::getId() != -1) {
    fprintf(IO::err()," <<%d>>",IO::getId());
  }
  fprintf(IO::err(),"\n");
  va_end(ap);
}

// so we cheat and log and err are the same.
void DefaultPrintfPort::l(char* fmt, ...) {
  if (IO::err()==0) { return; }
  va_list ap;
  va_start(ap, fmt);
  vfprintf(IO::err(), fmt, ap);
  va_end(ap);
}

void DefaultPrintfPort::l(const char* fmt, ...) {
  if (IO::err()==0) { return; }
  va_list ap;
  va_start(ap, fmt);
  vfprintf(IO::err(), fmt, ap);
  va_end(ap);
}

void DefaultPrintfPort::ln(char * fmt, ...) {
  if (IO::err()==0) { return; }
  va_list ap;
  va_start(ap, fmt);
  vfprintf(IO::err(), fmt, ap);
  fprintf(IO::err(),"\n");
  va_end(ap);
}

void DefaultPrintfPort::ln(const char * fmt, ...) {
  if (IO::err()==0) { return; }
  va_list ap;
  va_start(ap, fmt);
  vfprintf(IO::err(), fmt, ap);
  fprintf(IO::err(),"\n");
  va_end(ap);
}

#endif // HAVE_PRINTFPORT
