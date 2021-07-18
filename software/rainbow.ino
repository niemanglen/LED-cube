byte rainbow() {
  del = 20;//starting delay of 20 works well
  previousMillis = millis();
  mode = 0;//start at the base mode
  byte k = 0;//initialize a loop variable

  while (true){

  if (not rainbow_check()){
    return 3;
  }

  currentMillis = millis();
  
  if (currentMillis - previousMillis>del){
  //determine if the delay criterion has been met
  //if so, update the display
  if (k>255){
    //iterate the loop variable manually
    k = 0;
  } else {
    k += 1;
  }
  
  previousMillis = currentMillis;//reset the loop condition variable

  for (byte i=0;i<NUM_LEDS;i++){
    if (mode==0){
      leds[i] = CHSV(k,255,brightness);//mode 0 is for hue based rainbow
    }
    if (mode==1){
      //mode 1 is for blend
      if (k<128){
          leds[i] = HColor(blend(color1,color2,255-2*k).hue);
        } else {
          leds[i] = HColor(blend(color1,color2,2*k).hue);//not sure how this works as 2*(255) is larger than a byte
        }
    }
    if (mode>1){
      leds[i] = ColorFromPalette(currentPalette,k,brightness,currentBlending);
    }
  }
  FastLED.show();//display changes
  }
  
  }  
}
