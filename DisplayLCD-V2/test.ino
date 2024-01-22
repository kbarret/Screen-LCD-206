void serialRead(){
  if(Serial.available()){
    val = Serial.read();
    if(val == "l"){
      lcd.backlight();
    }
  }
}
