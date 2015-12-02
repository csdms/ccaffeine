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
// Pointer.h -- a class and enums which define a pointer class.
//-----------------------------------------------------------------------------
#ifndef _SILOON_POINTER_H_
#define _SILOON_POINTER_H_

#include <stddef.h>		// for NULL
#include <string.h>		// for memcpy, ...
#include "siloon_types.h"
#include "Type.h"

namespace Siloon {

#define SILOON_READ_C -2
#define SILOON_WRITE_C -3
#define SILOON_READ_F -4
#define SILOON_WRITE_F -5
  
class Buffer;
  
class Pointer {
 public:

  enum storage_type { BY_POINTER, BY_VALUE };
 
  // constructors
  Pointer(void) : ptype(0), pid(-1) { }
  Pointer(const Type& type, ContextID& id) :
    ptype(type), pid(id) { }

  // access methods
  inline const Type& type(void) const          { return ptype; }
  inline const ContextID& context(void) const  { return pid;   }
  inline void setType(const Type& t)           { ptype = t;    }
  inline void setContextID(const ContextID& c) { pid = c;      }

  // buffer packing methods
  virtual int pack(Buffer& b) const = 0;
  virtual void unpack(Buffer& b, long allocSize = -1) = 0;
  
 private:

  Type ptype;
  ContextID pid;
};

class ServerPointer : public virtual Pointer {

 public:

  // constructors
  ServerPointer(void) : Pointer(), sptr(NULL), mustFree(false) { }
  ServerPointer(Buffer& b, long n = -1) : mustFree(false)    { unpack(b, n); }
  ServerPointer(const void* ptr_, Type& type_, ContextID& id_)
    : Pointer(type_, id_), sptr((void*) ptr_), mustFree(false) { }

  // simple-type constructors
  ServerPointer(const void* ptr_, ContextID& id_);
  ServerPointer(const char* ptr_, ContextID& id_);
  ServerPointer(const short* ptr_, ContextID& id_);
  ServerPointer(const int* ptr_, ContextID& id_);
  ServerPointer(const long* ptr_, ContextID& id_);
  ServerPointer(const float* ptr_, ContextID& id_);
  ServerPointer(const double* ptr_, ContextID& id_);

  // destructor
  ~ServerPointer(void);

  // casting operators
  operator void*()	{ return sptr; }
  operator char*()	{ return (char *) sptr; }
  operator short*()	{ return (short *)sptr; }
  operator int*()	{ return (int *) sptr; }
  operator long*()	{ return (long *) sptr; }
  operator float*()	{ return (float *) sptr; }
  operator double*()	{ return (double *) sptr; }
  
  // access methods
  inline void* pointer(void) const	{ return sptr; }
  inline void setPointer(void* p)	{ sptr = p;    }
  
  // array manipulation methods
  int writeToBuffer(Buffer& b, int cnt = 1, int ofst = 0);
  int readFromBuffer(Buffer& b, int cnt = 1, int ofst = 0);

  // buffer packing methods
  int pack(Buffer& b) const;
  void unpack(Buffer& b, long allocSize = -1);

 private:
  void* sptr;
  bool mustFree;
  void unpackArray(Buffer& b, size_t & count, long allocSize = -1);
};

class ClientPointer : public virtual Pointer {

 public:

  // constructors
  ClientPointer(void) : Pointer()	{ memcpy(cptr.chr8, "00000000", 8); }
  ClientPointer(Buffer& b)		{ unpack(b); }
  ClientPointer(char ptr_[8], Type& type_, ContextID& id_, char alloc)
   : Pointer(type_, id_)		{ memcpy(cptr.chr8, ptr_, 8); }

  // access methods
  inline char* pointer(void)		{ return cptr.chr8; }
  inline void setPointer(char p[8])	{ memcpy(cptr.chr8, p, 8); }

  // pack for read/write methods
  int packForRead(Buffer& b, int count, int offset);
  int packForWrite(Buffer& b, int count, int offset);
  
  // buffer packing methods
  int pack(Buffer& b) const;
  void unpack(Buffer& b, long allocSize = -1);

  // partial buffer packing method
  void beginPackArray(Buffer& b, long count);

 private:
  union {
    void* ptr;
    char chr8[8];
  } cptr;
};
 
} // namespace Siloon

#endif  // _SILOON_POINTER_H
