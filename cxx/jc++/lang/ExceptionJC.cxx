#ifndef lint
static char id[] = 
"$Id: ExceptionJC.cxx,v 1.2 2000/10/27 18:46:02 kohl Exp $";
#endif

#include "jc++/lang/Object.h"
#include "jc++/jc++.h"

#include <exception> // the barebones (worthless, buggy) c++ version

#include "jc++/lang/ExceptionJC.h"

#include "util/freefree.h"


/** Like all good software, this comes with a demo.
That, however, does not imply that this is good software...
*/

#ifdef MAINExceptionJC
/** a function to get us away from any possible
weirdness resulting from being in the outermost scope.
*/
class food {
// it's exceptional at the livermore cafeteria.
};

void dumme(int argc, char **argv) {

  if (argc==1) {
    // generic exception version
    try {
      printf("\ntest c++ exception:\n");
      throw exception();
    } catch (exception& e) {
      printf("caught: %s\n\n",e.what());
    }
  
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
    // Informative, ben-derived version, where c++ takes care of memory.
    // This is the "least change" version that we want to use if we
    // want c++ to look like java. Must be caught in same scope.
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
#if 0 // toast under egcs-2.91.66 and some other compilers, exception reference
// becomes stale in the catch clause, ouch.
    try {
      printf("test generic cca ExceptionJC:\n");
      throw ExceptionJC("1st base");
    } catch (ExceptionJC& e) {
      printf("caught: %s, %s, %s\n",e.why(),e.kind(),e.what());
    }
#endif
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
    // remember that to throw outside a function scope, you must
    // throw new ExceptionJC or you will be reading freed stack.
    // Some compilers consider try {} the scope, so in general we
    // we must always do this new/delete exercise.
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//

    // Pointer version, which leaves annoying memory about if you forget
    // the delete call and core dumps if you forget the new or *.
    // Probably it is best to throw ExceptionJC rather than throw new ExceptionJC.
    // But don't forget to catch.
    try {
      printf("test ExceptionJC *:\n");
      throw new ExceptionJC("2nd base");
    } catch (ExceptionJC* e) {
      printf("caught: %s, %s, %s\n",e->why(),e->kind(),e->what());
      delete e;
    }
  }
  fflush(0);

  if (argc==2) {
    switch (argv[1][0]) {
    case 'a':
#ifdef _CXX_STD_EXCEPTIONS
      // catch something less specific but not _everything_, if we inherit from something.
      try {
        printf("test catch ExceptionJC w/exception and dynamic_cast:\n");
        throw new ExceptionJC("3rd base");
      } catch (exception* e) {
        printf("caught: %s\n",e->what());
        ExceptionJC *Ep = dynamic_cast<ExceptionJC *>(e);
        CHECKDC(Ep);
        if (Ep != NULL) {
          printf("caught: %s, %s, %s\n",Ep->why(),Ep->kind(),Ep->what());
        }
        delete e;
      }
#else
      printf("test catch ExceptionJC w/exception and dynamic_cast ignored on solaris\n");
#endif
      break;

    case 'b':
      // catch _everything_
      try {
        printf("test catch anything at all:\n");
        throw food();
      } catch (...) {
        printf("caught everything and nothing.\n");
      }
      break;

    case 'c':
      // miss ExceptionJC
      try {
        printf("test missed exception (should abort):\n");
        throw exception();
      } catch (ExceptionJC& e) {
        printf("caught: %s, %s, %s\n",e.why(),e.kind(),e.what());
      }
      break;

    case 'd':
      // almost miss ExceptionJC
      try {
        printf("test backup catch (should not abort):\n");
        throw exception();
      } 
      catch (ExceptionJC& e) {
        printf("caught: %s, %s, %s\n",e.why(),e.kind(),e.what());
      } 
      catch (exception& e) {
        printf("caught: %s\n\n",e.what());
      }
      break;

    case 'e':
      // subclass of cca exception
      try {
        printf("test very specific throw/catch:\n");
        throw new ClassNotFoundExceptionJC("load it please");
      } catch (ClassNotFoundExceptionJC* e) {
        printf("caught: %s, %s, %s\n",e->why(),e->kind(),e->what());
        delete e;
      } 
      break;

    case 'f':
#if 0 // toast under egcs-2.91.66 and some other compilers
      // subclass of cca exception abort test
      try {
        printf("test general cca throw/specific catch (should abort):\n");
        throw ExceptionJC("load it again please");
      } catch (ClassNotFoundExceptionJC& e) {
        printf("caught: %s, %s, %s\n",e.why(),e.kind(),e.what());
      } 
#endif // 0
      break;

    default:
      printf("%s: unrecognized test letter {%s}\n",argv[0], argv[1]);
    }
  }
}
// This program takes (optionally) a 1 letter commandline argument
// a thru f (or more if tests are expanded later).
int main(int argc, char **argv) {
#ifdef _EFENCE
// see the man page for these
  extern int EF_ALIGNMENT;
  extern int EF_PROTECT_BELOW;
  extern int EF_PROTECT_FREE;
  extern int EF_ALLOW_MALLOC_0;
  EF_ALIGNMENT=0;
  EF_PROTECT_BELOW=0;
  EF_PROTECT_FREE=1;
  EF_ALLOW_MALLOC_0=0;
#endif //_EFENCE
  // call malloc to get efence to get its
  // banner out of the way of the exception
  // test print statements.
  char *nothing = (char *)malloc(2);
  dumme(argc,argv);
  free(nothing);
  return 0;
}
#endif //MAINExceptionJC


ExceptionJC::ExceptionJC(char *why) {
  jwhat = strdup(why);
  printf("Uncaught ExceptionJC: %s\n",jwhat);
#ifdef NOISEX
  printf("alloc ExceptionJC(%p \"%s\") --> %p %s {%p}\n",why, why, jwhat, jwhat, this);
  fflush(0);
#endif //NOISEX
}

ExceptionJC::ExceptionJC() {

  jwhat = strdup(kind());
  printf("Uncaught ExceptionJC: %s\n",jwhat);

#ifdef NOISEX
  printf("alloc ExceptionJC() --> (%s) %p %s\n", kind(), jwhat, jwhat);
  fflush(0);
#endif //NOISEX

}


ExceptionJC::~ExceptionJC() {
  if (jwhat !=NULL) {

#ifdef NOISEX
    printf("dealloc ExceptionJC() --> %p %s {%p}\n\n", jwhat , jwhat, this);
    fflush(0);
#endif //NOISEX

    free(jwhat);
    jwhat = NULL;

#ifdef NOISEX
  } else {
    printf("dealloc ExceptionJC: called twice!\n");
    fflush(0);
#endif //NOISEX

  }
}

void ExceptionJC::checkDynamicCast(void *p, char *f, int l) {
  if (p == 0) {
    fprintf(stderr,"dynamic_cast failed at %s:%d.\n",f,l);
    throw new RuntimeExceptionJC("dynamic_cast failed");
  }
}

char *ExceptionJC::kind() { 
  return const_cast<char *>(typeid(this).name());
}

#ifndef _CXX_STD_EXCEPTIONS
char *ExceptionJC::what() { 
  return (char *)"NoThInG";
}
#endif // _CXX_STD_EXCEPTIONS

char *ExceptionJC::why() { 
  return jwhat;
}

// macro from hell to make more ExceptionJC subclass definitions.
#ifndef NOISEX

#ifdef _CXX_STD_EXCEPTIONS
#define EBODY(ae) \
ae::ae(char *why) { jwhat = strdup(why); printf("Uncaught exception: %s\n",jwhat); } \
ae::ae() { jwhat = strdup(kind()); } \
ae::~ae() { if (jwhat !=NULL) { free(jwhat); jwhat = NULL; } } \
char *ae::kind() { return const_cast<char *>(typeid(this).name()); } \
char *ae::why() { return jwhat; }

#else

#define EBODY(ae) \
ae::ae(char *why) { jwhat = strdup(why); printf("Uncaught exception: %s\n",jwhat); } \
ae::ae() { jwhat = strdup(kind()); } \
ae::~ae() { if (jwhat !=NULL) { free(jwhat); jwhat = NULL; } } \
char *ae::kind() { return const_cast<char *>(typeid(this).name()); } \
char *ae::what() { return (char *)"NoThInG"; } \
char *ae::why() { return jwhat; }

#endif //_CXX_STD_EXCEPTIONS

#else // NOISEX

#ifdef _CXX_STD_EXCEPTIONS
#define EBODY(ae) \
ae::ae(char *why) { \
  jwhat = strdup(why); \
  printf("EBODY(%p \"%s\") --> %p %s {%p}\n",why, why, jwhat, jwhat, this); \
} \
ae::ae() { \
  jwhat = strdup(kind()); \
  printf("EBODY() --> (%s) %p %s\n", kind(), jwhat, jwhat); \
} \
ae::~ae() { \
  if (jwhat !=NULL) { \
    printf("xEBODY() --> %p %s {%p}\n\n", jwhat , jwhat, this); \
    fflush(0); free(jwhat); jwhat = NULL; \
  } else { \
    printf("xEBODY: called twice!\n"); \
  } \
} \
char *ae::kind() { return const_cast<char *>(typeid(this).name()); } \
char *ae::why() { return jwhat; } 

#else // _CXX_STD_EXCEPTIONS

#define EBODY(ae) \
ae::ae(char *why) { \
  jwhat = strdup(why); \
  printf("EBODY(%p \"%s\") --> %p %s {%p}\n",why, why, jwhat, jwhat, this); \
} \
ae::ae() { \
  jwhat = strdup(kind()); \
  printf("EBODY() --> (%s) %p %s\n", kind(), jwhat, jwhat); \
} \
ae::~ae() { \
  if (jwhat !=NULL) { \
    printf("xEBODY() --> %p %s {%p}\n\n", jwhat , jwhat, this); \
    fflush(0); free(jwhat); jwhat = NULL; \
  } else { \
    printf("xEBODY: called twice!\n"); \
  } \
} \
char *ae::kind() { return const_cast<char *>(typeid(this).name()); } \
char *ae::what() { return (char *)"NoThInG"; } \
char *ae::why() { return jwhat; } 

#endif // _CXX_STD_EXCEPTIONS

#endif //NOISEX





/// Add all the kinds of exceptions you ever want here.

EBODY(ClassNotFoundExceptionJC);
EBODY(NullPointerExceptionJC);
EBODY(ConnectionVetoExceptionJC);
EBODY(EOFExceptionJC);
EBODY(IllegalAccessExceptionJC);
EBODY(InstantiationExceptionJC);
EBODY(IOExceptionJC);
EBODY(RuntimeExceptionJC);

