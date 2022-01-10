#include "HX711.h"
#include "U8g2lib.h"

#define SCALE_CALIBRATION 451

#define LOADCELL_DOUT_PIN 12
#define LOADCELL_SCK_PIN 13


unsigned long timerStart = 0;
unsigned short touch_threshold;

HX711 scale;
U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);


void setup() {

  display.begin();
  display.enableUTF8Print();
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(SCALE_CALIBRATION);
  scale.tare();
  
}

void loop() {
    float weight = (scale.get_units(3));

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
    

    display.sendBuffer();
}
