#ifndef StringBuffer_h_seen
#define StringBuffer_h_seen

namespace jcpp {


/* STRING_OVERFLOW marks functions which may overflow an array  provided
by the user if that array is not large enough.
*/
#define STRING_OVERFLOW

/** See java's string buffer, tcls DString, etc */
class StringBuffer : public virtual Object {

private:

    char *buffer;
    /** scratch for macros */
    int tmp; 
    /** does not include \0 terminator */
    int used; 
    int buffer_length;
    static const int SPARECAPACITY;

    int checkIndex(int index); // return -1 if bogus index. 0 else.
    void newdata(int l);

public:

    CDELETE StringBuffer() ;
    ~StringBuffer() ;

    CDELETE StringBuffer(char *str);

    CDELETE StringBuffer(int length);

    /** Note on all append/insert functions: the StringBuffer returned
    is the same as the one called.
    */
    /** Note, because there are no methods on c++ objects (void *)s
       we can't call toString on Object. so printed form is a pointer. */
    StringBuffer *append(Object *obj) ;

    StringBuffer *append ( char *str ) ;
    StringBuffer *append ( std::string str ) ;
    /** len is the number of characters appended, not counting
       the null character at the end of str. Note that str does
       NOT have to be null terminated at len+1.
    */
    StringBuffer *append ( char *str, int len ) ;

    /** append the stringified int value. */
    StringBuffer *append(int i);

#ifdef HAVE_BOOLEAN
    /** depends on c++ compiler. get duplicate symbol with append(int or char) if wrong. */
    StringBuffer *append(bool b);
#endif

    /** append a raw character. */
    StringBuffer *append(char c);

    /** the real workhorse of this class. */
    StringBuffer *append ( char *str, int offset, int len ) ;
    
    /** append double as %21.18g */
    StringBuffer *append(double d);

    /** append cast to double as %21.18g */
    StringBuffer *append(float f);

    /** append as %ld */
    StringBuffer *append(long l);

    /** return the total size allocated for the string so far. */
    int capacity();

    /** return s[index]th character. if bad index, err -> -1, else 0. */
    char charAt(int index, int & error);

    void ensureCapacity ( int minimumCapacity );

    STRING_OVERFLOW void getChars(int srcBegin, int srcEnd, char *dst, int dstBegin, int & rangeError);
      /// see java.

    StringBuffer *insert(int offset, Object *obj, int & offsetError);
      /// see java.

    StringBuffer *insert(int offset, char c, int & offsetError);
      /// see java.

    StringBuffer *insert(int offset, char *str, int & offsetError);
      /// see java.

    StringBuffer *insert(int offset, double d, int & offsetError);
      /// see java.

    StringBuffer *insert(int offset, float f, int & offsetError);
      /// see java.

#ifdef HAVE_BOOLEAN
    StringBuffer *insert(int offset, bool b, int & offsetError);
      /// insert(int) conflict not HAVE_BOOLEAN
#endif

    StringBuffer *insert(int offset, int i, int & offsetError);
      /// see java.

    StringBuffer *insert(int offset, long l, int & offsetError);
      /// see java.

    /** returns the current length (via strlen) **/
    int length();

    StringBuffer *reverse();

    void setCharAt(int index, char ch, int &err);

    void setLength(int newLength, int & StringIndexOutOfBoundsErrJC) ;

    /** Caller should free the pointer returned. Copies value into null terminated string. */
    CFREE char *toString() ;

};

} ENDSEMI //jcpp
#endif // StringBuffer_h_seen
