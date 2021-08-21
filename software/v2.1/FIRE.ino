byte FIRE() {
  del = 60;//starting delay of 20 works well
  previousMillis = millis();
  mode = 0;//start at the base mode
  byte k = 0;

    for (byte i=0;i<8;i++){
      for (byte j = 0;j<16;j++){
        //need to reset the heats so they don't roll over
        leds_hue_mat[j][i] = 0;
      }
    }


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

  calc_next_heats();

    for (byte i = 0; i<2; i++){
    byte addr = random(16);
    leds_hue_mat[(addr+15)%15][1] = (random(175)+50);
    leds_hue_mat[(addr+15+1)%15][1] = leds_hue_mat[(addr+15+1)%15][1] - 25 + random(50);
    leds_hue_mat[(addr+15-1)%15][1] = leds_hue_mat[(addr+15+1)%15][1] - 25 + random(50);
  }

  mat2arr(leds_hue,leds_hue_mat);

  for (byte i = 0; i<NUM_LEDS;i++){
    if (mode==0){
      leds[i] = HeaColor(leds_hue[i]);
    } else if (mode==1){
       leds[i] = CHSV(color1.hue,255-leds_hue[i],leds_hue[i]);
    } else if (mode==2){
      leds[i] = CHSV(color2.hue,255-leds_hue[i],leds_hue[i]);
    } else if (mode==3){
      leds[i] = CHSV(k,255-leds_hue[i],leds_hue[i]);
      //potentially make this k*n%256
      //n could be linked to the delay so that the color change speed can be controlled
    } else if (mode>3) {
      leds[i] = ColorFromPalette(currentPalette,leds_hue[i],leds_hue[i],currentBlending);
    }
  }

  FastLED.show();//display changes
  }
  
  }  
}






void calc_next_heats() {
    for (byte i=2;i<8;i++){
    for (byte j=0;j<16;j++){
      leds_hue_mat[j][i] = (
        
      leds_sat_mat[j][i]
      +0*leds_sat_mat[(j-1+15)%15][i]
      +0*leds_sat_mat[(j+1+15)%15][i]
      
      +leds_sat_mat[(j-1+15)%15][i-1]
      +leds_sat_mat[(j+1+15)%15][i-1]

      +2*leds_sat_mat[j][i-1]
      +leds_sat_mat[j][i-2]
      )/(6);
    }
  }

  for (byte i=0;i<16;i++){
    leds_hue_mat[i][0] = (
    leds_sat_mat[i][1]
    +leds_sat_mat[(i-1+15)%15][1]
    +leds_sat_mat[(i+1+15)%15][1]
    +255
    +255
    )/5;
  }

  for (byte i=0;i<16;i++){
    for (byte j=0;j<8;j++){

      leds_hue_mat[i][j] = max(0L,leds_hue_mat[i][j]-20);

      leds_sat_mat[i][j] = leds_hue_mat[i][j];
        
      //leds_sat_mat[i][j] = leds_hue_mat[i][j];
    }
  }


  
}
