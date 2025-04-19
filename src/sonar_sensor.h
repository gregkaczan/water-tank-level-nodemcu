#ifndef SONAR_SENSOR_H
#define SONAR_SENSOR_H

#include <Arduino.h>

class SonarSensor {
public:
    SonarSensor(int trigPin, int echoPin, int tankHeight);
    void setup();
    int getWaterLevelPercentage();

private:
    int _trigPin;
    int _echoPin;
    int _tankHeight;
    float measureDistance();
};

#endif 