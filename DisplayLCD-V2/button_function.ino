void actionButton(){
  if(digitalRead(switchDisplay) == LOW && table[0] == false){
    displaySelect++;
    if(displaySelect > numberOfScreen){
      displaySelect = 1;
    }
    table[0] = true;
  }
  if(digitalRead(switchDisplay) == HIGH && table[0] == true){
    table[0] = false;
  }
  
  if(digitalRead(switchInitTime) == LOW && table[5] == false){
    table[5] = true;
  }
  if(digitalRead(switchInitTime) == HIGH && table[5] == true){
    average = 0;
    sampling = 0;
    consoAverage = 0;
    eepromUpdate();
    table[5] = false;
  }
}
