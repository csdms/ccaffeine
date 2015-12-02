#ifndef object_h_seen
#define object_h_seen

#ifndef ENDSEMI
#ifdef __GNU_C__
#define ENDSEMI ;
#else
#define ENDSEMI
#endif
#endif

namespace jcpp {

#ifndef NULL
/** We geezer C coders still like this one. */
#define NULL 0
#endif

#ifndef null
/** We java coders still like this one. */
#define null 0
#endif

#ifdef __GNUC__
#define boolean bool
#endif

#ifndef boolean
/** we need a configure header to handle this one. */
#ifndef HAVE_BOOLEAN
#define boolean bool
#else
#define boolean char
#endif
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef true
#ifndef HAVE_BOOLEAN
#define true 1
#endif
#endif

#ifndef false
#ifndef HAVE_BOOLEAN
#define false 0
#endif
#endif

#ifndef FALSE
#define FALSE 0
#endif

/** SYNCHRONIZED notes methods that are not thread safe in C++
without the addition of mutex calls.
DON'T use this macro.
 */
#define SYNCHRONIZED kill_me_now_synchronized




/** Root of all objects stored in our java container classes,
 * except char * strings which the containers make a special case
 * of deliberately. This is so that void * doesn't bite us in
 * containers. CCAFFEINE also uses such a class for the same problem;
 * we define it compatibly. Our containers do not assume object
 * countability. 
 * <p>For now, ignore CCA Object compatibility -- want jc++ to live
 * in a different namespace.</p>
 * <p>castable void *. </p>
 * <p>Do NOT try to get cute and add refcounting or anything
 * to this class. Inherit from it if you want to do that.</p>
*/
class Object  {
public:
	virtual ~Object(){}
};


/** global functions for whining. */
class BadCastMessage {
  /** verifies that casting worked. exits with prejudice if not. */
public:
  static void checkDynamicCast(void *p, char *fi, int line);
  static void checkDynamicCastMessage(void *p, char *fi, int line, char *mess);
};
/** macro for debugging return of a cast. */
#define CHECKDC(p) jcpp::BadCastMessage::checkDynamicCast(p,(char *)__FILE__,__LINE__)

/** macro for debugging return of a cast. */
#define CHECKDCM(p,m) jcpp::BadCastMessage::checkDynamicCastMessage(p,__FILE__,__LINE__,m)

#ifndef CFREE
/** Since java garbage collects and c++ doesn't, define markers for
pointer returns and pointer filling operations in c++ where the
caller is is responsible for calling free() or delete. Note the
brokenness c++ has for arrays requiring "delete [] ary" and therefore
avoid returning pointers to new-ed arrays.

// CCA does the same thing.
Any pointer returned but not marked in the header as one of these may be
safely dropped on the floor.
*/
#define CFREE
#define CDELETE
#endif


// #include "jc++/lang/ExceptionJC.h"
// make throws clause go away, which is mainly because c++ exceptions
// are an ugly mess though we still want to see javalike headers.
#define throws(a) kill_me_now_throws

} ENDSEMI // jcpp
#endif
