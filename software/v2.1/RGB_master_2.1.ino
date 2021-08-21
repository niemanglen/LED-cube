#include <EEPROM.h>//library used for saving settings between power cycles

#include <FastLED.h>//library used for all of the led communication

#define NUM_LEDS 96//=16*6
#define DATA_PIN 16//do not change

CRGB leds[NUM_LEDS];//final array of RGB values used to populate led colors

byte leds_hue[NUM_LEDS];//array of led hue values used to calculate led rgb values
byte leds_sat[NUM_LEDS];//array of led saturation values used to calculate led rgb values

byte leds_hue_mat[16][8] = {0};//matrix that is cast to leds_hue
byte leds_sat_mat[16][8] = {0};//matrix that is cast to leds_sat

byte dots[NUM_LEDS] = {0};//used for the dots effect
byte dots_age[NUM_LEDS] = {0};

bool drops[16][8];//used for the drops effect


CHSV color1 = CHSV(0,255,255);//used defined color1
CHSV color2 = CHSV(120,255,255);//used defined color2
//these are poplulated with saved values in the setup function

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
//these are used for the continuous loops so that button presses are still picked up without delaying the LED displays

unsigned long del;//set the delay between loops of the continuous functions described above


byte dot_drop_num;
byte brightness = 255;
byte hue = 0;
//more settings used for rgb effects


const byte Button1Pin = 5;//RGB effect button, bottom right
const byte Button2Pin = 6;//Submode effect button, bottom left

const byte Button3Pin = 17;//Mode effect button1, top left
const byte Button4Pin = 18;//Mode effect button2, top right

byte mode;//variable used to track Submode effect


byte pattern = 2;
byte change = 0;
//vars used for controlling which effect is being displayed


CRGBPalette16 currentPalette;
const TBlendType    currentBlending = LINEARBLEND;
//these variables are required for implementing the ColorPallete function from FastLED

byte index = 0;//variable used for selecting currentPalette



void setup() {
  // put your setup code here, to run once:

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);//initialize the FastLED library

  //setup button pins as inputs
  pinMode(Button1Pin,INPUT);
  pinMode(Button2Pin,INPUT);
  pinMode(Button3Pin,INPUT);
  pinMode(Button4Pin,INPUT);



  //read the user settings from local EEPROM
  dot_drop_num = EEPROM.read(14);
  if (dot_drop_num>56){
    dot_drop_num = 56;
  }
  brightness = EEPROM.read(15);

  color1.hue = EEPROM.read(16);
  color1.sat = EEPROM.read(17);

  color2.hue = EEPROM.read(18);
  color2.sat = EEPROM.read(19);

  

  

}

void loop() {
    // put your main code here, to run repeatedly:
  
  pattern = (pattern+change+9)%9;//increment pattern(RGB effect), max val is 8

  //index = 0;
  index = 5;//initialize index for use in determining 

  //changePalette(index);

  for (byte i=0;i<NUM_LEDS;i++){
    //make sure there aren't any weird display issues when switching to the next effect
    leds[i] = CRGB::Black;
  }

  delay(300);//button debounce timer
  if (pattern==0){
    change = black() - 2;
  } else if (pattern==1){
    change = user_set() - 2;
  } else if (pattern==2){
    change = rainbow() - 2;
  } else if (pattern==3){
    change = rainbow_h() - 2;
  } else if (pattern==4){
    change = rainbow_osc() - 2;
  } else if (pattern==5){
    change = FIRE() - 2;
  //} else if (pattern==6) {
    //change = two_color() - 2;
  } else if (pattern==7) {
    change = dots_glen() - 2;
  } else if (pattern==8) {
    change = drops_glen() - 2;
  }

}




void changePalette(byte index) {
  if (index==1){  currentPalette = RainbowColors_p;}
  else if (index==2){ currentPalette = RainbowStripeColors_p;}
  else if (index==3){ currentPalette = PartyColors_p;}
  else if (index==4){ currentPalette = CloudColors_p;}
  else if (index==5){ currentPalette = ForestColors_p;}
  else if (index==6){currentPalette = OceanColors_p;}
  else if (index==7){currentPalette = LavaColors_p;}
}
