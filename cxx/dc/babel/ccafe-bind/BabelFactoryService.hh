#ifndef __BABELFACTORYSERVICE_HH__
#define __BABELFACTORYSERVICE_HH__

#include <SIDL_cxx.hh>

class BabelFactoryService : public virtual ccafeopq::FactoryService {
private:

  string path;
  map<string,string> cmptInfo;

  map<string,string>& loadCmptInfo(string path) {

  string& chomp(const string& toChomp) {
    string s = toChomp;
    int begin = s.find_first_not_of(" \t\n\b\r");
    int end = s.find_last_not_of(" \t\n\b\r");
    end++;
     if (begin >= end) {
       return string();
     }
     return s.substr(begin,end - begin);
  }

  vector<string>& split(string& s, const char c = ' ') {
    vector<string> v;
    int i = 0;
    int begin = i;
    int end = i;
    int count = 0;
    while(i != s.size()) {
      while((i != s.size()) && (s[i] == c)) {
	i++;
      }
      begin = i;
      while((i != s.size()) && (s[i] != c)) {
	i++;
      }
      end = i;
      if(end > begin) {
	v[count++] = s.substr(begin, end - begin);
      }
    }
    return v;
  }

  // inner class bogosity. fortunately we don't use this coe much.
  class ComponentInfo {
  public:
    string className;
    string libPath;
    string cmptType;
  };

  vector<ComponentInfo> loadComponentInfo(path) {
    vector<string> paths = split(path, ';');
    return vector< ComponentInfo >();
  }

  bool bypassPaths;
  vector< string > compList;

public:
  virtual ~BabelFactoryService(){}
  BabelFactoryService() {
    bypassPaths = true;
    if (!bypassPaths) {
      char * s = getenv("SIDL_DLL_PATH");
      if(s != NULL) {
	path = chomp(s);
      }

      s = chomp(string(stp_getn("babel", "path")));
      if(s != NULL) {
	path += ";" + s + PATH; 
      }
      SIDL::Loader::setSearchPath(path.c_str());
      cmptInfo = loadCmptInfo(path);
    }
    
    const char * cmpts = stp_getn("babel", "components");    
    compList = split(cmpts);
  }

  virtual std::vector< std::string > getComponentClassNames() {
    return compList;
  }

  /** Memory Lifecycle
   * Returned description is shared_ptr.
   */
  //  virtual std::vector< ComponentClassDescription> getComponentClasses() = 0;

  /** 
   * All created components will be returned to the factory for
   * destruction. exception if class unknown.
   */
  virtual ccafeopq::Component * 
    createComponentInstance(const  std::string & className) 
    throw (ccafeopq::Exception ) {
    gov::cca::Component c;
    try {
      c = SIDL::Loader::createClass(className.c_str());
    } catch(std::exception e) {
      IO_dn2("Exception: %s\n", e.what());
      throw ccafeopq::Exception(string(e.what()));
    }
    return new BabelComponentWrapper(c);
  }

  virtual void 
    destroyComponentInstance(const std::string & componentClassName, 
			     ccafeopq::Component * component) 
    throw (Exception ) {
    delete component;
  }

};

#endif // __BABELFACTORYSERVICE_HH__
