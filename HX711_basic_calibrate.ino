#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

  if (scale.is_ready()) {
    Serial.print("set scale");
    scale.set_scale();
    delay(1000);
    Serial.print("tare");
    scale.tare();
    delay(1000);
    Serial.print("place weight now");
    delay(5000);
    Serial.print("reading now");
    long reading = scale.get_units(10);
    delay(1000);
    
    //long reading = scale.read();
    Serial.print("HX711 reading: ");
    Serial.println(reading);




    
  } else {
    Serial.println("HX711 not found.");
  }

  delay(5000);
  
}
