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
unsigned long average = 0;
unsigned long sampling = 0;
unsigned long currentMillis = 0;
unsigned long currentMillisConso = 0;

const long interval = 500;

byte displaySelect = 1;
byte numberOfScreen = 4 ;

const byte switchDisplay = 3;
const byte switchInitTime = 4;

boolean table[] = {false, false, false, false, false, false, false, false, false, false, false, false}; //buttonDisplay, clearDisplayTime, clearDisplayPerf1, clearDisplayPerf2, clearDisplayPerf3, buttonInitTime, com1, com2, com3, com4, com5, com6

struct can_frame canMsg1;
struct can_frame canMsg2;

float pulseWidth = 0;
float conso = 0;


double consoAverage = 0;

int speedVss = 0;
int rpm = 0;
int injectorSize = 350;
int valeurA0 = 0;
int valeurA1 = 0;
int valeurA0min = 0;
int valeurA1min = 0;
int valeurA0max = 0;
int valeurA1max = 0;
int valeurTampon = 0;


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
  
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  digitalWrite(switchDisplay, HIGH);
  digitalWrite(switchInitTime, HIGH);
  
  //moduleRTC
  //myRTC.setDS1302Time(second(), minute(), hour(), weekday(), day(), month() , year()); //Configuration du temps réel 
  //myRTC.setDS1302Time(0, 31, 17, 5, 13, 10 , 2023); //Configuration du temps réel 

  //EEPROM
  eepromRead();
}

void loop() {
  myRTC.updateTime();

  calculConso();
  
  actionButton();
  
  displayToLCD();
}
