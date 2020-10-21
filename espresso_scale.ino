#include "HX711.h"
#include "U8g2lib.h"
#include "Adafruit_FreeTouch.h"

#define SCALE_CALIBRATION 445
#define TOUCH_CALIBRATION 500


#define LOADCELL_DOUT_PIN 2
#define LOADCELL_SCK_PIN 3
#define TOUCH_PIN A0

unsigned long timerStart = 0;

HX711 scale;
U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

Adafruit_FreeTouch freetouch = Adafruit_FreeTouch(TOUCH_PIN, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);

void setup() {
  display.begin();
  display.enableUTF8Print();
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(SCALE_CALIBRATION);
  scale.tare();
  freetouch.begin();
}

void loop() {
    int touch = freetouch.measure();
    if (touch>TOUCH_CALIBRATION) {
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
    display.print(scale.get_units(2), 1);
    display.print(" g");
    display.setFont(u8g2_font_helvB08_tf); 
    display.setCursor(0, 35);
    display.print(touch);
    display.sendBuffer();
}
