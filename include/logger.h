#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger {
public:
    static void setup(unsigned long baudRate = 9600);
    static void logWiFiStatus(const char* status, const char* ip = nullptr);
    static void logMQTTStatus(const char* status);
    static void logWaterLevel(int percentage);
    static void logError(const char* message);

private:
    static void printTimestamp();
    static void printSeparator();
};

#endif // LOGGER_H 