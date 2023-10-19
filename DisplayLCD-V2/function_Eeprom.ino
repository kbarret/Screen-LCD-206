void eepromUpdate(){ 
  EEPROM.put(0, consoAverageAffiche);
}

void eepromRead(){
  EEPROM.get(0, consoAverageAffiche);
}
