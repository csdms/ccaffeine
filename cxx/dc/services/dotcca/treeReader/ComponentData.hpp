#ifndef __ComponentData_hpp
#define __ComponentData_hpp

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include <boost/smart_ptr.hpp>
#include <complex>
#include "dc/export/ccafeopq.hh"

namespace ccafe {

class ComponentData : public virtual ::ccafeopq::ComponentClassDescription_Interface {

public:

  ComponentData() ;
  virtual ~ComponentData() ;

  virtual std::string getComponentClassName () throw (ccafeopq::Exception) ;
  virtual std::string getDeploymentClassAlias() throw (ccafeopq::Exception);
  virtual std::string getConstructorName () throw (ccafeopq::Exception) ;
  virtual std::string getCCASpecBinding() throw (ccafeopq::Exception);
  virtual std::string getLibraryLoading() throw (ccafeopq::Exception);
  virtual std::string getLibraryLocation() throw (ccafeopq::Exception);
  virtual std::string getLibraryName () throw (ccafeopq::Exception);
  virtual std::string getExecScript () throw (ccafeopq::Exception);
  virtual std::string getIndexFile() throw (ccafeopq::Exception);
  virtual void getDOMTree () throw (ccafeopq::Exception);

  static int main(int argc, char **argv);
  
  void setComponentClassName( std::string s);
  void setDeploymentClassAlias( std::string s);
  void setConstructorName( std::string s);
  void setCCASpecBinding( std::string s);
  void setLibraryLoading( std::string s);
  void setLibraryLocation( std::string s);
  void setLibraryName( std::string s);
  void setExecScript( std::string s);
  void setIndexFile( std::string s);

private:
  unsigned int dead;
  std::string componentClassName;
  std::string deploymentClassAlias;
  std::string ccaSpecBinding;
  std::string libraryLoading;
  std::string libraryLocation;
  std::string libraryName;
  std::string execScript;
  std::string ctorName;
  std::string indexFile;

  void initDummy();

};

} // end namespace ccafe
#endif
