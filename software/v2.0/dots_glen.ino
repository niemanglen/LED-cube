byte dots_glen(){
  mode = 0;
  del = 90;//starting delay of 90 works well
  
  while (true){

  if (not rainbow_check()){
    return 3;
  }

  currentMillis = millis();
  
  if (currentMillis - previousMillis>del){
  //determine if the delay criterion has been met
  //if so, update the display
  
  previousMillis = currentMillis;//reset the loop condition variable

  for (byte k=0;k<dot_drop_num;k++){
      byte addr = random(NUM_LEDS);
      if (mode==0){
        leds_hue[addr] = random(256);
        leds_sat[addr] = 255;
      } else if (mode==1){
        leds_hue[addr] = color1.hue;
        leds_sat[addr] = color1.sat;
      } else if (mode==2){
        leds_hue[addr] = color2.hue;
        leds_sat[addr] = color2.sat;
      } else if (mode==3){
        if (random(2)){
          leds_hue[addr] = color1.hue; 
          leds_sat[addr] = color1.sat;
        } else {
          leds_hue[addr] = color2.hue;
          leds_sat[addr] = color2.sat;
        }
      } else if (mode==4){
        leds_hue[addr] = color1.hue;
        leds_sat[addr] = 255;
      } else if (mode==5){
        leds_hue[addr] = color2.hue;
        leds_sat[addr] = 255;
      } else if (mode==6){
        if (random(2)){
          leds_hue[addr] = color1.hue; 
          leds_sat[addr] = 255;
        } else {
          leds_hue[addr] = color2.hue;
          leds_sat[addr] = 255;
        }
      }
      //dots[addr] = 85;
      dots_age[addr] = 6;
    }

    for (byte i=0;i<NUM_LEDS;i++){
      if (dots_age[i]>0){
        dots_age[i]-=1;
        leds[i] = HColor(leds_hue[i],leds_sat[i],dots_age[i]*25);
      }
    }

  
  FastLED.show();//display changes
  }
  
  }  
}
