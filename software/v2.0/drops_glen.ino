byte drops_glen(){
  del = 160;//starting delay of 160 works well
  mode = 0;
  previousMillis = millis();
  
  while (true){
  if (not rainbow_check()){
    return 3;
  }

  currentMillis = millis();
  bool gl = false;
  if (currentMillis - previousMillis>del){

    previousMillis = currentMillis;

    calc_next_drops();
    gl = not gl;

    if (gl){
      //only add new drops every other clock cycle
      for (byte i = 0; i<1; i++){//the "1" here is how many drops to add
        bool success;
        bool leave = true;
        byte addr;
        while (leave){
          success = true;
          addr = random(16);
          for (byte i=0;i<8;i++){
            //iterate over the heigh of the column to see if there are any drops
            if (drops[addr][i]){
              success = false;
            }
          }
          if (success){
            //success is only true if it is never set to false
            leave = false;
            drops[(addr+16)%16][7] = true;
            break;
          }
        }
      }
    }

    mat2arr(leds_hue,leds_hue_mat);

    for (byte i=0;i<NUM_LEDS;i++){
      if (mode%2==0){
        leds[i] = DColor(leds_hue[i],color1.hue);
      }
      if (mode%2==1){
        leds[i] = DColor(leds_hue[i],color2.hue);
      }
    }
    FastLED.show();
  }
  }
}



void calc_next_drops(){

    for (byte i=0;i<8;i++){
    for (byte j=0;j<16;j++){
      leds_hue_mat[j][i] = 0; 
    }
    }
  
    for (byte i=0;i<8;i++){//move all drops down one
    for (byte j=0;j<16;j++){
      if (drops[j][i]){
        drops[j][i] = false;
        //the drop no longer is where it was
        if (i>0){
          drops[j][i-1] = true;
          //it is instead one lower, unless it is off the bottom
        }
      }
    }
    }


    for (byte i=0;i<8;i++){
    for (byte j=0;j<16;j++){
      if (drops[j][i]){
        for (byte k=0;k<3;k++){
          if (i+k<7){
            leds_hue_mat[j][i+k] = k+1;
          }
        }
      }
    }
  }


    
}
