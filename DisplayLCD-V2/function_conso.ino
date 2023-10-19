void calculConso(){
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    emucan.checkEMUcan(canMsg.can_id, canMsg.can_dlc, canMsg.data);
  }
  if(emucan.emu_data.vssSpeed > 15){
    speedVss = emucan.emu_data.vssSpeed;
    rpm = emucan.emu_data.RPM;
    pulseWidth = emucan.emu_data.pulseWidth;
    conso = rpm*pulseWidth;;
    conso = conso*120;
    conso = conso/1000;
    conso = conso/60;
    conso = conso*injectorSize;
    conso = conso/1000;
    conso = (conso*100)/speedVss;

    if(counter < numberOfAverage){
      counter++;
      consoAverage = consoAverage + conso;
    } 
    else{
      consoAverageAffiche = consoAverage/1002;
      consoAverage = consoAverage/1002;
      counter = 0;
    }
  }
}
