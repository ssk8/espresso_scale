#include "HX711.h"

const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 4;

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

  if (scale.is_ready()) {
    Serial.println("set scale");
    scale.set_scale();
    delay(1000);
    Serial.println("tare");
    scale.tare();
    delay(1000);
    Serial.println("place reference mass now");
    delay(5000);
    Serial.println("reading now");
    long reading = scale.get_units(10);
    //long reading = scale.read();
    Serial.print(">>>>>>>>>>>>>>>  ");
    Serial.println(reading);
    Serial.println("Divide by reference mass");
    Serial.println("pass that to set_scale()");
    Serial.println("\n\n\n");
    
  } else {
    Serial.println("HX711 not found.");
  }

  delay(5000);
  
}
