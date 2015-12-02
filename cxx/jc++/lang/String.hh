#ifndef StringClass_seen
#define StringClass_seen

namespace jcpp {

/**
   $Author: baallan $
   Created : <2000-08-10 13:35:45 pippin>
   Last modified Time-stamp: <2000-08-10 13:35:58 pippin> 

   Life is much simpler with a string class around
   BUGBUG - should use the StringBuffer class as its buffer implementation...
 */

#include <string.h>

class StringJC : public virtual HashKey {
private:
  int buffer_size;
  char* buffer_ptr;
  char orig_buffer[64];
  void resize(int size); 
public:
  StringJC();
  StringJC(const char* str);
  virtual ~StringJC();

  void setString(const char* str);

  /** equivalence test */
  virtual boolean equals(Object* obj); 

  /** calc-ed using: s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]*/
  virtual int hashValue();

  void append(const char* str);
  

  char* getBuffer() { return buffer_ptr; };


  boolean startsWith(const char *needle) {
   return (::strstr(buffer_ptr,needle) == buffer_ptr);
  }

  int indexOf(const char *needle);

  void appendSubstring(const char* srcString, int begin, int end = 0);
  int length () { return ::strlen(buffer_ptr); }
/*

  this is just a list of some java methods I didn't need and therefore 
  didn't implement

  int indexOf(char c) ;

  int indexOf(char c, int r) ;

  int lastIndexOf(char c) ;

  int compareTo(const char *s2) ;

  int compareToIgnoreCase(const char *s2);

  CDELETE StringJC* toLowerCase();

  CFREE char *strdup();
*/
};

} ENDSEMI //jcpp

#endif //String_seen
