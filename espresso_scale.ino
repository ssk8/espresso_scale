#include "HX711.h"
#include "U8g2lib.h"
#include "Adafruit_FreeTouch.h"
#include <Adafruit_DotStar.h>

Adafruit_DotStar dot = Adafruit_DotStar(1, 7, 8, DOTSTAR_BRG);

#define SCALE_CALIBRATION 445

#define LOADCELL_DOUT_PIN 3
#define LOADCELL_SCK_PIN 4
#define TOUCH_PIN 1


unsigned long timerStart = 0;
unsigned short touch_threshold;

HX711 scale;
U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

Adafruit_FreeTouch freetouch = Adafruit_FreeTouch(TOUCH_PIN, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

void setup() {
  dot.begin();
  dot.clear();
  dot.show();
  
  display.begin();
  display.enableUTF8Print();
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(SCALE_CALIBRATION);
  scale.tare();
  
  freetouch.begin();
  touch_threshold = freetouch.measure() + 100;
}

void loop() {
    int touch = freetouch.measure();
    float weight = (scale.get_units(3));
    if (touch>touch_threshold) {
      scale.tare();
      timerStart = millis();
    }

    unsigned short timer = (millis() - timerStart)/1000;

    display.setFont(u8g2_font_helvB24_tf); 
    display.setFontDirection(0);
    display.clearBuffer();

    if (timer<60){
      display.setCursor(12, 24);
      if (timer<10) display.print('0');
      display.print(timer);
      display.print(" sec");
    }
    else{
      display.setCursor(24, 24);
      if (timer<600) display.print('0');
      display.print(timer/60);
      display.print(":");
      if (timer%60<10) display.print('0');
      display.print(timer%60);
    }
    display.setCursor(20, 55);
    display.print(weight, 1);
    display.print(" g");
    
//    display.setFont(u8g2_font_helvB08_tf); 
//    display.setCursor(0, 35);
//    display.print(touch);
//    display.setCursor(0, 55);
//    display.print(touch_threshold);
    display.sendBuffer();
}
