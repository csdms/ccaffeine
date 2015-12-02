#ifndef SingleClientDataCollector_seen
#define SingleClientDataCollector_seen

/**
   $Author: baallan $
   Created : <2000-08-10 13:35:45 pippin>
   Last modified Time-stamp: <2000-08-10 13:35:58 pippin> 

   This data collector ignores all but client 0. Messages from client 0
   are forward unchanged (ie, not edited by MessageData) to the controller.
*/

class SingleClientDataCollector :public virtual ClientOutputCollector {
 private:
  ClientOutputRelay* relay;
 public:
  SingleClientDataCollector( ClientOutputRelay* relay)
    { this->relay = relay; };
  static CDELETE ClientOutputCollector* create(ClientOutputRelay* relay) { return new SingleClientDataCollector(relay); };
  void computeClientOutput(ClientOutputEvent* evt) 
    { 
      printf ("SingleClientDataCollector::computeClientOutput\n");
      // take output from only one client
      if ((evt->getSource()->getId()) == 0)
	relay->relayMessageFromDataProducers(evt->getString());
    };
  void controllerClientOutput(ClientOutputEvent* evt)
    { 
      printf ("SingleClientDataCollector::computeClientOutput\n");
      relay->relayMessageFromController(evt->getString()); 
    }
  void setClientOutputRelay( ClientOutputRelay* cR)
    { if (relay) delete relay; relay = cR;};
  void processOutOfBand(OutOfBandEvent * evt)
    {(void) evt;  printf ("SingleClientDataCollector::processOutOfBand Method not implemented\n");};
};
#endif
