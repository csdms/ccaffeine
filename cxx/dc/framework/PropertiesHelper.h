#ifndef dc_fwk_PropertiesHelper_h_seen
#define dc_fwk_PropertiesHelper_h_seen
#include <map>
#include <string>

/**
 * One of the points of the class, which will doubtless 
 * accumulate more functions later,
 * is to provide maps for filtering user TypeMap input.
 * See util/TypeMap.h for functions that can use the filters
 * provided here by privKeys and protKeys.
 */
class PropertiesHelper {

private:

  /** The stuff the user can never change directly. */
  static ::std::map< ::std::string, enum ccafeopq::Type> privKeys;

  /** The stuff the user can only specify during create/add/register. */
  static ::std::map< ::std::string, enum ccafeopq::Type> protKeys;

  /** did we set up yet? */
  static bool inited;

  static void init() {
    if (!inited) {

      privKeys[ ::ccafeopq::Keys::CCAFE_FRAMEX ] = ::ccafeopq::Int;
      privKeys[ ::ccafeopq::Keys::CCAFE_FRAMEY ] = ::ccafeopq::Int;

      privKeys[ ::ccafeopq::Keys::CCAFE_CONNTYPE ] = ::ccafeopq::String;
      privKeys[ ::ccafeopq::Keys::CCAFE_CONNUSERPORT ] = ::ccafeopq::String;
      privKeys[ ::ccafeopq::Keys::CCAFE_CONNPROVIDERPORT ] = ::ccafeopq::String;
      privKeys[ ::ccafeopq::Keys::CCAFE_CONNUSER ] = ::ccafeopq::String;
      privKeys[ ::ccafeopq::Keys::CCAFE_CONNPROVIDER ] = ::ccafeopq::String;

      privKeys[ ::ccafeopq::Keys::CCAFE_CLASS_SHORT_NAME ] = ::ccafeopq::String;

      privKeys[ ::ccafeopq::Keys::CCAFE_EXTERNAL_INSTANCE ] = ::ccafeopq::Bool;

      protKeys[ ::ccafeopq::Keys::CCA_MAXCONNECT ] = ::ccafeopq::Int;
      protKeys[ ::ccafeopq::Keys::CCA_MINCONNECT ] = ::ccafeopq::Int;

      protKeys[ ::ccafeopq::Keys::CCA_PORTNAME ] = ::ccafeopq::String;
      protKeys[ ::ccafeopq::Keys::CCA_PORTTYPE ] = ::ccafeopq::String;
      protKeys[ ::ccafeopq::Keys::CCAFE_CLASS_NAME ] = ::ccafeopq::String;

      protKeys[ ::ccafeopq::Keys::CCA_PROXYABLE ] = ::ccafeopq::Bool;

    }
    inited = true;
  }

public:

  static ::std::map< ::std::string, enum ccafeopq::Type> & getProtKeys()
  { init(); return protKeys; }

  static ::std::map< ::std::string, enum ccafeopq::Type> & getPrivKeys()
  { init(); return privKeys; }


};

#endif // dc_fwk_PropertiesHelper_h_seen
