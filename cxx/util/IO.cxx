#include "dc/export/config.hh"
namespace {
char id[] = 
"$Id: IO.cxx,v 1.12 2004/03/06 00:21:36 baallan Exp $";
} ENDSEMI

// do a little contract work for freefree.h
extern "C" {
#include <stdlib.h>
  void Free(void *p) {
    free(p);
  }
};

#include "IO.h"

#if defined(__SUNPRO_CC) || defined(__sgi)
#include <string.h>
#include <limits.h>
#else
#include <cstring>
#include <climits>
#endif // __SUNPRO_CC

FILE* IO::_out = stdout;
FILE* IO::_in = stdin;
FILE* IO::_err = stderr;

#include "util/freefree.h"

// ifndef or defined but 0 CCAFE_SPEW, debug printing is off by default.
#ifdef CCAFE_SPEW
#if CCAFE_SPEW
bool IO::debug = true;
#else
bool IO::debug = false;
#endif
#else
bool IO::debug = false;
#endif

static int io_mpi_rank = -1;

void IO::initId(int rank) {
  io_mpi_rank = rank;
}

int IO::getId() {
  return io_mpi_rank;
}

char *IO::getline(FILE *fp, char *line, long lineMaxSize) {
  if (lineMaxSize > INT_MAX || lineMaxSize < 0) {
    return NULL;
  }
  fgets(line,(int)lineMaxSize,fp);
  return line;
}

char *IO::getline(char *line, long lineMaxSize) {
  if (lineMaxSize > INT_MAX || lineMaxSize < 0 || line == NULL || _in == NULL) {
    return NULL;
  }
#ifdef _ODEBUG
  printf("IO::getline(%p, %ld)\n",line,lineMaxSize);
#endif
  fgets(line,(int)lineMaxSize,_in);
  return line;
}

// Output a string on out device ...
void IO::p(char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(_out, fmt, ap);
  va_end(ap);
}

// Output a string on out device ...
void IO::p(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(_out, fmt, ap);
  va_end(ap);
}

// Output a string on out device ...
void IO::pn(char * fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(_out, fmt, ap);
  if (io_mpi_rank != -1) {
    fprintf(_out," <<%d>>",io_mpi_rank);
  }
  fprintf(_out,"\n");
  va_end(ap);
}

void IO::pn(const char * fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(_out, fmt, ap);
  if (io_mpi_rank != -1) {
    fprintf(_out," <<%d>>",io_mpi_rank);
  }
  fprintf(_out,"\n");
  va_end(ap);
}

// Output a string on err device ...
void IO::e(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(_err, fmt, ap);
  va_end(ap);
}

// Output a string on err device using a vararg va_list...
void IO::err(const char* fmt, va_list ap) {
  vfprintf(_err, fmt, ap);
}

// Output a string on err device ...
void IO::en(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(_err, fmt, ap);
  if (io_mpi_rank != -1) {
    fprintf(_err," <<%d>>",io_mpi_rank);
  }
  fprintf(_err,"\n");
  va_end(ap);
}

void IO::en(const std::string &s) {
  fprintf(_err,"%s",s.c_str());
  if (io_mpi_rank != -1) {
    fprintf(_err," <<%d>>",io_mpi_rank);
  }
  fprintf(_err,"\n");
}

// Output a string on err device using a vararg va_list ...
void IO::errn(const char* fmt, va_list ap) {
  vfprintf(_err, fmt, ap);
  if (io_mpi_rank != -1) {
    fprintf(_err," <<%d>>",io_mpi_rank);
  }
  fprintf(_err,"\n");
}

// Return a string in the dn style: file and line prefixed to the
// message.
/*CFREE*/ char *
IO::sn(const char* file, const int line, 
       const char* ufmt, ...) {
  va_list ap;
  va_start(ap, ufmt);
#define LEN 102400
  static char str[LEN]; 
  snprintf(str, LEN, "%s:%d: ", file, line);
  int pre = strlen(str);
  char * nstr = str + pre;
  int left = LEN - pre; // buffer overflow attack here.
  vsnprintf(nstr, left, ufmt, ap);
  va_end(ap);
  left = LEN - strlen(str);
  (void)strncat(str, "\n", left);
  return strdup(str);
}


void IO::dn(const char* file, const int line, 
	    const char* ufmt, ...) {
  if(IO::debug == true) {
    if (_err == 0) { _err = stderr; }
    va_list ap;
    va_start(ap, ufmt);
    fprintf(_err, "%s:%d: ", file, line);
    vfprintf(_err, ufmt, ap);
    fprintf(_err,"\n");
    va_end(ap);
  } else {
    return;
  }
}

void IO::errorOut(const char * file, const int line, const char * ufmt, ...) {
  va_list ap;
  va_start(ap, ufmt);
  fprintf(_err, "%s:%d: ", file, line);
  vfprintf(_err, ufmt, ap);
  fprintf(_err,"\n");
  va_end(ap);
}

void IO::setOut(FILE *out) {
  IO::_out = out;
}

void IO::setErr(FILE *err) {
  IO::_err = err;
}

void IO::setIn(FILE *in) {
  IO::_in = in;
}

FILE *IO::out() {
  return _out;
}

FILE *IO::err() {
  return _err;
}

FILE *IO::in() {
  return _in;
}

FILE *IO::getOut() {
  return _out;
}

FILE *IO::getErr() {
  return _err;
}

FILE *IO::getIn() {
  return _in;
}

void IO::testMacros() {
	bool olddebug = IO::debug;
	printf("testing dn in default state\n");
IO_dn1("dn1_ok");
IO_dn2("dn2_ok %d", 1);
IO_dn3("dn3_ok %d %d", 1, 2);
IO_dn4("dn4_ok %d %d %d", 1, 2, 3);
IO_dn5("dn5_ok %d %d %d %d", 1, 2, 3, 4);
IO_dn6("dn6_ok %d %d %d %d %d", 1, 2, 3, 4, 5);
IO_dn7("dn7_ok %d %d %d %d %d %d", 1, 2, 3, 4, 5, 6);
	IO::setDebug(true);
	printf("testing dn in debug==true state\n");
IO_dn1("dn1_ok");
IO_dn2("dn2_ok %d", 1);
IO_dn3("dn3_ok %d %d", 1, 2);
IO_dn4("dn4_ok %d %d %d", 1, 2, 3);
IO_dn5("dn5_ok %d %d %d %d", 1, 2, 3, 4);
IO_dn6("dn6_ok %d %d %d %d %d", 1, 2, 3, 4, 5);
IO_dn7("dn7_ok %d %d %d %d %d %d", 1, 2, 3, 4, 5, 6);
	IO::setDebug(olddebug);

	printf("testing en in default state\n");
IO_en1("en1_ok");
IO_en2("en2_ok %d", 1);
IO_en3("en3_ok %d %d", 1, 2);
IO_en4("en4_ok %d %d %d", 1, 2, 3);
IO_en5("en5_ok %d %d %d %d", 1, 2, 3, 4);
IO_en6("en6_ok %d %d %d %d %d", 1, 2, 3, 4, 5);
IO_en7("en7_ok %d %d %d %d %d %d", 1, 2, 3, 4, 5, 6);
	printf("testing sn in default state\n");
 char *s = 0;
s = IO_sn1("sn1_ok"); printf("%s",s);
free(s);
s = IO_sn2("sn2_ok %d", 1); printf("%s",s);
free(s);
s = IO_sn3("sn3_ok %d %d", 1, 2); printf("%s",s);
free(s);
s = IO_sn4("sn4_ok %d %d %d", 1, 2, 3); printf("%s",s);
free(s);
s = IO_sn5("sn5_ok %d %d %d %d", 1, 2, 3, 4); printf("%s",s);
free(s);
s = IO_sn6("sn6_ok %d %d %d %d %d", 1, 2, 3, 4, 5); printf("%s",s);
free(s);
s = IO_sn7("sn7_ok %d %d %d %d %d %d", 1, 2, 3, 4, 5, 6); printf("%s",s);
free(s);

} // end macrotest
