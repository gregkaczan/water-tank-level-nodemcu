#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>

class LEDControl {
public:
    static void setup();
    static void blink(int duration);
    static void turnOn();
    static void turnOff();
};

#endif 