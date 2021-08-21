byte rainbow_osc(){
  del = 40;//starting delay of 20 works well
  previousMillis = millis();
  mode = 0;//start at the base mode
  byte k = 0;//initialize a loop variable

  bool forward = true;

 while (true){

  if (not rainbow_check()){
    return 3;
  }

  currentMillis = millis();

  if (currentMillis - previousMillis>del){
  //determine if the delay criterion has been met
  //if so, update the display
  //if (k>8){
  //  //iterate the loop variable manually
  //  k = 0;
  //} else {
  //  k += 1;
  //}
  
  if (k==16){
    forward = false;
  }
  if (k==0){
    forward = true;
  }

  if (forward) {
    k++;
  } else {
    k--;
  }
  
  previousMillis = currentMillis;//reset the loop condition variable

  CHSV hcolor;
  CRGB rcolor;
  
  for (byte i=0;i<8;i++){
    for (byte j = 0;j<16;j++){
      if (mode==0){
        leds_hue_mat[j][i] = (j*15+k*4)%256;
      }
      if (mode==1){
        if (j>7){
          hcolor = blend(color1,color2,255-(j*31+k*4)%256);
        } else {
          hcolor = blend(color1,color2,(j*31+k*4)%256);
        }
        leds_hue_mat[j][i] = hcolor.hue;
        leds_sat_mat[j][i] = hcolor.sat;
        }
      if (mode>1){
        rcolor = ColorFromPalette(currentPalette,(j*15+k*4)%256,brightness,currentBlending);
        leds_hue_mat[j][i] = rgb2hsv_approximate(rcolor).hue;
        leds_sat_mat[j][i] = rgb2hsv_approximate(rcolor).sat;
        //CRGB color = ColorFromPalette(currentPalette,(k*4)%256,brightness,currentBlending);
      }
    }
  }
  if (mode==0){
    mat2arr(leds_hue,leds_hue_mat);
  }
  if (mode==1){
    mat2arr(leds_hue,leds_hue_mat);
    mat2arr(leds_sat,leds_sat_mat);
  }
  if (mode>1){
    mat2arr(leds_hue,leds_hue_mat);
    mat2arr(leds_sat,leds_sat_mat);
  }

  for (byte i = 0; i<NUM_LEDS;i++){
    if (mode==0){
      leds[i] = HColor(leds_hue[i]);
    }
    else {
      leds[i] = HColor(leds_hue[i],leds_sat[i]);
    }
  }

  FastLED.show();
  }
  
  }  
}
