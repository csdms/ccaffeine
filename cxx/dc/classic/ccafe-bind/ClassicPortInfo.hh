#ifndef ClassicPortInfo_hh_seen
#define ClassicPortInfo_hh_seen
class ClassicPortInfo : public virtual ::classic::gov::cca::PortInfo
{

private:
	    ::ccafeopq::PortInfo *pi;
      bool dead;
      std::vector< std::string > supportsKind;

public:
      // the pi passed in becomes property of the wrapper and
      // gets deleted when the wrapper does.
      ClassicPortInfo( ::ccafeopq::PortInfo *pi_); 

      /** obligatory virtual destructor */
      virtual ~ClassicPortInfo();

      /** Returns the type for this Port.  This string corresponds to the 
      interface name of the port, but may not be identical. */
      virtual CONST char* getType() CONST;

      /** Returns the instance name for this Port.
          This name must be unique within the scope of 
          the CCA component which uses or provides this port.*/
      virtual CONST char* getName() CONST;

      /** Returns the string value for this property,
          or 0 if it is undefined. */
      virtual CONST char* getProperty(char* name);
    
      /** sets pi null internally. this is used iff someone else
         is known/expected to have called delete on it already. */
      void resetPortInfo();

      ::ccafeopq::PortInfo *getpi();

      /** add a name of a supported port kind (dynamic castable).
       * names come from ccafeopq.hh and are values like NEO_PORT. 
       */
      void addSupportsKind( const char * portKind);

      /** return list of supported kind, other than classic,
       * derived from the properties given in createPortInfo. */
      const std::vector< std::string >  & getSupportsKind();
};
#endif // ClassicPortInfo_hh_seen
