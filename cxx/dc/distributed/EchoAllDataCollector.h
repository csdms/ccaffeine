#ifndef EchoAllDataCollector_seen
#define EchoAllDataCollector_seen

/**
   $Author: baallan $
   Created : <2000-08-10 13:35:45 pippin>
   Last modified Time-stamp: <2000-08-10 13:35:58 pippin> 

   This data collector does nothing to the strings it recieves, just passes 
   them on to the controller as it recieves them.
*/
class EchoAllDataCollector :public virtual ClientOutputCollector {
 private:
  ClientOutputRelay* relay;
 public:
  EchoAllDataCollector( ClientOutputRelay* relay)
    { this->relay = relay; };
  static CDELETE ClientOutputCollector* create(ClientOutputRelay* relay) { return new EchoAllDataCollector(relay); };
  void computeClientOutput(ClientOutputEvent* evt) 
    { 
      printf ("EchoAllDataCollector::computeClientOutput\n");
      // take output from all clients
      relay->relayMessageFromDataProducers(evt->getString());
    };
  void controllerClientOutput(ClientOutputEvent* evt)
    { 
      printf ("EchoAllDataCollector::computeClientOutput\n");
      relay->relayMessageFromController(evt->getString()); 
    }
  void setClientOutputRelay( ClientOutputRelay* cR)
    { if (relay) delete relay; relay = cR;};
  void processOutOfBand(OutOfBandEvent * evt)
    { (void)evt;  printf ("EchoAllDataCollector::processOutOfBand Method not implemented\n");};
};
#endif
