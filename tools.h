
// Состояние прожига
bool FilterBurnout = false;
float CountSulfur = 0.0;

// 100 мс длительность вспышки светодиода
const int flashDuration = 100;   

//массивы цветов
int red[3] = {150, 0, 0};
int yellow[3] = {160, 50, 0};
int orange[3] = {150, 20, 0};
int green[3] = {0, 200, 0};
int blue[3] = {0, 0, 128};
int white[3] = {255, 255, 255};
int off_led[3] = {0, 0, 0};



// Коэффициент яркости (0.0 - 1.0)
float brightness = 0.5; 
//начальное время
unsigned long previousLedMillis = 0;
// флаг горения светодиода
bool isFlashing = false;




void SetColor(int color[3]){
  // Получает на вход массив из 3 чисел и включает цвет

  analogWrite(RED_RGB, color[0] * brightness);
  analogWrite(GREEN_RGB, color[1] * brightness);
  analogWrite(BLUE_RGB, color[2] * brightness);

}


void BlinkLedRGB(int flashInterval, int color[3]){
  // Функция на вход получет переод моргания в мс и цвет

  unsigned long currentMillis = millis();

  if (!isFlashing && currentMillis - previousLedMillis >= flashInterval){
          SetColor(color);
          previousLedMillis = currentMillis;
          isFlashing = !isFlashing;
  }

  if (isFlashing && currentMillis - previousLedMillis >= flashDuration){
          SetColor(off_led);
          isFlashing = !isFlashing;
  }

}

void GetDataCAN(){

  // на данный момент читает Serial port
  if(Serial.available()){
    String cu = Serial.readStringUntil(':');
    String fb = Serial.readStringUntil('\n');
    FilterBurnout = fb.toInt();
    CountSulfur = cu.toFloat();
    Serial.println(CountSulfur);
    Serial.println(FilterBurnout);
  }
 
}

void BlinkCountSulfur(){
  // Моргает при запуске поэтому использование Delay не критично.
  GetDataCAN();
  if (CountSulfur >= 10 ){
    SetColor(blue);
    delay(300);
    SetColor(off_led);
    CountSulfur=CountSulfur-10.0;
  }
  Serial.println(CountSulfur);
  for(int i=0; i < CountSulfur; i++ ){
      delay(400);
      SetColor(white);
      delay(400);
      SetColor(off_led);

  }


}