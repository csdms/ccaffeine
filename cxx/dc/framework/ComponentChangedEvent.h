#ifndef __COMPONENTCHANGEDEVENT_H__
#define __COMPONENTCHANGEDEVENT_H__


/** Mechanism for signalling a change in a component's status. */
class ComponentChangedEvent {

 public:
  virtual ~ComponentChangedEvent() {}

  /** This is an erroneously accessed event object (already deleted). */
  static int PORT_ERROR;

  /** A provides Port on this component has been removed. */
  static int PORT_REMOVED;

  /** A provides port on a component has been added. */
  static int PORT_ADDED;

  /** A uses Port on this component has been registered. */
  static int PORT_REGISTERED;

  /** A uses Port on this component has been unregistered. */
  static int PORT_UNREGISTERED;

  /** Returns the change type that has occurred. */
  virtual int getChangeType() = 0;

  /** Returns the instance name for this component. */
  virtual const char* getComponentInstance() = 0;

  /** Returns the instance name of the affected port, if any,
      otherwise returns null. */
  virtual const char* getPortInstance() = 0;

  virtual const char* getPortType() = 0;
};

#endif //__COMPONENTCHANGEDEVENT_H__
