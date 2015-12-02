#ifdef CCAFE_THREADS

#ifndef DataCollectorFactory_seen
#define DataCollectorFactory_seen


/**
   $Author: baallan $
   Created : <2000-08-10 13:35:45 pippin>
   Last modified Time-stamp: <2000-08-10 13:35:58 pippin> 

   This class maps strings to DataCollector creation functions. It is 
   implemented using a hash table of collector creators. Collector creators 
   are simply holders for creation functions.

   In order to add a new type of 
   DataCollector, you must currently modify and recompile this class. 
   BUGBUG - put this in a separate dyn load lib so that the whole dc/dist 
   lib doesn't need to be recompiled.
*/
class DataCollectorFactory :public virtual JCPN(Object) {
 private:
  JCPN(GenericHashTable) collectors;
 public:
  DataCollectorFactory();
  ~DataCollectorFactory();
  CDELETE ClientOutputCollector* create(char* name, ClientOutputRelay* relay);
};

class CollectorCreator :public virtual JCPN(Object) {
  CDELETE ClientOutputCollector* (*creationFunc) (ClientOutputRelay*);
 public:
  CollectorCreator( CDELETE ClientOutputCollector* (*creationFunc)(ClientOutputRelay*))
    { this->creationFunc = creationFunc; }; 
  CDELETE ClientOutputCollector* create(ClientOutputRelay* relay) { return creationFunc(relay); };
};
#endif // seen datacollector
#else // CCAFE_THREADS
extern int ccafe_no_datacollector;
#endif // CCAFE_THREADS
