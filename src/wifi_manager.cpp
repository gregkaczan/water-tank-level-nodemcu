#include "wifi_manager.h"
#include "logger.h"
#include "neopixel_manager.h"

WiFiManager::WiFiManager(const char* ssid, const char* password) 
    : _ssid(ssid), _password(password) {
}

void WiFiManager::connect() {
    delay(10);
    Logger::logWiFiStatus("Connecting...");
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(50);                      
    }
    Logger::logWiFiStatus("Connected");
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);                      
    digitalWrite(LED_BUILTIN, HIGH);
    
    // Initial signal strength update
    updateSignalStrength();
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

String WiFiManager::getLocalIP() {
    return WiFi.localIP().toString();
}

void WiFiManager::updateSignalStrength() {
    if (isConnected()) {
        int rssi = WiFi.RSSI();
        NeoPixelManager::updateWiFiSignal(rssi);
        NeoPixelManager::blink();
    }
} 