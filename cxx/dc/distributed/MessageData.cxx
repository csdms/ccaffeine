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
#include "MessageData.h"


char* MessageData::makeErrorMessage(const char* message, const char* idList)
{
  jcpp::StringJC string(ERROR_BEG);
  string.append(idList);
  string.append(END_LIST);
  string.append(message);
  return STRDUP(string.getBuffer());
}



char* MessageData::makeOutOfBandMessage(const char* message, const char* idList)
{
  jcpp::StringJC string(ALERT_BEG);
  string.append(idList);
  string.append(END_LIST);
  string.append(message);
  return STRDUP(string.getBuffer());
}



char* MessageData::makeNormalMessage(const char* message, const char* idList)
{
  jcpp::StringJC string(BEG_LIST);
  string.append(idList);
  string.append(END_LIST);
  string.append(message);
  return STRDUP(string.getBuffer());
}


const char *MessageData::BEG_LIST = "<<";
const char *  MessageData::END_LIST = ">>";
  // no client names in the list of client names can contain this string
  // b/c it is used as a separator by the plugins
const char * MessageData::LIST_SEP = ",";
const char * MessageData::ERROR_TOKEN = "!";
const char * MessageData::SERVER_ALERT_TOKEN = "#";

const char * MessageData::ALERT_BEG = "#<<";
const char * MessageData::ERROR_BEG = "!<<";

MessageData::MessageData(const char* fullMessage, Client* client)
{
#if 0
  BEG_LIST = "<<";
  END_LIST = ">>";
  // no client names in the list of client names can contain this string
  // b/c it is used as a separator by the plugins
  LIST_SEP = ",";
  ERROR_TOKEN = "!";
  SERVER_ALERT_TOKEN = "#";

  ALERT_BEG = "#<<";
  ERROR_BEG = "!<<";
#endif

  jcpp::StringJC fullMessageString(fullMessage);
  if (((fullMessageString.startsWith(ALERT_BEG)) ||
	     (fullMessageString.startsWith(ERROR_BEG)) ||
	     (fullMessageString.startsWith(BEG_LIST))) && 
	    (fullMessageString.indexOf(END_LIST) > 0)){

    idList.appendSubstring(fullMessageString.getBuffer(),
			   fullMessageString.indexOf(BEG_LIST) + 
			   ::strlen(BEG_LIST), 
			   fullMessageString.indexOf(END_LIST));
    message.appendSubstring(fullMessageString.getBuffer(),
			    fullMessageString.indexOf(END_LIST) + 
			    ::strlen(END_LIST));
    prefix.appendSubstring(fullMessageString.getBuffer(), 0, 
			   fullMessageString.indexOf(BEG_LIST) + 
			   ::strlen(BEG_LIST));
  } else {
    if (client != NULL)
      idList.append(client->getSourceName());
    else
      idList.append("NOCLIENT");
    message.append(fullMessage);
    prefix.append(BEG_LIST);
  }
  if (client != NULL)
    {
      clients.put(client, client);
    }

  makeFormattedMessage();
}

void MessageData::appendIds(const char* idList, Client* client)
{
  this->idList.append(LIST_SEP);
  this->idList.append(idList);
  if (client != NULL)
    {
      clients.put(client, client);
    }
  makeFormattedMessage();
}

boolean MessageData::equals(JCPN(Object)* obj)
{
  MessageData* msg = dynamic_cast <MessageData*> (obj); CHECKDC(msg);
  return (message.equals(&(msg->message)) &&
	  prefix.equals(&(msg->prefix)));
}

int MessageData::hashValue() 
{
  return message.hashValue() + prefix.hashValue();
}

void MessageData::makeFormattedMessage() 
{
  formattedMessage.setString(prefix.getBuffer());
  formattedMessage.append(idList.getBuffer());
  formattedMessage.append(END_LIST);
  formattedMessage.append(message.getBuffer());
}
char* MessageData::getMessage()  
 { return message.getBuffer(); };
#else // ccafethreads
int ccafe_no_messagedata=1;
#endif //CCAFE_THREADS
