#define CCAFE_KEYS_MACROS 1
#include "dc/export/config.hh"
#include "dc/export/Keys.hh"
namespace {
char id[]=
"$Id: PropertyStrings.cxx,v 1.4 2003/07/07 19:08:39 baallan Exp $";
} ENDSEMI

/* this is the implementation of the export Keys class */
namespace ccafeopq {

  const ::std::string Keys::CCAFE_COMPONENT_INSTANCE_NAME = COMPONENT_INSTANCE_NAME;
  const ::std::string Keys::CCA_PORTNAME =           PORTNAME;
  const ::std::string Keys::CCA_PORTTYPE =           PORTTYPE;
  const ::std::string Keys::CCA_PROXYABLE =          PROXYABLE;
  const ::std::string Keys::CCA_MAXCONNECT =         MAXCONNECT;
  const ::std::string Keys::CCA_MINCONNECT =         MINCONNECT;
  const ::std::string Keys::CCAFE_VISIBLE =          VISIBLE;
  const ::std::string Keys::CCAFE_USER_CLASS_ALIAS = USER_CLASS_ALIAS;
  const ::std::string Keys::CCAFE_CLASS_SHORT_NAME = CLASS_SHORT_NAME;
  const ::std::string Keys::CCAFE_CLASS_NAME =       CLASS_NAME;
  const ::std::string Keys::CCAFE_CLASS_IMAGE_FILE = CLASS_IMAGE_FILE;
  const ::std::string Keys::CCAFE_CLASS_IMAGE =      CLASS_IMAGE;
  const ::std::string Keys::CCAFE_FRAMEX =           FRAMEX;
  const ::std::string Keys::CCAFE_FRAMEY =           FRAMEY;
  const ::std::string Keys::CCAFE_CONNTYPE =         CONNTYPE;
  const ::std::string Keys::CCAFE_CONNUSERPORT =     CONNUSERPORT;
  const ::std::string Keys::CCAFE_CONNPROVIDERPORT = CONNPROVIDERPORT;
  const ::std::string Keys::CCAFE_CONNUSER =         CONNUSER;
  const ::std::string Keys::CCAFE_CONNPROVIDER =     CONNPROVIDER;
  const ::std::string Keys::CCAFE_EXTERNAL_INSTANCE = EXTERNAL_INSTANCE;

} ENDSEMI //end namespace
