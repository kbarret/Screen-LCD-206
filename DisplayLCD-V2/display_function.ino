void displayTime(){  
  if(table[1] == false){
    lcd.clear();
    table[1] = true;
    table[2] = false;
    table[3] = false;
  }
  displayHour();
  displayDate();
}

void displayPerf1(){
  if(table[2] == false){
    lcd.clear();
    table[3] = false;
    table[2] = true;
    table[1] = false;
  }
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
      lcd.print(emucan.emu_data.MAP);
      cursor(0,3);
      lcd.print("IAT:");
      lcd.print(emucan.emu_data.IAT);
    } else {
      cursor(0,0);
      lcd.print("No communication");
    }
  }
}

void displayPerf2(){
  if(table[3] == false){
    lcd.clear();
    table[3] = true;
    table[2] = false;
    table[1] = false;
  }
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
      lcd.print(emucan.emu_data.RPM);
      cursor(0,2);
      lcd.print("CLT:");
      lcd.print(emucan.emu_data.CLT);
      cursor(0,3);
      lcd.print("CONSO:");
      lcd.print(emucan.emu_data.fuel_used);
      cursor(13,0);
      lcd.print("MODE:");      
      if (emucan.emu_data.flags1 & emucan.F_TABLE_SET) {
        lcd.print("H");     
      }
      else{
        lcd.print("S"); 
      }
    } else {
      cursor(0,0);
      lcd.print("No communication");
    }
  }
}
