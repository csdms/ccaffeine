#ifndef CCAFE_OPQ_H_SEEN
#define CCAFE_OPQ_H_SEEN

// This tells us what we'll need if we want to write
// around changes to this header with macros in binding codes.
#define CCAFEOPQ 0.1

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <complex>
#include <boost/shared_ptr.hpp>

#include "dc/export/config.hh"

/**
 * This namespace and set of interfaces allows multiple
 * c++ bindings of the cca specification to be accomodated in
 * CCAFFEINE. The overall functionality is a generic implementation
 * of the pattern (uses/provides) expressed in the CCA spec. The
 * documentation of the CCA spec remains in cca.sidl.
 * The comments in this file are oriented to noting 
 * behavioral differences and wrapper semantics, not to repeating
 * the content of cca.sidl.
 *
 * It is helpful to remember the terminology used when referring
 * to the pieces of the implementations.
 * 1) kernel -- the core implementation of the uses/provides
 *              pattern manager and basic services.
 *              Runs lists of components, ports, connections, etc.
 * 2) client/binding -- a layer binding this set of interfaces
 *                      to a particular c++ rendering of the CCA
 *                      specification.
 * 3) real -- term used to distinguish the instances of classes
 *            implemented in a specific binding. E.g. in a babel/c++
 *            binding of the cca specification, one creates a
 *            babel component and it uses/provides babel ports.
 *            In that babel scenario, the babel-implemented
 *            ports/components are the 'real' components/ports.
 *            These real components/ports must be wrapped in
 *            objects satisfying the definitions ccafeopq::Component
 *            and ccafeopq::Port in order to be managed by ccaffeine.
 *            Essentially 'real' is what the component writer does
 *            as opposed to the bookkeeping mechanisms of the
 *            ccafeopq interfaces or the ccaffeine framework kernel.
 *
 * Finally, where there's a standard for a mechanism, by god we're
 * gonna use it.
 */
namespace ccafeopq {

class Port;
class Services;
class ServicesHelper;
class Component;
class ComponentID_Interface;
class ConnectionID_Interface;
class TypeMap_Interface; 
class ComponentClassDescription_Interface; 
class PortInfo;
class FactoryService;

#ifdef _SLOPPY_OPAQUE_TYPEDEFS
typedef boost::shared_ptr< ComponentID_Interface > ComponentID;
typedef boost::shared_ptr< ComponentID_Interface > ComponentID_ptr;
typedef boost::shared_ptr< ConnectionID_Interface > ConnectionID;
typedef boost::shared_ptr< ConnectionID_Interface > ConnectionID_ptr;
typedef boost::shared_ptr< ComponentClassDescription_Interface > ComponentClassDescription;
typedef boost::shared_ptr< TypeMap_Interface > TypeMap;
typedef boost::shared_ptr< TypeMap_Interface > TypeMap_ptr;
#endif

typedef boost::shared_ptr< ComponentID_Interface > ComponentID_shared;
typedef boost::shared_ptr< ConnectionID_Interface > ConnectionID_shared;
typedef boost::shared_ptr< ComponentClassDescription_Interface > ComponentClassDescription_shared;
typedef boost::shared_ptr< TypeMap_Interface > TypeMap_shared;


typedef std::map<std::string, std::string> OpqMap;

//===================================================================
/*
  The strings below are just in the ccafeopq namespace.
  This is intentional to allow extension later in other files.
*/

/** Indicates a port defined in java land but compiled and accessible
 * from c++ by gnu gcj or ibm's aix xl compiler for java.
 */
const std::string JAVA_PORT = std::string("java-compiled-native"); 

/** Indicates a dccafe new-kernel c++ port- superceded by opq. */
const std::string CPP_PORT = std::string("c++-ccafe-cca-spec");

/** Indicates a cca-spec-neo c++ port. */
const std::string NEO_PORT = std::string("c++-cca-spec-neo");

/** Indicates a c++ bound babel port. */
const std::string BABEL_PORT = std::string("c++-sidl-babel");

/** Indicates a c++ bound pure ccafeopq port. */
const std::string OPAQUE_PORT = std::string("c++-pure-opq");

/** Indicates a port as defined by classic::gov::cca:: used in dccafe */
const std::string CLASSIC_PORT = std::string("c++-dccafe-cca-spec-classic");

/** Indicates an xcat c++ port binding. */
// const std::string XCAT_PORT = std::string("c++-xcat");
// Dennis is properly the one to define this string value.

/** Indicates a scirun port binding. */
//const std::string SCIRUN2_PORT = std::string("c++-scirun2");
// Steve is properly the one to define this string value.



//===================================================================

/** The wrapper of a port in a specific binding.
 * The wrapper objects inherit from ccafeopq::Port,
 * but the ports in the bound components do not.
 * Items of type ccafeopq::Port are wrappers of real
 * CCA Ports. These wrappers are implemented by the
 * binding implementer, not the kernel implementer.
 *
 * Memory Lifecycle:
 * Creation:
 *   The ccafeopq::Port is created to wrap around the
 *   real port by the binding implementation wrapped
 *   around the kernel supplied ccafeopq::Services.
 *   This occurs when the binding providing CCA Services
 *   to the real component receives the real port during
 *   the addProvidesPort call.
 * Sharing:
 *   The ccafeopq::Port object implemented will be returned
 *   to the Services wrapper during getPort calls. The wrapper
 *   will not need to check the type being one of its own,
 *   as this is guaranteed, but will still need to cast it
 *   back to its own type in order to extract the real port
 *   to hand to the using real component.
 * Destruction:
 *   The ccafeopq::Port will be returned to the Services
 *   wrapper which created the ccafeopq::Port at the
 *   end of a successful removeProvidesPort() call made
 *   on the ccafeopq::Services interface. At this point
 *   the kernel and other components will have no other
 *   references to the ccafeopq::Port and it may be
 *   deleted by the binding in any way desired.
 *   Whether this implies destroying the underlying real
 *   Port instance is up to the binding.
 *   
 */
class Port {
public:
  virtual ~Port(){}

  /** The kind/style/gender of Port this wrapper hides (i.e the
   * name used to distinguish the c++ binding from others.
   * The strings above in this header are possibly supported
   * kinds. However other kinds may be known or discovered at
   * runtime. This string exists solely for human consumption.
   */
  virtual const std::string getKind() = 0;

  /** Test if the kind/style/gender of a port is the
   * same as this one during connection process.
   * The kernel will not attempt to connect directly
   * any port pair that differs in binding kind.
   * This gets the framework out of the
   * business of knowing any particular set of strings
   * corresponding to getKind results.
   * This doesn't test the class (type) of the two ports.
   *
   * returns true if 
   * intersection(p->getSupportedKinds,this->getSupportedKinds) > 0.
   */
  virtual bool isSameKind(Port *p) = 0;

  /** It turns out that there may be multiple
    * kinds supported by the same implementation.
   * If true for the particular case, this function
   * returns true.
   */
  virtual bool supportsMultipleKinds() = 0;

  /**
  * Return list of supported kinds, which must contain
  * getKind() result but may contain nothing else.
  */
  virtual const std::vector< std::string > getSupportedKinds() = 0;

  virtual bool supportsKind( const std::string & k) = 0;
};

//===================================================================
 
/** This definition is (and will be revised as necessary if the
 * cca spec CCAExceptionType changes).
 * It cannot be
 * skipped here and done as an alias for enum gov::cca::CCAExceptionType
 * because that would require babel be present to use the
 * ccafeopq API. (And now babel owns ::gov::cca).
 * The definitions for these values are in cca.sidl.
 *
 *  The bindings must catch all 'real' CCAExceptions and convert
 *  them to the stl-derived exception below. Why?
 *  Because the kernel does not know the type(s) of the real CCAException
 *  in each binding, it cannot catch them.
 */ 
enum ExceptionType {
  Unexpected          = -1,
  Correct	      = 0,
  Nonstandard         = 1,
  PortNotDefined      = 2,
  PortAlreadyDefined  = 3,
  PortNotConnected    = 4,
  PortNotInUse        = 5,
  UsesPortNotReleased = 6,
  BadPortName         = 7,
  BadPortType         = 8,
  BadProperties       = 9,
  BadPortInfo         = 10,
  OutOfMemory         = 11,
  NetworkError        = 12
};

//===================================================================

/** This class extends the stl exception to allow the thrower
 * to specify the message that the stl says we return via what().
 * By default stl says strings come out but provides now way to
 * put them into its base class exception.
 *
 * Memory Lifecycle:
 * This exception is thrown with throw new ccafeopq::exception(...) .
 * The catcher, if any, is responsible for calling delete exceptionInstance;
 * or rethrowing if appropriate.
 */
class Exception : public ::std::exception
{
private:
	enum ExceptionType ccaType;
	::std::string  ccaMessage;

public:
	virtual ~Exception() throw (){}
	virtual const char *what() const throw() { return ccaMessage.c_str(); }

	Exception(enum ExceptionType t, const ::std::string & message) throw ()
	{ ccaType = t; ccaMessage = message;
		std::cout << "OPQ Exception formed: (" << t <<") " << message << std::endl;
       	}

	Exception(enum ExceptionType t) throw ()
       	{ ccaType = t; ccaMessage = std::string("");
		std::cout << "OPQ Exception formed enum: " << t << std::endl;
       	}

	Exception() throw ()
       	{ ccaType = Nonstandard; ccaMessage = std::string("Nonstandard cca");
		std::cout << "OPQ Exception formed enui: " << ccaMessage << std::endl;
       	}

	Exception(const std::string & message) throw ()
       	{ ccaType = Nonstandard; ccaMessage = message;
		std::cout << "OPQ Exception formed: " << ccaMessage << std::endl;
       	}

       enum ExceptionType getType() { return ccaType; }

       /** string form of what(). */
       const std::string getMessage() {return ccaMessage; }

       void setType( enum ExceptionType t) { ccaType = t; }

       void setMessage(const ::std::string & message) { 
		std::cout << "OPQ Exception message set: " << message << std::endl;
		ccaMessage = message;
       }

};

//===================================================================

/**
 * The kernel implements this interface and the binding provides
 * a wrapper around it during the call to 
 *   ccafeopq::Component::setServices(ccafeopq::Services *s);
 * The real component sees the wrapper as its CCA Services.
 *
 * Memory Lifecycle:
 *   Created by the kernel during setServices.
 *   Shared by the kernel and the wrapper while the component lives.
 *   Returned to the kernel during setServices(null,...) by the wrapper.
 *   Kernel then free to delete/recycle/whatever.
 */

class Services {

public:
  virtual ~Services(){}

  /** Get a Port by its instance name. The binding will then
   * unwrap the returned object to its proper binding specific type.
   **/
  virtual Port * getPort(const std::string & name, enum ExceptionType& status) throw(Exception) = 0;

  /** Release a previously obtained Port. */
  virtual void releasePort(const std::string & name) throw(Exception) = 0;

  /** The PortInfo which presumably came from createPortInfo is the
   * Services responsibility (i.e. it takes over the memory management
   * from here on) and the user code should no longer refer to the
   * pInfo passed in. If another PortInfo is needed createPortInfo should be
   * called again.
   * For supported keys in portinfo properties, see dc/export/ccafe_keys.hh.
   */
  virtual void registerUsesPort(PortInfo * pInfo) throw(Exception) = 0;

  /** For all future spec bindings use this one. For legacy bindings,
   * use the portinfo version above.
   * properties may be an empty/null typemap.
   * For supported keys in typemap, see dc/export/ccafe_keys.hh.
   */
  virtual void registerUsesPort( const ::std::string & name, const ::std::string & type, TypeMap_shared properties) throw(Exception ) = 0;


  /** Inform kernel that we no longer need this
      Port. Returns -1 if error. 0 otherwise.  */
  virtual void unregisterUsesPort(const std::string & name) throw(Exception)= 0;

  /** Export a Port wrapped for the kernel to manage.  The port will
      come back to the binding from the removeProvidesPort call. The
      PortInfo pointer is now the Services responsibility, it can no
      longer be trusted to remain the same as when the user created
      it.  If another PortInfo is needed createPortInfo should be
      called again.
   * For supported keys in portinfo, see dc/export/ccafe_keys.hh.
   */
  virtual void addProvidesPort(Port * port, PortInfo * pi) throw(Exception)= 0;

  /** The binding manufactures the ccafeopq::Port wrapper inPort and
   * hands it to the kernel for keeping until removeProvidesPort() returns
   * it to the binding for final disposal.
   * For supported keys in typemap, see dc/export/ccafe_keys.hh.
   */
    virtual void addProvidesPort( Port * inPort, const ::std::string & name, const ::std::string & type, TypeMap_shared properties) throw (Exception ) = 0;


  /** Inform kernel that this Port is no longer available for export.
   * The kernel will return the port if it was previously added and
   * is no longer in use. */
  virtual Port * removeProvidesPort(const std::string & name)  throw (Exception)= 0;

  /** Return a portinfo in the classic way.
   * Memory LifeCycle
   * The creator should destroy the PortInfo if they do not use 
   * it for a register or add function call. 
   * It will be destroyed before a register/add call returns.
   * For supported keys in typemap, see dc/export/ccafe_keys.hh.
   * @param properties may be an empty map.
   */
  virtual PortInfo * 
  createPortInfo(const std::string & name, const std::string & type, 
		 const std::map<std::string, std::string> & properties)  throw (Exception)= 0;

  /** called when registration or addition via portinfo is done. */
  virtual void destroyPortInfo(PortInfo * pi) = 0;

  /** Return a ComponentID.
   * See the class ComponentID for memory lifecycle.
   * Those who fetch this ID pointer are basically
   * free to set their pointer to 0 at any time
   * as the ID object will be deleted by boost
   * at component delete time when the kernel drops the last reference. 
   **/
  virtual ComponentID_shared getComponentID() = 0;

  /** return a typemap. may not be mapped to older service bindings,
   * but still in kernel. Memory model yet to be worked out, pending
   * builderservice details.
   */
  virtual TypeMap_shared createTypeMap() throw (Exception )= 0;

  virtual TypeMap_shared getPortProperties(const ::std::string & portName)  throw (Exception ) = 0;

  /** Port name creator ala steve. never returns the same name twice
  * and accounts for already in use port instance names. */
  virtual ::std::string genUniquePortName(const ::std::string & base) = 0;

  /** Bindings can define the port autoconnect helper for
   * special ports which don't live in the future-perfect
   * factories+events pattern. The give a pointer here
   * that goes with the receiving opq Services instance
   * until that instance is going out of service at
   * setServices null.
   * The original caller of this function remains responsible
   * for calling delete or equivalent on the pointer
   * supplied at the appropriate time.
   */
  virtual void addServicesHelper( ServicesHelper *sh) = 0;

  /** This returns the ultimate map of component properties.
   * It should not be exposed to user components, but is sometimes
   * needed for bindings. The map fetched with this function
   * should only be passed on to the user components after
   * being cloned.
   */
  virtual TypeMap_shared getComponentInternalPropertyMap() = 0;

  /** Get the fortran format of a shared communicator reference that
   * lives a the scope of the frame. It will live at least as
   * long as the frame the services is part of.
   * @param fortranBorrowComm an output if mpi supported, or 0/undefined if not.
   * @return false if there is no Comm in the frame, true if there is.
   * The comm returned must be converted with mpi_comm_f2c after casting
   * if needed to the appropriate type.
   */
  virtual bool hasMPIComm(int64_t & fortranBorrowComm) = 0;
};

	
/** 
 * Memory lifecycle:
 *
 * If this interface is received through a function argument,
 * createEmptyFramework/destroyEmptyFramework must be
 * used as noted. The usual rule applies: only the
 * code creating the AbstractFramework instance should
 * destroy it.
 *
 * If this interface is obtained by casting from a concrete
 * implementation, the original object should be deleted
 * or allowed to fall off the stack as appropriate.
 */
class AbstractFramework 
{
public:

  /** init with a string looking something like a commandline, but
      deeply in need of parsing. At present supported are:
   */
  virtual void initWithString( const ::std::string &s ) = 0;

  /** init with typical shell argument. 
      UNIMPLEMENTED.
   */
  virtual void initWithArgv( const char **argv, int argc) = 0;

// Above is ccaffeine specific stuff.
// Below is the cca-like stuff.

public:
  virtual ~AbstractFramework(){}

  virtual TypeMap_shared createTypeMap() = 0;

  virtual Services *getServices(const std::string & selfInstanceName, const std::string & selfClassName, TypeMap_shared selfProperties) = 0;

  virtual void releaseServices( Services * svc) = 0;

  /** Tell the framework to close up shop, but the framework
   * instance still needs to be deallocated by falling off the stack
   * or by being deleted or by being passed back to
   * destroyEmptyFramework() in the case that it was
   * created with createEmptyFramework.
   */
  virtual void shutdownFramework() = 0;

  /** Constructor of a sub-framework instance -- a separate
   * container from this one with the same implementation,
   * but probably little or no common content.
   */
  virtual AbstractFramework * createEmptyFramework() = 0;

  /** Destructor of a framework instance obtained from
   *  createEmptyFramework. 
   *  subframe->shutdown() will be called if it has not
   *  already been.
   */
  virtual void destroyEmptyFramework( AbstractFramework * subframe) = 0;

};

		
//===================================================================
/** This is the component mesomorph implemented by the binding.
 *
 * Memory lifecycle:
 * Creation:
 *   The component wrapper instance is created by the binding-
 *   supplied FactoryService. 
 * Destruction:
 *   The component wrapper instance will be returned to the Factory
 *   when the kernel has determined that everyone is done with the
 *   component or its ports.
 */
class Component
{
public:
  virtual ~Component(){}

  /** 
   * Basic idea: when binding is done with the kernel services
   * (because setServices(0) is called by the kernel)
   * the binding returns the Services it received to the kernel
   * for disposal.
   * @return the previous value of Services object, i.e.
   *   0 on the first call to setServices and the originally
   *   received Services on the followup setServices(0) that
   *   shuts down the component.
   */
  virtual void setServices(Services * svc) throw (Exception) = 0;

};


//===================================================================
//

/** An opaque interface to a Component opaque reference.
 * This is getting weird, eh?
 *
 * Memory Lifecycle:
 * Created by the kernel. Wrapped by the binding.
 * Shared in lists by everybody and his brother but still owned
 * by the kernel. Thus if the binding has semantics that allow
 * real recipients of a 'real' CCA ComponentID to destroy it, that
 * destruction must not delete the kernel's ccafeopq::ComponentID
 * that is wrapped.
 * Destroyed by the kernel at any time after the component identified
 * is fully destroyed. Anyone caching a ComponentID (other than
 * the Services wrapper of the identified component) should be
 * sure to make arrangements for finding out when the component
 * is about to be destroyed so that the cached ID is not accidentally
 * used after it may have been destroyed.
 *
 * ComponentID's get exchanged so freely in various interfaces
 * (in arrays, etc) that we do not attempt a get/release mechanism.
 *
 * The recommended method of wrapping the ComponentID is
 * for the Services wrapping class to get and wrap the ComponentID
 * once and hand that one wrapper instance out as needed.
 */
class ComponentID_Interface
{
public:
  /** required destructor */
  virtual ~ComponentID_Interface(){}

  /** The ComponentID binding wrapper will receive the exception type
   * and message if an exception should be thrown. Status 0 on returns
   * means everything is ok and message will not have been changed.
   * The binding may do with this information what it pleases.
   */
  virtual const ::std::string getInstanceName() throw (Exception) = 0;

  virtual const ::std::string getSerialization() throw (Exception) =0;

  /** ComponentID identity may not be testable
   * as a pointer comparison. All ids originate in the kernel, however.
   * So we do the comparison internally.
   **/
  virtual bool isSameAs(ComponentID_shared & cid) = 0;
}; // end interface ComponentID



/** Follows the memory lifecycle of of Port identically. */
class GoPort : public virtual Port {
 public:
  virtual ~GoPort() {}

  virtual int go() = 0;

};

//===================================================================

/** It would be nice if we could match this enum to the cca.sidl enum.
 * However, the cca.sidl enum omits the integer values (and should be fixed).
 * Thus a babel binding will have to provide mapping functions until
 * and unless cca.sidl *is* fixed.
 */
enum Type {
	// cca.sidl
	//(gkk) Added by Motion#30 [2].  [3] has explicit integer values.
	NoType = -1, 
	Int = 1, 
	Long = 2,
	Float = 3, 
	Double = 4, 
	Fcomplex = 5, 
	Dcomplex = 6, 
	String = 7, 
	Bool = 8, 
	IntArray = 21, 
	LongArray = 22, 
	FloatArray = 23, 
	DoubleArray = 24, 
	FcomplexArray = 25, 
	DcomplexArray = 26, 
	StringArray = 27, 
	BoolArray = 28,
	Object = 29 // not yet properly supported in typemap
};

//===================================================================
    
class TypeMismatchException : public Exception
{
private:
	enum Type rt;
	enum Type at;

public:

  TypeMismatchException(enum Type requestedType, enum Type actualType, const ::std::string & message)
  {
    rt = requestedType;
    at = actualType;
    setMessage(message);
    setType(Nonstandard);
  }

  enum Type getRequestedType()
  { return rt; }

  enum Type getActualType()
  { return at; }

  virtual ~TypeMismatchException() throw (){}
};
    
//===================================================================

/**
 * Memory lifecycle:
 * This object we're going to  boost::shared_ptr 
 * All typemaps are created by the kernel and then shared
 * liberally. 
 */
//class TypeMap_Interface;

/**
 * This typedef is the type everyone should use everywhere in the 
 * ccafeopq kernel/binding firewall.
 * For practical purposes the memory lifecycle is as
 * follows:
 * Memory lifecycle:
 * 	The kernel creates items of type TypeMap via
 * 	createTypeMap functions and the TypeMap clone function.
 * 	The binding simply fetches and uses TypeMaps
 * 	as if they are an STL type like ::std::string that is
 * 	self managing on the stack memory-wise.
 * 	There is no destroyTypeMap function in any interface.
 * 	Where possible and sensible, TypeMap items are
 * 	passed by reference.
 * 	Because TypeMap has copy semantics anyway,
 * 	we might as well think of it as a fancy STL
 * 	container (like vector) that just lives on the stack.
 * 	Boost will take care of deleting a TypeMap_shared on last
 * 	reference going out of scope.
 *
 *	Anyone caught calling TypeMap.get() {unwrapping the shared_ptr}
 *	will be summarily shot.
 *	As typemap is never cast to anything else, the oddity of
 *	the shared_ptr dynamic_cast does not occur.
 *
 * Other notes:
 * The cca.sidl array-returning functions are bound to return STL vectors.
 * The cca.sidl array-input functions are bound to accept references to STL
 * vectors for copying and also to accept raw arrays+length for copying.
 * There is no way to get a raw array out of this interface.
 * If desired we can someday support copying the internal data
 * directly to a raw buffer of appropriate size supplied by the
 * caller.
 */

/** Never reference this type anywhere else. Use everywhere
 * TypeMap_shared instead.
 * Note: when we Assign a key and value, any value previously assigned
 * to the same key will be overwritten so long as it
 * is of the same type. If types conflict, an exception occurs.
 * Memory LifeCycle: see TypeMap_shared typedef.
 */
class TypeMap_Interface
{
public:
  /** required destructor */
  virtual ~TypeMap_Interface(){}

  /** Create an exact copy of this Map. */
  virtual TypeMap_shared cloneData() = 0;
  /** Create an exact copy of this Map. */
  virtual TypeMap_shared cloneTypeMap() = 0;

  /** Create a new Map with no key/value associations. */
  virtual TypeMap_shared cloneEmpty() = 0;

  virtual int32_t      getInt( const ::std::string & key,  int32_t dflt) throw (TypeMismatchException ) = 0;

  virtual int64_t     getLong( const ::std::string & key,  int64_t dflt) throw (TypeMismatchException ) = 0;

  virtual float    getFloat( const ::std::string & key,  float dflt) throw (TypeMismatchException ) = 0;

  virtual double   getDouble( const ::std::string & key,  double dflt) throw (TypeMismatchException ) = 0;

  virtual ::std::complex<float> getFcomplex( const ::std::string & key, ::std::complex<float> dflt) throw (TypeMismatchException ) = 0;

  virtual ::std::complex<double> getDcomplex( const ::std::string & key, ::std::complex<double> dflt) throw (TypeMismatchException ) = 0;

  virtual ::std::string  getString( const ::std::string & key, ::std::string dflt) throw (TypeMismatchException ) = 0;

  virtual bool  getBool( const ::std::string & key, bool dflt) throw (TypeMismatchException ) = 0;

    // ======================================================

  /** Get the value associated with a given key.  If the key
      was not found, return the value dflt. */
  virtual ::std::vector< int32_t > getIntArray( const ::std::string & key,  ::std::vector< int32_t >&  dflt) throw (TypeMismatchException ) = 0;

  /** Get the value associated with a given key.  If the key
      was not found, return the value dflt. */
  virtual ::std::vector< int64_t > getLongArray( const ::std::string & key,  ::std::vector< int64_t >&  dflt) throw (TypeMismatchException ) = 0;

#define ALLOW_MUSHY_INTS 0
#if ALLOW_MUSHY_INTS
  /** Get the value associated with a given key.  If the key
      was not found, return the value dflt. Internally,
	    the data is stored as int64_t, so the wisdom of this move
	    may be very dubious on compilers with short longs. 
			An exception may occur.
	 */
  virtual ::std::vector< long int > getLongArray( const ::std::string & key,  ::std::vector< long int >&  dflt) throw (TypeMismatchException ) = 0;

#endif // ALLOW_MUSHY_INTS

  /** Get the value associated with a given key.  If the key
      was not found, return the value dflt. */
  virtual ::std::vector< float >    getFloatArray( const ::std::string & key,  ::std::vector< float >&  dflt) throw (TypeMismatchException ) = 0;

  /** Get the value associated with a given key.  If the key
      was not found, return the value dflt. */
  virtual ::std::vector< double > getDoubleArray( const ::std::string & key,  ::std::vector< double >&  dflt) throw (TypeMismatchException ) = 0;

  /** Get the complex value associated with a given key.  If the key
      was not found, return the complex value dflt. */
  virtual ::std::vector< ::std::complex<float> > getFcomplexArray( const ::std::string & key,  ::std::vector< ::std::complex<float> >&  dflt) throw (TypeMismatchException ) = 0;

  /** Get the complex value associated with a given key.  If the key
      was not found, return the complex value dflt. */
  virtual ::std::vector< ::std::complex<double> > getDcomplexArray( const ::std::string & key,  ::std::vector< ::std::complex<double> >&  dflt) throw (TypeMismatchException ) = 0;

  /** Get the value associated with a given key.  If the key
      was not found, return the value dflt. */
  virtual ::std::vector< ::std::string > getStringArray( const ::std::string & key,  ::std::vector< ::std::string >&  dflt) throw (TypeMismatchException ) = 0;

  /** Get the value associated with a given key.  If the key
      was not found, return the value dflt. */
  virtual ::std::vector< bool > getBoolArray( const ::std::string & key,  ::std::vector< bool >&  dflt) throw (TypeMismatchException ) = 0;


    // ======================================================
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten.  */
  virtual void putInt( const ::std::string & key,  int32_t value) throw (TypeMismatchException ) = 0;
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten.  */
  virtual void putLong( const ::std::string & key,  int64_t value) throw (TypeMismatchException )= 0;
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten.  */
  virtual void putFloat( const ::std::string & key,  float value) throw (TypeMismatchException ) = 0;
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten.  */
  virtual void putDouble( const ::std::string & key,  double value) throw (TypeMismatchException ) = 0;
    
  /** Assign a key and complex value.
      Any complex value previously assigned will be overwritten.  */
  virtual void putFcomplex( const ::std::string & key,  ::std::complex<float> value) throw (TypeMismatchException ) = 0;
    
  /** Assign a key and complex value. 
      Any complex value previously assigned will be overwritten. */
  virtual void putDcomplex( const ::std::string & key,  ::std::complex<double> value) throw (TypeMismatchException ) = 0;
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten.  */
  virtual void putString( const ::std::string & key, const ::std::string & value) throw (TypeMismatchException ) = 0;
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten.  */
  virtual void putBool( const ::std::string & key,  bool value) throw (TypeMismatchException ) = 0;

    // ======================================================
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten. Raw arrays and vector content are stored
      by COPY, not by reference. */
  virtual void putIntArray( const ::std::string & key,  int32_t * value ,int length) throw (TypeMismatchException ) = 0;
  /** c++ convenience function. */
  virtual void putIntArray( const ::std::string & key,  ::std::vector< int32_t >&  value) throw (TypeMismatchException ) = 0;
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten. Arrays are stored
      by COPY, not by reference. */
  virtual void putLongArray( const ::std::string & key,  int64_t * value ,int length) throw (TypeMismatchException ) = 0;
  /** c++ convenience function. */
  virtual void putLongArray( const ::std::string & key,  ::std::vector< int64_t >&  value ) throw (TypeMismatchException ) = 0;
#if ALLOW_MUSHY_INTS
  /** c++/babel convenience function.
	 * The wisdom of the conversion is not investigated.
	 */
  virtual void putLongArray( const ::std::string & key,  ::std::vector< long int >&  value ) throw (TypeMismatchException ) = 0;
#endif // ALLOW_MUSHY_INTS
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten. Arrays are stored
      by COPY, not by reference. */
  virtual void putFloatArray( const ::std::string & key,  float * value ,int length) throw (TypeMismatchException ) = 0;
  /** c++ convenience function. */
  virtual void putFloatArray( const ::std::string & key,  ::std::vector< float >&  value ) throw (TypeMismatchException ) = 0;
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten. Arrays are stored
      by COPY, not by reference. */
  virtual void putDoubleArray( const ::std::string & key,  double * value ,int length) throw (TypeMismatchException ) = 0;
  /** c++ convenience function. */
  virtual void putDoubleArray( const ::std::string & key,  ::std::vector< double >&  value) throw (TypeMismatchException ) = 0;
    
  /** Assign a key and complex array value. Any value previously assigned
      to the same key will be overwritten. complex arrays are stored by COPY.*/
  virtual void putFcomplexArray( const ::std::string & key,  ::std::complex<float> * value ,int length) throw (TypeMismatchException ) = 0;
  /** c++ convenience function. */
  virtual void putFcomplexArray( const ::std::string & key,  ::std::vector< ::std::complex<float> >&  value) throw (TypeMismatchException ) = 0;
    
  /** Assign a key and complex array value. Any value previously assigned
     to the same key will be overwritten. Complex arrays are stored by COPY. */
  virtual void putDcomplexArray( const ::std::string & key,  ::std::complex<double> * value ,int length) throw (TypeMismatchException ) = 0;
  /** c++ convenience function. */
  virtual void putDcomplexArray( const ::std::string & key,  ::std::vector< ::std::complex<double> >&  value) throw (TypeMismatchException ) = 0;
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten. Arrays are stored
      by COPY, not by reference. */
  virtual void putStringArray( const ::std::string & key,  ::std::vector< ::std::string >&  value) throw (TypeMismatchException ) = 0;
    
  /** Assign a key and value. Any value previously assigned
      to the same key will be overwritten. Arrays are stored
      by COPY, not by reference. */
  virtual void putBoolArray( const ::std::string & key,  bool * value ,int length) throw (TypeMismatchException ) = 0;
  /** c++ convenience function. */
  virtual void putBoolArray( const ::std::string & key,  ::std::vector< bool >&  value) throw (TypeMismatchException ) = 0;

    // ======================================================

  /** Make the key and associated value disappear from the object. */
  virtual void remove ( const ::std::string & key) = 0;

  /** Get all the names associated with a particular type
      without exposing the data implementation details.  The keys
      will be returned in an arbitrary order. If type specified is
      NoType (no specification) all keys of all types are returned.
      @see Type
  */
  virtual ::std::vector< ::std::string > getAllKeys( enum Type t) = 0;

  /** Return true if the key exists in this map */
  virtual bool hasKey( const ::std::string & key) = 0;

  /** Return the type of the value associated with this key */
  virtual enum Type typeOf( const ::std::string & key) = 0;

} ; // end TypeMap_Interface


/**
 * This typedef is the type everyone should use everywhere in the 
 * ccafeopq kernel/binding firewall.
 * For practical purposes the memory lifecycle is as
 * follows:
 * Memory lifecycle:
 * 	The kernel creates items of type ConnectionID 
 * 	and they get shoveled around to all comers by BuilderServices
 * 	and related ports. 
 * 	The binding simply fetches and uses ConnectionIDs
 * 	as if they are an STL type like ::std::string that is
 * 	self-managing on the stack memory-wise.
 * 	There is no destroyConnectionID function in any interface.
 * 	Where possible and sensible, ConnectionID items are
 * 	passed by reference.
 * 	Boost will take care of deleting a ConnectionID_Interface on last
 * 	reference going out of scope.
 *
 *	Anyone caught calling ConnectionID.get() {unwrapping the shared_ptr}
 *	will be summarily shot.
 *	As ConnectionID is never cast to anything else, the oddity of
 *	the shared_ptr dynamic_cast does not
 */
// typedef boost::shared_ptr < ConnectionID_Interface > ConnectionID;

/**
  This interface describes a CCA connection between components.
  A connection is made at the users direction
  when one component provides a Port that another component
  advertises for and uses.  The components are referred to by their
  opaque ComponentID_shared references and the Ports are referred to
  by their string instance names.
 */
class ConnectionID_Interface  
{
public:
  /** required destructor */
  virtual ~ConnectionID_Interface(){}

  /** Returned id is self-counting/self-deleting. Just let it
   * fall off the stack.
   */
  virtual ComponentID_shared getProvider() throw (Exception ) = 0;

  /** Returned id is self-counting/self-deleting. Just let it
   * fall off the stack.
   * @throws a Exception if the underlying connection is no longer valid.
   */
  virtual ComponentID_shared getUser() throw (Exception ) = 0; 

  virtual ::std::string getProviderPortName() throw (Exception ) = 0; 

  virtual ::std::string getUserPortName() throw (Exception ) = 0; 

  virtual bool isSameAs( ConnectionID_shared & c) = 0;
} ; // end interface ConnectionID_Interface

//===================================================================

// class ComponentClassDescription_Interface;
// typedef boost::shared_ptr< ComponentClassDescription_Interface > ComponentClassDescription_shared;
class ComponentClassDescription_Interface { 
public:
  virtual ~ComponentClassDescription_Interface() {}
  virtual ::std::string getComponentClassName() throw (Exception ) = 0;
  virtual ::std::string getCCASpecBinding() throw (Exception ) = 0;
  virtual ::std::string getIndexFile() throw (Exception ) = 0;
  virtual ::std::string getDeploymentClassAlias() throw (Exception ) = 0;
  virtual ::std::string getConstructorName() throw (Exception ) = 0;
  virtual ::std::string getLibraryLoading() throw (Exception ) = 0;
  virtual ::std::string getLibraryName() throw (Exception ) = 0;
  virtual ::std::string getLibraryLocation() throw (Exception) = 0;
  virtual ::std::string getExecScript() throw (Exception ) = 0;
  virtual void getDOMTree() throw (Exception ) = 0;

};

//===================================================================
//===================================================================

/**NOT YET DEFINED IN CCA.SIDL:
 * This is related to, but not the same as, ComponentRepository.  
 * This is because this interface can create a raw
 * Component and ComponentRepository on purpose cannot. 
 * A raw component is just an instance on which setServices
 * has not been called at all.
 * 
 * The only safe way this port can be used,
 * since it dictates that destroyComponentInstance
 * must be called when done, is for the caller
 * to never release the factory port in the interval
 * between create and destroy. Since the likely caller
 * is the framework, this usually isn't a problem.
 *
 * This port type is recognized by dynamic_cast and
 * string checks and automatically added to the factory
 * list the framework maintains to answer queries for
 * component instances by type string.
 * It is implemented by component writers and/or
 * bindings of the opaque layer, but not the
 * opaque layer itself.
 */ 
class ComponentFactory : public virtual Port
{
public:
  virtual ~ComponentFactory() {}

  /** Names of classes for which this factory can make instances.
   * These names are the palette alias names for presentation to
   * a user. The real names can be obtained by querying the
   * corresponding componentClassDescriptions.
   * The names returned here are those of classes that are
   * definitely in the runtime in the case of classic/opaque
   * components and those of classes that are babel components.
   */
  virtual std::vector< std::string> getComponentClassAliases() = 0;

  /** Descriptions of classes this factory might make based
   * on parsing metadata files. A loadClass may be needed
   * before createComponentInstance is possible.
   */
  virtual std::vector< ComponentClassDescription_shared > getComponentClasses() = 0;

  /**
   * Make one uninitialized instance object on which something
   * must still setServices: either a driver or the framework.
   * This raw instance will eventually come back to this port
   * for disposal.
   * @param properties -- whatever suggestions the driver has
   * or the framework obtains by whatever method from the user.
   */
  virtual Component * createComponentInstance(const std::string & className) = 0;
  /** properties is currently ignored. */
  virtual Component * createComponentInstance(const std::string & className, TypeMap_shared & properties) = 0;

  /**
   * This call will be made *after* setServices(0) has
   * been called on the component obtained from createInstance.
   */
  virtual void destroyComponentInstance(const std::string & componentClassName, Component * component) = 0;

  /** replace current path with new paths. each vector element is one
   * directory name. Path is searched for .cca elements.
   */
  virtual void setComponentPath(const std::vector< std::string > & paths) = 0;

  /** return the list of directories searched for .cca files. */
  virtual std::vector< std::string > getComponentPath() = 0;

  /** parse a file for component descriptions and add them
   * to repository list.
   */
  virtual void loadComponentDescription(const std::string & uri) = 0;
  /**
   * Generate an index (populate the component repository) based on 
   * current component path value.
   */
  virtual void indexComponentPath( ) = 0;

  /**
   * Cause the named class to become instantiable by a subsequent
   * call to createComponentInstance(). This may require side effects
   * with dlopen.
   *   In dlopen terms, lazy=true -> RTLD_LAZY, false->RTLD_NOW;
   *                  global=true ->RTLD_GLOBAL, false->RTLD_LOCAL.
   */
  virtual void loadClass( const std::string paletteClassAlias , bool global, bool lazy) = 0;

  virtual int loadPorts( const std::string & libraryPath) = 0;
}; // end class ComponentFactory


//===================================================================

/**
 * ServiceProvider interface implements a non-singleton service Port.
 * It is a port type that can be exported as normal or to the
 * framework exclusively by using the ServiceRegistry port.
 * This is the Port interface that is implemented by 
 * a component wishing to provide a service for other 
 * components.  The behavior is as follows:  
 *
 * 1. The component registers for a ServiceRegistry Port (above) and
 * does a "getPort()" to get it.  
 *
 * 2. It adds a ServiceProvider Port to the ServiceRegistry.
 *
 * 3. When called the implementation of ServiceProvider::createService()
 * must create the Port asked for, and addProvidesPort to register it on
 * the originating component.  createService() returns the Port instance
 * name for this Port just provided.  
 *
 * 4. The framework connects the originating component to the component
 * requesting the service.
 *
 * This port is implemented by each binding and the bindings
 * have to intercept corresponding addProvidesPort calls
 * to wrap the native ServiceProvider implementation in a
 * ccafeopq form.
 */
class ServiceProvider : public virtual Port
{
public:
  virtual ~ServiceProvider() {}

  /** the bindings have to manage this function. it is not
      exposed to the component writers.
   */
  virtual ComponentID_shared getProviderID() = 0;

  /**
   * Create the Port for the Service, informing the framework through
   * "addProvidesPort()" on the originating component.
   * @return the name of the port created.
   */
  virtual const std::string createService(const std::string & portType) = 0;

  /** Informs the originating component that the instance of the
   * provided service is no longer needed. The ServiceProvider
   * can now safely removePort on the named port.
   */
  virtual void destroyService(const std::string & portName) = 0;   

}; // end class ServiceProvider

/** the bindings hand us a pointer to a wrapper they may not
 * want to keep track of. so when we delete our reference
 * the binding may or may not have it's own to take care of.
 */
typedef boost::shared_ptr< ServiceProvider > ServiceProvider_shared;


//===================================================================
/**
 * ServiceRegistry is a Port that is primordially provided by the framework
 * and can be fished out by a component wishing to provide service Ports. 
 * Each binding has to provide a wrapping of this Service.
 * In the bindings (eg. neo and classic) the component space version
 * of this port will have a raw pointer instead of a shared one.
 */
class ServiceRegistry : public virtual Port
{
public:
  virtual ~ServiceRegistry() {}

    /**
     * Add a ServiceProvider that can be asked to produce service Port's
     * for other components to use subsequently.
     * True means success. False means that for some reason, the
     * provider isn't going to function.
     */
    virtual bool addService(const std::string & type, ServiceProvider_shared portProvider) = 0;

    /** Add a "reusable" service gov.cca.Port for other components to use 
     * subsequently.
     */
    virtual bool addSingletonService(const std::string & type, Port * service) = 0;

    /** Inform the framework that this service Port is no longer to
     * be used, subsequent to this call. This is likely to
     * cause an exception unless all the ports obtained from the
     * previously added services have been released and disconnected.
     */
    virtual void removeService(const std::string & serviceType) = 0;

}; // class ServiceRegistry

//===================================================================
class GUIService : public virtual Port
{
public:
  virtual ~GUIService() {}
  /** send a message to ui per ccafe.sidl interace of same name. 
    first word in uicommand is a java class name in the case of java guis. 
   */
  virtual void load(const std::string & uicommand) = 0;
}; // class GUIService


//===================================================================

/**
------------------------------------------------------------------------
Service Port's are in no way distinguished from late-binding "regular" Port's. 

Consider a port of arbitrary type T.

In some cases the component writer will want to connect 
a Port of type T in the "regular" way
and in other cases the component writer will expect the
T port connected immediately (by the framework) as a service
during setServices or as soon as the uses port of type T
is registered.

In order to distinguish, 
we add an indicating modifier ahead of the type name in the 
registerUsesPort() call on interface Services.
This requires a back-compatible change to the core Service specification.
The separator is a ";" to make it easy to parse and the modifiers
"[no_]auto" should be used to indicate that it was to be auto-matically 
connected or not.  The default if no modifier is specified is "no_auto".

"auto;gov.cca.BuilderService" indicates that you would like to be 
auto-connected to BuilderService as a framework service immediately. 

"no_auto;gov.cca.BuilderService" indicates that you would NOT like
to be auto-connected to BuilderService as a framework service immediately. 

Exception: A few CCA services default to "auto".
These four default services are shall be auto-connected:
  gov.cca.BuilderService 
  gov.cca.ConnectionEventService 
  gov.cca.ComponentRepository 
  gov.cca.ParameterPortFactory
------------------------------------------------------------------------
*/

//===================================================================


/** A class of which only a portion is exposed in the cca component
 *  spec. Use is deprecated.
 **/
class PortInfo 
{

public:
  virtual ~PortInfo() {}

  /** port namespace qualified class name */
  virtual ::std::string getType() = 0;
  virtual void setType(::std::string newType) = 0;

  /** port component scoped instance name. */
  virtual ::std::string getName() = 0;

  /** std::stringified port properties.
   * return the empty string for unknown property.
   * may need fixing */
  virtual ::std::string getProperty(const ::std::string & propertyKey) = 0;

  virtual ::std::vector< ::std::string > getKeys() = 0;

  /** explains a lot at debugging time. real important when
   * navigating multiple frameworks.
   * Don't have to expose this function in the binding.
   * legacy kernels may choose to return the empty string.
   */
  virtual ::std::string toString() = 0; 

};

//===================================================================

/**
 * Memory lifecycle:
 * This is a port the kernel holds onto for use
 * until at least until the last component from the
 * factory has been destroyed.
 *
 * This is a legacy alias of the agreed port named ComponentFactory.
 * It conveniently add a no-typemap version of the function 
 * createComponentInstance.
 */
class FactoryService : public virtual Port, public virtual ComponentFactory
{
public:
  virtual ~FactoryService() {}

  // pretend this isn't here.
  virtual Component * createComponentInstance(const std::string & className, TypeMap_shared & properties) = 0;

  /** 
   * All created components will be returned to the factory for
   * destruction. exception if class unknown.
   */
  virtual Component * createComponentInstance(const  std::string & className) throw (Exception ) = 0;

};

//===================================================================
/** The port whereby components can manipulate the peer world. */
class BuilderService : public virtual Port
{

public:

  virtual ~BuilderService(){}

  /** The ComponentID_shared can be forgotten if desired;
   * that won't cause the component instance to stop existing.
   */
  virtual ComponentID_shared createInstance(const ::std::string & instanceName, const ::std::string & className, TypeMap_shared & properties) throw (Exception ) = 0; 

  /** Memory lifecycle:
   * The vector is returned on the stack and when it goes out of scope,
   * all the ComponentID_shared take care of themselves.
   */
  virtual ::std::vector< ComponentID_shared > getComponentIDs() throw (Exception ) = 0; 

  /** 
   * Memory Lifecycle:
   * The info is returned on the stack and takes care of itself
   * per shared_ptr.
  */
  virtual TypeMap_shared getComponentProperties( ComponentID_shared & cid) throw (Exception ) = 0;

  /**
   */
  virtual void setComponentProperties( ComponentID_shared & cid,  TypeMap_shared & map) throw (Exception ) = 0;

  /** 
   * Memory Lifecycle:
   * The id is returned on the stack and takes care of itself
   * per shared_ptr.
  */
  virtual ComponentID_shared getDeserialization( const ::std::string & s) throw (Exception ) = 0;

  /**
   * Memory Lifecycle:
   * The id is returned on the stack and takes care of itself
   * per shared_ptr.
  */
  virtual ComponentID_shared getComponentID( const ::std::string & componentInstanceName) throw (Exception ) = 0;

   /** 
    */
  virtual void destroyInstance( ComponentID_shared & toDie,  float timeout ) throw (Exception ) = 0;

   /** 
    */
  virtual ::std::vector< ::std::string > getProvidedPortNames( ComponentID_shared & cid) throw (Exception ) = 0; 

   /** 
    */
  virtual ::std::vector< ::std::string > getUsedPortNames( ComponentID_shared & cid) throw (Exception ) = 0; 

  /**
   */
  virtual TypeMap_shared getPortProperties( ComponentID_shared & cid, const ::std::string & portname) throw (Exception ) = 0;

  /**
  */
  virtual void setPortProperties( ComponentID_shared & cid, const ::std::string & portname,  TypeMap_shared & map) throw (Exception ) = 0;

  /**
  */
  virtual ConnectionID_shared connect( ComponentID_shared & user, const ::std::string & usingPortName,  ComponentID_shared & provider, const ::std::string & providingPortName) throw (Exception ) = 0; 

  /**
   */
  virtual ::std::vector < ConnectionID_shared > getConnectionIDs( ::std::vector< ComponentID_shared > & componentList) throw (Exception ) = 0; 

  /** return the list of zero or more connections as specified by names. */
  virtual ::std::vector < ConnectionID_shared > getConnectionIDs( const ::std::string & userName, const ::std::string & userPortName, const ::std::string & providerName, const ::std::string & providerPortName) throw (Exception ) = 0; 

  /**
    */
  virtual TypeMap_shared getConnectionProperties( ConnectionID_shared & connID) throw (Exception ) = 0;

  /**
  */
  virtual void setConnectionProperties( ConnectionID_shared & connID,  TypeMap_shared & map) throw (Exception ) = 0;

  /** 
  */
  virtual void disconnect( ConnectionID_shared & connID,  float timeout) throw (Exception ) = 0; 

  /**
  */
  virtual void disconnectAll( ComponentID_shared & id1,  ComponentID_shared & id2,  float timeout) throw (Exception ) = 0; 

  virtual std::vector< ccafeopq::ComponentID_shared > 
    getComponentsThatUse(const std::string& portType) = 0;

  virtual std::vector< ccafeopq::ComponentID_shared > 
    getComponentsThatProvide(const std::string& portType) = 0;

} ; // end interface BuilderService

//===================================================================

typedef ::std::map< ::std::string, Port * > SvcPortMap;
/*
 * This is an interface to breakout and isolate
 * special binding-specific internal supports
 * of the legacy gizzard pattern (memory created
 * and destroyed with gizzard).
 * Each helper is added to the Gizzard by the
 * binding in question.
 *
 * This should go away with the advent of a full-blown
 * opaque event model ported from the java/ccafe04
 * framework, but that won't happen before SC.
 * We need this for sc so the babel case can
 * also be handled and isolated.
 */
class ServicesHelper
{
public:
	virtual ~ServicesHelper(){}

	/** 
	 * Fetch a port wrapper to be connected.
	 * @return 0 if uses port is not specially supported, or
	 * 	the port to be connected if it is.
	 * @param portName, uses port name sought.
	 * @param portType, uses port type sought.
	 * @param gpm, a porttype-keyed map of native opq
	 * 	port instances owned by the kernel
	 * 	and wrappable by the binding. 
	 * 	These instances will not go away
	 * 	until after the helper has been
	 * 	destroyed.
	 */
	virtual ::ccafeopq::Port * checkSupport(
		const std::string & portName, 
		const std::string & portType,
		SvcPortMap & gpm) = 0;

	/** clear out all memory associated
	 * with port wrappers that may have been created
	 * while returning checkSupport results.
	 * This is called when the ccafeopq::Services is being
	 * destroyed. After this has happened, the
	 * binding wrapper around services should destroy
	 * the helper instance because the
	 * kernel gizzard will drop it on the floor.
	 */
	virtual void destroy() = 0;

}; // end interface ServicesHelper

} ENDSEMI // end namespace ccafeopq
#include "dc/export/Keys.hh"

#include "dc/export/connectionevents/AllConnectionEvent.hh"
#endif //CCAFE_OPQ_H_SEEN
