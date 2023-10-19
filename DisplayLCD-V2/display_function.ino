void displayTime(){ //Screen 1 
  clearLCD(1);
  displayHour();
  displayDate();
}

void displayPerf1(){ //Screen 2
  clearLCD(2);
  // Call the EMUcan lib with every received frame:
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    emucan.checkEMUcan(canMsg.can_id, canMsg.can_dlc, canMsg.data);
  }

  // Serial out every second:
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (emucan.EMUcan_Status() == EMUcan_RECEIVED_WITHIN_LAST_SECOND) {
      cursor(0,0);
      lcd.print("Lambda:");
      lcd.print(emucan.emu_data.wboLambda);
      cursor(0,1);
      lcd.print("Target:");
      lcd.print(emucan.emu_data.lambdaTarget);
      cursor(0,2);
      lcd.print("MAP:");
      if(emucan.emu_data.MAP < 100){
        lcd.print("0");
      }
      if(emucan.emu_data.MAP < 10){
        lcd.print("0");
      }
      lcd.print(emucan.emu_data.MAP);
      cursor(0,3);
      lcd.print("IAT:");
      if(emucan.emu_data.IAT < 100){
        lcd.print("0");
      }
      if(emucan.emu_data.IAT < 10){
        lcd.print("0");
      }
      lcd.print(emucan.emu_data.IAT);
    } 
    else {
      cursor(0,0);
      lcd.print("No communication");
    }
  }
}

void displayPerf2(){ //Screen 3
  clearLCD(3);
  // Call the EMUcan lib with every received frame:
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    emucan.checkEMUcan(canMsg.can_id, canMsg.can_dlc, canMsg.data);
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (emucan.EMUcan_Status() == EMUcan_RECEIVED_WITHIN_LAST_SECOND) {
      
      cursor(0,0);
      lcd.print("Vitesse:");
      if(emucan.emu_data.vssSpeed < 100){
        lcd.print("0");
      }
      if(emucan.emu_data.vssSpeed < 10){
        lcd.print("0");
      }
      lcd.print(emucan.emu_data.vssSpeed);
      
      cursor(0,1);
      lcd.print("RPM:");
      if(emucan.emu_data.RPM < 1000){
        lcd.print("0");
      }
      if(emucan.emu_data.RPM < 100){
        lcd.print("0");
      }
      if(emucan.emu_data.RPM < 10){
        lcd.print("0");
      }
      lcd.print(emucan.emu_data.RPM);
      
      cursor(0,2);
      lcd.print("CLT:");
      if(emucan.emu_data.CLT < 100){
        lcd.print("0");
      }
      if(emucan.emu_data.CLT < 10){
        lcd.print("0");
      }
      lcd.print(emucan.emu_data.CLT);
      
      cursor(0,3);
      lcd.print("CONSO:");
      lcd.print(emucan.emu_data.fuel_used);
      
      cursor(14,0);
      lcd.print("MODE:");      
      if (emucan.emu_data.flags1 & emucan.F_TABLE_SET) {
        lcd.print("H");     
      }
      else{
        lcd.print("S"); 
      }
      
      cursor(14,1);
      lcd.print("GEAR:");      
      lcd.print(emucan.emu_data.gear);     
        
    } else {
      cursor(0,0);
      lcd.print("No communication");
    }
  }
}

void displayPerf3(){ //Screen 4
  clearLCD(4);
  // Call the EMUcan lib with every received frame:
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    emucan.checkEMUcan(canMsg.can_id, canMsg.can_dlc, canMsg.data);
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (emucan.EMUcan_Status() == EMUcan_RECEIVED_WITHIN_LAST_SECOND) {
      cursor(0,0);
      lcd.print("RPM:");
      if(emucan.emu_data.RPM < 1000){
        lcd.print("0");
      }
      if(emucan.emu_data.RPM < 100){
        lcd.print("0");
      }
      if(emucan.emu_data.RPM < 10){
        lcd.print("0");
      }
      lcd.print(emucan.emu_data.RPM);
      
      cursor(0,1);
      lcd.print("Ign:");
      lcd.print(emucan.emu_data.IgnAngle);

      cursor(0,2);
      lcd.print("Volt:");
      lcd.print(emucan.emu_data.Batt);
          
      cursor(14,0);
      lcd.print("MODE:");      
      if (emucan.emu_data.flags1 & emucan.F_TABLE_SET) {
        lcd.print("H");     
      }
      else{
        lcd.print("S"); 
      }
      
      cursor(14,1);
      lcd.print("GEAR:");      
      lcd.print(emucan.emu_data.gear);
    } else {
      cursor(0,0);
      lcd.print("No communication");
    }
  }
}
