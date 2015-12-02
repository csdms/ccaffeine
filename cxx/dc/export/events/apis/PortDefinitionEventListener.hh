/* CPP BINDING - generated CCA file. do not edit. */
#ifndef __ccafeopq__PortDefinitionEventListener_H__
#define __ccafeopq__PortDefinitionEventListener_H__

namespace ccafeopq {
namespace event {



/** This is the interface that a component must implement
    in order to be notified specifically of PortDefinition Events. 
*/

class PortDefinitionEventListener
{
public:
  /** required destructor */
  virtual ~PortDefinitionEventListener(){}


  /** Called on listeners when an event occurs. */
  virtual void doPortDefinition( PortDefinitionEvent_shared  event) = 0; 

} ; // end interface PortDefinitionEventListener



} ENDSEMI // end namespace event
} ENDSEMI // end namespace ccafeopq


/* $Header: /cvs/ccaffeine/repository/dccafe/cxx/dc/export/events/apis/PortDefinitionEventListener.hh,v 1.1 2004/03/20 02:16:09 baallan Exp $ */

#endif // __ccafeopq__PortDefinitionEventListener_H__
