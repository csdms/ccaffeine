/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__PortActivityEventListener_H__
#define __ccafeopq__PortActivityEventListener_H__

namespace ccafeopq {
namespace event {



/** This is the interface that a component must implement
    in order to be notified specifically of PortActivity Events. 
*/

class PortActivityEventListener
{
public:
  /** required destructor */
  virtual ~PortActivityEventListener(){}


  /** Called on listeners when an event occurs. */
  virtual void doPortActivity( PortActivityEvent_shared  event) = 0; 

} ; // end interface PortActivityEventListener



} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/PortActivityEventListener.hh,v 1.1 2004/03/20 02:16:09 baallan Exp $ */

#endif // __ccafeopq__PortActivityEventListener_H__
