#ifndef __IO_H__
#define __IO_H__

#if defined(__SUNPRO_CC) || defined(__sgi)
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#else
//#include <cstdio>
//#include <cstdlib>
//#include <cstdarg>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#endif //__SUNPRO_CC

#include <string>


/** A knobby little STATIC class Rob started to allow a C-interfaced,
    globally usable IO object that can redirect stdin/out/err
    as desired (probably to sockets real soon now).
    Works fine under g++; hates old solaris releases.

    Sort of a namespace avoidance method.
*/

#define IO_C(Q) const_cast<const char *>(Q)
//No way to get macros to include comma'd arguments -- holy cow:
#define IO_dn1(X) IO::dn(__FILE__, __LINE__, X )
#define IO_dn2(X, Y) IO::dn(__FILE__, __LINE__, (X), (Y) )
#define IO_dn3(X, Y, Z) IO::dn(__FILE__, __LINE__, (X), (Y), (Z) )
#define IO_dn4(X, Y, Z, A) IO::dn(__FILE__, __LINE__, (X), (Y), (Z), (A) )
#define IO_dn5(X, Y, Z, A, B) IO::dn(__FILE__, __LINE__, (X), (Y), (Z), (A), (B))
#define IO_dn6(X, Y, Z, A, B, C) IO::dn(__FILE__, __LINE__, (X), (Y), (Z), (A), (B), (C))
#define IO_dn7(X, Y, Z, A, B, C, D) IO::dn(__FILE__, __LINE__, (X), (Y), (Z), (A), (B), (C), (D))

//No way to get macros to include comma'd arguments -- holy cow:
#define IO_en1(X) IO::errorOut(IO_C(__FILE__), __LINE__, IO_C(X) )
#define IO_en2(X, Y) IO::errorOut(IO_C(__FILE__), __LINE__, IO_C(X), (Y) )
#define IO_en3(X, Y, Z) IO::errorOut(IO_C(__FILE__), __LINE__, IO_C(X), (Y), (Z) )
#define IO_en4(X, Y, Z, A) IO::errorOut(IO_C(__FILE__), __LINE__, IO_C(X), (Y), (Z), (A) )
#define IO_en5(X, Y, Z, A, B) IO::errorOut(IO_C(__FILE__), __LINE__, IO_C(X), (Y), (Z), (A), (B))
#define IO_en6(X, Y, Z, A, B, C) IO::errorOut(IO_C(__FILE__), __LINE__, IO_C(X), (Y), (Z), (A), (B), (C))
#define IO_en7(X, Y, Z, A, B, C, D) IO::errorOut(IO_C(__FILE__), __LINE__, IO_C(X), (Y), (Z), (A), (B), (C), (D))

// Same thing only returns the string that must subsequently be freed.
#define IO_sn1(X) IO::sn(__FILE__, __LINE__, X )
#define IO_sn2(X, Y) IO::sn(__FILE__, __LINE__, (X), (Y) )
#define IO_sn3(X, Y, Z) IO::sn(__FILE__, __LINE__, (X), (Y), (Z) )
#define IO_sn4(X, Y, Z, A) IO::sn(__FILE__, __LINE__, (X), (Y), (Z), (A) )
#define IO_sn5(X, Y, Z, A, B) IO::sn(__FILE__, __LINE__, (X), (Y), (Z), (A), (B))
#define IO_sn6(X, Y, Z, A, B, C) IO::sn(__FILE__, __LINE__, (X), (Y), (Z), (A), (B), (C))
#define IO_sn7(X, Y, Z, A, B, C, D) IO::sn(__FILE__, __LINE__, (X), (Y), (Z), (A), (B), (C), (D))

class IO {

 private:

  static bool debug;

  // these are default init to stdout/stdin/stderr in IO.cxx
#if 1 //old
  /** These should be private, and for some reason aren't. */
  static FILE* _out;
  static FILE* _in;
  static FILE* _err;
#else
  FILE * _out;
  FILE * _in;
  FILE * _err;
#endif

public:

  IO(){}

  static bool getDebug() { return IO::debug; }

  static void setDebug(bool tf) {
    IO::debug = tf;
  }

  /** fgets wrapper, for whatever reason. */
  static char *getline(FILE *fp, char *line, long lineMaxSize);

  /** fgets wrapper, for whatever reason, that uses _in. */
  static char *getline(char *line, long lineMaxSize);

  
  /** Output a string on out device ... ala printf */
  static void p(char* fmt, ...) ;
  static void p(char const* fmt, ...) ;

  /** Output a string with \n on out device ... ala printf */
  static void pn(char * fmt, ...) ;
  static void pn(const char * fmt, ...) ;

  /** Output a string on err device ... ala printf */
  static void e(const char* fmt, ...) ;

  /** Output a string on err device ... ala printf */
  static void err(const char* fmt, va_list ap);

  /** Output a string with \n on err device ... ala printf */
  static void en(const char* fmt, ...);
  static void en(const  std::string & s);

  /** Same as en but takes a File and Line argument.*/
  static void errorOut(const char * file, const int line, const char * fmt, ...);

  /** hack around some compiler insanities. */
  // static void errorOut(char const * fname, const int lineno, char const * fmt, ... );

  /** Output a string with \n on err device ... ala printf */
  static void errn(const char* fmt, va_list ap);

  /** Output a debug string with \n on err device. */
  static void dn(const char* file, const int line, 
		 const char* ufmt, ...);

  /** Output a debug string with \n on err device. */
  static /*CFREE*/ char * sn(const char* file, const int line, 
			 const char* ufmt, ...);

   /** Call with mpi rank or pid (other than -1) to add rank at the END of 
      printed newlines. */
  static void initId(int pid);

  /** Return pid from last initId call, or -1 if never set */
  static int getId();
 
  
  /** File pointer redirections */
  static void setOut(FILE *out) ;
  static void setErr(FILE *err) ;
  static void setIn(FILE *in) ;

  /** File pointer acquisition */
  static FILE *out() ;
  static FILE *err() ;
  static FILE *in() ;

  /** File pointer acquisition, this time more nicely*/
  static FILE *getOut() ;
  static FILE *getErr() ;
  static FILE *getIn() ;

  /** mainly a linker test */
  static void testMacros();
};
#endif // __IO_H__

