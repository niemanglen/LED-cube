bool rainbow_check(){
  if (digitalRead(Button1Pin)){
    return false;
  }
  if (digitalRead(Button2Pin)){
      mode = (mode+1)%7;//important to note that this 7 submodes is used for all effects including dots
      changePalette(mode+1);
      delay(200);
  }
  if (del<2){
    del = 1;
  }

  byte delta_del = 20;
  if (del<10){
    delta_del = 1;
  } else if(del<30){
    delta_del = 3;
  } else if(del<100){
    delta_del = 5;
  }

  if (digitalRead(Button3Pin)){
    del += 1;
    delay(50);
  }
  if (digitalRead(Button4Pin)){
    del -= 1;
    delay(50);
  }
  if (del>200){
    del = 200;
  }
  return true;
}
