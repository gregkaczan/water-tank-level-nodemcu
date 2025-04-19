#include <Arduino.h>
#include "wifi_manager.h"
#include "mqtt_manager.h"
#include "led_control.h"
#include "median_filter.h"
#include "sonar.h"
#include "logger.h"
#include "config.h"
#include "neopixel_manager.h"

WiFiManager wifiManager(WIFI_SSID, WIFI_PASSWORD);
MQTTManager mqttManager(MQTT_SERVER, MQTT_PORT);
MedianFilter medianFilter(5);  // window size of 5

const int trigPin = 12;
const int echoPin = 13;
const int tankHeight = 320;

Sonar sonar(trigPin, echoPin, tankHeight);

void setup() {
    Logger::setup();
    
    LEDControl::setup();
    NeoPixelManager::setup(14);  // Initialize NeoPixel on pin 14
    wifiManager.connect();
    Logger::logWiFiStatus("Connected", wifiManager.getLocalIP().c_str());
    mqttManager.setup();
}

void loop() {
    if (!mqttManager.isConnected()) {
        mqttManager.reconnect();
    }
    mqttManager.loop();

    // Send message every 5 seconds
    static unsigned long lastMsg = 0;
    static unsigned long lastSignalCheck = 0;
    
    if (millis() - lastMsg > 5000) {
        lastMsg = millis();
        int percentage = sonar.getWaterLevelPercentage();
        int smoothedPercentage = medianFilter.filter(percentage);
        Logger::logWaterLevel(smoothedPercentage);
        char percentageStr[8];
        snprintf(percentageStr, sizeof(percentageStr), "%d", smoothedPercentage);
        mqttManager.publish("my/topic", percentageStr);
    }
    
    // Check WiFi signal strength every 10 seconds
    if (millis() - lastSignalCheck > 2000) {
        lastSignalCheck = millis();
        wifiManager.updateSignalStrength();
    }
}
