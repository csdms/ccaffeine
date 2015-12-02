#ifndef jcpp_h_seen
/** This is a set of concrete classes ala the java coding
 environment. We, however, eschew using extraneous empty
 c++ macros to absorb java keywords and we avoid exceptions.
 Just delete the extra keywords and stick in appropriate
 colons. 

 One notable insanity in C++ is exceptions during constructors
 which java handles just fine. To get around the unsatisfactory
 state of c++, all the constructors that may fail take an
 int reference which will be 0 if ok and -1 if an error occurs
 in construction.

 This lets us minimize changes to java code to recompile it
 as c++. A smart perl script could do a much better job.

 The approach to memory management is to avoid overloading
 assignments. Code thus is perhaps ugly but clear wrt memory
 management.
*/
#define jcpp_h_seen

#include <string>
#ifdef HAVE_CLASSIC
#include <cca.h> //fixme!
#endif

/* failure to remove the following keywords will induce
compiler errors.
*/
#define abstract  kill_me_now_abstract
#define final kill_me_now_final
#define implements replace_me_now_implements_colon
#define native kill_me_now_native
#define interface  kill_me_now_native

/* including the evil, unenforceable one from C */
#ifndef CONST
#define CONST
#endif

/* where public is irrelevant in c++ (on class names) upcase the p to kill it */
#define Public kill_me_now_Public
/* private likewise */
#define Private kill_me_now_Private

/* where abstract is equivalent of virtual in member function definitions fix */
#define Abstract kill_me_now_Abstract

/* make single inheritance work most of the time.
Where a class inherits only interfaces by 'implements'
then a : will need to be inserted manually.
*/
#define extends replace_me_now_extends_colon


/* some c++ compilers don't support boolean. assume char. */
#ifdef __GNUC__
#define HAVE_BOOLEAN 1
#undef TRUE
#define TRUE 1
#undef FALSE
#define FALSE 0
#endif

#ifndef HAVE_BOOLEAN
#undef boolean
#undef bool
#undef true
#undef false
#define bool char
#define boolean char
#define true 1
#define false 0
#endif

/* java's Class is most distantly approximated by c++ type_info */
/* type_info instance ti has the following usefulmethods:
  char * ti.name();
  bool operator== (const type_info& arg) const;
  bool operator!= (const type_info& arg) const;
*/
#if (defined(__KCC) || defined(__SUNPRO_CC) || defined(__sgi))
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <typeinfo.h>
#include <assert.h>
#else
#include <cstring>
#include <cstdio>
#include <cstdlib>
//#include <typeinfo>
#include <cassert>
#endif // __SUNPRO_CC
/* stl : we will not use it in a java emulator. */
// #include <string>
// #define String string

/** changing this value will break things without further maintenance. */
#define JCPP_USE_NAMESPACES 0

// eschew exceptions: #include "jc++/lang/ExceptionJC.h"
#include "jc++/lang/Object.h"

/** Whether or not we live in a namespace, the following macro
    marks an object as one of ours. It will change if jc++ goes
    into the gov::sandia::baallan namespace.
 */
#define JCPN(jcppClassName) jcpp::jcppClassName

#endif // jcpp_h_seen
