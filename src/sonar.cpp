#include "sonar.h"

Sonar::Sonar(int trigPin, int echoPin, int tankHeight) 
    : _trigPin(trigPin), _echoPin(echoPin), _tankHeight(tankHeight) {
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}

float Sonar::measureDistance() {
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    float duration = pulseIn(_echoPin, HIGH);
    return (duration * 0.0343) / 2;
}

int Sonar::getWaterLevelPercentage() {
    float distance = measureDistance();
    int diff = _tankHeight - distance;
    return (int)((float)diff / (float)_tankHeight * 100);
} 