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
