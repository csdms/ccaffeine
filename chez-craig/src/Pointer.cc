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

#include "Pointer.h"
#include "Buffer.h"
#include <assert.h>

using namespace Siloon;

// simple-type constructors
ServerPointer::ServerPointer(const void* ptr_, ContextID& id_) : Pointer()
{
  Type t(pdbItem::TY_NA);
  setType(t);
  setContextID(id_);
  sptr = (void *) ptr_;
  mustFree = false;
}

ServerPointer::ServerPointer(const char* ptr_, ContextID& id_) : Pointer()
{
  Type t(pdbItem::TY_INT, pdbItem::I_CHAR);
  setType(t);
  setContextID(id_);
  sptr = (void *) ptr_;
  mustFree = false;
}

ServerPointer::ServerPointer(const short* ptr_, ContextID& id_) : Pointer()
{
  Type t(pdbItem::TY_INT, pdbItem::I_SHORT);
  setType(t);
  setContextID(id_);
  sptr = (void *) ptr_;
  mustFree = false;
}

ServerPointer::ServerPointer(const int* ptr_, ContextID& id_) : Pointer()
{
  Type t(pdbItem::TY_INT, pdbItem::I_INT);
  setType(t);
  setContextID(id_);
  sptr = (void *) ptr_;
  mustFree = false;
}

ServerPointer::ServerPointer(const long* ptr_, ContextID& id_) : Pointer()
{
  Type t(pdbItem::TY_INT, pdbItem::I_LONG);
  setType(t);
  setContextID(id_);
  sptr = (void *) ptr_;
  mustFree = false;
}

ServerPointer::ServerPointer(const float* ptr_, ContextID& id_) : Pointer()
{
  Type t(pdbItem::TY_FLOAT, pdbItem::FL_FLOAT);
  setType(t);
  setContextID(id_);
  sptr = (void *) ptr_;
  mustFree = false;
}

ServerPointer::ServerPointer(const double* ptr_, ContextID& id_) : Pointer()
{
  Type t(pdbItem::TY_FLOAT, pdbItem::FL_DBL);
  setType(t);
  setContextID(id_);
  sptr = (void *) ptr_;
  mustFree = false;
}

ServerPointer::~ServerPointer(void)
{
  const Type& ptype = type();
  int type = ptype.type();
  int subtype = ptype.subtype();

  // check to see if array has been allocated, if not, no need to free
  if (mustFree == false) return;
  
  // free sptr (has been malloced locally as an array)
  switch (type) {
    // integer types
  case pdbItem::TY_INT:
    if ( subtype >= pdbItem::I_CHAR && subtype <= pdbItem::I_UCHAR ) {
      delete[] (char *) sptr;
    }
    else if ( subtype <= pdbItem::I_USHORT ) {
      delete[] (short *) sptr;
    }
    else if ( subtype <= pdbItem::I_UINT ) {
      delete[] (int *) sptr;
    }
    else if ( subtype <= pdbItem::I_ULONG ) {
      delete[] (long *) sptr;
    }
    break;
    
    // floating point types
  case pdbItem::TY_FLOAT:
    if ( subtype == pdbItem::FL_FLOAT ) {
      delete[] (float *) sptr;
    }
    else if ( subtype == pdbItem::FL_DBL ) {
      delete[] (double *) sptr;
    }
    break;
    
  case pdbItem::TY_VOID:	// note fall through
  case pdbItem::TY_PTR:	// note fall through
  case pdbItem::TY_REF:	// note fall through
  default:
    break;
  }
}

//
// Copy cnt items from Buffer b into this pointer's address (sptr).
//
int ServerPointer::readFromBuffer(Buffer& b, int cnt, int ofst)
{
  const Type& ptype = type();
  int type = ptype.type();
  int subtype = ptype.subtype();

  switch (type) {
    // integer types
  case pdbItem::TY_INT:
    if ( subtype >= pdbItem::I_CHAR && subtype <= pdbItem::I_UCHAR )
      b.unpack(reinterpret_cast<char*>(sptr) + ofst, cnt);

    else if ( subtype <= pdbItem::I_USHORT )
      b.unpack(reinterpret_cast<short*>(sptr) + ofst, cnt);

    else if ( subtype <= pdbItem::I_UINT )
      b.unpack(reinterpret_cast<int*>(sptr) + ofst, cnt);

    else if ( subtype <= pdbItem::I_ULONG )
      b.unpack(reinterpret_cast<long*>(sptr) + ofst, cnt);

    break;
    
    // floating point types
  case pdbItem::TY_FLOAT:
    if ( subtype == pdbItem::FL_FLOAT )
      b.unpack(reinterpret_cast<float*>(sptr) + ofst, cnt);
    
    else if ( subtype == pdbItem::FL_DBL )
      b.unpack(reinterpret_cast<double*>(sptr) + ofst, cnt);
    
    else if ( subtype >= pdbItem::FL_LONGDBL ) {
      cnt = 0;
    }
    break;
    
  case pdbItem::TY_VOID:	// note fall through
  case pdbItem::TY_PTR:	// note fall through
  case pdbItem::TY_REF:	// note fall through
  default:
    cnt = 0;
    break;
  }
  b.reset();
  b.pack(cnt);		// return number actually unpacked in buffer

  return cnt;
}

int ServerPointer::writeToBuffer(Buffer& b, int cnt, int ofst)
{
  const Type& ptype = type();
  int type = ptype.type();
  int subtype = ptype.subtype();

  int count = cnt;
  b.pack(count);	// assume correct # of items will be written

  switch (type) {
    // integer types
  case pdbItem::TY_INT:
    if ( subtype >= pdbItem::I_CHAR && subtype <= pdbItem::I_UCHAR ) {
      b.pack(reinterpret_cast<char*>(sptr) + ofst, cnt);
    }
    else if( subtype <= pdbItem::I_USHORT ) {
      b.pack(reinterpret_cast<short*>(sptr) + ofst, cnt);
    }
    else if ( subtype <= pdbItem::I_UINT ) {
      b.pack(reinterpret_cast<int*>(sptr) + ofst, cnt);
    }
    else if ( subtype <= pdbItem::I_ULONG ) {
      b.pack(reinterpret_cast<long*>(sptr) + ofst, cnt);
    }
    break;
    
    // floating point types
  case pdbItem::TY_FLOAT:
    if ( subtype == pdbItem::FL_FLOAT ) {
      b.pack(reinterpret_cast<float*>(sptr) + ofst, cnt);
    }
    else if ( subtype == pdbItem::FL_DBL ) {
      b.pack(reinterpret_cast<double*>(sptr) + ofst, cnt);
    }
    else if ( subtype >= pdbItem::FL_LONGDBL ) {
      cnt = 0;
    }
    break;
    
  case pdbItem::TY_VOID:	// note fall through
  case pdbItem::TY_PTR:	// note fall through
  case pdbItem::TY_REF:	// note fall through
  default:
    cnt = 0;
    break;
  }

  if (count != cnt) {
    // this should eventually be reported as an error
    b.reset();
    b.pack(cnt);	// fix count of items packed
  }

  return cnt;
}


//-----------------------------------------------------------------------------
// Pack a Pointer type into the buffer b.
//-----------------------------------------------------------------------------
int ServerPointer::pack(Buffer& b) const
{
   char storageType = Pointer::BY_POINTER;
   b.pack(storageType);
   type().pack(b);

   ContextID id = context();
   b.pack(id);

   b.packPointer(sptr);
   return SILOON_SUCCESS;
}

//-----------------------------------------------------------------------------
// Unpack a Pointer type from the buffer where allocSize is the suggested
// size of the buffer to allocate (if < 0, ignore hint).
//-----------------------------------------------------------------------------
void ServerPointer::unpack(Buffer& b, long allocSize)
{
   char storageType;
   b.unpack(&storageType);

   // unpack the type information
   Type ptrType(b);
   setType(ptrType);

   ContextID id;
   b.unpack(&id);
   setContextID(id);

   if (storageType == Pointer::BY_POINTER) {
      b.unpackPointer(sptr, false);
   } else if (storageType == Pointer::BY_VALUE) {
      size_t count;
      unpackArray(b, count, allocSize);
   }
}


//-----------------------------------------------------------------------------
// Pointer stored BY_VALUE, unpack count number of values. The parameter
// allocSize is the suggested size of the buffer to allocate.
//-----------------------------------------------------------------------------
void ServerPointer::unpackArray(Buffer& b, size_t & count, long allocSize)
{
   const Type& ptype = type();
   int type = ptype.type();
   int subtype = ptype.subtype();
   int sclass = ptype.sclassType();

   switch (type) {

     // Fortran character 
   case pdbItem::TY_FCHAR:
     count = b.unpackArrayInPlace(reinterpret_cast<char*>(sptr));
     break;

     // integer types
   case pdbItem::TY_INT:
      if ( subtype >= pdbItem::I_CHAR && subtype <= pdbItem::I_UCHAR ) {
	// assume this may be used as null terminated string
	count = b.unpackArrayInPlace(reinterpret_cast<char*>(sptr));
      }
      else if ( subtype <= pdbItem::I_USHORT ) {
	 count = b.unpackArrayInPlace(reinterpret_cast<short*>(sptr));
      }
      else if ( subtype <= pdbItem::I_UINT ) {
	 count = b.unpackArrayInPlace(reinterpret_cast<int*>(sptr));
      }
      else if ( subtype <= pdbItem::I_ULONG ) {
	 count = b.unpackArrayInPlace(reinterpret_cast<long*>(sptr));
      }
      break;
    
      // floating point types
   case pdbItem::TY_FLOAT:
      if ( subtype == pdbItem::FL_FLOAT ) {
	 count = b.unpackArrayInPlace(reinterpret_cast<float*>(sptr));
      } 
      else if ( subtype == pdbItem::FL_DBL ) {
	 count = b.unpackArrayInPlace(reinterpret_cast<double*>(sptr));
      }
      break;
    
      // string type
   case pdbItem::TY_GROUP:
      if ( sclass == Type::SCL_STRING ) {
	 count = b.unpackArrayInPlace(reinterpret_cast<char*>(sptr));
      }
      break;

   case pdbItem::TY_VOID:	// note fall through
   case pdbItem::TY_PTR:	// note fall through
   case pdbItem::TY_REF:	// note fall through
   default:
      break;
   }
}

// ClientPointer methods

int ClientPointer::packForRead(Buffer& b, int count, int offset)
{
  int fid = SILOON_READ_C;
  b.pack(fid);
  pack(b);
  b.pack(count);
  b.pack(offset);

  return count;
}  

int ClientPointer::packForWrite(Buffer& b, int count, int offset)
{
  int fid = SILOON_WRITE_C;
  b.pack(fid);
  pack(b);
  b.pack(count);
  b.pack(offset);

  return count;
}

// Pack a Pointer type.
int ClientPointer::pack(Buffer& b) const
{
  char storageType = Pointer::BY_POINTER;
  b.pack(storageType);
  type().pack(b);

  ContextID id = context();
  b.pack(id);

  b.packPointer(cptr.ptr, true);
  return SILOON_SUCCESS;
}

//--- unpack ------------------------------------------------------------------
// unpack a Pointer type (ignore allocSize)
//-----------------------------------------------------------------------------
void ClientPointer::unpack(Buffer& b, long allocSize)
{
  char storageType;
  b.unpack(&storageType);

  Type type(b);
  setType(type);

  ContextID id;
  b.unpack(&id);
  setContextID(id);
  
  b.unpackPointer(cptr.ptr, true);
}

// pack only the Type and ContextID of the Pointer
void ClientPointer::beginPackArray(Buffer& b, long count)
{
  char storageType = Pointer::BY_VALUE;
  b.pack(storageType);
  type().pack(b);

  ContextID id = context();
  b.pack(id);

  b.pack(count);
}
