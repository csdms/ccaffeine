#ifndef __GizzardComponentChangedEvent_H__
#define __GizzardComponentChangedEvent_H__

/** Default implementation of ComponentChangedEvent.
  @see ComponentChangedEvent
*/
class GizzardComponentChangedEvent : public virtual ComponentChangedEvent {
 public:
  GizzardComponentChangedEvent(const int type, 
			       const char* componentName, 
			       ccafeopq::PortInfo * opi);
  GizzardComponentChangedEvent(const int type, 
			       const ::std::string &componentName, 
			       const ::std::string & pName, const ::std::string & pType);

  virtual ~GizzardComponentChangedEvent() ;

  int getChangeType() ;
  const char* getComponentInstance() ;
  const char* getPortInstance() ;
  const char* getPortType();
 private:
  int type;
  ::std::string componentName;
  ::std::string portName;
  ::std::string portType;
};

#endif // __GizzardComponentChangedEvent_H__
