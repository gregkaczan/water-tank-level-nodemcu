#include "mqtt_manager.h"
#include <logger.h>

MQTTManager::MQTTManager(const char* server, int port) 
    : _client(_espClient), _server(server), _port(port) {
}

void MQTTManager::setup() {
    _client.setServer(_server, _port);
}

void MQTTManager::reconnect() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2000);
    
    Logger::logMQTTStatus("Connecting...");
    while (!_client.connected()) {
        if (_client.connect("ArduinoClient")) {
            Logger::logMQTTStatus("Connected");
            digitalWrite(LED_BUILTIN, LOW);
            delay(500);                      
            digitalWrite(LED_BUILTIN, HIGH);
        } else {
            char errorMsg[32];
            snprintf(errorMsg, sizeof(errorMsg), "Connection failed, rc=%d", _client.state());
            Logger::logError(errorMsg);
            delay(5000);
        }
    }
}

bool MQTTManager::isConnected() {
    return _client.connected();
}

void MQTTManager::publish(const char* topic, const char* payload) {
    _client.publish(topic, payload);
}

void MQTTManager::loop() {
    _client.loop();
} 