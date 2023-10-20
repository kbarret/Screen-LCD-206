void eepromUpdate(){ 
  EEPROM.put(0, average);
  EEPROM.put(8, sampling);
}

void eepromRead(){
  if(EEPROM.read(20) > 100){
    EEPROM.write(20, 0);
    EEPROM.put(0, average);
    EEPROM.put(8, sampling);
    EEPROM.get(0, average);
    EEPROM.get(8, sampling);
  }
  else{
    //EEPROM.write(20, 255);
    EEPROM.get(0, average);
    EEPROM.get(8, sampling);
    consoAverage = average/(sampling/100);
    consoAverage = consoAverage*0.01;
    Serial.println(sampling);
    Serial.println(average);
    Serial.println(consoAverage);
    //    Serial.println(sampling);
    //Serial.print(EEPROM.read(20));
    
  } 
}
