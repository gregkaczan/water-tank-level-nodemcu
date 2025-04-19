#include "wifi_manager.h"

WiFiManager::WiFiManager(const char* ssid, const char* password) 
    : _ssid(ssid), _password(password) {
}

void WiFiManager::connect() {
    delay(10);
    Serial.println("Connecting to WiFi...");
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(50);                      
        Serial.print(".");
    }
    Serial.println("WiFi connected");
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);                      
    digitalWrite(LED_BUILTIN, HIGH);
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

String WiFiManager::getLocalIP() {
    return WiFi.localIP().toString();
} 