#include "led_control.h"

void LEDControl::setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);  // LED is off when HIGH on ESP8266
}

void LEDControl::blink(int duration) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(duration);
    digitalWrite(LED_BUILTIN, HIGH);
}

void LEDControl::turnOn() {
    digitalWrite(LED_BUILTIN, LOW);  // LED is on when LOW on ESP8266
}

void LEDControl::turnOff() {
    digitalWrite(LED_BUILTIN, HIGH);  // LED is off when HIGH on ESP8266
} 