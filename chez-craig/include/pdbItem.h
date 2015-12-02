/*************************************************************************/
/* DUCTAPE Version 2.0                                                   */
/* Copyright (C) 2001                                                    */
/* Forschungszentrum Juelich, Zentralinstitut fuer Angewandte Mathematik */
/*************************************************************************/

#ifndef __PDB_ITEM_H__
#define __PDB_ITEM_H__

#include "pdb.h"
#include "pdbSimpleItem.h"
#include "pdbFile.h"  /*???*/

class pdbItem : public pdbSimpleItem {
public:
  enum access_t { AC_NA, AC_PRIV, AC_PROT, AC_PUB };
  enum routine_t { RO_NA, RO_ASM, RO_AUTO, RO_EXT, RO_STAT, RO_TPROTO,
                   RO_FEXT, RO_FPROG, RO_FBLDAT, RO_FINTRIN, RO_FINT,
                   RO_FSTFN, RO_FMPROC, RO_FUNSPEC, RO_FALIAS };
  enum rspec_t { RS_NA, RS_CONV, RS_CTOR, RS_DTOR, RS_OP };
  enum virt_t { VI_NO, VI_PURE, VI_VIRT };
  enum macro_t { MA_NA, MA_DEF, MA_UNDEF };
  enum templ_t { TE_NA, TE_CLASS, TE_FUNC, TE_MEMCLASS, TE_MEMFUNC,
                 TE_STATMEM, TE_TPARAM };
  enum float_t { FL_NA, FL_FLOAT, FL_DBL, FL_LONGDBL };
  enum int_t { I_NA, I_CHAR, I_SCHAR, I_UCHAR, I_SHORT, I_USHORT, I_INT,
               I_UINT, I_LONG, I_ULONG, I_LONGLONG, I_ULONGLONG, I_WCHAR };
  enum type_t { TY_NA = 0,
	  TY_BOOL  =0x0001, TY_ENUM =0x0002, TY_ERR  =0x0004, TY_FUNC  =0x0008,
	  TY_VOID  =0x0010, TY_INT  =0x0020, TY_FLOAT=0x0040, TY_PTR   =0x0080,
	  TY_REF   =0x0100, TY_ARRAY=0x0200, TY_TREF =0x0400, TY_PTRMEM=0x0800,
	  TY_TPARAM=0x1000, TY_WCHAR=0x2000,
	        TY_C_TYPE=0xffff,
          TY_FERR  =0x00010000, TY_FVOID =0x00020000, TY_FINT  =0x00040000,
	  TY_FLOGIC=0x00080000, TY_FFLOAT=0x00100000, TY_FFUNC =0x00200000,
	  TY_FCHAR =0x00400000, TY_FARRAY=0x00800000, TY_FCMPLX=0x01000000,
	  TY_FUNSPECFUNC=0x02000000,
	  TY_FBLDAT=0x04000000, TY_FMOD  =0x08000000, TY_FPTR  =0x10000000,
	        TY_F_TYPE=0x7fff0000,
          TY_GROUP=0x70007000
  };
  enum group_t { GR_NA, GR_CLASS, GR_STRUCT, GR_UNION, GR_TPROTO,
	         GR_FDERIVED, GR_FMODULE };
  enum link_t { LK_NA, LK_INTERNAL, LK_CXX, LK_C, LK_FINT, LK_F90 };
  enum mem_t { M_NA, M_TYPE, M_STATVAR, M_VAR, M_TEMPL };
  enum shape_t { SH_NA, SH_EXPLICIT, SH_ASIZE, SH_ASHAPE, SH_DEFERRED };

  enum qual_t { QL_NA, QL_CONST, QL_VOLATILE, QL_RESTRICT };
  
  pdbItem(int id);
  pdbItem(const string& name, int id);
  virtual ~pdbItem();

  const string& fullName() const;
  access_t access() const;
  const pdbGroup* parentGroup() const;
  pdbLoc& location();
  const pdbLoc& location() const;
  const pdbNamespace* parentNSpace() const;

  void fullName(const string& name);
  void access(access_t attr);
  void parentGroup(const pdbGroup* pgroup);
  void location(const pdbLoc& loc);
  void parentNSpace(const pdbNamespace* nspace);
  
  virtual ostream& print(ostream& ostr) const;
  virtual void adjustPtrs(PDB*);
  virtual void process(PDB*);
  virtual dupl_t findDuplicate(pdbSimpleItem* r);

  static const char *toName(access_t v);
  static const char *toName(routine_t v);
  static const char *toName(rspec_t v);
  static const char *toName(virt_t v);
  static const char *toName(macro_t v);
  static const char *toName(templ_t v);
  static const char *toName(float_t v);
  static const char *toName(int_t v);
  static const char *toName(type_t v);
  static const char *toName(qual_t v);
  static const char *toName(group_t v);
  static const char *toName(link_t v);
  static const char *toName(mem_t v);
  static const char *toName(shape_t v);

  static access_t  toAccess(const char *v);
  static routine_t toRoutine(const char *v);
  static rspec_t   toRSpecial(const char *v);
  static virt_t    toVirt(const char *v);
  static macro_t   toMacro(const char *v);
  static templ_t   toTempl(const char *v);
  static float_t   toFloat(const char* v);
  static int_t     toInt(const char* v);
  static type_t    toType(const char* v);
  static qual_t    toQual(const char* v);
  static group_t   toGroup(const char* v);
  static link_t    toLink(const char* v);
  static mem_t     toMem(const char* v);
  static shape_t   toShape(const char* v);

private:
  pdbLoc              lc;
  access_t            acs;
  const pdbGroup     *gptr;
  const pdbNamespace *nptr;
  string              full;
};

#ifndef NO_INLINE
#  include "pdbItem.inl"
#endif
#endif
