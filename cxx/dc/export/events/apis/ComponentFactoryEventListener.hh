/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__ComponentFactoryEventListener_H__
#define __ccafeopq__ComponentFactoryEventListener_H__

namespace ccafeopq {
namespace event {



/** This is the interface that a component must implement
    in order to be notified specifically of ComponentFactory Events. 
*/

class ComponentFactoryEventListener
{
public:
  /** required destructor */
  virtual ~ComponentFactoryEventListener(){}


  /** Called on listeners when an event occurs. */
  virtual void doComponentFactory( ComponentFactoryEvent_shared  event) = 0; 

} ; // end interface ComponentFactoryEventListener



} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/ComponentFactoryEventListener.hh,v 1.1 2004/03/20 02:16:09 baallan Exp $ */

#endif // __ccafeopq__ComponentFactoryEventListener_H__
