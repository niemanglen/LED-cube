byte user_set() {
  //this mode is used for allowing the user to set two custom colors, the overall brightness, and the number of dots used for future effects
  byte seta = 0;

  
while (true){

  if (digitalRead(Button1Pin) and digitalRead(Button2Pin) and digitalRead(Button3Pin) and digitalRead(Button4Pin)){

    dot_drop_num = 6;
    brightness = 100;
    color1.hue = 130;
    color1.sat = 255;
    color2.hue = 205;
    color2.sat = 255;

    EEPROM.update(14,dot_drop_num);
    EEPROM.update(15,brightness);
        
    EEPROM.update(16,color1.hue);
    EEPROM.update(17,color1.sat);
    
    EEPROM.update(18,color2.hue);
    EEPROM.update(19,color2.sat);


    delay(3000);

    return 3;
  }
  if (digitalRead(Button1Pin)){
    //RGB effect change button pressed
    EEPROM.update(14,dot_drop_num);
    EEPROM.update(15,brightness);
    
    EEPROM.update(16,color1.hue);
    EEPROM.update(17,color1.sat);

    EEPROM.update(18,color2.hue);
    EEPROM.update(19,color2.sat);


    return 3;
  }
  
  if (digitalRead(Button2Pin)){
    //Submode button pressed
    seta = (seta + 1)%4;
    delay(200);
  }
  if (digitalRead(Button3Pin)){
    //Topleft button pressed
    if (seta==0){
      color1.hue = (color1.hue+1)%256;
    } else if (seta==1) {
      color2.hue = (color2.hue+1)%256;
    } else if (seta==2){
      if (brightness<255){
        brightness = brightness+1;
      }
    } else if (seta==3) {
      dot_drop_num += 1;
      if (dot_drop_num>56){
        dot_drop_num=56;
      }
      delay(250);
    }
    delay(50);
  }
  if (digitalRead(Button4Pin)){
    //Topright button pressed
    if (seta==0){
      color1.sat = (color1.sat+1)%256;//set the "1" to a "0" to disable this mode
    } else if (seta==1){
      color2.sat = (color2.sat+1)%256;//set the "1" to a "0" to disable this mode
    } else if (seta==2){
      if (brightness>0){
        brightness = brightness-1;
      }
    }else if (seta==3) {
        dot_drop_num -= 1;
        if (dot_drop_num<1){
          dot_drop_num=1;
        }
      delay(250);
    }
    delay(50);
  }
  for (byte i=0;i<NUM_LEDS;i++){
    //start with a blank slate
      leds[i] = CRGB(0,0,0);
  }
  if (seta==3) {
    //dot num mode
    for (byte i=0;i<dot_drop_num;i++){
      leds[i] = CRGB(brightness,brightness,brightness);
    }
  } else if (seta==2){
    //brightness mode
    for (byte i=0;i<NUM_LEDS;i++){
      leds[i] = CHSV(color1.hue,color1.sat,brightness);
    }
  } else {
    //color select mode
    for (byte i=0;i<8;i++){
      leds[i] = color1;
      leds[i+8] = color2;
    }
  }
  FastLED.show();
  }


  
}
