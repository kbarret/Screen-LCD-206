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



//if(digitalRead(switchInitTime) == LOW && table[5] == false){
//    
//    table[5] = true;
//    canMsg1.can_id = 0x0F6;
//    canMsg1.can_dlc = 2;
//    canMsg1.data[0] = 0xFF;
//    mcp2515.sendMessage(&canMsg1);
//  }
//  if(digitalRead(switchInitTime) == HIGH && table[5] == true){
//    
//    table[5] = false;
//    canMsg1.can_id = 0x0F6;
//    canMsg1.can_dlc = 2;
//    canMsg1.data[0] = 0x00;
//    mcp2515.sendMessage(&canMsg1);
//  }
