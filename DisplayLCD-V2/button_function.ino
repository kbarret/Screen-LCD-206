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
}
