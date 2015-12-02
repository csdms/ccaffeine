/** fake CCA header for dlopen testing only. !!!!!!!!!!!!!!!!!!!!1
 * This doesn't change when the real cca.h does.
 */
#ifdef _FAKE_CCA_TESTING
#ifndef __TestCCA_H__
#define __TestCCA_H__


/** Some compilers are finicky about whether namespaces are closed
    with a "}" or a "};"
    If a compiler is not picky, then "} ;" is preferred.
 */
#define ENDSEMI   // use of this macro is deprecated
#define CCA_NAMESPACE_ENDSEMICOLON 
#define CONST 

/** 

 */
namespace classic {

namespace gov {
/** 
 * <p>The spec lives in C++ namespace ::classic::gov::cca .</p>
 */
  namespace cca {

    /** UNADOPTED: A class to support the runtime introspection of the CCA version.
        The int returning functions are capitalized because sysmacros.h
        #defines both major() and minor(), sheesh. */
    class Version {
    public:
      /** The descriptive source release string. */
      static const char *name(); 
      /** The dot notation release number string; major.minor.patch.  */
      static const char *id();
      /**@ Revision numbering scheme will be rigorously followed after
           1_0_0. */
      //@{
      /** Major version; increments with binary incompatible changes 
          in this header. */
      static const int Major(); 
      /** Minor revision; increments with binary incompatible changes in
          well known ports, including changes in namings expressed with
          string name or type arguments. Changes in the spec but outside
          this header. */
      static const int Minor(); 
      /** Patch revision; binary compatible changes, such as addition of
          new common port definitions. */
      static const int Patch(); 
      //@}
    };

 
//===================================================================

    /** A tag interface to identify an interface capable of being exported to
	or imported from a CCA component. */
    class Port  {
    public:
      /** obligatory virtual destructor */
      virtual ~Port (){}
    };

//===================================================================
    /** An interface (deprecated) that describes a Port. */
    class PortInfo  {
    public:
      /** obligatory virtual destructor */
      virtual ~PortInfo(){}

      /** Returns the type for this Port.  This string corresponds to the 
	  interface name of the port, but may not be identical. */ 
      virtual const char* getType() const = 0;

      /** Returns the instance name for this Port.
          This name must be unique within the scope of 
          the CCA component which uses or provides this port.*/
      virtual const char* getName() const = 0;

      /** Returns the string value for this property,
          or 0 if it is undefined. */
      virtual const char* getProperty(char* name) = 0;

    };

//===================================================================
    /** An opaque reference (deprecated, see ComponentID_STL) to a Component. */
    class ComponentID  {
    public:
      /** obligatory virtual destructor */
      virtual ~ComponentID() {}

      /** Produce a string that, within the current
          framework, that uniquely defines this component reference.
         @return toString is probably a bad choice of name for this
            method as toString is likely to be used in a more
            Java-conventional sense. */
      virtual char* toString()=0;


    };

//===================================================================
    /** The handle (deprecated; see Services_STL) through which 
     * the component communicates with its
     *  containing framework.
     */
    class Services  {
    public:
      /** obligatory virtual destructor */
      virtual ~Services (){}

      /** Creates a PortInfo to be used in subsequent
          calls to describe a Port. The arguments given are copied, not kept.
          properties is an even length list (argv) of key/value pairs 
          terminated by a NULL key. Note that names of Ports in a 
          component are not distinct for used and provided ports. 
          Standard properties: (UNADOPTED, extensible list)
                MIN_CONNECTIONS (int >= 0; default 0)
		MAX_CONNECTIONS (int >= 1, default 1)
		ABLE_TO_PROXY   (true,false; default false)
      */
      virtual PortInfo *  createPortInfo(const char *name, const char *type, const char** properties) = 0;

      /**  Fetch a port from the framework. Normally this means a uses port.
      If no uses port is connected and a provided port of the name requested
      is available, the component will be handed back that port.
       Returns NULL if no provided port or uses port connection matches name.
       UNADOPTED C++ definition of "an error occurs".
   */
      virtual Port *getPort(const char *name) = 0;

      /** Free's the port indicated by the instance name for modification
	  by the component's containing framework.  After this call the
	  port will not be valid for use until getPort() is called
	  again.*/
      virtual void releasePort(const char *name) = 0;

      /** Notifies the framework that a port described by PortInfo
	  may be used by this component. The portinfo is obtained 
      from createPortInfo. Returns nonzero if there is an error
      in registering, such as bad PortInfo or already registered.
       UNADOPTED C++ definition of "an error occurs".
      */
      virtual int registerUsesPort(PortInfo *name_and_type) = 0;

      /** Notify the framework that a Port, previously
          registered by this component, is no longer desired.
          Returns nonzero if the port is still in use, ignoring
          the unregister request.
        UNADOPTED C++ definition of "an error occurs".
       */
      virtual int unregisterUsesPort(const char *name) = 0;

      /** Exports a Port implemented by this component to the framework.  
	  This Port is now available for the framework to
	  connect to other components. The PortInfo is obtained 
      from createPortInfo. Returns nonzero if addProvidesPort fails,
      for example, because that name is already provided.
        UNADOPTED C++ definition of "an error occurs". */
      virtual int addProvidesPort(Port *inPort, PortInfo *name) = 0;

      /** Notifies the framework that a previously exported Port is no longer 
	  available for use. */
      virtual void removeProvidesPort(const char *name) = 0;

      /** Get a reference to the component which this 
          Services object belongs. Delete it when you're done
       with it.
       */
      virtual ComponentID* getComponentID() = 0;

    };

//===================================================================
    /** Component object model (deprecated; see Component_STL) 
     * that all Components must implement.
     */
    class CCAComponent {
    public:
      /** obligatory virtual destructor */
      virtual ~CCAComponent(){}

      /** The components containing framework provides services through
	  the Services interface. */
      virtual void setServices(Services *cc)=0;
    };

//===================================================================

} CCA_NAMESPACE_ENDSEMICOLON // end namespace cca
} CCA_NAMESPACE_ENDSEMICOLON // end namespace gov
} CCA_NAMESPACE_ENDSEMICOLON // end namespace classic

#endif //__TestCCA_H_ 
#endif // _FAKE_CCA_TESTING
