#include "median_filter.h"
#include <string.h>

MedianFilter::MedianFilter(int windowSize) : _windowSize(windowSize) {
    _readings = new float[windowSize];
    // Initialize all readings to 0
    for (int i = 0; i < windowSize; i++) {
        _readings[i] = 0;
    }
}

MedianFilter::~MedianFilter() {
    delete[] _readings;
}

void MedianFilter::shiftValues(float newValue) {
    // Shift old values
    for (int i = _windowSize - 1; i > 0; i--) {
        _readings[i] = _readings[i - 1];
    }
    _readings[0] = newValue;
}

float MedianFilter::getMedian() {
    // Copy & sort
    float* sorted = new float[_windowSize];
    memcpy(sorted, _readings, sizeof(float) * _windowSize);
    
    for (int i = 0; i < _windowSize - 1; i++) {
        for (int j = i + 1; j < _windowSize; j++) {
            if (sorted[j] < sorted[i]) {
                float temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    
    float median = sorted[_windowSize / 2];
    delete[] sorted;
    return median;
}

int MedianFilter::filter(float newValue) {
    shiftValues(newValue);
    return round(getMedian());
} 