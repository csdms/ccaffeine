#ifdef CCAFE_THREADS

#include <errno.h>
#include <string.h>
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "jc++/lang/String.hh"
#include "jc++/util/Thread.h"
#include "ConnectionManager.h"
#include "ClientInterfaces.h"
#include "DataCollectorFactory.h"
#include "ServerMux.h"
#include "ServerOutOfBandListener.h"

void ServerOutOfBandListener::processOutOfBand( OutOfBandEvent* evt)
{
  char* string = evt->getOutOfBandCommand();
  Client* src = evt->getSource();

  // check for messages the server mux understands
  if (strstr(string, ServerMux::DATA_COLLECTOR_MSG) == string) {
    // the client would like to reset the data collector
    printf("Got data collector message\n");
    char* className = &(string[strlen(ServerMux::DATA_COLLECTOR_MSG)]);
    server->setDataCollectorByName(className);
  } else if (strstr(string, ServerMux::SHUTDOWN_MSG) == string) {
    // the client would like to shut down the entire system
    printf("Got shutdown message\n");
    server->shutdown();
  } else if (strstr(string, ServerMux::REMOVE_CLIENT_MSG) == string) {
    // the client would like to be removed.
    printf("Got disconnect message from a client\n");
    src->disconnect();
  }
  
}
#else  // ccafethread
int ccafe_no_serveroobl=1;
#endif // CCAFE_THREADS
