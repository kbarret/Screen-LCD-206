void calculConso(){
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    emucan.checkEMUcan(canMsg.can_id, canMsg.can_dlc, canMsg.data);
  }
  if(emucan.emu_data.vssSpeed > 20){
    speedVss = emucan.emu_data.vssSpeed;
    rpm = emucan.emu_data.RPM;
    pulseWidth = emucan.emu_data.pulseWidth;
    conso = rpm*pulseWidth;
    conso = conso*120;
    conso = conso/1000;
    conso = conso/60;
    conso = conso*injectorSize;
    conso = conso/1000;
    conso = (conso*100)/speedVss;
    average = average + conso;
    sampling++;
    eepromUpdate();
    consoAverage = average/sampling;
      
//    currentMillisConso = millis();
//    if (currentMillis - previousMillis >= interval) {
//      previousMillis = currentMillis;
//      
//    }
  }
//  rpm = emucan.emu_data.RPM;
//  pulseWidth = emucan.emu_data.pulseWidth;
//  conso = rpm*pulseWidth;
//  conso = conso*120;
//  conso = conso/1000;
//  conso = conso/60;
//  conso = conso*injectorSize;
//  conso = conso/1000;
//  average = average + conso;
//  //Serial.println(average);
//  sampling++;
//  eepromUpdate();
//  consoAverage = average/sampling;
//  
}
