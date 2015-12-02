#ifndef __REVALIDATETEST_H__
#define __REVALIDATETEST_H__

/* 
   This is a portable component.  there is nothing here
   that relates to any specific framework, or any useful task.
   it has the following ports:
      uses:
         "timer out"        -- type: "Time_idl"
         "my output string" -- type: "String_idl"
      privides:
         "my input string"  -- type: "String_idl"
*/
class RevalidateTest: public virtual classic::gov::cca::Component, public virtual classic::gov::cca::StringConsumerPort, public virtual ParameterGetListener, public virtual classic::gov::cca::ConnectionEventListener {

public:

  classic::gov::cca::Services* core;
  //   UsesString_idlPort *output;
  //   UsesTime_idlPort *timer;
		   public:
  RevalidateTest();
  virtual ~RevalidateTest();

/** Implements ConnectionEventListener for the
    ConnectionEventService. If either of the StringConsumer Ports are
    connected the configure port will disappear. */
  virtual void connectionActivity(classic::gov::cca::ConnectionEvent* evt);

  bool updateParameterPort(ConfigurableParameterPort *dpp);

  void setServices(classic::gov::cca::Services *cc);

  virtual void setString(const char* s);

private:
  classic::gov::cca::JPrintfPort *pfp;
  ConfigurableParameterPort *pp;
  StringParameter *prefix;
  BoolParameter *commie;
  BoolParameter *utest;
  DoubleParameter *dtest;
  StringParameter *anything;
  bool utestdone;
  /** True if configure port is already removed. */
  bool alreadyRemoved;
  /** The ConnectionEventService that we get from the framework. */
  classic::gov::cca::ConnectionEventService* eSvc;
  void setupParameters(ConfigurableParameterFactory *cpf);
};

#endif // __REVALIDATETEST_H__
