namespace gov {
  namespace cca {


/** Mapping of standard exceptional event types to integers. 
*/
enum CCAExceptionType {

   /** Someone caught a non-CCAException that was declared
       at an interface that claims it throws ONLY CCAException. */
   Unexpected,

   /** A CCAException that is carrying a non-standard message. */
   Nonstandard,

   /** Action attempted on a port name that is neither registered
       nor added. */
   PortNotDefined,

   /** Adding/registering an already added/registered Port was
       attempted. */
   PortAlreadyDefined,

   /** Attempt to getPort, getPortNonblocking, or releasePort
       with a port named that is not connected. */
   PortNotConnected,

   /** Redundant attempt to release a Port. */
   PortNotInUse,

   /** Attempt to unregister a Port that is still being used. */
   UsesPortNotReleased,

   /** Port name given to createPortInfo is bogus. */
   BadPortName,

   /** Port class/type given to createPortInfo is bogus. */
   BadPortType,

   /** Port properties given to createPortInfo is bogus.
       Note: null is NOT a bogus input, but a fairly common one. */
   BadProperties,

   /** PortInfo given in port add/register call is bogus or null. */
   BadPortInfo,

   /** Services implementation failed to allocate memory. */
   OutOfMemory,

   /** Port (or function within it) died on a remote error. */
   NetworkError

};

    /** A CCA exception type definition.  */
    class CCAException {

    public:
      /** returns a member of the enumeration in CCAExceptionType. */
      virtual int getType() = 0;

      /** return a  (hopefully) human parseable error. */
      virtual CFREE char* getMessage() = 0;

      /** set the type of an exception. */
      virtual void setType(int type) = 0;

      /** set the string message in an exception. The method creats a copy
	  for its own internal use.*/
      virtual void setMessage(char* message) = 0;
    };

  };
};
