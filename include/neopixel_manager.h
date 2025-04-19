#ifndef NEOPIXEL_MANAGER_H
#define NEOPIXEL_MANAGER_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class NeoPixelManager {
public:
    static void setup(int pin = 14);
    static void updateWiFiSignal(int rssi);
    static void blink();

private:
    static Adafruit_NeoPixel* _pixel;
    static uint32_t getSignalColor(int rssi);
    static void setColor(uint32_t color);
};

#endif // NEOPIXEL_MANAGER_H 