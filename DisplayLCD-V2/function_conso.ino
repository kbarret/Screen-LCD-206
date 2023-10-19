void calculConso(){
  // Call the EMUcan lib with every received frame:
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    emucan.checkEMUcan(canMsg.can_id, canMsg.can_dlc, canMsg.data);
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (emucan.EMUcan_Status() == EMUcan_RECEIVED_WITHIN_LAST_SECOND) {
      if(emucan.emu_data.vssSpeed > 4){
        speedVss = emucan.emu_data.vssSpeed;
        rpm = emucan.emu_data.RPM;
        pulseWidth = emucan.emu_data.pulseWidth;
        conso = rpm*2*60*pulseWidth;
        conso = conso/1000;
        conso = conso/60;
        conso = conso*injectorSize;
        conso = conso/1000;
        conso = (conso*100)/speedVss;

        consoAverage = (consoAverage + conso)/2;
      }
    } 
  }
}
