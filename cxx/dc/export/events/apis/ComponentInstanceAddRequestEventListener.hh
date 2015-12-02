/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__ComponentInstanceAddRequestEventListener_H__
#define __ccafeopq__ComponentInstanceAddRequestEventListener_H__

namespace ccafeopq {
namespace event {



/** This is the interface that a component must implement
    in order to be notified specifically of ComponentInstanceAddRequest Events. 
*/

class ComponentInstanceAddRequestEventListener
{
public:
  /** required destructor */
  virtual ~ComponentInstanceAddRequestEventListener(){}


  /** Called on listeners when an event occurs. */
  virtual void doComponentInstanceAddRequest( ComponentInstanceAddRequestEvent_shared  event) = 0; 

} ; // end interface ComponentInstanceAddRequestEventListener



} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/ComponentInstanceAddRequestEventListener.hh,v 1.1 2004/03/20 02:16:09 baallan Exp $ */

#endif // __ccafeopq__ComponentInstanceAddRequestEventListener_H__
