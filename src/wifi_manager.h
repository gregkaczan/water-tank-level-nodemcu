#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

class WiFiManager {
public:
    WiFiManager(const char* ssid, const char* password);
    void connect();
    bool isConnected();
    String getLocalIP();
    void updateSignalStrength();
    int getRSSI();

private:
    const char* _ssid;
    const char* _password;
};

#endif 