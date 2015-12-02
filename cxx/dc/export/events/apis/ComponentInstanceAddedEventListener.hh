/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__ComponentInstanceAddedEventListener_H__
#define __ccafeopq__ComponentInstanceAddedEventListener_H__

namespace ccafeopq {
namespace event {



/** This is the interface that a component must implement
    in order to be notified specifically of ComponentInstanceAdded Events. 
*/

class ComponentInstanceAddedEventListener
{
public:
  /** required destructor */
  virtual ~ComponentInstanceAddedEventListener(){}


  /** Called on listeners when an event occurs. */
  virtual void doComponentInstanceAdded( ComponentInstanceAddedEvent_shared  event) = 0; 

} ; // end interface ComponentInstanceAddedEventListener



} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/ComponentInstanceAddedEventListener.hh,v 1.1 2004/03/20 02:16:09 baallan Exp $ */

#endif // __ccafeopq__ComponentInstanceAddedEventListener_H__
