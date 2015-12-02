/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__ComponentInstanceDeletedEventListener_H__
#define __ccafeopq__ComponentInstanceDeletedEventListener_H__

namespace ccafeopq {
namespace event {



/** This is the interface that a component must implement
    in order to be notified specifically of ComponentInstanceDeleted Events. 
*/

class ComponentInstanceDeletedEventListener
{
public:
  /** required destructor */
  virtual ~ComponentInstanceDeletedEventListener(){}


  /** Called on listeners when an event occurs. */
  virtual void doComponentInstanceDeleted( ComponentInstanceDeletedEvent_shared  event) = 0; 

} ; // end interface ComponentInstanceDeletedEventListener



} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/ComponentInstanceDeletedEventListener.hh,v 1.1 2004/03/20 02:16:09 baallan Exp $ */

#endif // __ccafeopq__ComponentInstanceDeletedEventListener_H__
