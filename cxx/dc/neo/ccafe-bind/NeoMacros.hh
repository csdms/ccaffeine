#ifndef NeoMacros_hh_seen
#define NeoMacros_hh_seen

#ifndef CCAFE_AUDIT
#include "util/IO.h"
#endif


// Hints:
// Remember: when using try/catch, do not declare variables
// inside the try block that are used after the try/catch is done.

//--------------------------------------------------------
/** convert a neo tm named nm to a newly declared opq tm named om
 as efficiently as possible.
 side effects. define a bool variable ok.
 */
#define N2OMAP(nm,om) \
	::ccafeopq::TypeMap_shared om; \
	bool ok; \
	om = ccafe::TypeMap::unWrap(nm, ok); \
	if (!ok) om = NeoOpaqueTypeMap::opaqueWrap(nm)
	
//--------------------------------------------------------
/** throw an exception instance named ex with type t
 * and message m. also print message m if debug enabled. 
 */
#define NEO_THROW(ex,t,m) \
	neo::cca::Exception ex( t, m); \
	IO_en1(m); \
	throw ex;

//--------------------------------------------------------
	
/** wrap an opq exception in the neo cloud.  
   */
#define NEO_RETHROW  \
	catch ( ccafeopq::TypeMismatchException &e) \
{ \
  /* convert */ \
  neo::cca::TypeMismatchException ex( \
      NeoHelper::neoType(e.getRequestedType()), \
      NeoHelper::neoType(e.getActualType()),  \
      e.getMessage() \
  ); \
  string egetmessage =  e.getMessage(); \
  IO_en2("Exception: %s", egetmessage.c_str()); \
  throw ex; \
}  \
catch ( ::ccafeopq::Exception& e2) \
{ \
  neo::cca::Exception ex( \
	NeoHelper::neoExceptionType(e2.getType()), \
	e2.getMessage() \
  ); \
  string e2getmessage =  e2.getMessage(); \
  IO_en2("Exception: %s", e2getmessage.c_str()); \
  throw ex; \
} do {} while(0)

//--------------------------------------------------------
/** wrap an opq exception in the neo cloud
  after prefixing the string message with s, where
 s is a string literal or string. 
   */
#define NEO_RETHROW_PREPEND(s)  \
catch ( ccafeopq::TypeMismatchException &e) \
{ \
  /* convert */ \
  std::string newmsg = s; \
  newmsg += e.getMessage(); \
  neo::cca::TypeMismatchException ex( \
      NeoHelper::neoType(e.getRequestedType()), \
      NeoHelper::neoType(e.getActualType()),  \
      newmsg \
  ); \
  IO_en2("Exception: %s", newmsg.c_str()); \
  throw ex; \
}  \
catch ( ::ccafeopq::Exception& e2) \
{ \
  std::string newmsg2 = s; \
  newmsg2 += e2.getMessage(); \
  neo::cca::Exception ex( \
	NeoHelper::neoExceptionType(e2.getType()), \
	newmsg2 \
  ); \
  IO_en2("Exception: %s", newmsg2.c_str()); \
  throw ex; \
} do {} while(0)


#endif // NeoMacros_hh_seen
