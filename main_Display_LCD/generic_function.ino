void cursor(int colonne, int ligne){
  lcd.setCursor(colonne,ligne);
}

void conditionZero(int valeur, int colonne, int ligne){
  if(valeur < 10){
    lcd.print(0);
    cursor(colonne, ligne);
    lcd.print(valeur);
  }
  else{
    lcd.print(valeur);
  }
}

void displayHour(){
  cursor(0,0);
  conditionZero(myRTC.hours, 1, 0);
  cursor(2,0);
  lcd.print(":");
  cursor(3,0);
  conditionZero(myRTC.minutes, 4, 0);
  cursor(5,0);
  lcd.print(":");
  cursor(6,0);
  conditionZero(myRTC.seconds, 7, 0);
  
}
 
void displayDate(){
  cursor(5,3);
  conditionZero(myRTC.dayofmonth, 6, 3);
  cursor(7,3);
  lcd.print("/");
  cursor(8,3);
  conditionZero(myRTC.month, 9, 3);
  cursor(10,3);
  lcd.print("/");
  cursor(11,3);
  lcd.print(myRTC.year);
}

void displayToLCD(){
  if(menuDisplay == false){
    // Call the EMUcan lib with every received frame:
    if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
      emucan.checkEMUcan(canMsg.can_id, canMsg.can_dlc, canMsg.data);
     }
    // Serial out every second:
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if (emucan.EMUcan_Status() == EMUcan_RECEIVED_WITHIN_LAST_SECOND || testDisplay == true) {
        switch(displaySelect){
            case 1:
              displayTime();
               break;
            case 2:
              displayPerf1();
              break;
            case 3:
              displayPerf2();
              break;
            case 4:
              displayPerf3();
              break;
        }       
      }  
      else {
        lcd.clear();
        lcd.noBacklight();
      } 
    }
  }
  else{
    displayMenu(); 
  }
}

void clearLCD(int screen){
  //Serial.println(table[4]);
  if(table[screen] == false){
    lcd.clear();
    table[screen] = true;
    for(int i = 1; i != numberOfScreen+1; i++){
      if(i != screen){
        table[i] = false;
        
      }     
    }   
  }
}

void serialRead(){
  if(Serial.available()){
    val = Serial.read();
  }
}
