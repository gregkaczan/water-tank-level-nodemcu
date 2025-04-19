#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include <Arduino.h>

class MedianFilter {
public:
    MedianFilter(int windowSize);
    ~MedianFilter();
    int filter(float newValue);

private:
    int _windowSize;
    float* _readings;
    void shiftValues(float newValue);
    float getMedian();
};

#endif 