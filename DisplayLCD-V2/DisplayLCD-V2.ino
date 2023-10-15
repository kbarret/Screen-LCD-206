#include <EEPROM.h>

#include <LiquidCrystal_I2C.h>
// set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,20,4);  

#include "EMUcan.h"
// EMU initialized with base ID 600:
EMUcan emucan(0x600);

#include <mcp2515.h>
struct can_frame canMsg;
// MCP2515 with chip select (CS) pin 10:
MCP2515 mcp2515(10);

#include <virtuabotixRTC.h>
// CLK -> 6 , DAT -> 7, Reset -> 8
virtuabotixRTC myRTC(6, 7, 8);



unsigned long previousMillis = 0;
const long interval = 500;

byte displaySelect = 0;
//byte eepromTable[] = {0, 0};//litre, decimal apres la virgule
const byte switchDisplay = 3;
const byte switchInitTime = 4;

boolean table[] = {false, false, false, false, false}; //buttonDisplay, clearDisplayTime, clearDisplayPerf1, clearDisplayPerf2, buttonInitTime

void setup() {
  
  Serial.begin(115200);
  Serial.print("EMUCAN_LIB_VERSION: ");
  Serial.println(EMUCAN_LIB_VERSION);
  Serial.println("------- CAN Read ----------");
  
  //EMUcan
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  
  //DisplayLCD
  lcd.init();
  lcd.backlight();

    //bouton
  pinMode(switchDisplay, INPUT);
  pinMode(switchInitTime, INPUT);
  digitalWrite(switchDisplay, HIGH);
  digitalWrite(switchInitTime, HIGH);
  
  //moduleRTC
  //myRTC.setDS1302Time(second(), minute(), hour(), weekday(), day(), month() , year()); //Configuration du temps réel 
 //myRTC.setDS1302Time(0, 31, 17, 5, 13, 10 , 2023); //Configuration du temps réel 

  //EEPROM
//  eepromTable[0] = EEPROM.read(0);
//  eepromTable[1] = EEPROM.read(1);
}

void loop() {
  myRTC.updateTime();
  
  actionButton();
  
  switch(displaySelect){
    case 0:
      displayTime();
      break;
    case 1:
      displayPerf1();
      break;
    case 2:
      displayPerf2();
      break;
  }  
}

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
//    if (emucan.emu_data.flags1 & emucan.F_IDLE) {
//      Serial.println("Engine Idle active");
//    }
//    if (emucan.decodeCel()) {
//      Serial.println("WARNING Engine CEL active");
//    }
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

void actionButton(){
  if(digitalRead(switchDisplay) == LOW && table[0] == false){
    displaySelect++;
    if(displaySelect > 2){
      displaySelect = 0;
    }
    table[0] = true;
  }
  if(digitalRead(switchDisplay) == HIGH && table[0] == true){
    table[0] = false;
  }
  
//  if(digitalRead(switchInitTime) == LOW && table[4] == false){
//    int Minute = minute(now());
//    Serial.println(Minute);
//    myRTC.setDS1302Time(0, Minute, hour(now()), weekday(now()), day(now()), month(now()) , year(now())); //Configuration du temps réel 
//    //myRTC.setDS1302Time(second(now()), minute(now()), hour(now()), weekday(now()), day(now()), month(now()) , year(now())); //Configuration du temps réel 
//    table[4] = true;
//  }
//  if(digitalRead(switchInitTime) == HIGH && table[4] == true){
//    table[4] = false;
//  }
}

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
