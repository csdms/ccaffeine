#ifdef CCAFE_THREADS
#ifndef MessageData_seen
#define MessageData_seen

/**
   $Author: baallan $
   Created : <2000-08-10 13:35:45 pippin>
   Last modified Time-stamp: <2000-08-10 13:35:58 pippin> 

   This class handles parsing of message strings, chiefly the job of 
   stripping off the markers at the begining of the string which identify
   which type of message it is. Also makes well-formed messages out of 
   untagged strings.
*/

class MessageData : public virtual JCPN(Object) {
 private:
  jcpp::StringJC message;
  jcpp::StringJC prefix;
  jcpp::StringJC idList;
  jcpp::StringJC formattedMessage;
  JCPN(GenericHashTable) clients;
  void makeFormattedMessage();

 public:
  MessageData(const char* fullMessage, Client* client);
  ~MessageData() {};

  char* getIdList() { return idList.getBuffer(); };
  char* getPrefix() { return prefix.getBuffer(); };
  char* getMessage();
  char* getFormattedMessage() { 
    return formattedMessage.getBuffer(); 
  };
 
  void appendIds(const char* idList, Client* client);
  boolean hasClientData(Client* client) { return clients.contains(client); };

  boolean equals(JCPN(Object)* other);
  int hashValue();

  static const char* BEG_LIST;// = "<<";
  static const char* END_LIST ;//= ">>";
  // no client names in the list of client names can contain this string
  // b/c it is used as a separator by the plugins
  static const char* LIST_SEP ;//= ","; 
  static const char* ERROR_TOKEN ;//= "!";
  static const char* SERVER_ALERT_TOKEN ;//= "#";
  
  static const char* ALERT_BEG ;//= "#<<";
  static const char* ERROR_BEG ;//= "!<<";

  static CFREE char* makeErrorMessage(const char* message, const char* idList);
  static CFREE char* makeOutOfBandMessage(const char* message, const char* idList);
  static CFREE char* makeNormalMessage(const char* message, const char* idList);
};
#endif // seen
#else // ccafethreads
extern int ccafe_no_messagedata;
#endif //CCAFE_THREADS
