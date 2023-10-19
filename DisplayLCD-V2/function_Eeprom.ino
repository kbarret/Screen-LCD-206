void eepromUpdate(){ 
  
//  chaine = String(consoAverage);
//  if(consoAverage >= 10){
//    unite = chaine.substring(0,1);
//    decimal = chaine.substring(3,4);
//    EEPROM.update(0, unite);
//    EEPROM.update(1, decimal);
//  }
//  else{
//    unite = chaine.substring(0,0);
//    decimal = chaine.substring(2,3);
//    EEPROM.update(0, unite);
//    EEPROM.update(1, decimal);
//  }  
}

void eepromRead(){
  unite = EEPROM.read(0);
  decimal = EEPROM.read(1)/100;
  consoAverage = unite + decimal;
}
