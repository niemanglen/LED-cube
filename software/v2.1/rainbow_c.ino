byte rainbow_c(){
  del = 100;//starting delay of 100 works well
  previousMillis = millis();
  byte k = 0;//initialize a loop variable


  while (true){

  if (not rainbow_check()){
    return 3;
  }

  currentMillis = millis();

  if (currentMillis - previousMillis>del){
  //determine if the delay criterion has been met
  //if so, update the display
  if (k>63){
    //iterate the loop variable manually
    k = 0;
  } else {
    k += 1;
  }
  
  previousMillis = currentMillis;//reset the loop condition variable

  for (byte i=0;i<96;i++){
    leds[i] = HColor(k*4);
  }
  for (byte i=0;i<6;i++){
    leds[5+16*i] = HColor((k+8)%64*4);
    leds[6+16*i] = HColor((k+8)%64*4);
    leds[9+16*i] = HColor((k+8)%64*4);
    leds[10+16*i] = HColor((k+8)%64*4);
  }
 

  FastLED.show();
  }
  
  }  
}
