//void saveEeprom(){
//  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
//    emucan.checkEMUcan(canMsg.can_id, canMsg.can_dlc, canMsg.data);
//  }
//
//  // Serial out every second:
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis >= interval) {
//    previousMillis = currentMillis;
//    if (emucan.EMUcan_Status() == EMUcan_RECEIVED_WITHIN_LAST_SECOND) {
//      EEPROM.write(0, eepromTable[0]); 
//      EEPROM.write(1, eepromTable[1]); 
//    }      
//  }
//}

//void cutNumber(float val){
//  String number = String(val); 
//  number.sub
//}
