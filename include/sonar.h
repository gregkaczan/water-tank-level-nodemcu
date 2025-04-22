#ifndef SONAR_H
#define SONAR_H

#include <Arduino.h>

class Sonar {
public:
    Sonar(int trigPin, int echoPin, int tankHeight);
    int getWaterLevelPercentage();
    float measureDistance();

private:
    int _trigPin;
    int _echoPin;
    int _tankHeight;
};

#endif // SONAR_H 