#ifdef _USE_EXJC
# error NO_NO_NO_NO_NO_
// this file goes away unless you define _USE_EXJC during migration.
// never develop new code based on this header.
#ifndef ExceptionJC_h_seen
#define ExceptionJC_h_seen

/** macro BDeclExceptionJC composes another class, ae, exactly like the
principal ExceptionJC class, but inheriting from it.
(can you say templates for simpleminded C folks?)
*/

#ifdef _CXX_STD_EXCEPTIONS

#define BDeclExceptionJC(ae) \
class ae : public virtual ExceptionJC { \
public: \
ae(); \
ae(char *why); \
virtual ~ae(); \
virtual char *kind(); \
virtual char *why(); \
private: char *jwhat; \
}

#else

#define BDeclExceptionJC(ae) \
class ae : public virtual ExceptionJC { \
public: \
ae(); \
ae(char *why); \
virtual ~ae(); \
virtual char *kind(); \
virtual char *why(); \
virtual char *what() ; \
private: char *jwhat; \
}

#endif //_CXX_STD_EXCEPTIONS

// pick one of the following with -D_CXX_STD_EXCEPTIONS throughout build
#ifdef _CXX_STD_EXCEPTIONS
/** DO NOT USE */
class ExceptionJC : public exception { /// needed if you want what() 
#else
/** DO NOT USE */
class ExceptionJC {
#endif

public:

  /** the string this is called with is _copied_. It should be a
      literal or something you have stashed a pointer to so that
      you do not leak it in the throw call.
  */
  ExceptionJC(char *why) ;


  /** With no argument, the why string becomes the same as the kind string
      value.
   */
  ExceptionJC() ;

  /** duh. cleans up the internal copied string jwhat */
  virtual ~ExceptionJC() ;

  /** returns the name of the exception class a la typeinfo */
  virtual char *kind() ;

  /** returns the thrower defined message or kind if none specified on throw */
  virtual char *why() ;

#ifndef _CXX_STD_EXCEPTIONS
  /** returns the c++ stl defined what, if it exists, or why() if not */
  virtual char *what() ;
#endif

  /** verifies that casting worked */
  static void checkDynamicCast(void *p, char *fi, int line);

private:
  char *jwhat;

#ifdef _CXX_STD_EXCEPTIONS
// this ifdef to keep doc++ happy about {} count
};
#else
};
#endif

/** add as many exception classes as you want here, but don't forget
 to define their bodies in ExceptionJC.cc with EBODY() macros.
*/
BDeclExceptionJC(NullPointerExceptionJC);

BDeclExceptionJC(ClassNotFoundExceptionJC);

BDeclExceptionJC(ConnectionVetoExceptionJC);

BDeclExceptionJC(EOFExceptionJC);

BDeclExceptionJC(IllegalAccessExceptionJC);

BDeclExceptionJC(InstantiationExceptionJC);

BDeclExceptionJC(IOExceptionJC);

BDeclExceptionJC(RuntimeExceptionJC);

#define CHECKDC(p) ExceptionJC::checkDynamicCast(p,__FILE__,__LINE__)
/// macro for debugging, for application to return of a cast.

#endif //ExceptionJC_h_seen
#else
#
# error NO_NO_NO_NO_NO_
#errprint("m4: ExceptionJC.h seen: fatal error.")
#exit(1)
#endif
