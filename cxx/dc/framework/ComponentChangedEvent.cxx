#include "dc/export/config.hh"
#ifdef HAVE_CLASSIC
#include <cca.h>
#endif // HAVE_CLASSIC

#include "dc/framework/ComponentChangedEvent.h"
namespace {
char id[]=
"$Id: ComponentChangedEvent.cxx,v 1.6 2004/10/16 05:53:20 baallan Exp $";
} ENDSEMI

int ComponentChangedEvent::PORT_ERROR      = 0;
int ComponentChangedEvent::PORT_REMOVED      = 1;
int ComponentChangedEvent::PORT_ADDED        = 2;
int ComponentChangedEvent::PORT_REGISTERED   = 3;
int ComponentChangedEvent::PORT_UNREGISTERED = 4;
