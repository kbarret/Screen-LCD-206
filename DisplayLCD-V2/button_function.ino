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
    canMsg1.can_id = 0x0F6;
    canMsg1.can_dlc = 2;
    canMsg1.data[0] = 0xFF;
    mcp2515.sendMessage(&canMsg1);
  }
  if(digitalRead(switchInitTime) == HIGH && table[5] == true){
    
    table[5] = false;
    canMsg1.can_id = 0x0F6;
    canMsg1.can_dlc = 2;
    canMsg1.data[0] = 0x00;
    mcp2515.sendMessage(&canMsg1);
  }
}
