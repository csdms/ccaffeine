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
#ifndef _SILOON_BUFFER_H_
#define _SILOON_BUFFER_H_

#include <stdlib.h>
#include <string>
#include <siloon.h>
#include <Pointer.h>
#include <Complex.h>

using namespace std;
namespace Siloon {

//
// Abstract interface for the Buffer class.  This class is used to store
// parameters as they are passed between the Siloon client and the server.
// Concrete subclasses are LocalBuffer and JBuffer.  The LocalBuffer
// can be used only within the same address space while the JBuffer
// can be used across the network (uses Java to marshall and transport
// data).
//

class Buffer {

public:

  //#--------------------------------------------------------------------------
  // Constructs a Buffer.
  // <ul>
  // <li><b>size</b> -- the size of the buffer to create (in bytes)
  // </ul>
  //#--------------------------------------------------------------------------
  Buffer(void)			{ }
  Buffer(size_t)		{ }

  //#--------------------------------------------------------------------------
  // Destructor.  Frees any memory that was allocated for the buffer.
  //#--------------------------------------------------------------------------
  virtual ~Buffer(void)		{ }

  virtual void reset(void) = 0;
  virtual size_t size(void) const = 0;
  virtual int sendGlobalCFunction(ContextID& target) = 0;
  virtual int sendGlobalFFunction(ContextID& target) = 0;
  virtual void openIStream(void) = 0;
  virtual void addToFreeList(void* ptr) = 0;

  //#--------------------------------------------------------------------------
  // These methods pack (marshall) data into the buffer.  They all take a
  // const pointer to a block of data with an optional count for the number
  // of objects to copy.
  // <ul>
  // <li><b>data</b> -- pointer to data to copy into the buffer
  // </ul>
  //#--------------------------------------------------------------------------
  // <group>
  virtual int pack(float item) = 0;
  virtual int pack(double item) = 0;
  virtual int pack(bool item) = 0;
  virtual int pack(char item) = 0;
  virtual int pack(unsigned char item) = 0;
  virtual int pack(short item) = 0;
  virtual int pack(unsigned short item) = 0;
  virtual int pack(int item) = 0;
  virtual int pack(unsigned int item) = 0;
  virtual int pack(long item) = 0;
  virtual int pack(unsigned long item) = 0;
  virtual int pack(ComplexFloat& item) = 0;
  virtual int pack(Siloon::ComplexDouble& item) = 0;
  virtual int pack(const float* data, size_t cnt=1) = 0;
  virtual int pack(const double* data, size_t cnt=1) = 0;
  virtual int pack(const bool* data, size_t cnt=1) = 0;
  virtual int pack(const char* data, size_t cnt=1) = 0;
  virtual int pack(const unsigned char* data, size_t cnt=1) = 0;
  virtual int pack(const short* data, size_t cnt=1) = 0;
  virtual int pack(const unsigned short* data, size_t cnt=1) = 0;
  virtual int pack(const int* data, size_t cnt=1) = 0;
  virtual int pack(const unsigned int* data, size_t cnt=1) = 0;
  virtual int pack(const long* data, size_t cnt=1) = 0;
  virtual int pack(const unsigned long* data, size_t cnt=1) = 0;
  virtual int pack(const string& str) = 0;	  // pack an STL string
  virtual int packCString(const char* data) = 0;  // pack a C-style string
  virtual int packCString(const char* szVal, Type& ptrType) = 0;
  virtual int packPointer(const void* data, bool isNetPointer = false) = 0;
  virtual int packLong(long item, int subtype) = 0;
  virtual int packDouble(double item, int subtype) = 0;
  // </group>

  //#--------------------------------------------------------------------------
  // These methods unpack (unmarshall) data from the buffer.  They all take a
  // pointer to a block of data with an optional count for the number of
  // objects to copy from the buffer.
  // <ul>
  // <li><b>data</b> -- on output, receives the objects from the buffer
  // <li><b>count</b> -- the number of objects to copy
  // </ul>
  //#--------------------------------------------------------------------------
  // <group>

  // 
  // Warning, notice the use of const here.  It is used to facilitate
  // code generation for siloon_execute.  The parameters are treated as
  // const in siloon_execute, but during the initialization process of
  // the const data (while receiving/unpacking data), the constness
  // is cast away.  In summary, data will be modified in the unpack
  // routines, contrary to what is claimed by const.
  // 
  virtual void unpack(const float* data, long cnt = 1) = 0;
  virtual void unpack(const double* data, long cnt = 1) = 0;
  virtual void unpack(const bool* data, long cnt = 1) = 0;
  virtual void unpack(const char* data, long cnt = 1) = 0;
  virtual void unpack(const unsigned char* data, long cnt = 1) = 0;
  virtual void unpack(const short* data, long cnt = 1) = 0;
  virtual void unpack(const unsigned short* data, long cnt = 1) = 0;
  virtual void unpack(const int* data, long cnt = 1) = 0;
  virtual void unpack(const unsigned int* data, long cnt = 1) = 0;
  virtual void unpack(const long* data, long cnt = 1) = 0;
  virtual void unpack(const unsigned long* data, long cnt = 1) = 0;
  virtual void unpack(const string& str) = 0;	// unpack an STL string
  virtual long unpackCString(char* data, long count) = 0;  // unpack C-String
  virtual void unpackPointer(void*& data, bool isNetPointer = false) = 0;
  virtual int unpackLong(long& item, int subtype) = 0;
  virtual int unpackDouble(double& item, int subtype) = 0;

  virtual void unpackInPlace(float*& data) = 0;
  virtual void unpackInPlace(double*& data) = 0;
  virtual void unpackInPlace(bool*& data) = 0;
  virtual void unpackInPlace(char*& data) = 0;
  virtual void unpackInPlace(unsigned char*& data) = 0;
  virtual void unpackInPlace(short*& data) = 0;
  virtual void unpackInPlace(unsigned short*& data) = 0;
  virtual void unpackInPlace(int*& data) = 0;
  virtual void unpackInPlace(unsigned int*& data) = 0;
  virtual void unpackInPlace(long*& data) = 0;
  virtual void unpackInPlace(unsigned long*& data) = 0;
  virtual void unpackInPlace(Siloon::ComplexFloat*& data) = 0;
  virtual void unpackInPlace(Siloon::ComplexDouble*& data) = 0;
  virtual void unpackInPlace(void*& data) = 0;

  virtual size_t unpackArrayInPlace(float*& data) = 0;
  virtual size_t unpackArrayInPlace(double*& data) = 0;
  virtual size_t unpackArrayInPlace(bool*& data) = 0;
  virtual size_t unpackArrayInPlace(char*& data) = 0;
  virtual size_t unpackArrayInPlace(unsigned char*& data) = 0;
  virtual size_t unpackArrayInPlace(short*& data) = 0;
  virtual size_t unpackArrayInPlace(unsigned short*& data) = 0;
  virtual size_t unpackArrayInPlace(int*& data) = 0;
  virtual size_t unpackArrayInPlace(unsigned int*& data) = 0;
  virtual size_t unpackArrayInPlace(long*& data) = 0;
  virtual size_t unpackArrayInPlace(unsigned long*& data) = 0;
  // </group>
};


//#----------------------------------------------------------------------------
// Class LocalBuffer.  Marshalls data into a buffer.  Must remain local to
// an address space as the marshalling is not done in a way which is
// independent of machine architecture.
//#----------------------------------------------------------------------------

class LocalBuffer : public Buffer {

public:

  //#--------------------------------------------------------------------------
  // Constructs a Buffer.
  // <ul>
  // <li><b>size</b> -- the size of the buffer to create (in bytes)
  // <li><b>buffer</b> -- use this buffer for storage, if not NULL
  // <li><b>isGrowable</b> -- the size of buffer can grow (realloc), if true
  // </ul>
  //#--------------------------------------------------------------------------
  LocalBuffer(size_t size = 0, void* buffer = NULL, bool isGrowable = true);

  virtual ~LocalBuffer(void);

  void   copyBuffer(const LocalBuffer& buf, size_t size);
  void   reset(void);
  void   openIStream(void)			{ offset_ = 0; }
  void   setSize(size_t size);
  size_t size(void) const			{ return size_; }
  size_t currentSize(void) const		{ return offset_; }
  const void* buffer(void) const		{ return (void*) buffer_; }

  virtual int sendGlobalCFunction(ContextID& target);
  virtual int sendGlobalFFunction(ContextID& target);

  virtual void addToFreeList(void* ptr);

  virtual int pack(float item);
  virtual int pack(double item);
  virtual int pack(bool item);
  virtual int pack(char item);
  virtual int pack(unsigned char item);
  virtual int pack(short item);
  virtual int pack(unsigned short item);
  virtual int pack(int item);
  virtual int pack(unsigned int item);
  virtual int pack(long item);
  virtual int pack(unsigned long item);
  virtual int pack(Siloon::ComplexFloat& item);
  virtual int pack(Siloon::ComplexDouble& item);
  virtual int pack(const float* data, size_t cnt=1);
  virtual int pack(const double* data, size_t cnt=1);
  virtual int pack(const bool* data, size_t cnt=1);
  virtual int pack(const char* data, size_t cnt=1);
  virtual int pack(const unsigned char* data, size_t cnt=1);
  virtual int pack(const short* data, size_t cnt=1);
  virtual int pack(const unsigned short* data, size_t cnt=1);
  virtual int pack(const int* data, size_t cnt=1);
  virtual int pack(const unsigned int* data, size_t cnt=1);
  virtual int pack(const long* data, size_t cnt=1);
  virtual int pack(const unsigned long* data, size_t cnt=1);
  virtual int pack(const string& str);		// pack an STL string
  virtual int packCString(const char* data);	// pack a C-style string
  virtual int packCString(const char* szVal, Type& ptrType);
  virtual int packPointer(const void* data, bool isNetPointer = false);
  virtual int packLong(long item, int subtype);
  virtual int packDouble(double item, int subtype);

  virtual void unpack(const float* data, long cnt = 1);
  virtual void unpack(const double* data, long cnt = 1);
  virtual void unpack(const bool* data, long cnt = 1);
  virtual void unpack(const char* data, long cnt = 1);
  virtual void unpack(const unsigned char* data, long cnt = 1);
  virtual void unpack(const short* data, long cnt = 1);
  virtual void unpack(const unsigned short* data, long cnt = 1);
  virtual void unpack(const int* data, long cnt = 1);
  virtual void unpack(const unsigned int* data, long cnt = 1);
  virtual void unpack(const long* data, long cnt = 1);
  virtual void unpack(const unsigned long* data, long cnt = 1);
  virtual void unpack(const string& str);  // unpack an STL string
  virtual long unpackCString(char* data, long count);  // unpack C-style string
  virtual void unpackPointer(void*& data, bool isNetPointer = false);
  virtual int unpackLong(long& item, int subtype);
  virtual int unpackDouble(double& item, int subtype);

  virtual void unpackInPlace(float*& data);
  virtual void unpackInPlace(double*& data);
  virtual void unpackInPlace(bool*& data);
  virtual void unpackInPlace(char*& data);
  virtual void unpackInPlace(unsigned char*& data);
  virtual void unpackInPlace(short*& data);
  virtual void unpackInPlace(unsigned short*& data);
  virtual void unpackInPlace(int*& data);
  virtual void unpackInPlace(unsigned int*& data);
  virtual void unpackInPlace(long*& data);
  virtual void unpackInPlace(unsigned long*& data);
  virtual void unpackInPlace(Siloon::ComplexFloat*& data);
  virtual void unpackInPlace(Siloon::ComplexDouble*& data);
  virtual void unpackInPlace(void*& data);

  virtual size_t unpackArrayInPlace(float*& data);
  virtual size_t unpackArrayInPlace(double*& data);
  virtual size_t unpackArrayInPlace(bool*& data);
  virtual size_t unpackArrayInPlace(char*& data);
  virtual size_t unpackArrayInPlace(unsigned char*& data);
  virtual size_t unpackArrayInPlace(short*& data);
  virtual size_t unpackArrayInPlace(unsigned short*& data);
  virtual size_t unpackArrayInPlace(int*& data);
  virtual size_t unpackArrayInPlace(unsigned int*& data);
  virtual size_t unpackArrayInPlace(long*& data);
  virtual size_t unpackArrayInPlace(unsigned long*& data);

protected:
  size_t   offset_;		// current offset into buffer
  size_t   size_;		// size of the buffer 
  char*    buffer_;		// address of buffer memory
  bool     doOwnBuffer_;	// ownership of buffer for freeing purposes
  bool	   isGrowable_;		// size of buffer can grow (realloc)
  vector<void*> freeList_;	// list of pointers to free

  void reallocIfNecessary(size_t size);
  int  copyToBuffer(const void* data, size_t size);
  void copyFromBuffer(void* data, size_t size);

  template <class T> inline int copyToBuffer(const T& item);
  template <class T> inline int copyToBuffer(const T* data);
  template <class T> inline int copyFromBuffer(T& item);
  template <class T> inline size_t arrayFromBuffer(T* & data);
};

} // namespace Siloon

#endif  // _SILOON_BUFFER_H_
