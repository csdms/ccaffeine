#ifndef CmdLineClient_h_seen
#define CmdLineClient_h_seen


#define DEFAULTPROCFILEPATH "processors"

// Colin's Port of choice:
#define DEFAULTPORT 2023 


// base names for executables
#define CCAFE_SINGLE "ccafe-single"
#define CCAFE_BATCH "ccafe-batch"
#define CCAFE_CLIENT "ccafe-client"

/** Switch type for startup processing */
enum runtype_ {
  /** Normal client mode with a GUI View */
  CLIENT, 
  /** Local mode with no sockets, just stdio for human interaction. */
  INTERACTIVE, 
   /** Local mode with no sockets, just stdio for GUI interaction */
  GUI_INTERACTIVE,
   /** Normal client mode with a Human View, good for remote debugging. */
  HUMANCLIENT,
  /** Expects to be the only process, talking to
   a human at the keyboard.*/
  ONE_PROC_INTERACTIVE,
  /** Behave as a Server for the GUI.  Listen for a connection from a
      remote process. */
  SERVER,
  /** Run without connecting to anything outside this process.  IO
      will be remapped to files. */
  BATCH
};

typedef runtype_ runtype;

/** some ugly private implementation details. */
class MachWrapper;
class CmdLineBuilderController2;
class ClientServerSocket;

/**
  Client for handling remote gui or vice versa.
*/
class CmdLineClient {
private:

  CmdLineBuilderController2* controller;

  /** File to read that contain the participating processors */
  char* procFile;

  /** holds a jcpn(Vector) of dc/distributed/ProcessorInfo* 's  */
  MachWrapper * mWrap; 

  /** The index of this processor into the machines vector. */
  int myProcIndex;

  /** Name or IP number of this processor. */
  char* myProcName;

  /** What kind of hookup we will be using. */
  runtype runType;

  /** My proc rank: <= 1 is a single proc run. */
  int rank;
  /** Number of participating processors: <= 1 is a single processor run. */
  int size;

  /** Port number to connect to the server from which we will receive
      parse-able commands. */
  int port;

  /** True to print out sometimes helpful debugging information. */
  bool debug;

  /** Have we initialized Stovepipe to the command line arguments yet? */
  bool stp_initialized;

	bool useMPI;

  /** If using mpi, this is the communicator the framework has.
   * set as driver in CmdLineClientMain normally. Note it is in
   * fortran cast up to 8 byte format, which requires conversions
   * before use if MPI_Fint is not int64_t.
   */
  int64_t fortranMPIComm;
  bool hasComm;

public:

  CmdLineClient();
  ~CmdLineClient();
  int parse();
  /** Map the IO stream in static class IO to the given file.  The
      file is open to a line-buffered FILE pointer. */
  void mapIOToFile(const char* outName, const char* errName);
  /** Map the IO to the controlling tty. */
  void mapEverythingToTTY();
  /** Map the IO stream in static class IO to the given file as well
      as stdout and stderr.  The file is open to a line-buffered FILE
      pointer. */
  void mapEverythingToFile(const char* outName, const char* errName);
  /** Remap the IO to files named: procOut<rank> and procErr<rank> */
  void remapIO();
  /** Command line arg parser using Stovepipe.*/
  void parseArgsX(int argc, char** argv);
  /** Command line arg parser.*/
  void parseArgs(int argc, char** argv);

  /** Writes out the current machine jcpn(Vector)*. */
  void dumpMachines();
#ifdef CCAFE_SOCKETS
  /** Returns the ClientServerSocket for this configuration. */
  /*CDELETE*/ ClientServerSocket* setupSockets();
#endif // CCAFE_SOCKETS
  int main(int argc, char** argv, StaticFactory *sf = 0);
  /** machine name */
  void setName(char *name);
  /** parallel process enumerated id */
  void setRank(int rank);
  /** number of parallel processes */
  void setSize(int size);
  /** fortran comm, if mpi. needs to be called before main(). */
  void setComm(int64_t fComm);

  void setInitRunType(runtype_ runType);
	void setUseMPI(bool b);
	bool getUseMPI();
};




#endif //CmdLineClient_h_seen
