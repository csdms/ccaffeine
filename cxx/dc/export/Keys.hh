#ifndef ccafe_Keys_hh_seen
#define ccafe_Keys_hh_seen
/*
 * USAGE NOTES:
 * one can include and use this header any of a number of ways.
 * 1) HARD
 * By default it comes with ccafeopq.hh, but everything is very long
 * and uninteresting to type, e.g.
 *   ::ccafeopq::Keys::CCA_MAXCONNECT
 * 2) MIDDLING
 * Drop the ccafeopq by doing
 *   using ::ccafeopq::Keys;  // just this class, not all ccafeopq using.
 *   Keys::CCA_MAXCONNECT (which is easier to type than keeping up with the
 *                         spec which blows in the wind).
 * 3) EASY, but conflicts possible with other packages.
 * #define CCAFE_KEYS_MACROS 1
 * #include "dc/export/Keys.hh"
 *   So now just type MAXCONNECT and you get the right string.
 *   See bottom of file. Mostly all the prefixes get dropped.
 * #define CCAFE_KEYS_MACROS 0
 * #include "dc/export/Keys.hh"
 *   Will cause all the macros defined here to become undefined again.
 * Note that for this, Keys.hh can be included multiple times.
 *
 */ 
#include <string>
namespace ccafeopq {
/**
 * <p>
    Class defining some keys that will be found in various property maps.
    These are useful either internally or for a user interface.
    Obviously, this is just a first stab. Various agents are likely
    define their own keys. GUI authors are encouraged to get together
    and define a more complete set, which should perhaps be kept in
    a separate package instead of as part of CCAFE.
    Items marked 'Protected' may not be changable after an initial
    value is set (by the framework).
    </p>

    <p>
    The reason we need keys that are UI-implementation independent
    and storable on component properties is that during long running
    apps on big machines the gui comes and goes. The user will want
    the gui to save state. a gui can of course keep it in its own keys,
    on the component properties, but a better solution in a multi-
    user/multi-desktop accessing the same big job scenario is to
    have at least a base set of keys that all gui's understand.
    </p>


    <p>
    Some keys and types that are protected
    by the framework for its own use and cannot be set by user.
    Attempts to reset them inappropriately will be ignored.
    <ul>
    <li> Int: CCAFE_FRAMEX, CCAFE_FRAMEY </li>
    <li> String: CCAFE_CONNTYPE, CCAFE_CONNUSERPORT, CCAFE_CONNPROVIDERPORT,
        CCAFE_CONNUSER, CCAFE_CONNPROVIDER, CCAFE_CLASS_SHORT_NAME </li>
    <li> Bool: CCAFE_EXTERNAL_INSTANCE </li>
    </ul>
    </p>
    <p>
    Some keys and types that are protected
    by the framework after initial definition from the user.
    Attempts to reset them inappropriately
    may be ignored.
    <ul>
    <li> Int: CCA_MAXCONNECT, CCA_MINCONNECT </li>
    <li> String: CCA_PORTNAME, CCA_PORTTYPE, CCAFE_CLASS_NAME </li>
    <li> Bool: CCA_PROXYABLE </li>
    </ul>
    </p>

  */
class Keys
{
public:

  //
  // Keys the average component writer might well use.
  //

  /** Protected typemap port property String instance name. */
  static const ::std::string CCA_PORTNAME;

  /** Protected typemap port property String class name. */
  static const ::std::string CCA_PORTTYPE;

  /** Protected typemap port property String proxy friendly. */
  static const ::std::string CCA_PROXYABLE ;

  /** Protected typemap port property int maximum connections on port. */
  static const ::std::string CCA_MAXCONNECT ;

  /** Protected typemap port property int minimum connections on port. */
  static const ::std::string CCA_MINCONNECT ;
 

  //
  // Keys mostly for the internal consumption of the framework
  // and gui writers but useful for others to read.
  //

  /** Typemap component instance, port, or connection instance visibility.
      Value is boolean. Items tagged false can be omitted from lists
      rendered to the user unless the user has opted to see hidden items.
   */
  static const ::std::string CCAFE_VISIBLE ;

  /** Typemap component class name alias property
      String abbreviated class name for user consumption,
      which may be strictly political in origin.
   */
  static const ::std::string CCAFE_USER_CLASS_ALIAS ;

  /** Typemap component class name property
      String unqualified class name. e.g. Vector, not Lib.Vector.
   */
  static const ::std::string CCAFE_CLASS_SHORT_NAME ;

  /** Typemap component class name property
      String fully qualified class name. e.g. Lib.Vector, not Vector.
   */
  static const ::std::string CCAFE_COMPONENT_INSTANCE_NAME ;

  /** Typemap component class name property
      String fully qualified class name. e.g. Lib.Vector, not Vector.
   */
  static const ::std::string CCAFE_CLASS_NAME ;

  /** Typemap component class name property
      String url of image file for class in a user interface.
   */
  static const ::std::string CCAFE_CLASS_IMAGE_FILE ;

  /** Protected typemap component class name property
      String xbm string of image file for class in a user interface.
   */
  static const ::std::string CCAFE_CLASS_IMAGE ;

  /** Typemap component instance frame position (integer) X. */
  static const ::std::string CCAFE_FRAMEX ;

  /** Typemap component instance frame position (integer) Y. */
  static const ::std::string CCAFE_FRAMEY ;



  //
  // Keys mostly for the internal consumption of the framework
  // but useful for others to read.
  //

  /** Protected typemap connectionid property string 
      user/provider port class name. */
  static const ::std::string CCAFE_CONNTYPE ;

  /** Protected typemap connectionid property string 
      user port instance name. */
  static const ::std::string CCAFE_CONNUSERPORT ;

  /** Protected typemap connectionid property string 
      provider port instance name. */
  static const ::std::string CCAFE_CONNPROVIDERPORT ;

  /** Protected typemap connectionid property string 
      user component instance name. */
  static const ::std::string CCAFE_CONNUSER ;

  /** Protected typemap connectionid property string 
      provider component instance name. */
  static const ::std::string CCAFE_CONNPROVIDER ;

  /** Protected typemap component instance property 
      boolean inserted via AbstractFramework. */
  static const ::std::string CCAFE_EXTERNAL_INSTANCE ;

}; // end class Keys

} ENDSEMI  // end namespace ccafeopq
#endif // ccafe_Keys_hh_seen

/** These are the values we actually use. They are
 * subject to change as the cca winds blow them about.
 * If you want to type the strings directly instead of using
 * the Keys members or the macros, well, fine.
 * Don't be surprised if your code stops working later.
 */
#ifdef CCAFE_KEYS_MACROS
  #if CCAFE_KEYS_MACROS // value 1
    #ifndef CCAFE_KEYS_DEFINED
    #define CCAFE_KEYS_DEFINED
#define PORTNAME            "cca.portName"
#define PORTTYPE            "cca.portType"
#define PROXYABLE           "ABLE_TO_PROXY"
#define MAXCONNECT          "MAX_CONNECTIONS"
#define MINCONNECT          "MIN_CONNECTIONS"
#define VISIBLE           "gov.ccafe.visible"
#define SINGLETON         "gov.ccafe.singleton"
#define USER_CLASS_ALIAS  "gov.ccafe.PalletClassAlias"
#define CLASS_SHORT_NAME  "gov.ccafe.PalletLeafName"
#define COMPONENT_INSTANCE_NAME    "gov.ccafe.instanceName"
#define CLASS_NAME        "gov.ccafe.PalletClassName"
#define CLASS_IMAGE_FILE  "gov.ccafe.PalletImageURL"
#define CLASS_IMAGE       "gov.ccafe.PalletImage"
#define FRAMEX            "gov.ccafe.frameX"
#define FRAMEY            "gov.ccafe.frameY"
#define CONNTYPE          "gov.ccafe.ConnectionType"
#define CONNUSERPORT      "gov.ccafe.UserPortInstance"
#define CONNPROVIDERPORT  "gov.ccafe.ProviderPortInstance"
#define CONNUSER          "gov.ccafe.UserComponentInstance"
#define CONNPROVIDER      "gov.ccafe.ProviderComponentInstance"
#define EXTERNAL_INSTANCE "gov.ccafe.ExternalComponentInstance"
    #endif // CCAFE_KEYS_DEFINED def
  #else  // if CCAFE_KEYS_MACROS value 0
    #ifdef CCAFE_KEYS_DEFINED
    #undef CCAFE_KEYS_DEFINED
#undef PORTNAME  
#undef PORTTYPE   
#undef PROXYABLE   
#undef MAXCONNECT   
#undef MINCONNECT    
#undef VISIBLE        
#undef USER_CLASS_ALIAS
#undef CLASS_SHORT_NAME
#undef COMPONENT_INSTANCE_NAME  
#undef CLASS_NAME      
#undef CLASS_IMAGE_FILE 
#undef CLASS_IMAGE
#undef FRAMEX      
#undef FRAMEY       
#undef CONNTYPE      
#undef CONNUSERPORT   
#undef CONNPROVIDERPORT
#undef CONNUSER        
#undef CONNPROVIDER     
#undef EXTERNAL_INSTANCE 
    #endif // CCAFE_KEYS_DEFINED undef
  #endif // ifelse CCAFE_KEYS_MACROS done
#endif // ifdef CCAFE_KEYS_MACROS done

