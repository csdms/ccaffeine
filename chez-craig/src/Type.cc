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
// Type.cc -- a class and enums which define generic data types.
//-----------------------------------------------------------------------------

#include "Type.h"
#include "Buffer.h"

using namespace Siloon;

Type::Type(const Type& t)
{
   type_ = t.type_;
   numElements_ = t.numElements();
   if (t.indirectType() != NULL) {
      Type* pt = t.indirectType();
      indirectType_ = new Type(pt->type(), pt->subtype(),
			       pt->qualifier(), pt->sclassType(),
			       pt->numElements());
   } else {
      indirectType_ = NULL;
   }
}


Type::Type(Buffer& buf) : type_(0), indirectType_(NULL), numElements_(0)
{
   unpack(buf);
}


Type::~Type(void)
{
   if (indirectType_ != NULL) delete indirectType_;
}


Type& Type::operator=(const Type& t)
{
   if (this == &t) return(*this);
   
   type_ = t.type_;
   numElements_ = t.numElements();
   if (t.indirectType() != NULL) {
      if (indirectType_ != NULL) delete indirectType_;
      Type* pt = t.indirectType();
      indirectType_ = new Type(pt->type(), pt->subtype(),
			       pt->qualifier(), pt->sclassType(),
			       pt->numElements());
   } else {
      indirectType_ = NULL;
   }

   return *this;
}


void Type::setIndirectType(unsigned int type, unsigned int subtype,
			   unsigned int qualifier, unsigned int sclass,
			   long numElements)
{
   if (indirectType_ != NULL) delete indirectType_;
   indirectType_ = new Type(type, subtype, qualifier, sclass, numElements);
}


int Type::pack(Buffer& buf) const
{
   buf.pack(type_);
   if (indirectType_ != NULL) {
      int hasIndirect = 1;
      buf.pack(hasIndirect);
      indirectType_->pack(buf);
   } else {
      int hasIndirect = 0;
      buf.pack(hasIndirect);
   }
   return SILOON_SUCCESS;
}


void Type::unpack(Buffer& buf)
{
   if (indirectType_ != NULL) delete indirectType_;
   indirectType_ = NULL;

   buf.unpack(&type_);

   // unpack indirectType, if exists
   int hasIndirect;
   buf.unpack(&hasIndirect);
   if (hasIndirect != 0) {
      indirectType_ = new Type(buf);
   }
}


bool Type::isSupported(const Type& t)
{
   switch (t.type()) {
      // integer types
      case pdbItem::TY_ENUM:	 return true;
      case pdbItem::TY_BOOL:	 return true;
      case pdbItem::TY_FCHAR:	 return true;

      case pdbItem::TY_INT:	// note fall through
      case pdbItem::TY_FINT:
	 if (    t.subtype() >= pdbItem::I_CHAR
              && t.subtype() <= pdbItem::I_ULONG) return true;
	 break;

      // floating point types
      case pdbItem::TY_FLOAT:	// note fall through
      case pdbItem::TY_FFLOAT:
	 if (    t.subtype() >= pdbItem::FL_FLOAT
	      && t.subtype() <= pdbItem::FL_DBL) return true;
	 break;
     
      case pdbItem::TY_FCMPLX:	return true;
      case pdbItem::TY_FARRAY:	return true;

      case pdbItem::TY_VOID:	// note fall through
      case pdbItem::TY_FVOID:	// note fall through
      case pdbItem::TY_PTR:	// note fall through
      case pdbItem::TY_FPTR:	// note fall through
      case pdbItem::TY_REF:	 return true;

      // string types (std::string is actually a TY_TREF (typedef) so
      // the indirect type is set to TY_GROUP, SCL_STRING

      case pdbItem::TY_GROUP:
	 if (t.sclassType() == SCL_STRING) return true;
         break;

      case pdbItem::TY_TREF: {
	 Type* itype = t.indirectType();
	 if (itype != NULL) return Type::isSupported(*itype);
	 break;
      }

      default:
         break;
   }
   return false;
}


bool Type::isSupported(unsigned int type, unsigned int subtype,
		       unsigned int qualifier, unsigned int sclass,
		       long numElements)
{
  Type t(type, subtype, qualifier, sclass, numElements);
  return Type::isSupported(t);
}


bool Type::isElemental(const Type& type)
{
   switch (type.type()) {
      // integer types
      case pdbItem::TY_ENUM:	 return true;
      case pdbItem::TY_BOOL:	 return true;

      case pdbItem::TY_INT:	// note fall through
      case pdbItem::TY_FINT:
	 if (    type.subtype() >= pdbItem::I_CHAR
              && type.subtype() <= pdbItem::I_ULONG) return true;
	 break;

      // floating point types
      case pdbItem::TY_FLOAT:	// note fall through
      case pdbItem::TY_FFLOAT:
	 if (    type.subtype() >= pdbItem::FL_FLOAT
	      && type.subtype() <= pdbItem::FL_DBL) return true;
	 break;
     
      case pdbItem::TY_FCMPLX:	return true;

      default:
         break;
   }
   return false;
}
