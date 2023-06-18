# espresso_scale
timer and scale for pulling the perfect espresso shot

equally useful for pourover coffee as well


<img src=https://github.com/ssk8/project_pics/blob/main/new_espresso_scale.jpg width="300"/> 

<img src=https://github.com/ssk8/project_pics/blob/main/esspresso_scale_action1.jpg width="300"/>

## Main components:
- 1 kg load cell
- HX711 amplifier
- SH1106 128X64 oled
- microcontroller

## Operation overview:
-count up seconds and give weight in g
-reset counter after initial 0.2g change in weight

### for arduino sketches, install:
- bogde's [HX711 library](https://github.com/bogde/HX711)
- olikraus's [U8G2 library](https://github.com/olikraus/u8g2)

Use the calibration program to find CALIBRATION with a serial terminal
Depending on the ADC, you may need to remove the number of times for average for the tare and measurments. Currently set to 20 but should be none for old (uncapped) ADC


## 2022 update:
I found that the capacitive touch for tareing and starting the timer didn't work smoothly and actually isn't needed at all


## Raspberry Pi Pico
The Arduino "sketches" lalbed "Pico" work on that microcontroller
- install [Earle Philhower's 2040 core](https://github.com/earlephilhower/arduino-pico)
- HX711 on physical pins 17 and 16 (GP13 and GP12)
- SH1106 on physical pins 7 and 6 (GP5 and GP4)
