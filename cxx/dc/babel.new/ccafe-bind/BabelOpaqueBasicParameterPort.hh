#ifndef __BABELOPAQUEBASICPARAMETERPORT_H__
#define __BABELOPAQUEBASICPARAMETERPORT_H__


class BabelOpaqueBasicParameterPort : public virtual ccafeopq::ports::BasicParameterPort, 
			  public virtual BabelOpaquePort ,
			  public virtual KernelPort
{
 private:
  gov::cca::ports::BasicParameterPort bpp;
 
 public:
  BabelOpaqueBasicParameterPort ( gov::cca::ports::BasicParameterPort bpp_ );
  virtual ~BabelOpaqueBasicParameterPort();
  virtual ccafeopq::TypeMap_shared readConfigurationMap();
  virtual void writeConfigurationMap( ccafeopq::TypeMap_shared map );
  virtual ::std::vector< ::std::string> readConfigurationKeys () ;

};


#endif //__BABELOPAQUEBASICPARAMETERPORT_H__
