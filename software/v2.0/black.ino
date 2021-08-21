byte black(){
  for (byte i=0;i<96;i++){
    //blank all leds
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
  while (true){
  if (digitalRead(Button1Pin)){
    //return to next mode
    return 3;
  }
  }
}
