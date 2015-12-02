/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__ContextEventListener_H__
#define __ccafeopq__ContextEventListener_H__

namespace ccafeopq {
namespace event {



/** This is the interface that a component must provide
    in order to be notified of Events. 
    This is the interface we subclass to receive
    more particular event types.
*/

class ContextEventListener
{
public:
  /** required destructor */
  virtual ~ContextEventListener(){}


  /** Called on listeners when an event occurs. */
  virtual void contextActivity( ContextEvent_shared  ed) = 0; 

} ; // end interface ContextEventListener



} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/ContextEventListener.hh,v 1.1 2004/03/20 02:16:09 baallan Exp $ */

#endif // __ccafeopq__ContextEventListener_H__
