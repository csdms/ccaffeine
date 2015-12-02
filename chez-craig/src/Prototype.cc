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
// Prototype.C -- definitions for a category of classes to support
// function prototypes and to provide a mapping between HPC++ function ids
// and function prototypes.
//
// This file implements two classes:
//     Prototype
//     IdProtoMap
//-----------------------------------------------------------------------------

#include "Prototype.h"
#include <assert.h>

using namespace Siloon;


Prototype::Prototype()
  : d_signature(NULL), d_name(NULL), d_funcId(-1), d_numArgs(-1),
    d_isMethod(false), d_isStatic(false)
{
}


//-----------------------------------------------------------------------------
// Construct a Prototype object by reading it from a buffer.
//-----------------------------------------------------------------------------
Prototype::Prototype(Buffer& buf)
{
  buf.unpack(&d_funcId);
}


#ifdef ADD_TYPE_SIZES
Prototype::Prototype(const char* signature,
		     int funcId, vector<Type> types, int numDefaultArgs,
		     vector<int> sizes)
   :d_types(types),
    d_numDefaultArgs(numDefaultArgs),
    d_sizes(sizes)
#else
Prototype::Prototype(const char* signature, int funcId, vector<Type> types,
		     int numDefaultArgs)
   :d_types(types),
    d_numDefaultArgs(numDefaultArgs)
#endif
{
   d_signature = new char[strlen(signature) + 1];
   strcpy(d_signature, signature);
   d_name = NULL;			// allocate this lazily, if d
   d_numArgs = types.size() - 1;	// first type is return
   d_funcId = funcId;
   d_isMethod = false;
   d_isStatic = false;
}


Prototype::Prototype(const Prototype& s)
{
   if (s.d_signature == NULL) {
      d_signature = NULL;
      d_numArgs = -1;
      d_numDefaultArgs = -1;
      d_funcId = -1;
      d_isMethod = false;
      d_isStatic = false;
   } else {
      d_signature = new char[strlen(s.d_signature) + 1];
      strcpy(d_signature, s.d_signature);
      d_numArgs = s.d_numArgs;
      d_numDefaultArgs = s.d_numDefaultArgs;
      d_funcId = s.d_funcId;
      d_isMethod = s.d_isMethod;
      d_isStatic = s.d_isStatic;
      d_types = s.d_types;
#ifdef ADD_TYPE_SIZES
      d_sizes = s.d_sizes;
#endif
   }
   d_name = NULL;
}


Prototype::~Prototype()
{
    if (d_signature != NULL) delete [] d_signature;
    if (d_name != NULL) delete [] d_name;
}


Prototype& Prototype::operator=(const Prototype& s)
{
   if (this != &s) {
      if (d_signature != NULL) delete[] d_signature;

      if (s.d_signature == NULL) {
	 d_signature = NULL;
	 d_numArgs = -1;
	 d_numDefaultArgs = -1;
	 d_funcId = -1;
	 d_isMethod = false;
	 d_isStatic = false;
      } else {
	 d_signature = new char[strlen(s.d_signature) + 1];
	 strcpy(d_signature, s.d_signature);
	 d_numArgs = s.d_numArgs;
	 d_numDefaultArgs = s.d_numDefaultArgs;
	 d_funcId = s.d_funcId;
	 d_isMethod = s.d_isMethod;
	 d_isStatic = s.d_isStatic;
	 d_types = s.d_types;
#ifdef ADD_TYPE_SIZES
	 d_sizes = s.d_sizes;
#endif
      }
      d_name = NULL;
   }  
   return *this;
}


const char* Prototype::name(void)
{
   if (d_name == NULL) {                
      char* begin = strchr(d_signature, ' ' );
      while (begin != NULL
	     && (*begin == ' ' || *begin == '*' || *begin == '&')) begin += 1;

      // check for destructor (no return type)
      char* cc = strstr(d_signature, "::");
      if (cc != NULL && cc < begin) {
	 begin = d_signature;
      }

      char* end = strchr(begin, '(');
      if (end == NULL) return "badly_formed_function_prototype";

      // remove trailing blanks
      while (*(end-1) == ' ') end -= 1;

      int len = end - begin;
      d_name = new char[len + 1];
      strncpy(d_name, begin, len);
      d_name[len] = '\0';
   }
   return d_name;
}


//---- isMethod ---------------------------------------------------------------
// Returns true if the signature is a method (member function), has "::"
// in the signature.
//-----------------------------------------------------------------------------
bool Prototype::isMethod(const char* signature)
{
   return (strstr(signature, "::") == NULL) ? false : true;
}

//---- isStaticMethod ---------------------------------------------------------
// Returns true if the signature is a method (member function and nonstatic).
// Note, a constructor is not considered to be a static as it doesn't
// require a this pointer (like static functions).
//
// BEWARE of BUG, returns true for static member functions other than
// constructors as is impossible to tell if static from signature alone.
//-----------------------------------------------------------------------------
bool Prototype::isStaticMethod(const char* signature)
{
   char* cc = strstr(signature, "::");
   if (cc == NULL) return false;

   // find symbol name in from of ::
   char* funcName = cc;
   while (funcName != signature && *(funcName-1) != ' ') funcName -= 1;

   // check for constructor
   int len = cc - funcName;
   if (strncmp(funcName, cc + 2, len) == 0) {
      char term = *(cc + 2 + len);
      if (term == '(' || term == ' ' || term == '\0') return false;
   }
   return true;
}


//---- packForReturn ----------------------------------------------------------
// Pack the return type.  The value doesn't matter, really just saving
// space in the buffer for the return value.
//-----------------------------------------------------------------------------
void Prototype::packForReturn(Buffer& buf)
{
   switch(returnType().type()) {
     case pdbItem::TY_VOID: {
       // Don't pack anything for return of void.
       break;
     }
     case pdbItem::TY_INT: {
       long lResult;
       buf.pack(lResult);	// pack space for an integer (long) type
       break;
     }
     case pdbItem::TY_FLOAT: {
       double dResult;
       buf.pack(dResult);	// pack space for a float (double) type
       break;
     }
     case pdbItem::TY_PTR: {
       Type* ptrType = returnType().indirectType();
       if (ptrType != NULL
	   && ptrType->type() == pdbItem::TY_INT
	   && ptrType->subtype() == pdbItem::I_CHAR) {

	 string s;		// Pack space for a string.
	 buf.pack(s);
       } else {
	 char pResult[8];	// Pack space for a pointer, stored in 8 bytes
	 buf.packPointer(pResult, true);
       }
       break;
     }
     case pdbItem::TY_REF: {
       Type* refType = returnType().indirectType();
       if (refType != NULL
	   && refType->type() == pdbItem::TY_GROUP
	   && refType->sclassType() == Type::SCL_STRING
           && refType->qualifier() == pdbItem::QL_CONST) {
	 string s;		// Pack space for a string.
	 buf.pack(s);
       } else {
	 char pResult[8];	// Pack space for a pointer, stored in 8 bytes
	 buf.packPointer(pResult, true);
       }
       break;
     }
   }
}


void Prototype::setIsMethod(bool isStatic)
{
   d_isMethod = true;
   d_isStatic = isStatic;
}


// Print the Prototype.
ostream & Siloon::operator<<(ostream& o, const Prototype& s)
{
   return(o << s.prototype());
}


//-----------------------------------------------------------------------------
// PrototypeMap definitions
//-----------------------------------------------------------------------------


int PrototypeMap::addPrototype(const Prototype& s, int id)
{
   if (id < 0) {
      id = s.functionId();
   }
   d_idProtoMap[id] = s;
   d_sigProtoMap[s.prototype()] = s;

   return id;
}


//---- createRegisterCode -----------------------------------------------------
// Creates code to register functions with HPC++ and create an
// IdProtoMap, given prototypes in a file.
//
// prototypeFile -- path to a file containing prototypes, one per line
// codeFile -- code file to be produced (eg, register.C)
//-----------------------------------------------------------------------------
void PrototypeMap::createRegisterCode( const char* prototypeFile,
				       const char* codeFile )
{
}


//-----------------------------------------------------------------------------
// Prototype-related functions
//-----------------------------------------------------------------------------

// Given a function signature, return the number of arguments.
// NOTE: Very primitive implementation.
int Prototype::numberOfArgs(const char *signature)
{
   while (*signature != '(' && *signature != '\0')
      signature++;
   if (*signature != '\0') signature++;

   while (*signature == ' ' && *signature != '\0')
      signature++;

   if (*signature == ')')
      return(0);
   
   int numArgs = 1;

   while (*signature != '\0') {
      if (*signature == ',')
	 numArgs++;
      signature++;
   }
   return(numArgs);
}
