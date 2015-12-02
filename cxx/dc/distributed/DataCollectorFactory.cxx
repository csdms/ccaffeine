#ifdef CCAFE_THREADS
#include <string.h>
#include <errno.h>
#include "jc++/jc++.h"
#include "jc++/lang/Object.h"
#include "jc++/util/jc++util.h"
#include "jc++/util/Thread.h"
#include "jc++/lang/String.hh"
#include "ConnectionManager.h"
#include "ClientInterfaces.h"
#include "EchoAllDataCollector.h"
#include "SingleClientDataCollector.h"
#include "DataCollectorFactory.h"


DataCollectorFactory::DataCollectorFactory()
{
  collectors.put (new jcpp::StringJC("SingleClientDataCollector"), new CollectorCreator(SingleClientDataCollector::create));
  collectors.put (new jcpp::StringJC("EchoAllDataCollector"), new CollectorCreator(EchoAllDataCollector::create));
}

DataCollectorFactory::~DataCollectorFactory()
{
}

CDELETE ClientOutputCollector* DataCollectorFactory::create(char* name, ClientOutputRelay* relay)
{
  jcpp::StringJC string(name);
  CollectorCreator* creator = dynamic_cast<CollectorCreator*> (collectors.get(&string)); 
  if (creator) {
    return creator->create(relay);
  } else {
    return NULL;
  }
}
#else // CCAFE_THREADS
int ccafe_no_datacollector=1;
int ccafe_no_clientinterfaces=1;
#endif // CCAFE_THREADS
