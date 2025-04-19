#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

class MQTTManager {
public:
    MQTTManager(const char* server, int port = 1883);
    void setup();
    void reconnect();
    bool isConnected();
    void publish(const char* topic, const char* payload);
    void loop();

private:
    PubSubClient _client;
    const char* _server;
    int _port;
    WiFiClient _espClient;
};

#endif 