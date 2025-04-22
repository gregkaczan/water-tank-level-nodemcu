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

    // Send message every MQTT_WATER_LEVEL_INTERVAL
    static unsigned long lastWaterLevelMsg = 0;
    static unsigned long lastSignalCheck = 0;
    
    if (millis() - lastWaterLevelMsg > MQTT_WATER_LEVEL_INTERVAL) {
        lastWaterLevelMsg = millis();
        float distance = sonar.measureDistance();
        int smoothed = medianFilter.filter(distance);
        Logger::logWaterLevel(smoothed);
        char distanceStr[8];
        snprintf(distanceStr, sizeof(distanceStr), "%d", smoothed);
        mqttManager.publish(MQTT_WATER_LEVEL_TOPIC, distanceStr);
    }
    
    // Check WiFi signal strength every MQTT_SIGNAL_CHECK_INTERVAL
    if (millis() - lastSignalCheck > MQTT_SIGNAL_CHECK_INTERVAL) {
        lastSignalCheck = millis();
        wifiManager.updateSignalStrength();
        
        // Publish signal strength
        if (wifiManager.isConnected()) {
            int rssi = wifiManager.getRSSI();
            char rssiStr[8];
            snprintf(rssiStr, sizeof(rssiStr), "%d", rssi);
            mqttManager.publish(MQTT_SIGNAL_STRENGTH_TOPIC, rssiStr);
        }
    }
}
