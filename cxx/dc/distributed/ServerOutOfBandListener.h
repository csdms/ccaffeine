#ifdef  CCAFE_THREADS
#ifndef ServerOutOfBandListener_seen
#define ServerOutOfBandListener_seen

/**
   $Author: baallan $
   Created : <2000-08-10 13:35:45 pippin>
   Last modified Time-stamp: <2000-08-10 13:35:58 pippin> 

   This class handles out of band messages for the server mux -
   specifically setting the data collector, disconnecting clients,
   and shutting down the server mux.
*/
class ServerMux;

class ServerOutOfBandListener : public virtual OutOfBandListener {
 private:
  ServerMux* server;
 public:
  ServerOutOfBandListener(ServerMux* server)
    {
      this->server = server;
    };
  void processOutOfBand(OutOfBandEvent* evt); 
};

#endif // seen soobl
#else  // ccafethread
extern int ccafe_no_serveroobl;
#endif // CCAFE_THREADS
