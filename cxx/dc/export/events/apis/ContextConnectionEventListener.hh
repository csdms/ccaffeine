/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__ContextConnectionEventListener_H__
#define __ccafeopq__ContextConnectionEventListener_H__

namespace ccafeopq {
namespace event {



/** This is the interface that a component must implement
    in order to be notified specifically of ContextConnection Events. 
*/

class ContextConnectionEventListener
{
public:
  /** required destructor */
  virtual ~ContextConnectionEventListener(){}


  /** Called on listeners when an event occurs. */
  virtual void doContextConnection( ContextConnectionEvent_shared  event) = 0; 

} ; // end interface ContextConnectionEventListener



} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/ContextConnectionEventListener.hh,v 1.1 2004/03/20 02:16:09 baallan Exp $ */

#endif // __ccafeopq__ContextConnectionEventListener_H__
