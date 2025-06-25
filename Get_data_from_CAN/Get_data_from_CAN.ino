                                                                      

/// управляющие пины RGB
#define RED_RGB 3
#define GREEN_RGB 5
#define BLUE_RGB 6


// импортируем нащ файл с функциясм
#include "tools.h"





void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  pinMode(RED_RGB, OUTPUT);
  pinMode(GREEN_RGB, OUTPUT);
  pinMode(BLUE_RGB, OUTPUT);
  BlinkCountSulfur();
}


void loop() {

  GetDataCAN();

  if(!FilterBurnout && CountSulfur >= 15.0 && CountSulfur < 15.5 ){
    BlinkLedRGB(5000, green);
  }
  else if(!FilterBurnout && CountSulfur >= 15.5 && CountSulfur < 15.75){
    BlinkLedRGB(2500, green);
  }
  else if(!FilterBurnout && CountSulfur >= 15.75 && CountSulfur < 16.0 ){
    BlinkLedRGB(1000, orange);
  }
  else if(!FilterBurnout && CountSulfur >= 16.00 ){
    BlinkLedRGB(500, red);
  }
  else if(FilterBurnout ){
    SetColor(red);
    BlinkLedRGB(500, red);
  }
  else{
    SetColor(off_led);
  }
    

}
