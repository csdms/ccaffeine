#ifndef __COMPONENTCHANGEDLISTENER_H__
#define __COMPONENTCHANGEDLISTENER_H__

/** Interface to be implemented by anyone interested in
 change events. */
class ComponentChangedListener {
 public:
  virtual ~ComponentChangedListener() {}
  /** Signal a change in the Component's status. */
  virtual void componentChanged(ComponentChangedEvent* evt) = 0;
};


#endif //__COMPONENTCHANGEDLISTENER_H__
