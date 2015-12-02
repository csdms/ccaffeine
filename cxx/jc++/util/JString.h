#ifndef JString_h_seen
#define JString_h_seen

//#include "jc++/jc++.h"


/** A java string class replacement for c++ without strings
 as objects. e.g. java
  s.startsWith(needle); 
 is in c++
 JString::startsWith(s,needle);
 For now we are only implementing the functions needed, as the
 real java class is full of cruft.
 This class is deliberately out of jcpp::. As it is all static,
 jcpp is redundant with JString.

 @see java's String.
*/
class JString {

public:

	static boolean startsWith(char *haystack, char *needle) ;

	static int indexOf(char *haystack, char *needle) ;

	static int indexOf(char *s, char c) ;

	static int indexOf(char *s, char c, int r) ;

	static int lastIndexOf(char *s, char c) ;

	static int compareTo(const char *s1, const char *s2);

	static int compareToIgnoreCase(const char *s1, const char *s2);

	CFREE static char *toLowerCase(const char *s);

	CFREE static char *strdup(const char *s);
};
#ifndef STRDUP
/** the following is likely equivalent to any other STRDUP.*/
#define STRDUP(s) JString::strdup((char *)(s))
#endif

#endif // JString_h_seen
