/*************************************************************************/
/* DUCTAPE Version 2.0                                                   */
/* Copyright (C) 2001                                                    */
/* Forschungszentrum Juelich, Zentralinstitut fuer Angewandte Mathematik */
/*************************************************************************/

#ifndef __PDB_H__
#define __PDB_H__

#ifdef _OLD_HEADER_
# include <iostream.h>
# include <map.h>
# include <vector.h>
# include <mstring.h>
# define STR_NPOS NPOS
#else
# include <iostream>
  using std::ostream;
  using std::cout;
  using std::cerr;
  using std::endl;
# include <map>
  using std::map;
# include <vector>
  using std::vector;
# include <string>
# define STR_NPOS string::npos
  using std::string;
#endif

class PDB;
class pdbSimpleItem;
class pdbItem;
class pdbType;
class pdbFile;
class pdbGroup;
class pdbClass;
class pdbModule;
class pdbRoutine;
class pdbCRoutine;
class pdbFRoutine;
class pdbTemplate;
class pdbMacro;
class pdbNamespace;
class pdbGroupField;

template<class tag>
struct PDBTraits {
  typedef int item_t;
};

class PDB {
public:
  // public types and typedefs
  enum lang_t { LA_NA = 0x00,
	        LA_C  = 0x01, LA_CXX = 0x02, LA_C_or_CXX = 0x03,
		LA_FORTRAN = 0x04,
		LA_JAVA = 0x08,
		LA_MULTI = 0x10};
  typedef vector<pdbType*> typevec;
  typedef vector<pdbFile*> filevec;
  typedef vector<pdbClass*> classvec;
  typedef vector<pdbModule*> modulevec;
  typedef vector<pdbCRoutine*> croutinevec;
  typedef vector<pdbFRoutine*> froutinevec;
  typedef vector<pdbTemplate*> templatevec;
  typedef vector<pdbMacro*> macrovec;
  typedef vector<pdbNamespace*> namespacevec;
  typedef vector<pdbSimpleItem*> itemvec;

  typedef map<int, pdbType*> typemap;
  typedef map<int, pdbFile*> filemap;
  typedef map<int, pdbClass*> classmap;
  typedef map<int, pdbModule*> modulemap;
  typedef map<int, pdbCRoutine*> croutinemap;
  typedef map<int, pdbFRoutine*> froutinemap;
  typedef map<int, pdbTemplate*> templatemap;
  typedef map<int, pdbMacro*> macromap;
  typedef map<int, pdbNamespace*> namespacemap;

  // PDB basic interface
  PDB(char *fname);
  ~PDB();
  bool write(char *fname);
  void write(ostream& ostr);
  bool merge(char *fname);
  operator void *() const;
  int version() const;
  lang_t language() const;

  // PDB item hierachies
  pdbRoutine *callTree();
  pdbFile    *fileTree();
  pdbClass   *classTree();

  // PDB item vectors
  typevec&      getTypeVec();
  filevec&      getFileVec();
  classvec&     getClassVec();
  modulevec&    getModuleVec();
  croutinevec&  getCRoutineVec();
  froutinevec&  getFRoutineVec();
  templatevec&  getTemplateVec();
  macrovec&     getMacroVec();
  namespacevec& getNamespaceVec();
  itemvec&      getItemVec();

  // PDB item maps
  typemap&      getTypeMap();
  filemap&      getFileMap();
  classmap&     getClassMap();
  modulemap&    getModuleMap();
  croutinemap&  getCRoutineMap();
  froutinemap&  getFRoutineMap();
  templatemap&  getTemplateMap();
  macromap&     getMacroMap();
  namespacemap& getNamespaceMap();

  class typeTag {};
  class fileTag {};
  class classTag {};
  class moduleTag {};
  class croutineTag {};
  class froutineTag {};
  class templateTag {};
  class macroTag {};
  class namespaceTag {};

private:
  struct ltstr {
    bool operator()(const char* s1, const char* s2) const {
      return strcmp(s1, s2) < 0;
    }
  };

  enum attr_t { NOATTR,
       // Common Item Attributes
       ACS, CLASS, GROUP, LOC, NSPACE, POS,

       // Common Template Item Attributes
       TEMPL, SPECL, GSPARAM,

       // Item Specific Attributes
       // -- classes (V1.0)
       CBASE, CFRCLASS, CFRFUNC, CFUNC, CMEM, CMCONST, CMISBIT,
       CMKIND, CMMUT, CMTYPE, CKIND,
       // -- groups (V2.0)
       GBASE, GFRGROUP, GFRFUNC, GFUNC, GMEM, GMCONST, GMISBIT,
       GMKIND, GMMUT, GMTYPE, GKIND,
       // -- macros
       MKIND, MTEXT,
       // -- namespaces
       NALIAS, NMEM,
       // -- routines
       RALIAS, RARGINFO, RCALL, RCATCH, RCGEN, RCRVO, REXPL, RIMPL,
       RINLINE, RISELEM, RKIND, RLINK, RREC, RRET, RROUT, RSIG, RSKIND,
       RSTAT, RSTART, RSTOP, RSTORE, RVIRT,
       // -- source files
       SINC, SSYS,
       // -- templates
       TDECL, TDEF, TKIND, TPARAM, TPROTO, TSPARAM, TTEXT, TTYPE,
       YARGT, YCLEN, YDIM, YELEM, YELLIP, YENUM, YEXCEP, YFKIND,
       YIKIND, YKIND, YMPGROUP, YMPTYPE, YNELEM, YQUAL, YPTR, YRANK,
       YREF, YRETT, YSHAPE, YSIGNED, YSTAT, YTREF
  };

  typedef map<const char*, attr_t, ltstr> attrmap;
  typedef map<attr_t, const char*> namemap;

  itemvec      itemVec;
  typevec      typeVec;
  filevec      fileVec;
  classvec     classVec;
  modulevec    moduleVec;
  croutinevec  croutineVec;
  froutinevec  froutineVec;
  templatevec  templateVec;
  macrovec     macroVec;
  namespacevec namespaceVec;

  static attr_t toAttr(const char *v);
  static void   initAttrs(void);
  static bool   attrsAreInit;

  static attrmap attr;
  static namemap name;

  typemap      typeMap;
  filemap      fileMap;
  classmap     classMap;
  modulemap    moduleMap;
  croutinemap  croutineMap;
  froutinemap  froutineMap;
  templatemap  templateMap;
  macromap     macroMap;
  namespacemap namespaceMap;

  pdbRoutine *topRoutine;
  pdbClass *topClass;
  pdbFile *topFile;
  bool status;
  int versNum;
  lang_t lang;

  bool read(char *fname);
  pdbType *getTypeOrGroup(const char *value);
  bool getLocation(const char *value, char **ptr,
                   pdbFile*& file, int& line, int& col);

  template<class tag>
  typename PDBTraits<tag>::item_t *findItem(tag t, int id);

  template<class tag>
  typename PDBTraits<tag>::item_t *findItem(tag t, const string& name, int id);

  template<class tag>
  void finalCheck(tag t);

  template<class tag>
  void markDuplicates(tag t, PDB& other);
};

#ifndef NO_INLINE
#  include "pdb.inl"
#endif
#endif
