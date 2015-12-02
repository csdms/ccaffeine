/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__ComponentInstanceDeleteRequestEventListener_H__
#define __ccafeopq__ComponentInstanceDeleteRequestEventListener_H__

namespace ccafeopq {
namespace event {



/** This is the interface that a component must implement
    in order to be notified specifically of ComponentInstanceDeleteRequest Events. 
*/

class ComponentInstanceDeleteRequestEventListener
{
public:
  /** required destructor */
  virtual ~ComponentInstanceDeleteRequestEventListener(){}


  /** Called on listeners when an event occurs. */
  virtual void doComponentInstanceDeleteRequest( ComponentInstanceDeleteRequestEvent_shared  event) = 0; 

} ; // end interface ComponentInstanceDeleteRequestEventListener



} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/ComponentInstanceDeleteRequestEventListener.hh,v 1.1 2004/03/20 02:16:09 baallan Exp $ */

#endif // __ccafeopq__ComponentInstanceDeleteRequestEventListener_H__
