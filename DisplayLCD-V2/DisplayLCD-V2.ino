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

byte displaySelect = 1;
byte numberOfScreen = 4;
//byte eepromTable[] = {0, 0};//litre, decimal apres la virgule
const byte switchDisplay = 3;
const byte switchInitTime = 4;

boolean table[] = {false, false, false, false, false, false}; //buttonDisplay, clearDisplayTime, clearDisplayPerf1, clearDisplayPerf2, clearDisplayPerf3, buttonInitTime

struct can_frame canMsg1;

void setup() {
  
  Serial.begin(115200);
  
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
  
  displayToLCD();
}
