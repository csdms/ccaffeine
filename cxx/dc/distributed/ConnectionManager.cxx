#ifdef CCAFE_THREADS

#include <stdio.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include "jc++/jc++.h"
#include "jc++/util/jc++util.h"
#include "jc++/util/Thread.h"
#include "ConnectionManager.h"

ConnectionManager::ConnectionManager() {};
ConnectionManager::~ConnectionManager() {};
#else // CCAFE_THREADS
int ccafe_no_connectionmanager=1;
#endif // CCAFE_THREADS
