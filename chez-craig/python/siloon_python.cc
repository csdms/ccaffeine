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
#include <Python.h>
#include <siloon.h>
#include <Buffer.h>
#include <Prototype.h>
#include <Pointer.h>
#include <stdarg.h>
#include <map>
#include <string>

#define DEBUG_LEVEL 0
#define SIL_MAX_ARGS 20
#define INVOKE_BUF_SIZE 512

using namespace Siloon;
using namespace std;

Buffer* gBuf = NULL;

static PrototypeMap *prototypeMap;

// ----------------------------------------------------------------------
// This class is used for converting Python representations of
// Type objects.
// ----------------------------------------------------------------------
class PythonType : public Type
{
 public:
   PythonType(PyObject* pObj);

   // pythonValue is a class function because the Pointer class stores a
   // Type, not a PythonType
   static PyObject* pythonValue(const Type& type);
};


// ----------------------------------------------------------------------
// This class is used for converting Python representations of
// Pointer objects.
// ----------------------------------------------------------------------
class PythonClientPointer : public ClientPointer
{
 public:
   PythonClientPointer(PyObject* pObj);
   PythonClientPointer(Buffer& buf) : ClientPointer(buf) { } 
   static bool isaPointer(PyObject* pObj);
   PyObject* pythonValue(void);
   double doubleValue(void);
   void* pointerValue(void) { return *(char**) (pointer() + 4); }
};


class PythonValue
{
 public:
   PythonValue(PyObject* pObj, Type& ptrType);
   void pack(Buffer& buf, Type& ptrType);
 private:
   PyObject* pyValue;
};


#ifdef USE_JAVA_BUFFER

#include <jni.h>
#include <JBuffer.h>

// ----------------------------------------------------------------------
// Factory method returns correct buffer type to use for marshalling data.
// ----------------------------------------------------------------------
Buffer& getBuffer(void)
{
   if (gBuf != NULL) {
      gBuf->reset();	// reuse buffer, destroys/overwrites old contents
      return *gBuf;
   }

   JavaVM *jvm;       // denotes a Java VM
   JNIEnv *jenv;      // pointer to native method interface
    
   JDK1_1InitArgs vm_args; // JDK 1.1 VM initialization arguments
   
   vm_args.version = 0x00010001; // New in 1.1.2: VM version
   // Get the default initialization arguments and set the class path
   JNI_GetDefaultJavaVMInitArgs(&vm_args);

   vm_args.classpath = "/usr/local/packages/jdk/lib/classes.zip"
		       ":/home/rasmussn/siloon/src/java/siloon";
    
    // load and initialize a Java VM, return a JNI interface pointer in env
    JNI_CreateJavaVM(&jvm, &jenv, &vm_args);
    
    jclass cls = jenv->FindClass("JBuffer");
    if (cls == NULL) {
      printf("SClient: FAILED to find JBuffer class\n");
      exit(1);
    }

    jmethodID mid = jenv->GetMethodID(cls, "<init>", "()V");
    if (mid == 0) {
      printf("SClient: FAILED to get JBuffer constructor id\n");
      exit(1);
    }

    jobject jbuf = jenv->NewObject(cls, mid);
    gBuf = new JBuffer(jenv, jbuf);
    return *gBuf;
}

#else

Buffer& getBuffer(void)
{
   if (gBuf == NULL) {
      gBuf = new LocalBuffer(INVOKE_BUF_SIZE);
   } else {
       gBuf->reset();	// reuse buffer, destroys/overwrites old contents
   }
   return *gBuf;
}

#endif


//
// Define a local exception object and a macro to raise exceptions
//
static PyObject* SiloonError;		// local exception object
#define onError(message) \
	{ PyErr_SetString(SiloonError, message); return NULL; }


// pack/unpack a Python argument
static PyObject* packCArg(Buffer& buf, int i,
			  PyObject* arg, const Type& argType);
static int packFArg(Buffer& buf, int i, PyObject* arg, const Type& argType);
static PyObject* unpackFArg(Buffer& buf, const Type& argType);

// invokes function with given return type
static PyObject*
invokeWithCType(Buffer& buf, const char* sel, const Type& returnType);

#ifdef __cplusplus
extern "C" {
#endif

// function prototypes
static PyObject* siloon_python_read(PyObject* self, PyObject* args);
static PyObject* siloon_python_write(PyObject* self, PyObject* args);
static PyObject* siloon_python_invoke_C(PyObject* self, PyObject* args);
static PyObject* siloon_python_invoke_F(PyObject* self, PyObject* args);
static long packArray(Buffer& buf, PyObject* items, const Type& ptrType,
		      long count, bool packPointerHeader);
static PyObject* unpackArray(Buffer& buf, long count, const Type& ptrType);
bool nativeArrayType(PyObject* arg);

static struct PyMethodDef siloon_methods[] = {
   {"invoke_C", siloon_python_invoke_C, 1},
   {"invoke_F", siloon_python_invoke_F, 1},
   {"read", siloon_python_read, 1},
   {"write", siloon_python_write, 1},
   {NULL, NULL}
};


void initcca_siloon()
{
   PyObject *m, *d;

   // Python initializations
   m = Py_InitModule("cca_siloon", siloon_methods);
   d = PyModule_GetDict(m);
   SiloonError = PyString_FromString("siloon.error");
   PyDict_SetItemString(d, "error", SiloonError);
   if (PyErr_Occurred()) {
      Py_FatalError("Can't initialize module cca_siloon");
   }

   // C initializations
   siloon_init(prototypeMap);
}

//-----------------------------------------------------------------------------
// Read from a remote pointer into a python array.
//-----------------------------------------------------------------------------
static PyObject*
siloon_python_read(PyObject* self, PyObject* args)
{
   char msg[128];
   int nArgs = PyTuple_Size(args);
   if (nArgs < 2 || nArgs > 3) {
      sprintf(msg, "siloon::read(): wrong number of arguments (%d)", nArgs);
      onError(msg);
   }

   Buffer& buf = getBuffer();

   // create the receiving pointer object (pointers stored as 3-tuples)
   PythonClientPointer ptr(PyTuple_GetItem(args, 0));

   // get the count and offset

   long count;
   long offset = 0;

   PyObject* arg = PyTuple_GetItem(args, 1);
   if (!PyArg_Parse(arg, "l;count must be an integer", &count)) return NULL;

   if (nArgs == 3) {
      arg = PyTuple_GetItem(args, 2);
      if (!PyArg_Parse(arg, "l;offset must be an integer", &offset)) {
	 return NULL;
      }
   }

   ptr.packForRead(buf, count, offset);

   if (DEBUG_LEVEL > 3) {
      fprintf(stderr, "siloon_python_read: pointer = %p, count = %ld, "
	      "offset = %ld\n", ptr.pointerValue(), count, offset);
   }

   // call function
   ContextID target = 0;
   if (buf.sendGlobalCFunction(target) != SILOON_SUCCESS) {
      fprintf(stderr, "FAILED in calling remote write\n");
      return NULL;
   }

   // unpack the return arguments
   long nUnpacked;
   buf.openIStream();	// allows unpacking of current contents
   buf.unpack(&nUnpacked);
   if (nUnpacked != count) {
      fprintf(stderr, "FAILED in calling remote read, incorrect count, "
	      "is %ld, should be %ld\n", nUnpacked, count);
      return NULL;
   }

   // create a python tuple and unpack array from buf into python tuple
   return unpackArray(buf, count, ptr.type());
}


//-----------------------------------------------------------------------------
// Write from a local python array into a remote pointer.
//-----------------------------------------------------------------------------
static PyObject*
siloon_python_write(PyObject* self, PyObject* args)
{
   char msg[128];
   int nArgs = PyTuple_Size(args);
   if (nArgs < 3 || nArgs > 4) {
      sprintf(msg, "siloon::write(): wrong number of arguments (%d)", nArgs);
      onError(msg);
   }

   Buffer& buf = getBuffer();

   // create the receiving pointer object (pointers stored as 3-tuples)
   PythonClientPointer ptr(PyTuple_GetItem(args, 0));

   // get the source array object, count and offset

   long count;
   long offset = 0;
   PyObject* array = PyTuple_GetItem(args, 1);

   PyObject* arg = PyTuple_GetItem(args, 2);
   if (!PyArg_Parse(arg, "l;count must be an integer", &count)) return NULL;

   if (nArgs == 4) {
      arg = PyTuple_GetItem(args, 3);
      if (!PyArg_Parse(arg, "l;offset must be an integer", &offset)) {
	 return NULL;
      }
   }

   ptr.packForWrite(buf, count, offset);

   if (DEBUG_LEVEL > 3) {
      fprintf(stderr, "siloon_python_write: pointer = %p, count = %ld, "
	      "offset = %ld\n", ptr.pointerValue(), count, offset);
   }

   // pack the source array

   const Type& ptrType = ptr.type();
   long nPacked = packArray(buf, array, ptrType, count, false);
   if (nPacked != count) return NULL;

   // call function
   ContextID target = 0;
   if (buf.sendGlobalCFunction(target) != SILOON_SUCCESS) {
      fprintf(stderr, "FAILED in calling remote write\n");
      return NULL;
   }

   // unpack the return arguments
   buf.openIStream();	// allows unpacking of current contents
   buf.unpack(&nPacked);
   if (nPacked != count) {
      fprintf(stderr, "FAILED in calling remote write, incorrect count, "
	      "is %ld, should be %ld\n", nPacked, count);
      return NULL;
   }

   Py_INCREF(Py_None);
   return Py_None;
}


void resetBufferToReturn(Siloon::Buffer& buf)
{
      int* iptr;
      buf.openIStream();	// allows unpacking of current contents
      buf.unpackInPlace(iptr);      
      buf.unpackInPlace(iptr);      
}


static PyObject*
siloon_python_invoke_C(PyObject* self, PyObject* args)
{
   char* sel;
   char msg[512];
   int numPrototypeArgs, numDefaultPrototypeArgs, numActualFunctionArgs;
   
   if (DEBUG_LEVEL > 1) {
      printf("In siloon.invokeC()\n");
   }
   
   Buffer& buf = getBuffer();

   int numPythonArgs = PyTuple_Size(args);
   PyObject* arg = PyTuple_GetItem(args, 0);
   if (!PyArg_Parse(arg, "s;first argument must be a string selector", &sel)) {
      return NULL;
   }
   if (DEBUG_LEVEL > 3) {
      printf("siloon_invoke: selector = \"%s\", number of Python args = %d\n",
             sel, numPythonArgs);
   }

   //
   // Get the function Prototype using the given selector.
   //
   Prototype proto = (*prototypeMap)[sel];
   if (proto.functionId() == -1) {
      sprintf(msg, "siloon::invoke(): unknown function, \"%s\"", sel);
      onError(msg);
   }
   if (DEBUG_LEVEL > 3) {
      fprintf(stderr, "function id: %d, return type: %d\n",
	      proto.functionId(), proto.returnType().type());
   }

   numPrototypeArgs = proto.numberOfArgs();	// number of function arguments
   int iArg0 = 1;			// index of first function argument
   if (proto.isMethod() && !proto.isStaticMethod()) iArg0 += 1;

   proto.pack(buf);		// pack prototype as first item in the buffer

   // Number of C++ function arguments.
   numPrototypeArgs = proto.numberOfArgs();
   // Number of C++ function arguments that are optional (defaulted).
   numDefaultPrototypeArgs = proto.numberOfDefaultArgs();
   // Number of actual Python function arguments that correspond to function
   // arguments (not function ID or object pointer).
   numActualFunctionArgs = numPythonArgs - iArg0;
   
   //
   // Check Arguments.  The number of Python args must match the number of
   // declared prototype args (plus 1 (selector).
   //
   if (numPrototypeArgs + iArg0 > SIL_MAX_ARGS) {
      sprintf(msg, "siloon::invoke(): too many arguments, "
	           "maximum is %d.\n", SIL_MAX_ARGS - iArg0);
      onError(msg);
   }
   // Check if number of perl args matches number of declared prototype args.
   // The accepted range is [numPrototypeArgs - numDefaultPrototypeArgs,
   // numPrototypeArgs], since we allow default argument values.
   if (numActualFunctionArgs < numPrototypeArgs - numDefaultPrototypeArgs ||
       numActualFunctionArgs > numPrototypeArgs) {
      sprintf(msg, "siloon::invoke(): wrong number of arguments, "
	      "%d vs. expected range of %d-%d.\n", numActualFunctionArgs,
	      numPrototypeArgs - numDefaultPrototypeArgs,
	      numPrototypeArgs);
      onError(msg);
   }

   // Pack the actual number of arguments.
   buf.pack(numActualFunctionArgs);
   if (DEBUG_LEVEL > 3) {
      fprintf(stderr, "Packed number of python args: %d.\n",
	      numActualFunctionArgs);
   }

   //
   // Pack the this pointer, if necessary.
   //
   if (proto.isMethod() && !proto.isStaticMethod()) {
      arg = PyTuple_GetItem(args, 1);
      Py_INCREF(arg);

      // pack the this pointer object (pointers stored as 3-tuples)
      PythonClientPointer ptr(arg);
      ptr.pack(buf);
      if (DEBUG_LEVEL > 3) {
	 fprintf(stderr, "Packed object pointer: %p.\n", ptr.pointerValue());
      }
      Py_DECREF(arg);
   }

   //
   // Iterate over the arguments, packing them into the buffer.
   //
   for (int i = 0; i < numActualFunctionArgs; i++) {
      arg = PyTuple_GetItem(args, i + iArg0);
      Py_INCREF(arg);

      if (packCArg(buf, i, arg, proto.argTypeN(i)) == NULL) {
	 sprintf(msg, "siloon::invoke(), FAILED to pack argument %d, unknown "
		 "argument type", i+1);
	 onError(msg);
      }
      Py_DECREF(arg);
   }

   //
   // Now make the call with the buffer that's ready to go.
   //

   return invokeWithCType(buf, sel, proto.returnType());
}


static PyObject*
siloon_python_invoke_F(PyObject* self, PyObject* args)
{
   char* sel;
   char msg[512];
   int numPrototypeArgs, numDefaultPrototypeArgs, numActualFunctionArgs;
   
   int error = 0;
   PyObject* rtnVal = Py_None;

   if (DEBUG_LEVEL > 1) {
      printf("In siloon.invokeF()\n");
   }
   
   Buffer& buf = getBuffer();

   int numPythonArgs = PyTuple_Size(args);
   PyObject* arg = PyTuple_GetItem(args, 0);
   if (!PyArg_Parse(arg, "s;first argument must be a string selector", &sel)) {
      return NULL;
   }
   if (DEBUG_LEVEL > 3) {
      printf("siloon_invoke: selector = \"%s\", number of Python args = %d\n",
             sel, numPythonArgs);
   }

   //
   // Get the function Prototype using the given selector.
   //
   Prototype proto = (*prototypeMap)[sel];
   if (proto.functionId() == -1) {
      sprintf(msg, "siloon::invoke(): unknown function, \"%s\"", sel);
      onError(msg);
   }
   if (DEBUG_LEVEL > 3) {
      fprintf(stderr, "function id: %d, return type: %d\n",
	      proto.functionId(), proto.returnType().type());
   }

   numPrototypeArgs = proto.numberOfArgs();	// number of function arguments
   int iArg0 = 1;			// index of first function argument

   proto.pack(buf);		// pack prototype as first item in the buffer

   // Number of Fortran function arguments.
   numPrototypeArgs = proto.numberOfArgs();
   // Number of Fortran function arguments that are optional (defaulted).
   numDefaultPrototypeArgs = proto.numberOfDefaultArgs();
   // Number of actual Python function arguments that correspond to function
   // arguments (not function ID or object pointer).
   numActualFunctionArgs = numPythonArgs - iArg0;
   
   //
   // Check Arguments.  The number of Python args must match the number of
   // declared prototype args (plus 1 (selector).
   //
   if (numPrototypeArgs + iArg0 > SIL_MAX_ARGS) {
      sprintf(msg, "siloon::invoke(): too many arguments, "
	           "maximum is %d.\n", SIL_MAX_ARGS - iArg0);
      onError(msg);
   }
   // Check if number of Python args matches number of declared prototype args.
   // The accepted range is [numPrototypeArgs - numDefaultPrototypeArgs,
   // numPrototypeArgs], since we allow default argument values.
   if (numActualFunctionArgs < numPrototypeArgs - numDefaultPrototypeArgs ||
       numActualFunctionArgs > numPrototypeArgs) {
      sprintf(msg, "siloon::invoke(): wrong number of arguments, "
	      "%d vs. expected range of %d-%d.\n", numActualFunctionArgs,
	      numPrototypeArgs - numDefaultPrototypeArgs,
	      numPrototypeArgs);
      onError(msg);
   }

   // Pack the actual number of arguments.
   buf.pack(numActualFunctionArgs);
   if (DEBUG_LEVEL > 3) {
      fprintf(stderr, "Packed number of python args: %d.\n",
	      numActualFunctionArgs);
   }

   //
   // Pack placeholder for return type.
   //
   if (packFArg(buf, -1, NULL, proto.returnType()) == SILOON_FAILURE) {
     sprintf(msg, "siloon::invoke(), FAILED to pack return, unknown "
	          "return type");
     onError(msg);
   }

   //
   // Iterate over the arguments, packing them into the buffer.
   //
   for (int i = 0; i < numActualFunctionArgs; i++) {
      arg = PyTuple_GetItem(args, i + iArg0);
      Py_INCREF(arg);

      if (packFArg(buf, i, arg, proto.argTypeN(i)) == SILOON_FAILURE) {
	 sprintf(msg, "siloon::invoke(), FAILED to pack argument %d, unknown "
		 "argument type", i+1);
	 onError(msg);
      }
      Py_DECREF(arg);
   }

   //
   // Now make the call with the buffer that's ready to go.
   //
   ContextID target = 0;
   int rtntype = proto.returnType().type();
   int subtype = proto.returnType().subtype();

   switch(rtntype) {
   case pdbItem::TY_FVOID: {
     if (DEBUG_LEVEL > 3) {
       fprintf(stderr, "Calling a function that returns void.\n");
     }
     error = buf.sendGlobalFFunction(target);
     resetBufferToReturn(buf);
     break;
   }
   case pdbItem::TY_FCHAR: {
     // This is a string.
     string sResult;
     if (DEBUG_LEVEL > 3) {
       fprintf(stderr, "Calling a function that returns a string.\n");
     }
     error = buf.sendGlobalFFunction(target);
     resetBufferToReturn(buf);
     rtnVal = unpackFArg(buf, proto.returnType());
     break;
   }
   case pdbItem::TY_FPTR:	// pointers and arrays passed by int handles
   case pdbItem::TY_FARRAY:	// note fall through
   case pdbItem::TY_FLOGIC:	// note fall through
   case pdbItem::TY_FINT: {
     if (DEBUG_LEVEL > 3) {
       fprintf(stderr, "Calling a function that returns an int.\n");
     }
     error = buf.sendGlobalFFunction(target);
     resetBufferToReturn(buf);
     rtnVal = unpackFArg(buf, proto.returnType());
     break;
   }
   case pdbItem::TY_FFLOAT: {
     double dResult;
     if (DEBUG_LEVEL > 3) {
       fprintf(stderr, "Calling a function that returns a float.\n");
     }
     error = buf.sendGlobalFFunction(target);
     resetBufferToReturn(buf);
     rtnVal = unpackFArg(buf, proto.returnType());
     break;
   }
   case pdbItem::TY_FCMPLX: {
     double cmplx[2];
     if (DEBUG_LEVEL > 3) {
       fprintf(stderr, "Calling a function that returns a complex.\n");
     }
     error = buf.sendGlobalFFunction(target);
     resetBufferToReturn(buf);
     rtnVal = unpackFArg(buf, proto.returnType());
     break;
   }
   default: {
      sprintf(msg, "siloon::invoke(), FAILED to call function with return "
	      "type %d, unknown return type", proto.returnType().type());
      onError(msg);
   }
   }

   if (error != SILOON_SUCCESS) {
      sprintf(msg, "siloon::invoke(), error %d returned by function \"%s\"",
	           error, sel);
      onError(msg);
   }

   //
   // Iterate over the arguments, unpacking them from the buffer.
   //
   //   for (int i = 0; i < numActualFunctionArgs; i++) {
   //      arg = unpackFArg(buf, proto.argTypeN(i));
   //      PyTuple_SetItem(args, i + iArg0, arg);
   //      Py_INCREF(arg);
   //   }

   if (DEBUG_LEVEL > 4) {
      printf("python_invoke(): finished\n");
   }

   if (rtnVal == Py_None) Py_INCREF(rtnVal);
   return rtnVal;
}

#ifdef __cplusplus
};
#endif


static PyObject*
invokeWithCType(Buffer& buf, const char* sel, const Type& returnType)
{
   int error = 0;
   char msg[512];
   ContextID target = 0;
   PyObject* rtnVal = Py_None;

   int rtntype = returnType.type();
   int subtype = returnType.subtype();

   switch(rtntype) {
   case pdbItem::TY_VOID: {
      if (DEBUG_LEVEL > 3) {
	 fprintf(stderr, "Calling a function that returns void.\n");
      }
      error = buf.sendGlobalCFunction(target);
      break;
   }
   case pdbItem::TY_BOOL:	// note fall through
   case pdbItem::TY_ENUM:	// note fall through
   case pdbItem::TY_INT: {
      long lResult;
      if (DEBUG_LEVEL > 3) {
	 fprintf(stderr, "Calling a function that returns an int.\n");
      }
      error = buf.sendGlobalCFunction(target);
      buf.openIStream();	// allows unpacking of current contents

      if (rtntype == pdbItem::TY_BOOL) {
	 bool val;
	 buf.unpack(&val);
	 lResult = long(val);
      } else if (buf.unpackLong(lResult, subtype) != SILOON_SUCCESS) {
	 fprintf(stderr, "Unsupported integer type.\n");
      }
      if (DEBUG_LEVEL > 3) {
	 fprintf(stderr, "Return value is %ld\n", lResult);
      }
      rtnVal = Py_BuildValue("l", lResult);
      break;
   }
   case pdbItem::TY_FLOAT: {
      double dResult;
      if (DEBUG_LEVEL > 3) {
	 fprintf(stderr, "Calling a function that returns a float.\n");
      }

      error = buf.sendGlobalCFunction(target);
      buf.openIStream();	// allows unpacking of current contents

      if (buf.unpackDouble(dResult, subtype) != SILOON_SUCCESS) {
	 fprintf(stderr, "Unsupported float type.\n");
      }
      if (DEBUG_LEVEL > 3) {
	 fprintf(stderr, "Return value is %lf\n", dResult);
      }
      rtnVal = Py_BuildValue("d", dResult);
      break;
   }
   case pdbItem::TY_PTR: {
      // Pointers are special cases.  A char * is returned to perl as a
      // string, while any other pointer type is returned as a double.
      const Type *ptrType = returnType.indirectType();
      switch (ptrType->type()) {
      case pdbItem::TY_INT: {
	 if (ptrType->subtype() == pdbItem::I_CHAR) {
	    // This is a string.
	    string sResult;
	    if (DEBUG_LEVEL > 3) {
	       fprintf(stderr, "Calling a function that returns a string.\n");
	    }
	    error = buf.sendGlobalCFunction(target);
	    buf.openIStream();	// allows unpacking of current contents
	    buf.unpack(sResult);
	    if (DEBUG_LEVEL > 3) {
	      fprintf(stderr, "Return value is %s\n", sResult.c_str());
	    }
	    rtnVal = Py_BuildValue("s", sResult.c_str());
	    break;
	 }
      }
      default: {
         // This is something other than char *.
	 if (DEBUG_LEVEL > 3) {
	    fprintf(stderr, "Calling a function that returns a pointer.\n");
	 }
	 error = buf.sendGlobalCFunction(target);
	 buf.openIStream();	// allows unpacking of current contents
	 PythonClientPointer cp(buf);
	 if (DEBUG_LEVEL > 3) {
	    fprintf(stderr, "Return value is %p\n", cp.pointerValue());
	 }
	 rtnVal = cp.pythonValue();
	 break;
      }
      }
      break;
   }
   case pdbItem::TY_REF: {
      // References are also special cases.  A const string& is returned to
      // python as a string, while any other pointer type is returned as a
      // double.
      const Type* refType = returnType.indirectType();
      if (refType != NULL && refType->type() == pdbItem::TY_GROUP
	                  && refType->subtype() == pdbItem::GR_CLASS
	                  && refType->qualifier() == pdbItem::QL_CONST
	                  && refType->sclassType() == Type::SCL_STRING) {
	 // This is: const string &
	 string sResult;
	 if (DEBUG_LEVEL > 3) {
	    fprintf(stderr, "Calling a function that returns a string.\n");
	 }
	 error = buf.sendGlobalCFunction(target);
	 buf.openIStream();	// allows unpacking of current contents
	 buf.unpack(sResult);
	 if (DEBUG_LEVEL > 3) {
	    fprintf(stderr, "Return value is %s\n", sResult.c_str());
	 }
	 rtnVal = Py_BuildValue("s", sResult.c_str());
	 break;
      } else if (refType != NULL && Type::isElemental(*refType)) {
	 // reference to basic type, packed directly
	 if (DEBUG_LEVEL > 3) {
	    fprintf(stderr, "Calling a function that returns a reference.\n");
	 }
	 return invokeWithCType(buf, sel, *refType);
      } else {
         // Treat as a generic pointer, unpack a pointer (stored as 8 bytes)
	 // to an object on the server
	 if (DEBUG_LEVEL > 3) {
	    fprintf(stderr, "Calling a function that returns a reference.\n");
	 }
	 error = buf.sendGlobalCFunction(target);
	 buf.openIStream();	// allows unpacking of current contents
	 PythonClientPointer cp(buf);
	 if (DEBUG_LEVEL > 3) {
	    fprintf(stderr, "Return value is %p\n", cp.pointerValue());
	 }
	 rtnVal = cp.pythonValue();
	 break;
      }
   }
   case pdbItem::TY_TREF: {
      // This type could be a std::string (a typecast basic_string)
      const Type* refType = returnType.indirectType();
      if (refType != NULL && refType->type() == pdbItem::TY_GROUP
	                  && refType->subtype() == pdbItem::GR_CLASS
	                  && refType->sclassType() == Type::SCL_STRING) {
         // This is a "std::string"
	 string sResult;
	 if (DEBUG_LEVEL > 3) {
	    fprintf(stderr, "Calling a function that returns a string.\n");
	 }
	 error = buf.sendGlobalCFunction(target);
	 buf.openIStream();	// allows unpacking of current contents
	 buf.unpack(sResult);
	 if (DEBUG_LEVEL > 3) {
	    fprintf(stderr, "Return value is %s\n", sResult.c_str());
	 }
	 rtnVal = Py_BuildValue("s", sResult.c_str());
      } else {
	 sprintf(msg, "invokeWithCType(), FAILED to call function with return "
		 "type %d, unknown return type", rtntype);
	 onError(msg);
      }
      break;
   }
   default: {
      sprintf(msg, "invokeWithCType(), FAILED to call function with return "
	      "type %d, unknown return type", rtntype);
      onError(msg);
   }
   }

   if (error != SILOON_SUCCESS) {
      sprintf(msg, "invokeWithCType(), error %d returned by function \"%s\"",
	           error, sel);
      onError(msg);
   }

   if (rtnVal == Py_None) Py_INCREF(rtnVal);
   return rtnVal;
}


//--- packArray ---------------------------------------------------------------
// Packs the contents of an array into a buffer.
//
// buf -- receiving buffer
// items -- python list or tuple containing source array
// ptrType -- type of contents of array
// count -- number of items to pack
// packPointerHeader -- pack pointer header if true
//
// Returns the number of items packed
//-----------------------------------------------------------------------------
static long packArray(Buffer& buf, PyObject* items, const Type& ptrType,
		      long count, bool packPointerHeader)
{
   char msg[128];
   long size = 0;
   PyObject* (*getItem)(PyObject*, int);

   if (PyList_Check(items)) {
      size = PyList_Size(items);
      getItem = &PyList_GetItem;
   } else if (PyTuple_Check(items)) {
      size = PyTuple_Size(items);
      getItem = &PyTuple_GetItem;
   } else {
      sprintf(msg, "Source is not an array type (must be a list or tuple).\n");
      PyErr_SetString(SiloonError, msg);
      return 0;
   }

   if (size > count) {
      size = count;
   } else if (size < count) {
      sprintf(msg, "Source array size is too small, must be >= %ld.\n", count);
      PyErr_SetString(SiloonError, msg);
      return 0;
   }

   if (packPointerHeader) {
      // create a client pointer to pack initial array information
      ClientPointer cp;
      cp.setType(ptrType);
      cp.beginPackArray(buf, count);
   }

   int nPacked = 0;
   switch(ptrType.type()) {
     case pdbItem::TY_VOID: {
        fprintf(stderr, "ERROR, can't pack void array.\n");
	return -1;
     }
     case pdbItem::TY_BOOL:	// note fall through
     case pdbItem::TY_ENUM:	// note fall through
     case pdbItem::TY_INT: {
        for (int i = 0; i < size; i++) {
	   long lVal;
	   PyObject* item = getItem(items, i);
	   if (!PyArg_Parse(item, "l;array argument must be an integer",
			           &lVal)) {
	      return -1;	// error
	   }
	   if (ptrType.type() == pdbItem::TY_BOOL) {
	     buf.pack( bool(lVal) );
	     nPacked += 1;
	   } 
	   else if (buf.packLong(lVal, ptrType.subtype()) != SILOON_SUCCESS) {
	      fprintf(stderr, "Unsupported integer subtype = %ld.\n", lVal);
	   } else {
	     nPacked += 1;
	   }
	}
	if (DEBUG_LEVEL > 3) {
	   fprintf(stderr, "Packed %ld TY_INT array arguments.\n", size);
	}
	break;
     }
     case pdbItem::TY_FLOAT: {
        for (int i = 0; i < size; i++) {
	   double rVal;
	   PyObject* item = getItem(items, i);
	   if (!PyArg_Parse(item, "d;array argument must be a float",
			           &rVal)) {
	      return -1;	// error
	   }
	   if (buf.packDouble(rVal, ptrType.subtype()) != SILOON_SUCCESS) {
	      fprintf(stderr, "Unsupported float subtype = %f.\n", rVal);
	   } else {
	     nPacked += 1;
	   }
	}
	if (DEBUG_LEVEL > 3) {
	   fprintf(stderr, "Packed %ld TY_FLOAT array arguments.\n", size);
	}
	break;
     }
   }

   if (count != nPacked) {
      sprintf(msg, "Error packing array, packed %d out of %ld "
	           "elements.\n", nPacked, count);
      PyErr_SetString(SiloonError, msg);
   }
   return nPacked;
}


//--- unpackArray -------------------------------------------------------------
// Unpacks the contents of an array into a buffer.
//
// buf -- receiving buffer
// count -- number of items to pack
// ptrrType -- pack pointer type if true, nothing otherwise
//
// Returns the number of items packed
//-----------------------------------------------------------------------------
static PyObject* unpackArray(Buffer& buf, long count, const Type& ptrType)
{
   // create a python tuple to hold the data
   PyObject* tuple = PyTuple_New(count);

   switch(ptrType.type()) {
     case pdbItem::TY_VOID: {
        fprintf(stderr, "ERROR, can't unpack void array.\n");
	return NULL;
     }
     case pdbItem::TY_BOOL:	// note fall through
     case pdbItem::TY_ENUM:	// note fall through
     case pdbItem::TY_INT: {
        for (int i = 0; i < count; i++) {
	  long lVal;
	  if (ptrType.type() == pdbItem::TY_BOOL) {
	    bool val;
	    buf.unpack(&val);
	    lVal = long(val);
	  }
	  else if (buf.unpackLong(lVal, ptrType.subtype()) != SILOON_SUCCESS) {
	    fprintf(stderr, "Unsupported integer type.\n");
	  }
	  PyTuple_SetItem(tuple, i, Py_BuildValue("l", lVal));
	}
	if (DEBUG_LEVEL > 3) {
	  fprintf(stderr, "Unpacked %ld TY_INT array arguments.\n", count);
	}
	break;
     }
     case pdbItem::TY_FLOAT: {
        for (int i = 0; i < count; i++) {
	   double rVal;
	   if (buf.unpackDouble(rVal, ptrType.subtype()) != SILOON_SUCCESS) {
	      fprintf(stderr, "Unsupported float type.\n");
	   }
	   PyTuple_SetItem(tuple, i, Py_BuildValue("d", rVal));
	}
	if (DEBUG_LEVEL > 3) {
	   fprintf(stderr, "Packed %ld TY_FLOAT array arguments.\n", count);
	}
	break;
     }
   }
   return tuple;
}


//-----------------------------------------------------------------------------
// Packs a Python argument into the provided buffer.  Returns NULL on an
// error.
//-----------------------------------------------------------------------------
static PyObject* packCArg(Buffer& buf, int i,
			  PyObject* arg, const Type& argType)
{
   char msg[512];
   int type = argType.type();
   int subtype = argType.subtype();

   switch(type) {
     case pdbItem::TY_VOID: {
        fprintf(stderr, "Probable error, not packing void arg%d.\n", i);
	break;
     }
     case pdbItem::TY_BOOL:	// note fall through
     case pdbItem::TY_ENUM:	// note fall through
     case pdbItem::TY_INT: {
        long lVal = 0;
	if (!PyArg_Parse(arg, "l;argument must be an integer", &lVal)) {
	   return NULL;
	}
	if (type == pdbItem::TY_BOOL) {
	  buf.pack( bool(lVal) );
	} else if (buf.packLong(lVal, subtype) != SILOON_SUCCESS) {
	   fprintf(stderr, "Unsupported integer subtype = %ld.\n", lVal);
	}
	if (DEBUG_LEVEL > 3) {
	   fprintf(stderr, "Packed TY_INT argument: %ld.\n", lVal);
	}
	break;
     }
     case pdbItem::TY_FLOAT: {
        double rVal = 0.0;
	if (!PyArg_Parse(arg, "d;argument must be a float", &rVal)) {
	   return NULL;
	}
	if (buf.packDouble(rVal, subtype) != SILOON_SUCCESS) {
	   fprintf(stderr, "Unsupported float type = %f.\n", rVal);
	}
	if (DEBUG_LEVEL > 3) {
	   fprintf(stderr, "Packed TY_FLOAT argument: %f.\n", rVal);
	}
	break;
     }
     case pdbItem::TY_GROUP: {
	if (   argType.subtype() == pdbItem::GR_CLASS
	    && argType.sclassType() == Type::SCL_STRING) {
	   // This is a "std::string"
	   char* szVal;
	   if (PyString_Check(arg)) {
	      if (!PyArg_Parse(arg, "s;argument must be a string", &szVal)) {
	         return NULL;
	      }
	      buf.packCString(szVal);
	      if (DEBUG_LEVEL > 3) {
	         fprintf(stderr, "Packed string argument: \"%s\".\n", szVal);
	      }
	   }
	} else {
	   return NULL;
	}
	break;
     }
     case pdbItem::TY_PTR: {
        // Pointers are special cases.  A char* is returned to python as a
        // string, while other pointer types are normally returned as an
        // 8 byte quantity.  However, if the python arg is a list or a
        // tuple, pack an array.
        Type* ptrType = argType.indirectType();
	if (ptrType != NULL && ptrType->type() == pdbItem::TY_INT
	                    && ptrType->subtype() == pdbItem::I_CHAR) {

	   // this pointer is assumed to be a NULL terminated C string
	   char* szVal;
	   if (PyString_Check(arg)) {
	      if (!PyArg_Parse(arg, "s;argument must be a string", &szVal)) {
		 return NULL;
	      }
	      buf.packCString(szVal);
	      if (DEBUG_LEVEL > 3) {
		 fprintf(stderr, "Packed string argument: \"%s\".\n", szVal);
	      }
	   } else {
	      sprintf(msg, "argument %d, python string type expected.\n", i);
	      onError(msg);
	   }
	} else {
	   if (! (PyTuple_Check(arg) || PyList_Check(arg)) ) {
	      sprintf(msg, "argument %d, pointer or array type expected.\n",i);
	      onError(msg);
	   } else if (nativeArrayType(arg)) {
	      // pack an array
	      long size = 0;
	      if (PyList_Check(arg) ) size = PyList_Size(arg);
	      if (PyTuple_Check(arg)) size = PyTuple_Size(arg);
	      long nPacked = packArray(buf, arg, *ptrType, size, true);
	      if (nPacked != size) {
	          fprintf(stderr, "FAILED to pack array of correct size, "
			          "%ld(%ld)\n", nPacked, size);
		  return NULL;
	      }
	   } else {
	      // pack a pointer object (pointers stored as 3-tuples)
	      PythonClientPointer ptr(arg);
	      ptr.pack(buf);
	      if (DEBUG_LEVEL > 3) {
	         fprintf(stderr, "Packed TY_PTR argument: %p.\n",
                                 ptr.pointerValue());
	      }
	   }
	}
	break;
     }
     case pdbItem::TY_REF: {
        // Two possibilities exist:
        // 1. The argument is stored as a pointer.  In this case just
        // pass the pointer on to the server.
        // 2. The argument is a ref to a supported type, pack it.

        if (PythonClientPointer::isaPointer(arg)) {
	   PythonClientPointer ptr(arg);
	   ptr.pack(buf);
	   if (DEBUG_LEVEL > 3) {
	      fprintf(stderr, "Packed TY_REF argument: %p.\n"
		            , ptr.pointerValue());
	   }
	} else {
	   // pack by value
	   Type* refType = argType.indirectType();
	   if (refType) {
	      packCArg(buf, i, arg, *refType);
	   } else {
	      return NULL;
	   }
	}
	break;
     }
     case pdbItem::TY_TREF: {
        // This type could be a std::string (a typecast basic_string)
	Type* refType = argType.indirectType();
	if (refType) {
	   packCArg(buf, i, arg, *refType);
	} else {
	   return NULL;
	}
	break;
     }
     default: {
        fprintf(stderr, "FAILED to Pack argument of type: %d.\n", type);
	return NULL;
     }
   }
   return arg;
}


//-----------------------------------------------------------------------------
// Packs a Python argument into the provided buffer.  If arg == NULL,
// packs an empty placeholder (e.g., for return values).  Returns NULL on an
// error.
//-----------------------------------------------------------------------------
int packFArg(Buffer& buf, int i, PyObject* arg, const Type& argType)
{
   char msg[512];
   int type = argType.type();
   int subtype = argType.subtype();

   switch(type) {
     case pdbItem::TY_FVOID: break;
     case pdbItem::TY_FCHAR: {
        // this pointer is assumed to be a NULL terminated C string
        char* szVal;
	long count = argType.numElements();
	if (!arg) {
	  // a string return, cannot be variable length
	  if (argType.sclassType() == Siloon::Type::SCL_FCHARVARLEN) {
	    PyErr_SetString(SiloonError, "FORTRAN string error in packFArg\n");
	    return SILOON_FAILURE;
	  }
	  szVal = (char*) malloc(1 + count);
	  szVal[count] = '\0';
	  buf.packPointer(szVal);
	  buf.addToFreeList(szVal);
	} else if (PyString_Check(arg)) {
	  if (!PyArg_Parse(arg, "s;argument must be a string", &szVal)) {
	    return SILOON_FAILURE;
	  }
	  size_t szValLength = strlen(szVal);
	  if (argType.sclassType() == Siloon::Type::SCL_FCHARVARLEN) {
	    // variable length string, use python string buffer
	    buf.packPointer(szVal);
	  } else {
	    // make a copy of the python string
	    char* cptr = (char*) malloc(1 + count);
	    for (int i = 0; i < count; i++) {
	      if (i < szValLength) cptr[i] = szVal[i];
	      else cptr[i] = ' ';
	    }
	    cptr[count] = '\0';
	    buf.packPointer(cptr);
	    buf.addToFreeList(cptr);
	  }
	} else {
	  sprintf(msg, "argument %d, python string type expected.\n", i);
	  PyErr_SetString(SiloonError, msg);
	  return SILOON_FAILURE;
	}
	if (DEBUG_LEVEL > 3) {
	  fprintf(stderr, "Packed string argument: \"%s\".\n", szVal);
	}
	break;
     }
     case pdbItem::TY_FPTR:	// pointers and arrays passed by int handles
     case pdbItem::TY_FARRAY:	// note fall through
     case pdbItem::TY_FLOGIC:	// note fall through
     case pdbItem::TY_FINT: {
        long lVal = 0;
	if (arg && !PyArg_Parse(arg, "l;argument must be an integer", &lVal)) {
	   return SILOON_FAILURE;
	}
	if (type == pdbItem::TY_FPTR || type == pdbItem::TY_FARRAY) {
	  subtype = pdbItem::I_INT;
	} else if (type == pdbItem::TY_FLOGIC) {
	  subtype = pdbItem::I_UCHAR;
	}
	if (buf.packLong(lVal, subtype) != SILOON_SUCCESS) {
	   fprintf(stderr, "Unsupported integer subtype = %ld.\n", lVal);
	}
	if (DEBUG_LEVEL > 3) {
	   fprintf(stderr, "Packed TY_INT argument: %ld.\n", lVal);
	}
	break;
     }
     case pdbItem::TY_FFLOAT: {
        double rVal = 0.0;
	if (arg && !PyArg_Parse(arg, "d;argument must be a float", &rVal)) {
	   return SILOON_FAILURE;
	}
	if (buf.packDouble(rVal, subtype) != SILOON_SUCCESS) {
	   fprintf(stderr, "Unsupported float type = %f.\n", rVal);
	}
	if (DEBUG_LEVEL > 3) {
	   fprintf(stderr, "Packed TY_FLOAT argument: %f.\n", rVal);
	}
	break;
     }
     case pdbItem::TY_FCMPLX: {
        Py_complex c;
	c.real = 0.0;
        c.imag = 0.0;
	if (arg && !PyArg_Parse(arg, "D;argument must be complex", &c)) {
	   return SILOON_FAILURE;
	}
	if (buf.packDouble(c.real, subtype) != SILOON_SUCCESS) {
	   fprintf(stderr, "Unsupported float type = %f.\n", c.real);
	}
	if (buf.packDouble(c.imag, subtype) != SILOON_SUCCESS) {
	   fprintf(stderr, "Unsupported float type = %f.\n", c.imag);
	}
	if (DEBUG_LEVEL > 3) {
	   fprintf(stderr, "Packed TY_FCMPLX argument: %lf, %lf.\n",
		           c.real, c.imag);
	}
	break;
     }
     default: {
        fprintf(stderr, "FAILED to Pack argument of type: %d.\n",
		argType.type());
	return SILOON_FAILURE;
     }
   }
   return SILOON_SUCCESS;
}


//-----------------------------------------------------------------------------
// Unpacks a Python argument from the provided buffer.  Returns NULL on an
// error.
//-----------------------------------------------------------------------------
PyObject* unpackFArg(Buffer& buf, const Type& argType)
{
   char msg[512];
   int type = argType.type();
   int subtype = argType.subtype();

   PyObject* rtnVal = Py_None;

   switch(type) {
     case pdbItem::TY_FVOID: break;
     case pdbItem::TY_FCHAR: {
        // this pointer is assumed to be a NULL terminated C string
        char* cptr;
	buf.unpackPointer((void*)cptr);
	rtnVal = Py_BuildValue("s", cptr);

	if (DEBUG_LEVEL > 3) {
	  fprintf(stderr, "Unpacked string argument: \"%s\".\n", cptr);
	}
	break;
     }
     case pdbItem::TY_FPTR:	// pointers and arrays passed by int handles
     case pdbItem::TY_FARRAY:	// note fall through
     case pdbItem::TY_FLOGIC:	// note fall through
     case pdbItem::TY_FINT: {
       long lVal;
	if (type == pdbItem::TY_FPTR || type == pdbItem::TY_FARRAY) {
	  subtype = pdbItem::I_INT;
	} else if (type == pdbItem::TY_FLOGIC) {
	  subtype = pdbItem::I_UCHAR;
	}
	switch(subtype) {
	  case pdbItem::I_CHAR:
	  case pdbItem::I_SCHAR:
	  case pdbItem::I_UCHAR: {
	    unsigned char* val;
	    buf.unpackInPlace(val);
	    lVal = long(*val);
	    break;
	  }
	  case pdbItem::I_SHORT:
	  case pdbItem::I_USHORT: {
	    unsigned short* val;
	    buf.unpackInPlace(val);
	    lVal = long(*val);
	    break;
	  }
	  case pdbItem::I_INT:
	  case pdbItem::I_UINT: {
	    unsigned int* val;
	    buf.unpackInPlace(val);
	    lVal = long(*val);
	    break;
	  }
	  case pdbItem::I_LONG:
	  case pdbItem::I_ULONG: {
	    unsigned long* val;
	    buf.unpackInPlace(val);
	    lVal = long(*val);
	    break;
	  }
	}
	rtnVal = Py_BuildValue("l", lVal);

	if (DEBUG_LEVEL > 3) {
	   fprintf(stderr, "Packed TY_INT argument: %ld.\n", lVal);
	}
	break;
     }
     case pdbItem::TY_FFLOAT: {
        double rVal;
	switch(subtype) {
	  case pdbItem::FL_FLOAT: {
	    float* val;
	    buf.unpackInPlace(val);
	    rVal = double(*val);
	    break;
	  }
	  case pdbItem::FL_DBL: {
	    double* val;
	    buf.unpackInPlace(val);
	    rVal = double(*val);
	    break;
	  }
	}
	rtnVal = Py_BuildValue("d", rVal);

	if (DEBUG_LEVEL > 3) {
	   fprintf(stderr, "Packed TY_FLOAT argument: %f.\n", rVal);
	}
	break;
     }
     case pdbItem::TY_FCMPLX: {
        double cmplx[2];
	switch(subtype) {
	  case pdbItem::FL_FLOAT: {
	    Siloon::ComplexFloat* c;
	    buf.unpackInPlace(c);
	    cmplx[0] = double(c->real);
	    cmplx[1] = double(c->imag);
	    break;
	  }
	  case pdbItem::FL_DBL: {
	    Siloon::ComplexDouble* c;
	    buf.unpackInPlace(c);
	    cmplx[0] = double(c->real);
	    cmplx[1] = double(c->imag);
	    rtnVal = PyComplex_FromDoubles(cmplx[0], cmplx[1]);
	    break;
	  }
	}
	rtnVal = PyComplex_FromDoubles(cmplx[0], cmplx[1]);

	if (DEBUG_LEVEL > 3) {
	   fprintf(stderr, "Unpacked TY_FCMPLX argument: %lf, %lf.\n",
		           cmplx[0], cmplx[1]);
	}
	break;
     }
   }

   return rtnVal;
}


//-----------------------------------------------------------------------------
// Construct a Pointer object from a Python tuple.  The pointer is stored as
// (pointer, context, (Type)).
//-----------------------------------------------------------------------------
PythonClientPointer::PythonClientPointer(PyObject* pObj) : ClientPointer()
{
   if (!PythonClientPointer::isaPointer(pObj)) {
      fprintf(stderr, "Pointer argument must be a tuple with 3 components\n");
      return;
   }

   // read pointer, context, and type variables

   double ptr, cid;
   PyObject* targ = PyTuple_GetItem(pObj, 0);
   if (!PyArg_Parse(targ, "d;pointer argument must be a float", &ptr)) return;
   targ = PyTuple_GetItem(pObj, 1);
   if (!PyArg_Parse(targ, "d;pointer argument must be a float", &cid)) return;
   PythonType type(PyTuple_GetItem(pObj, 2));

   setType(type);
   setContextID(cid);
   setPointer((char*) &ptr);

   if (DEBUG_LEVEL > 3) {
      fprintf(stderr, "Constructed Pointer object (%p, %lf, ())\n"
	            , pointerValue(), cid);
   }
}


//-----------------------------------------------------------------------------
// Return true if python object stores a pointer (ptr, context, (type)),
// false otherwise.
//-----------------------------------------------------------------------------
bool PythonClientPointer::isaPointer(PyObject* pObj)
{
   if (!PyTuple_Check(pObj))    return false;
   if (PyTuple_Size(pObj) != 3) return false;
   return true;
}


//-----------------------------------------------------------------------------
// Returns the python Tuple corresponding to this Pointer, represented as
// (ptr, context, (type))
//-----------------------------------------------------------------------------
PyObject* PythonClientPointer::pythonValue(void)
{
   PyObject* tuple = PyTuple_New(3);
   PyTuple_SetItem(tuple, 0, Py_BuildValue("d", doubleValue()));
   PyTuple_SetItem(tuple, 1, Py_BuildValue("d", context()));
   PyTuple_SetItem(tuple, 2, PythonType::pythonValue(type()));
   return tuple;
}


//-----------------------------------------------------------------------------
// Returns the double value of the Pointer.
//-----------------------------------------------------------------------------
double PythonClientPointer::doubleValue(void)
{
   double d;
   const char* ptr = pointer();
   memcpy(&d, ptr, 8);
   return d;
}


//-----------------------------------------------------------------------------
// Construct a Type object from a Python tuple.  The type is stored as
// (type, subtype, qualifier, (indirectType)).
//-----------------------------------------------------------------------------
PythonType::PythonType(PyObject* pObj) : Type(0)
{
   if (!PyTuple_Check(pObj)) {
      fprintf(stderr, "Type argument must be a tuple\n");
      return;
   }

   int nVals = PyTuple_Size(pObj);
   if (nVals < 3) {
      fprintf(stderr, "Type tuple argument must have at least 3 components\n");
      return;
   } else if (nVals > 4) {
      fprintf(stderr, "Type tuple argument has too many components (%d)\n"
	            , nVals);
      return;
   }

   // read and set the type, subtype, and qualifier variables

   long type, subtype, qual;
   PyObject* targ = PyTuple_GetItem(pObj, 0);
   if (!PyArg_Parse(targ, "l;type must be an integer", &type)) return;
   targ = PyTuple_GetItem(pObj, 1);
   if (!PyArg_Parse(targ, "l;subtype must be an integer", &subtype)) return;
   targ = PyTuple_GetItem(pObj, 2);
   if (!PyArg_Parse(targ, "l;qualifier must be an integer", &qual)) return;
   set(type, subtype, qual);

   if (DEBUG_LEVEL > 3) {
      fprintf(stderr, "Constructed type object (%ld, %ld, %ld)\n"
	            , type, subtype, qual);
   }

   // construct indirect type if present

   if (nVals == 4) {
      PythonType ind(PyTuple_GetItem(pObj, 3));
      setIndirectType(ind.type(), ind.subtype(), ind.qualifier());
      if (DEBUG_LEVEL > 3) {
	 fprintf(stderr, "Constructed indirect type object (%d, %d, %d)\n"
		       , ind.type(), ind.subtype(), ind.qualifier());
      }
   }
}


//-----------------------------------------------------------------------------
// Returns the python Tuple corresponding to this Type, represented as
// (type, subtype, qualifier, (indirectType)).
//-----------------------------------------------------------------------------
PyObject* PythonType::pythonValue(const Type& type)
{
   PyObject* tuple;
   Type* iType = type.indirectType();
   if (iType == NULL) { 
      tuple = PyTuple_New(3);
   } else {
      tuple = PyTuple_New(4);
      PyTuple_SetItem(tuple, 3, PythonType::pythonValue(*iType));
   }
   PyTuple_SetItem(tuple, 0, Py_BuildValue("i", type.type()));
   PyTuple_SetItem(tuple, 1, Py_BuildValue("i", type.subtype()));
   PyTuple_SetItem(tuple, 2, Py_BuildValue("i", type.qualifier()));
   return tuple;
}


//-----------------------------------------------------------------------------
// Returns true if a native array type, false if a pointer type
// ptr = (ptr, context, (type))
//-----------------------------------------------------------------------------
bool nativeArrayType(PyObject* arg)
{
   if (PyTuple_Check(arg)) {
      int nElements = PyTuple_Size(arg);
      if (nElements != 3) return true;
      PyObject* type = PyTuple_GetItem(arg, 2);

      // if the third item is a tuple, assume a pointer type rather than array
      if (PyTuple_Check(type)) return false;
   }
   return true;
}



//-----------------------------------------------------------------------------
// Construct a PythonValue object from a Python object of a given type t.
//-----------------------------------------------------------------------------
PythonValue::PythonValue(PyObject* pObj, Type& t) : pyValue(pObj)
{
   if (t.type() == pdbItem::TY_ENUM || t.type() == pdbItem::TY_BOOL
                                    || t.type() == pdbItem::TY_INT) {
     if (!PyInt_Check(pObj)) {
        fprintf(stderr, "Python argument must be of integer type.\n");
     }
   } else if (t.type() == pdbItem::TY_FLOAT) {
     if (!PyInt_Check(pObj) && !PyFloat_Check(pObj)) {
        fprintf(stderr, "Python argument must be of float type.\n");
     }
   } else if (   t.type() == pdbItem::TY_GROUP
	      && t.subtype() == pdbItem::GR_CLASS
              && t.sclassType() == Type::SCL_STRING) {
     if (!PyString_Check(pObj)) {
        fprintf(stderr, "Python argument must be a string.\n");
     }
   } else {
      fprintf(stderr, "Python argument is unsupported (can't be packed).\n");
   }
}


//-----------------------------------------------------------------------------
// Pack this value into the given buffer.  The value is packed as if it
// were an array of length 1.
//-----------------------------------------------------------------------------
void PythonValue::pack(Buffer& buf, Type& ptrType)
{
   // create a client pointer to pack initial array information

   if (PyString_Check(pyValue)) {
      char* szVal;
      PyArg_Parse(pyValue, "s", &szVal);
      buf.packCString(szVal);
      if (DEBUG_LEVEL > 3) {
	 fprintf(stderr, "Packed string argument: \"%s\"\n", szVal);
      }
      return;
   }

   ClientPointer cp;
   cp.setType(ptrType);
   cp.beginPackArray(buf, 1);

   if (PyInt_Check(pyValue) || PyFloat_Check(pyValue)) {
      packCArg(buf, -2, pyValue, ptrType);
   } else {
      fprintf(stderr, "Python argument is unsupported (can't be packed).\n");
   }
}
