#include "logger.h"

void Logger::setup(unsigned long baudRate) {
    Serial.begin(baudRate);
    while (!Serial) {
        ; // Wait for serial port to connect
    }
    printSeparator();
    Serial.println(F("System initialized"));
    printSeparator();
}

void Logger::printTimestamp() {
    Serial.print(F("["));
    Serial.print(millis());
    Serial.print(F("ms] "));
}

void Logger::printSeparator() {
    Serial.println(F("----------------------------------------"));
}

void Logger::logWiFiStatus(const char* status, const char* ip) {
    printTimestamp();
    Serial.print(F("WiFi: "));
    Serial.print(status);
    if (ip != nullptr) {
        Serial.print(F(" (IP: "));
        Serial.print(ip);
        Serial.print(F(")"));
    }
    Serial.println();
}

void Logger::logMQTTStatus(const char* status) {
    printTimestamp();
    Serial.print(F("MQTT: "));
    Serial.println(status);
}

void Logger::logWaterLevel(int percentage) {
    printTimestamp();
    Serial.print(F("Water Level: "));
    Serial.print(percentage);
    Serial.println(F("%"));
}

void Logger::logError(const char* message) {
    printTimestamp();
    Serial.print(F("ERROR: "));
    Serial.println(message);
} 