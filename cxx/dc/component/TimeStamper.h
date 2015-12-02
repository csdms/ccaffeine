#ifndef __TIMESTAMPSTRING_H__
#define __TIMESTAMPSTRING_H__

/* 
   this is a portable component.  there is nothing here
   that relates to any specific framework
   it has the following ports:
      uses:
	StringConsumerPort, Timer
      provides:
        StringConsumerPort
*/
class TimeStamper: public virtual classic::gov::cca::Component, public virtual classic::gov::cca::StringConsumerPort, public virtual ParameterGetListener {

public:

		   
  TimeStamper();
  virtual ~TimeStamper();

  virtual bool updateParameterPort(ConfigurableParameterPort *dpp);

  virtual void setServices(classic::gov::cca::Services *cc);

   
  virtual void setString(const char* s);

private:
  classic::gov::cca::Services* core;
  ConfigurableParameterPort *pp;
  StringParameter *prefix;
  BoolParameter *commie;
  BoolParameter *utest;
  DoubleParameter *dtest;
  StringParameter *anything;
  bool utestdone;

  void setupParameters(ConfigurableParameterFactory *cpf);
};

#endif // __TIMESTAMPSTRING_H__
