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
// Type.h -- a class and enums which define generic data types.
//-----------------------------------------------------------------------------

#ifndef _SILOON_TYPE_H_
#define _SILOON_TYPE_H_

#include <stddef.h>		// for NULL
#include <pdbItem.h>

namespace Siloon {

class Buffer;

class Type {
  public:

  enum sclass_t { SCL_NA, SCL_STRING, SCL_FCHAR, SCL_FCHARVARLEN };

  // constructors
  Type(void);
  Type(unsigned int type, unsigned int subtype = 0,
       unsigned int qualifier = 0, unsigned int sclass = SCL_NA,
       long numElements = 0);
  Type(const Type& t);
  Type(Buffer& buf);

  ~Type(void);

  Type& operator=(const Type& t);
  operator unsigned int() const;		// convert to an integer

  // access functions
  unsigned int type(void) const;
  unsigned int subtype(void) const;
  unsigned int qualifier(void) const;
  unsigned int sclassType(void) const;
  long numElements(void) const;
  void set(unsigned int type, unsigned int subtype = 0,
	   unsigned int qualifier = 0, unsigned int sclass = SCL_NA,
	   long numElements = 0);

  // The indirect methods are used to get at the Type of pointers and
  // references.
  Type* indirectType(void) const;
  void setIndirectType(unsigned int type, unsigned int subtype = 0,
		       unsigned int qualifier = 0,
		       unsigned int sclass = SCL_NA,
		       long numElements = 0);

  // buffer packing methods
  int pack(Buffer& b) const;
  void unpack(Buffer& b);

  static bool isElemental(const Type& t);
  static bool isSupported(const Type& t);
  static bool isSupported(unsigned int type, unsigned int subtype = 0,
			  unsigned int qualifier = 0,
			  unsigned int sclass = SCL_NA,
			  long numElements = 0);

  static void* convertNetPointer(double np)
    { return ((char*) &np) + 4; }

  private:

  unsigned int type_;	// 4 bytes => <sclasstype|qualifier|subtype|type>
  Type* indirectType_;	// type pointed to, if type_ == TY_PTR or TY_TREF
  long numElements_;    // number of elements (e.g., in a string)  
};

//
// inline code
//

// constructors

inline Type::Type(void)
  {
    type_ = 0;
    numElements_ = 0;
    indirectType_ = NULL;
  }

inline Type::Type(unsigned int type, unsigned int subtype,
		  unsigned int qualifier, unsigned int sclass,
		  long numElements)
  {
    set(type, subtype, qualifier, sclass, numElements);
    indirectType_ = NULL;
  }

// convert to an integer
inline Type::operator unsigned int() const	    { return type_; }

//
// access functions
//

inline Type* Type::indirectType(void) const { return indirectType_; }

//-----------------------------------------------------------------------------
// Must convert from internal representation to pdbItem type which uses
// 32 bits to store the type and only one bit at a time is turned on.
// The internal representation just compresses this down to a 4 bit unsigned
// integer.  At this time, the subtype and qualifier representation is
// the same as used in pdbItem.  WARNING, this may change in the future.
//-----------------------------------------------------------------------------
inline unsigned int Type::type(void) const
   { 
      switch (0xff & type_) {
        case  0:  return pdbItem::TY_NA;
        case  1:  return pdbItem::TY_BOOL;
        case  2:  return pdbItem::TY_ENUM;
        case  3:  return pdbItem::TY_ERR;
        case  4:  return pdbItem::TY_FUNC;
        case  5:  return pdbItem::TY_VOID;
        case  6:  return pdbItem::TY_INT;
        case  7:  return pdbItem::TY_FLOAT;
        case  8:  return pdbItem::TY_PTR;
        case  9:  return pdbItem::TY_REF;
        case 10:  return pdbItem::TY_ARRAY;
        case 11:  return pdbItem::TY_TREF;
        case 12:  return pdbItem::TY_PTRMEM;
        case 13:  return pdbItem::TY_TPARAM;
        case 14:  return pdbItem::TY_WCHAR;
        case 15:  return pdbItem::TY_C_TYPE;
        case 16:  return pdbItem::TY_FERR;
        case 17:  return pdbItem::TY_FVOID;
        case 18:  return pdbItem::TY_FINT;
        case 19:  return pdbItem::TY_FLOGIC;
        case 20:  return pdbItem::TY_FFLOAT;
        case 21:  return pdbItem::TY_FFUNC;
        case 22:  return pdbItem::TY_FCHAR;
        case 23:  return pdbItem::TY_FARRAY;
        case 24:  return pdbItem::TY_FCMPLX;
        case 25:  return pdbItem::TY_FUNSPECFUNC;
        case 26:  return pdbItem::TY_FBLDAT;
        case 27:  return pdbItem::TY_FMOD;
        case 28:  return pdbItem::TY_FPTR;
        case 29:  return pdbItem::TY_F_TYPE;
        case 30:  return pdbItem::TY_GROUP;
      }
      // shouldn't arrive here
      return pdbItem::TY_NA;
   }

inline unsigned int Type::subtype(void) const
   {
      return 0xff & (type_ >> 8);
   }

inline unsigned int Type::qualifier(void) const
   {
      return 0xff & (type_ >> 16);
   }

inline unsigned int Type::sclassType(void) const
   {
      return 0xff & (type_ >> 24);
   }

inline long Type::numElements(void) const
   {
      return numElements_;
   }

//-----------------------------------------------------------------------------
// The type parameter must be converted from pdbItem format to the
// more efficient Siloon format.  The other parameters (i.e., subtype)
// are the same.
//-----------------------------------------------------------------------------
inline void Type::set(unsigned int type, unsigned int subtype,
		      unsigned int qualifier, unsigned int sclass,
		      long numElements)
   {
      unsigned int stype;
      switch (type) {
         case pdbItem::TY_NA:		stype =  0;  break;
         case pdbItem::TY_BOOL:		stype =  1;  break;
	 case pdbItem::TY_ENUM:		stype =  2;  break;
	 case pdbItem::TY_ERR:		stype =  3;  break;
	 case pdbItem::TY_FUNC:		stype =  4;  break;
	 case pdbItem::TY_VOID:		stype =  5;  break;
	 case pdbItem::TY_INT:		stype =  6;  break;
	 case pdbItem::TY_FLOAT:	stype =  7;  break;
	 case pdbItem::TY_PTR:		stype =  8;  break;
	 case pdbItem::TY_REF:		stype =  9;  break;
	 case pdbItem::TY_ARRAY:	stype = 10;  break;
	 case pdbItem::TY_TREF:		stype = 11;  break;
	 case pdbItem::TY_PTRMEM:	stype = 12;  break;
	 case pdbItem::TY_TPARAM:	stype = 13;  break;
	 case pdbItem::TY_WCHAR:	stype = 14;  break;
	 case pdbItem::TY_C_TYPE:	stype = 15;  break;
	 case pdbItem::TY_FERR:		stype = 16;  break;
	 case pdbItem::TY_FVOID:	stype = 17;  break;
	 case pdbItem::TY_FINT:		stype = 18;  break;
	 case pdbItem::TY_FLOGIC:	stype = 19;  break;
	 case pdbItem::TY_FFLOAT:	stype = 20;  break;
	 case pdbItem::TY_FFUNC:	stype = 21;  break;
	 case pdbItem::TY_FCHAR:	stype = 22;  break;
	 case pdbItem::TY_FARRAY:	stype = 23;  break;
	 case pdbItem::TY_FCMPLX:	stype = 24;  break;
	 case pdbItem::TY_FUNSPECFUNC:	stype = 25;  break;
	 case pdbItem::TY_FBLDAT:	stype = 26;  break;
	 case pdbItem::TY_FMOD:		stype = 27;  break;
	 case pdbItem::TY_FPTR:		stype = 28;  break;
	 case pdbItem::TY_F_TYPE:	stype = 29;  break;
	 case pdbItem::TY_GROUP:	stype = 30;  break;
      }
      type_ = stype | (subtype << 8) | (qualifier << 16) | (sclass << 24);
      numElements_ = numElements;
   } // Type::set

} // namespace Siloon

#endif // _SILOON_TYPE_H_
