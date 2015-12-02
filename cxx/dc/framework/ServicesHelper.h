#ifndef __CCASERVICESHELPER_H__
#define __CCASERVICESHELPER_H__

/** Little functions to manipulate port lists. */
class ServicesHelper {

public:

  ServicesHelper(){};
  ~ServicesHelper(){};

  static ::std::vector< int > getProvidesIndexByName( const ::std::vector< ProviderPortData > & pData, const ::std::string & name);

  static ::std::vector< int > getUsesIndexByName( const ::std::vector< UserPortData > & uData, const std::string & name);

  static ::std::string toStringUserPortData(const UserPortData & pi);
  static ::std::string toStringProviderPortData(const ProviderPortData & pi);


/*  CFREE */ static char* toStringPortInfo(ccafeopq::PortInfo * opi);

private:
  int dummy;
  
};

#endif //__CCASERVICESHELPER_H__
