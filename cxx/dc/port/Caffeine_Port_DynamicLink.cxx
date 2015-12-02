#include "jc++/jc++.h"
#include "CCA_Block.h"
#include "BlockPort.h"
#include "dc/port/Caffeine_Port_DynamicLink.h"

Caffeine_Port_DynamicLink::Caffeine_Port_DynamicLink(int i) {
  iSave = 0;
  if((iSave = i)) {
    bd = new CCA_BlockDescription();
    db = new CCA_DoubleBlock(bd);
  }
}
Caffeine_Port_DynamicLink::~Caffeine_Port_DynamicLink(){
  if(iSave) {
    delete db;
    delete bd;
  }
}
