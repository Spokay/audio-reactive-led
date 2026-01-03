//
// Created by spokay on 1/3/26.
//

#include "PerformanceMonitor.h"
#include <Arduino.h>

namespace state {
    void PerformanceMonitor::startFFTTimer() {
        fftStartTime = micros();
    }

    void PerformanceMonitor::stopFFTTimer() {
        lastFFTTime = micros() - fftStartTime;
    }

    unsigned long PerformanceMonitor::getLastFFTTime() const {
        return lastFFTTime;
    }

    void PerformanceMonitor::printFFTTime() const {
        Serial.printf("FFT processing time: %lu us\n", lastFFTTime);
    }
} // state