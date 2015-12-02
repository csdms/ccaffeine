// ACL:license
// ----------------------------------------------------------------------
// This software and ancillary information (herein called "SOFTWARE")
// called SILOON is made available under the terms described here.  The
// SOFTWARE has been approved for release with associated LA-CC Number
// LA-CC-98-32.
// 
// Unless otherwise indicated, this SOFTWARE has been authored by an
// employee or employees of the University of California, operator of the
// Los Alamos National Laboratory under Contract No.  W-7405-ENG-36 with
// the U.S. Department of Energy.  The U.S. Government has rights to use,
// reproduce, and distribute this SOFTWARE, and to allow others to do so.
// The public may copy, distribute, prepare derivative works and publicly
// display this SOFTWARE without charge, provided that this Notice and
// any statement of authorship are reproduced on all copies.  Neither the
// Government nor the University makes any warranty, express or implied,
// or assumes any liability or responsibility for the use of this
// SOFTWARE.
// 
// If SOFTWARE is modified to produce derivative works, such modified
// SOFTWARE should be clearly marked, so as not to confuse it with the
// version available from LANL.  
// 
// For more information about SILOON, send e-mail to
// siloon-team@acl.lanl.gov, or visit the SILOON web page at
// http://www.acl.lanl.gov/siloon/.
// ----------------------------------------------------------------------
// ACL:license
//-----------------------------------------------------------------------------
// Buffer.C - Siloon implementation a data buffer class
//-----------------------------------------------------------------------------
// $Id: Buffer.cc,v 1.1 2002/01/15 18:54:04 rasmussn Exp $
//-----------------------------------------------------------------------------
#include "Buffer.h"
#include <stdio.h>		// needed with assert on Linux?
#include <assert.h>
#include <string.h>		// memcpy, ...
#ifndef _OLD_HEADER_
#include <iostream>
#endif

using namespace Siloon;

#define SIZEOF_LONG   ( sizeof(long) )
#define SIZEOF_DOUBLE ( sizeof(double) )
#define DEFAULT_BUF_SIZE 64

//
// inline code
//


//-----------------------------------------------------------------------------
// Returns padding necessary for word alignment.
//-----------------------------------------------------------------------------
static inline size_t padding(size_t size)
{
  size_t extra = size % sizeof(void*);
  return (extra == 0) ? 0 : sizeof(void*) - extra;
}


//-----------------------------------------------------------------------------
// Returns size of packed item.
//-----------------------------------------------------------------------------
template <class T>
static inline size_t packedSize(T t, size_t count = 1)
{
  return count*sizeof(T) + padding(count*sizeof(T));
}


//---- reallocIfNecessary -----------------------------------------------------
// Reallocs more memory if the current size won't be able to contain an element
// of the given size.
//-----------------------------------------------------------------------------
inline void LocalBuffer::reallocIfNecessary(size_t size)
{
  if (size + offset_ > size_) {
    assert(isGrowable_);
    size_ *= 2;
    if (size + offset_ > size_) size_ = size + offset_;
    buffer_ = (char*) realloc(buffer_, size_);
    assert(buffer_ != NULL);
  }
}


//---- copyToBuffer -----------------------------------------------------------
// Copies item into the buffer
//-----------------------------------------------------------------------------
template <class T> inline int LocalBuffer::copyToBuffer(const T& item)
{
  size_t pSize = packedSize(item);
  reallocIfNecessary(pSize);
  new (buffer_ + offset_) T(item);
  offset_ += pSize;
  return SILOON_SUCCESS;
}


//---- copyToBuffer -----------------------------------------------------------
// Copies data from the provided buffer into this buffer.  For a local
// buffer, just copy the pointer.
//
// data -- the data to copy
//-----------------------------------------------------------------------------
template <class T> inline int LocalBuffer::copyToBuffer(const T* data)
{
  size_t pSize = packedSize(data);
  reallocIfNecessary(pSize);
  new (buffer_ + offset_) const T*(data);
  offset_ += pSize;
  return SILOON_SUCCESS;
}


//---- copyFromBuffer ---------------------------------------------------------
// Copies from this buffer into the given buffer.
//
// item -- receives the data
//-----------------------------------------------------------------------------
template <class T> inline int LocalBuffer::copyFromBuffer(T& item)
{
  size_t pSize = packedSize(item);
  item = *(reinterpret_cast<T*>(buffer_ + offset_));
  offset_ += pSize;

  return SILOON_SUCCESS;
}


//---- arrayFromBuffer --------------------------------------------------------
// Copies properly typed pointer to array data within the buffer.  Returns
// the number of items in the array.
//
// data -- receives the array pointer
//-----------------------------------------------------------------------------
template <class T> inline size_t LocalBuffer::arrayFromBuffer(T* & data)
{
  size_t count;
  copyFromBuffer(count);
  data = reinterpret_cast<T*>(buffer_ + offset_);
  offset_ += packedSize(*data, count);
  return count;
}


//---- copyToBuffer -----------------------------------------------------------
// Copies data from the given buffer into this buffer.
//
// data -- the data to copy
// count -- the number of bytes to copy
//-----------------------------------------------------------------------------
inline int LocalBuffer::copyToBuffer(const void* data, size_t count)
{
  size_t pSize = count + padding(count);
  reallocIfNecessary(pSize);
  memcpy(buffer_ + offset_, data, count);
  offset_ += pSize;
  return SILOON_SUCCESS;
}


//---- copyFromBuffer ---------------------------------------------------------
// Copies from this buffer into the given buffer.
//
// data -- receives the data
// count -- the number of bytes to copy
//-----------------------------------------------------------------------------
inline void LocalBuffer::copyFromBuffer(void* data, size_t count)
{
  memcpy(data, buffer_ + offset_, count);
  offset_ += count + padding(count);
}


//---- Buffer -----------------------------------------------------------------
// Constructor.
//
// bufSize -- the size of the buffer to be allocated
// buffer -- a buffer to use rather than allocating one directly
// isGrowable -- the size of buffer can grow (realloc), if true
//-----------------------------------------------------------------------------
LocalBuffer::LocalBuffer(size_t bufSize, void* buffer, bool isGrowable)
{
  offset_ = 0;
  size_ = bufSize;
  isGrowable_ = isGrowable;

  if (size_ <= 0) size_ = DEFAULT_BUF_SIZE;

  if (buffer != NULL) {
    buffer_ = (char*) buffer;
    doOwnBuffer_ = false;
  } else {
    buffer_ = (char*) malloc(size_);
    doOwnBuffer_ = true;
  }
  assert (buffer_ != NULL);
}


//---- ~Buffer ----------------------------------------------------------------
// Destructor.
//-----------------------------------------------------------------------------
LocalBuffer::~LocalBuffer()
{
  if (buffer_ && doOwnBuffer_) {
    free(buffer_);
    buffer_ = NULL;
  }

  //
  // free character strings that have been allocated locally
  //
  for (vector<void*>::const_iterator it = freeList_.begin();
	it != freeList_.end();
	it++) {
    free(*it);
  }
}


//---- copyBuffer -------------------------------------------------------------
// Copies data from the given buffer into this buffer.
//
// buf  -- the buffer to copy from
// size -- the number of bytes to copy
//-----------------------------------------------------------------------------
void LocalBuffer::copyBuffer(const LocalBuffer& buf, size_t size)
{
  reallocIfNecessary(size);
  memcpy(buffer_ + offset_, buf.buffer_ + buf.offset_, size);
  offset_ += size;
}


//---- reset ------------------------------------------------------------------
// Resets data buffer so that it can be reused.  Data currently stored in the
// buffer will be overwritten.
//-----------------------------------------------------------------------------
void LocalBuffer::reset(void)
{
  offset_ = 0;
}


//---- setSize ----------------------------------------------------------------
// Sets the allocated size of the buffer to be at least the given amount.
//-----------------------------------------------------------------------------
void LocalBuffer::setSize(size_t size)
{
  reallocIfNecessary(size);
}


int LocalBuffer::sendGlobalCFunction(ContextID& target)
{
  return SiloonInvokeCFunction(*this, target);
}


int LocalBuffer::sendGlobalFFunction(ContextID& target)
{
  return SiloonInvokeFFunction(*this, target);
}

void LocalBuffer::addToFreeList(void* ptr)
{
  freeList_.push_back(ptr);
}


//
// packing routines
//

int LocalBuffer::pack(float item)
{
  return copyToBuffer(item);
}

int LocalBuffer::pack(double item)
{
  return copyToBuffer(item);
}

int LocalBuffer::pack(bool item)
{
  return copyToBuffer(item);
}

int LocalBuffer::pack(char item)
{
  return copyToBuffer(item);
}

int LocalBuffer::pack(unsigned char item)
{
  return copyToBuffer(item);
}

int LocalBuffer::pack(short item)
{
  return copyToBuffer(item);
}

int LocalBuffer::pack(unsigned short item)
{
  return copyToBuffer(item);
}

int LocalBuffer::pack(int item)
{
  return copyToBuffer(item);
}

int LocalBuffer::pack(unsigned int item)
{
  return copyToBuffer(item);
}

int LocalBuffer::pack(long item)
{
  return copyToBuffer(item);
}

int LocalBuffer::pack(unsigned long item)
{
  return copyToBuffer(item);
}

int LocalBuffer::pack(Siloon::ComplexFloat& item)
{
  return copyToBuffer(item);
}

int LocalBuffer::pack(Siloon::ComplexDouble& item)
{
  return copyToBuffer(item);
}

int LocalBuffer::pack(const float* data, size_t cnt)
{
  if (cnt == 1) return copyToBuffer(*data);
  else          return copyToBuffer(data, cnt*sizeof(*data));
}

int LocalBuffer::pack(const double* data, size_t cnt)
{
  if (cnt == 1) return copyToBuffer(*data);
  else          return copyToBuffer(data, cnt*sizeof(*data));
}

int LocalBuffer::pack(const bool* data, size_t cnt)
{
  if (cnt == 1) return copyToBuffer(*data);
  else          return copyToBuffer(data, cnt*sizeof(*data));
}

int LocalBuffer::pack(const char* data, size_t cnt)
{
  printf("pack(const char*) make sure this is correct.\n");
  pack(cnt);
  return copyToBuffer(data, cnt);
}

int LocalBuffer::pack(const unsigned char* data, size_t cnt)
{
  if (cnt == 1) return copyToBuffer(*data);
  else          return copyToBuffer(data, cnt*sizeof(*data));
}

int LocalBuffer::pack(const short* data, size_t cnt)
{
  if (cnt == 1) return copyToBuffer(*data);
  else          return copyToBuffer(data, cnt*sizeof(*data));
}

int LocalBuffer::pack(const unsigned short* data, size_t cnt)
{
  if (cnt == 1) return copyToBuffer(*data);
  else          return copyToBuffer(data, cnt*sizeof(*data));
}

int LocalBuffer::pack(const int* data, size_t cnt)
{
  if (cnt == 1) return copyToBuffer(*data);
  else          return copyToBuffer(data, cnt*sizeof(*data));
}

int LocalBuffer::pack(const unsigned int* data, size_t cnt)
{
  if (cnt == 1) return copyToBuffer(*data);
  else          return copyToBuffer(data, cnt*sizeof(*data));
}

int LocalBuffer::pack(const long* data, size_t cnt)
{
  if (cnt == 1) return copyToBuffer(*data);
  else          return copyToBuffer(data, cnt*sizeof(*data));
}

int LocalBuffer::pack(const unsigned long* data, size_t cnt)
{
  if (cnt == 1) return copyToBuffer(*data);
  else          return copyToBuffer(data, cnt*sizeof(*data));
}

// pack a C-style string
int LocalBuffer::packCString(const char* szVal)
{
   size_t count = 1 + strlen(szVal);
   pack(count);
   return copyToBuffer(szVal, count);
}

//-----------------------------------------------------------------------------
// Pack a C-style string as a ClientPointer array.
//-----------------------------------------------------------------------------
int LocalBuffer::packCString(const char* szVal, Type& ptrType)
{
   ClientPointer cp;
   cp.setType(ptrType);
   size_t count = 1 + strlen(szVal);
   cp.beginPackArray(*this, count);
   return copyToBuffer(szVal, count);
}

// pack an STL string
int LocalBuffer::pack(const string& str)
{
  return packCString(str.c_str());
}

// Pack a pointer type.  
int LocalBuffer::packPointer(const void* data, bool isNetPointer)
{
  return copyToBuffer<const void*>(data);
}

// Pack a long type.  
int LocalBuffer::packLong(long lVal, int subtype)
{
  switch(subtype) {
    case pdbItem::I_SCHAR:
    case pdbItem::I_CHAR:	pack( char(lVal) );		break;
    case pdbItem::I_UCHAR:      pack( (unsigned char) lVal );	break;
    case pdbItem::I_SHORT:      pack( short(lVal) );		break;
    case pdbItem::I_USHORT:     pack( (unsigned short) lVal );	break;
    case pdbItem::I_INT:	pack( int(lVal) );		break;
    case pdbItem::I_UINT:	pack( (unsigned int) lVal );	break;
    case pdbItem::I_LONG:	pack( lVal );			break;
    case pdbItem::I_ULONG:	pack( (unsigned long) lVal );	break;
    default:			return SILOON_FAILURE;
  }
  return SILOON_SUCCESS;
}

// Pack a double type.  
int LocalBuffer::packDouble(double rVal, int subtype)
{
  switch(subtype) {
    case pdbItem::FL_FLOAT:	pack( float(rVal) );		break;
    case pdbItem::FL_DBL:	pack( rVal );			break;
    default:			return SILOON_FAILURE;
  }
  return SILOON_SUCCESS;
}


//
// unpack routines
//
// Warning, notice the use of const here.  It is used to facilitate
// code generation for siloon_execute.  The parameters are treated as
// const in siloon_execute, but during the initialization process of
// the const data (while receiving/unpacking data), the constness
// is cast away.  In summary, data will be modified in the unpack
// routines, contrary to what is claimed by const.
// 

void LocalBuffer::unpack(const float* cdata, long count)
{
  for (int i = 0; i < count; i++) {
    copyFromBuffer( *(const_cast<float*>(cdata++)) );
  }
}

void LocalBuffer::unpack(const double* cdata, long count)
{
  for (int i = 0; i < count; i++) {
    copyFromBuffer( *(const_cast<double*>(cdata++)) );
  }
}

void LocalBuffer::unpack(const bool* cdata, long count)
{
  for (int i = 0; i < count; i++) {
    copyFromBuffer( *(const_cast<bool*>(cdata++)) );
  }
}

void LocalBuffer::unpack(const char* cdata, long count)
{
  for (int i = 0; i < count; i++) {
    copyFromBuffer( *(const_cast<char*>(cdata++)) );
  }
}

void LocalBuffer::unpack(const unsigned char* cdata, long count)
{
  for (int i = 0; i < count; i++) {
    copyFromBuffer( *(const_cast<unsigned char*>(cdata++)) );
  }
}

void LocalBuffer::unpack(const short* cdata, long count)
{
  for (int i = 0; i < count; i++) {
    copyFromBuffer( *(const_cast<short*>(cdata++)) );
  }
}

void LocalBuffer::unpack(const unsigned short* cdata, long count)
{
  for (int i = 0; i < count; i++) {
    copyFromBuffer( *(const_cast<unsigned short*>(cdata++)) );
  }
}

void LocalBuffer::unpack(const int* cdata, long count)
{
  for (int i = 0; i < count; i++) {
    copyFromBuffer( *(const_cast<int*>(cdata++)) );
  }
}

void LocalBuffer::unpack(const unsigned int* cdata, long count)
{
  for (int i = 0; i < count; i++) {
    copyFromBuffer( *(const_cast<unsigned int*>(cdata++)) );
  }
}

void LocalBuffer::unpack(const long* cdata, long count)
{
  for (int i = 0; i < count; i++) {
    copyFromBuffer( *(const_cast<long*>(cdata++)) );
  }
}

void LocalBuffer::unpack(const unsigned long* cdata, long count)
{
  for (int i = 0; i < count; i++) {
    copyFromBuffer( *(const_cast<unsigned long*>(cdata++)) );
  }
}


// unpack an STL string
void LocalBuffer::unpack(const string& cstr)
{
   string& str = const_cast<string&>(cstr);
   size_t count;
   unpack(&count);	// includes '\0'

   char* data = new char[count];
   copyFromBuffer(data, count);
   str = data;
   delete[] data;
}

//-----------------------------------------------------------------------------
// Unpack a C-style string.  This is a two step process.  If called with a
// count of 0, only returns the number of characters in C-String (+1).
// If called with count > 0, copies string to preallocated buffer cdata.
//-----------------------------------------------------------------------------
long LocalBuffer::unpackCString(char* data, long count)
{
   if (count == 0) {
      unpack(&count);
   } else if (count > 0) {
      copyFromBuffer(data, count);
   } else {
      count = -1;
   }
   return count;
}

// unpack a pointer type
void LocalBuffer::unpackPointer(void*& data, bool isNetPointer)
{
  unpackInPlace(data);  
}

// unpack a long type into a long
int LocalBuffer::unpackLong(long& lVal, int subtype)
{
  switch(subtype) {
    case pdbItem::I_SCHAR:
    case pdbItem::I_CHAR: {
      char val;
      unpack(&val);
      lVal = long(val);
      break;
    }
    case pdbItem::I_UCHAR: {
      unsigned char val;
      unpack(&val);
      lVal = long(val);
      break;
    }
    case pdbItem::I_SHORT: {
      short val;
      unpack(&val);
      lVal = long(val);
      break;
    }
    case pdbItem::I_USHORT: {
      unsigned short val;
      unpack(&val);
      lVal = long(val);
      break;
    }
    case pdbItem::I_INT: {
      int val;
      unpack(&val);
      lVal = long(val);
      break;
    }
    case pdbItem::I_UINT: {
      unsigned int val;
      unpack(&val);
      lVal = long(val);
      break;
    }
    case pdbItem::I_LONG:
    case pdbItem::I_ULONG: {
      unpack(&lVal);
      break;
    }
    default: return SILOON_FAILURE;
  }
  return SILOON_SUCCESS;
}

// unpack a float type into a double
int LocalBuffer::unpackDouble(double& rVal, int subtype)
{
  switch(subtype) {
    case pdbItem::FL_FLOAT: {
      float fResult;
      unpack(&fResult);
      rVal = double(fResult);
      break;
    }
    case pdbItem::FL_DBL: {
      unpack(&rVal);
      break;
    }
    default: return SILOON_FAILURE;
  }
  return SILOON_SUCCESS;
}

//
// The following routines don't actually unpack the value, they
// return a pointer to the data at the location within the buffer.
//

void LocalBuffer::unpackInPlace(float*& data)
{
  data = reinterpret_cast<float*>(buffer_ + offset_);
  offset_ += packedSize(*data);
}

void LocalBuffer::unpackInPlace(double*& data)
{
  data = reinterpret_cast<double*>(buffer_ + offset_);
  offset_ += packedSize(*data);
}

void LocalBuffer::unpackInPlace(bool*& data)
{
  data = reinterpret_cast<bool*>(buffer_ + offset_);
  offset_ += packedSize(*data);
}

void LocalBuffer::unpackInPlace(char*& data)
{
  data = reinterpret_cast<char*>(buffer_ + offset_);
  offset_ += packedSize(*data);
}

void LocalBuffer::unpackInPlace(unsigned char*& data)
{
  data = reinterpret_cast<unsigned char*>(buffer_ + offset_);
  offset_ += packedSize(*data);
}

void LocalBuffer::unpackInPlace(short*& data)
{
  data = reinterpret_cast<short*>(buffer_ + offset_);
  offset_ += packedSize(*data);
}

void LocalBuffer::unpackInPlace(unsigned short*& data)
{
  data = reinterpret_cast<unsigned short*>(buffer_ + offset_);
  offset_ += packedSize(*data);
}

void LocalBuffer::unpackInPlace(int*& data)
{
  data = reinterpret_cast<int*>(buffer_ + offset_);
  offset_ += packedSize(*data);
}

void LocalBuffer::unpackInPlace(unsigned int*& data)
{
  data = reinterpret_cast<unsigned int*>(buffer_ + offset_);
  offset_ += packedSize(*data);
}

void LocalBuffer::unpackInPlace(long*& data)
{
  data = reinterpret_cast<long*>(buffer_ + offset_);
  offset_ += packedSize(*data);
}

void LocalBuffer::unpackInPlace(unsigned long*& data)
{
  data = reinterpret_cast<unsigned long*>(buffer_ + offset_);
  offset_ += packedSize(*data);
}

void LocalBuffer::unpackInPlace(Siloon::ComplexFloat*& data)
{
  data = reinterpret_cast<Siloon::ComplexFloat*>(buffer_ + offset_);
  offset_ += packedSize(*data);
}

void LocalBuffer::unpackInPlace(Siloon::ComplexDouble*& data)
{
  data = reinterpret_cast<Siloon::ComplexDouble*>(buffer_ + offset_);
  offset_ += packedSize(*data);
}

void LocalBuffer::unpackInPlace(void*& data)
{
  data = * reinterpret_cast<void**>(buffer_ + offset_);
  offset_ += packedSize(data);
}

size_t LocalBuffer::unpackArrayInPlace(float*& data)
{  
  return arrayFromBuffer(data);
}

size_t LocalBuffer::unpackArrayInPlace(double*& data)
{  
  return arrayFromBuffer(data);
}

size_t LocalBuffer::unpackArrayInPlace(bool*& data)
{  
  return arrayFromBuffer(data);
}

size_t LocalBuffer::unpackArrayInPlace(char*& data)
{  
  return arrayFromBuffer(data);
}

size_t LocalBuffer::unpackArrayInPlace(unsigned char*& data)
{  
  return arrayFromBuffer(data);
}

size_t LocalBuffer::unpackArrayInPlace(short*& data)
{  
  return arrayFromBuffer(data);
}

size_t LocalBuffer::unpackArrayInPlace(unsigned short*& data)
{  
  return arrayFromBuffer(data);
}

size_t LocalBuffer::unpackArrayInPlace(int*& data)
{  
  return arrayFromBuffer(data);
}

size_t LocalBuffer::unpackArrayInPlace(unsigned int*& data)
{  
  return arrayFromBuffer(data);
}

size_t LocalBuffer::unpackArrayInPlace(long*& data)
{  
  return arrayFromBuffer(data);
}

size_t LocalBuffer::unpackArrayInPlace(unsigned long*& data)
{  
  return arrayFromBuffer(data);
}
