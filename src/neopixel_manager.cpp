#include "neopixel_manager.h"
#include "logger.h"

Adafruit_NeoPixel* NeoPixelManager::_pixel = nullptr;

void NeoPixelManager::setup(int pin) {
    _pixel = new Adafruit_NeoPixel(1, pin, NEO_GRB + NEO_KHZ800);
    _pixel->begin();
    _pixel->setBrightness(30);  // Set to 30% brightness
    _pixel->show();  // Initialize all pixels to 'off'
}

uint32_t NeoPixelManager::getSignalColor(int rssi) {
    // WiFi signal strength ranges from -100 (weakest) to 0 (strongest)
    // Map to colors based on signal strength:
    // > -50: Green (excellent signal)
    // -51 to -60: Yellow (good signal)
    // -61 to -70: Orange (fair signal)
    // -71 to -85: Red (poor signal)
    // < -86: Dark red (very poor signal)
    
    if (rssi <= -86) {
        return _pixel->Color(128, 0, 0);  // Dark red
    } else if (rssi <= -71) {
        return _pixel->Color(255, 0, 0);  // Red
    } else if (rssi <= -61) {
        return _pixel->Color(255, 128, 0);  // Orange
    } else if (rssi <= -51) {
        return _pixel->Color(255, 255, 0);  // Yellow
    } else {
        return _pixel->Color(0, 255, 0);  // Green
    }
}

void NeoPixelManager::setColor(uint32_t color) {
    if (_pixel != nullptr) {
        _pixel->setPixelColor(0, color);
        _pixel->show();
    }
}

void NeoPixelManager::updateWiFiSignal(int rssi) {
    uint32_t color = getSignalColor(rssi);
    setColor(color);
    
    // Log the signal strength
    char signalMsg[32];
    snprintf(signalMsg, sizeof(signalMsg), "WiFi Signal: %d dBm", rssi);
    Logger::logWiFiStatus(signalMsg);
}

void NeoPixelManager::blink() {
    if (_pixel != nullptr) {
        // Store current color
        uint32_t currentColor = _pixel->getPixelColor(0);
        
        // Turn off
        _pixel->clear();
        _pixel->show();
        
        // Use longer delay for very weak signals (dark red)
        if (currentColor == _pixel->Color(128, 0, 0)) {
            delay(200);  // Longer blink for very weak signal
        } else {
            delay(50);   // Normal blink for other signal strengths
        }
        
        // Restore color
        setColor(currentColor);
    }
} 