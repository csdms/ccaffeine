// #include <typeinfo>
#include <string>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/JString.h"
#include "jc++/util/Enumeration.h"
#include "jc++/util/StringEnumeration.h"
#include "jc++/util/HashEnum.h"
#include "jc++/util/StringHashEnum.h"
#include "jc++/util/StringHashBucket.h"
#include "jc++/util/ResourceBucket.h"
#include "jc++/util/StringHash.h"
#include <string>
#include "jc++/util/StringBuffer.h"

#include "util/IO.h"
#include "util/freefree.h"

#ifndef lint
static char id[]="$Id: StringBuffer.cc,v 1.10 2003/09/02 23:20:41 baallan Exp $"; // RCS string
#endif

const int jcpp::StringBuffer::SPARECAPACITY = 16;

int jcpp::StringBuffer::checkIndex(int index)
{
    if (index < 0 || index >= used) {
        IO::en("StringBuffer::checkIndex range error.");
        return -1;
    }
    return 0;
}

// only works in StringBuffer scope. s is a char *, l is a length,
// including the ending NULL.
#define NEWSTRING(s,l) tmp=(l); (s)=(char *)malloc(tmp); assert(s != NULL)
// likewise for buffer, but set the object properties, too.
#define NEWSB(l) newdata(l)

void jcpp::StringBuffer::newdata(int l) {
    buffer_length=l;
    buffer=(char *)calloc(buffer_length,1);
    assert(buffer != NULL);
}


CDELETE jcpp::StringBuffer::StringBuffer() {
    NEWSB(SPARECAPACITY+1);
    used = 0;
}

jcpp::StringBuffer::~StringBuffer() {
  free(buffer);
  buffer = 0;
  tmp = -1;
    /** does not include \0 terminator */
  used = -2;
  buffer_length =-3;

}

CDELETE jcpp::StringBuffer::StringBuffer(char *str)
{
    if ( str == null) {
        str = (char *)"NULL";
    }
    used   = strlen(str);
    NEWSB(used+SPARECAPACITY);
    sprintf(buffer,"%s",str);
}

// unlike java, 0 is not an acceptable length.
CDELETE jcpp::StringBuffer::StringBuffer(int length_)
{
    if (length_<=0) {
        length_ = 20;
    }
    NEWSB(length_+1);
    used = 0;
}

// note, because there are no mandatory methods on cca objects
// we can't call toString here.
jcpp::StringBuffer *jcpp::StringBuffer::append(Object *obj) {
    char val[40];
    sprintf(val,"(Object *)0x%p {",obj);
    append(val);
#ifdef HAVE_TYPEINFO
    append( const_cast<char *>(typeid(obj).name()));
#else
    append((char *)"NO_TYPEINFO");
#endif
    return append((char *)"}",1);
}

jcpp::StringBuffer *jcpp::StringBuffer::append ( char *str ) {
    if (str == null) {
        return this;
    }
    return (append( str, 0, strlen(str)));
}
jcpp::StringBuffer *jcpp::StringBuffer::append ( std::string str ) {
    if (str.size() == 0) {
        return this;
    }
    char * strx = (char*)str.c_str();
    return (append( strx, 0, strlen(strx)));
}

jcpp::StringBuffer *jcpp::StringBuffer::append ( char *str, int len ) {
    if (str == null) {
        return this;
    }
    return (append( str, 0, len));
}

jcpp::StringBuffer *jcpp::StringBuffer::append(int i)
{
    char val[40];
    sprintf(val,"%d",i);
    return append(val);
}

#ifdef HAVE_BOOLEAN
jcpp::StringBuffer *jcpp::StringBuffer::append(bool b)
{
	if (b) { return append("true"); }
	return append("false");
}
#endif

jcpp::StringBuffer *jcpp::StringBuffer::append(char c)
{
    if ( used + 1 > buffer_length ) {
        ensureCapacity(used+SPARECAPACITY);
    }
    buffer[used++] = c;

    return (this);
}


jcpp::StringBuffer *jcpp::StringBuffer::append ( char *str, int offset, int len ) {

   
    ensureCapacity(used+len+1);


    strncpy(&buffer[used], &str[offset], len);
    used += len;
    buffer[used]='\0';

    return this;
}

jcpp::StringBuffer *jcpp::StringBuffer::append(double d)
{
    char val[40];
    sprintf(val,"%g",d);
    return append(val);
}

jcpp::StringBuffer *jcpp::StringBuffer::append(float f)
{
    char val[40];
    sprintf(val,"%21.18g",(double)f);
    return append(val);
}

jcpp::StringBuffer *jcpp::StringBuffer::append(long l)
{
    char val[40];
    sprintf(val,"%ld",l);
    return append(val);
}

int jcpp::StringBuffer::capacity()
{
    return buffer_length;
}

char jcpp::StringBuffer::charAt(int index,int &err)
{
    if (checkIndex(index)) { err = -1; return 0;};
    err = 0;
    return buffer[index];
}

void jcpp::StringBuffer::ensureCapacity ( int minimumCapacity ) {
    int    n;
    char *oldBuffer;

    if ( (minimumCapacity < 0) || (buffer_length > minimumCapacity) ) {
        return; 
    }

    n = buffer_length*2;
    if ( minimumCapacity > n ) {
        n = minimumCapacity;
    }

    oldBuffer = buffer;
    NEWSB(n);

    strncpy(buffer, oldBuffer, used+1);
    free(oldBuffer);
}

STRING_OVERFLOW void jcpp::StringBuffer::getChars(int srcBegin, int srcEnd, char *dst, int dstBegin, int & err)
    {
    if (checkIndex(srcBegin)) { err = -1; return; }
    err = 0;
    if (checkIndex(srcEnd-1)) { err = -1; return; }
    err = 0;
    strncpy(&(dst[dstBegin]), &(buffer[srcBegin]), srcEnd-srcBegin);
}

jcpp::StringBuffer *jcpp::StringBuffer::insert(int offset, Object *obj, int &err)
{
    char val[40];
    if (checkIndex(offset)) { err = -1; return this; }
    err = 0;
    insert(offset,'}',err);
#ifdef HAVE_TYPEINFO
    insert(offset, const_cast<char *>(typeid(obj).name()),err);
#else
    insert(offset, const_cast<char *>("NO_TYPEINFO"),err);
#endif
    sprintf(val,"(Object *)0x%p {",obj);
    return insert(offset, val,err);
}

jcpp::StringBuffer *jcpp::StringBuffer::insert(int offset, char c,int &err)
{
    char s[2];
    s[0]=c;
    s[1]='\0';
    return insert(offset, s,err);
}

jcpp::StringBuffer *jcpp::StringBuffer::insert(int offset, char *str, int & err)
{
    if ((offset < 0) || (offset > used)) {
        err = -1;
        return this;
    }
    err = 0;
    if ( str == 0) {
        str = (char *)"NULL";
    }

    int added;
    added = strlen(str);

    ensureCapacity(used + added+1);

    // Copy buffer up to make space. probably off by one.
    for (int i=used + added; i>offset+added; i--) {
        buffer[i]=buffer[i-added];
    }

    /* Now, copy insert into place */
    strncpy(&(buffer[offset]), str, added);

    /* Update used count */
    used += added;

    return (this);
}

jcpp::StringBuffer *jcpp::StringBuffer::insert(int offset, double d, int &err)
{
    char val[40];
    sprintf(val,"%21.18g",d);
    return insert(offset, val,err);
}

jcpp::StringBuffer *jcpp::StringBuffer::insert(int offset, float f, int &err)
{
    char val[40];
    sprintf(val,"%21.18g",(double)f);
    return insert(offset, val,err);
}

#ifdef HAVE_BOOLEAN
jcpp::StringBuffer *jcpp::StringBuffer::insert(int offset, bool b, int &err)
{
    return insert(offset, (b)?"true":"false", err);
}
#endif

jcpp::StringBuffer *jcpp::StringBuffer::insert(int offset, int i, int &err)
{
    char val[40];
    sprintf(val,"%d",i);
    return insert(offset, val,err);
}

jcpp::StringBuffer *jcpp::StringBuffer::insert(int offset, long l, int &err)
{
    char val[40];
    sprintf(val,"%ld",l);
    return insert(offset, val,err);
}

int jcpp::StringBuffer::length()
{
    return used;
}

jcpp::StringBuffer *jcpp::StringBuffer::reverse()
{
    for (int pos = used/2 - 1; pos >= 0; pos--) {
        char ch = buffer[pos];
        buffer[pos] = buffer[used-pos-1];
        buffer[used-pos-1] = ch;
    }
    return (this);
}

void jcpp::StringBuffer::setCharAt(int index, char ch, int &err)
{
    if (checkIndex(index)) { err = -1; return; }
    buffer[index]=ch;
}

void jcpp::StringBuffer::setLength(int newLength, int & err) {
    if (newLength < 0) {
        err = -1;
        IO::en("StringIndexOutOfBoundsExceptionJC");
        return;
    }
    err = 0;
    if (newLength > used) {
        /* buffer expands */
        if (newLength > buffer_length) {
            /* Need new buffer */
            char *oldBuffer = buffer;
            oldBuffer[used]='\0';
            NEWSB(newLength);
            sprintf(buffer,"%s",oldBuffer);
            free(oldBuffer);
        }
        else {
            /* Pad buffer */
            for (int pos = used; pos < newLength; pos++) {
                buffer[pos] = '\0';
            }
        }
    }
    used = newLength;
}

CFREE char *jcpp::StringBuffer::toString() {
    buffer[used]='\0'; //ensure termination.
    return STRDUP(buffer);
}

