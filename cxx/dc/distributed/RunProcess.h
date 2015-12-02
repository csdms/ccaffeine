#ifndef RunProcess_seen
#define RunProcess_seen

#define TESTDEFAULTPORT 3141 //BUGBUG


class RunProcess :public virtual ReadCallback {
 private:
  // a JCPN(Vector) of dc/distributed/ProcessorInfo* 's 
  JCPN(Vector)* machines; 
  int myProcIndex; // The index of this processor into the machines vector.
  SocketConnectionManager* sockets;
  JCPN(BufferedReader)* reader;

  void doRedirect();
 public:
  RunProcess(char* procName, int Port);
  void execCommand(int argc, char** argv);
  void readReady (Connection* conn);
  ~RunProcess() { if (sockets) delete sockets; if (reader) delete reader; };
};


#endif // RunProcess_seen
