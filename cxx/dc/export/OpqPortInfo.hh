#ifndef __OPQPORTINFO_HH__
#define __OPQPORTINFO_HH__

/**
 * The PortInfo, like all objects in ccafeopq:: that
 * must be implemented, must be treated strictly as an
 * onion (properly nested wrapping layers only).
 * At its core, though no one cares, is a typemap.
 * Any binding which wishes to expose PortInfo and the
 * PortInfo related misfeatures of ccaffeine should
 * make a wrapper around this implementation class.
 * E.g. see classic/ccafe-bind/ClassicPortInfo.
 */
class OpqPortInfo : public virtual ::ccafeopq::PortInfo {
private:

  std::string type;
  std::string name;
  ::ccafeopq::TypeMap_shared tm;
  int serial;

public:
  virtual ~OpqPortInfo();

  OpqPortInfo(const std::string & name_, const std::string & type_, 
              const std::map<std::string, std::string> & properties);
  
  OpqPortInfo(const std::string & name_, const std::string & type_, 
              ::ccafeopq::TypeMap_shared & t);
  
  // this is backwards. do not create the inside of an onion
  // from the outside.
  // OpqPortInfo( ::classic::gov::cca::PortInfo * pi);

  virtual std::string getType();
  virtual void setType( std::string newType);

  virtual std::string getName();

  virtual std::string getProperty(const std::string & propertyKey);

  virtual std::string toString();

  virtual ::std::vector< ::std::string > getKeys();

  virtual ::ccafeopq::TypeMap_shared getPropertiesTypeMap();

};

#endif //__OPQPORTINFO_HH__
