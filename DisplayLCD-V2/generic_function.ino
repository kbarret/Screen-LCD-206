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

void clearLCD(int screen){
  if(table[screen] == false){
    lcd.clear();
    for(int i = 1; i != numberOfScreen; i++){
      if(i == screen){
        table[i] = true;
      }
      table[i] = false;
    }   
  }
}
