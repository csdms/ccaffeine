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
// Prototype.h -- declarations for a category of classes to support
// function prototypes and to provide a mapping between function ids
// and function prototypes.
//
// This file declares two classes:
//     Prototype
//     PrototypeMap
//-----------------------------------------------------------------------------

#ifndef _SILOON_PROTOTYPE_H_
#define _SILOON_PROTOTYPE_H_

#include "siloon.h"
#include "Buffer.h"
#include "Type.h"
#ifdef _OLD_HEADER_
# include <iostream.h>
#else
# include <iostream>
#endif
#include <map>
#include <vector>
#include <string>
 using std::string;

namespace Siloon {

   
//---- class Prototype --------------------------------------------------
// Provides information regarding a function prototypes.
//-----------------------------------------------------------------------------
class Prototype {
 public:

   Prototype();
   Prototype(Buffer& buf);
#ifdef ADD_TYPE_SIZES
   Prototype(const char* signature,
	     int funcId, vector<Type> types, int numDefaultArgs,
	     vector<int> sizes);
#else
   Prototype(const char* signature, int funcId, vector<Type> types,
	     int numDefaultArgs);
#endif
   Prototype(const Prototype& s);
   ~Prototype();

   Prototype& operator=(const Prototype&);
   
   int functionId(void) const;
   int numberOfArgs(void) const;
   int numberOfDefaultArgs(void) const;
   const Type& argTypeN(int i) const;
   const Type& returnType(void) const;
   bool isMethod(void) const;
   bool isStaticMethod(void) const;
   const char* name(void);
   const char* prototype(void) const;
   void setFunctionId(int funcId);
   void setIsMethod(bool isStatic = false);

   vector<Type>& types(void);
#ifdef ADD_TYPE_SIZES
   vector<int>& sizes(void);
#endif

   void pack(Buffer& buf);
   void packForReturn(Buffer& buf);

   friend int operator<(const Prototype& s1, const Prototype& s2);
   friend ostream& operator<<(ostream& o, const Prototype& s);

   static int numberOfArgs(const char *signature);
   static bool isMethod(const char *signature);
   static bool isStaticMethod(const char* signature);

 private:
   
   char* d_signature;		// e.g., "int foo(int, float)"
   char* d_name;		// e.g., "foo"
   int d_numArgs;		// the number of arguments
   int d_numDefaultArgs;        // the number of default arguments
   int d_funcId;		// function id
   bool d_isMethod;		// true function is a method
   bool d_isStatic;		// true if a static member function

   vector<Type> d_types;	// list of argument types
#ifdef ADD_TYPE_SIZES
   vector<int> d_sizes;		// list of argument sizes
#endif
};


//---- PrototypeMap -----------------------------------------------------------
// This class associates a function id with a Prototype object.
//-----------------------------------------------------------------------------
class PrototypeMap {
 public:

   static void createRegisterCode( const char* prototypeFile,
				   const char* codeFile );

   int addPrototype(const Prototype& s, int id = -1);
   int size() const { return d_idProtoMap.size(); }

   Prototype& operator[](int i)		{ return(d_idProtoMap[i]); }
   Prototype& operator[](const string &s)	{ return(d_sigProtoMap[s]); }

 private:
   map<int, Prototype> d_idProtoMap;
   map<const string, Prototype> d_sigProtoMap;
};


//
// inline functions
//

inline int Prototype::functionId(void) const		{ return d_funcId; }
inline bool Prototype::isMethod(void) const		{ return d_isMethod; }
inline bool Prototype::isStaticMethod(void) const	{ return d_isStatic; }
inline int Prototype::numberOfArgs(void) const		{ return d_numArgs; }
inline int Prototype::numberOfDefaultArgs(void) const	{ return d_numDefaultArgs; }
inline const char* Prototype::prototype(void) const	{ return d_signature; }
inline void Prototype::setFunctionId(int funcId)	{ d_funcId	= funcId; }

inline vector<Type>& Prototype::types(void)		{ return d_types; }
#ifdef ADD_TYPE_SIZES
inline vector<int>& Prototype::sizes(void)		{ return d_sizes; }
#endif

inline void Prototype::pack(Buffer& buf)		{ buf.pack(d_funcId);}

inline const Type& Prototype::argTypeN(int i) const
   { return d_types[i+1]; }

inline const Type& Prototype::returnType(void) const
   { return d_types[0]; }

inline int operator<(const Prototype& s1, const Prototype& s2)
   { return(strcmp(s1.d_signature, s2.d_signature)); }


} // namespace Siloon

#endif // _SILOON_PROTOTYPE_H_
