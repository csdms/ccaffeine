#ifndef neo_BasicParameterPortWrap_hh
#define neo_BasicParameterPortWrap_hh

/**
*/
class NeoBasicParameterPortWrap : public virtual neo::cca::ports::BasicParameterPort
{

private:
      ::ccafeopq::ports::BasicParameterPort *opp;
      int serial;
      static int nextNum() { genSerial++; return genSerial; }
      static int genSerial;
      void checkthrow(const char *funcName);
      

public:

      NeoBasicParameterPortWrap( ::ccafeopq::ports::BasicParameterPort *obpp);

      NeoBasicParameterPortWrap( int bogon);

      virtual ~NeoBasicParameterPortWrap();


      virtual ::neo::cca::TypeMap_shared readConfigurationMap() throw ( ::neo::cca::Exception);

      virtual void writeConfigurationMap ( neo::cca::TypeMap_shared map) throw ( ::neo::cca::Exception);

      virtual std::vector< ::std::string> readConfigurationKeys() throw () ;

};  // end class NeoBasicParameterPortWrap

#endif // neo_BasicParameterPortWrap_hh
