//
// Created by spokay on 1/3/26.
//

#include "SignalProcessor.h"
#include <Arduino.h>
#include <cmath>

namespace audio {
    double SignalProcessor::dcOffset = 2048.0;
    bool SignalProcessor::dcOffsetCalculated = false;

    void SignalProcessor::calibrateDCOffset() {
        Serial.println("Calibrating DC offset");
        double sum = 0.0;
        for (int i = 0; i < DC_OFFSET_SAMPLES; i++) {
            sum += analogRead(MIC_PIN);
            delay(1);
        }
        dcOffset = sum / DC_OFFSET_SAMPLES;
        dcOffsetCalculated = true;
        Serial.printf("DC offset calculated: %.2f\n", dcOffset);
    }

    double SignalProcessor::getDCOffset() {
        if (!dcOffsetCalculated) {
            calibrateDCOffset();
        }
        return dcOffset;
    }

    bool SignalProcessor::isDCOffsetCalculated() {
        return dcOffsetCalculated;
    }

    void SignalProcessor::applyHammingWindow(
        std::array<std::complex<double>, MIC_BUFFER_SIZE> &buffer
    ) {
        for (int i = 0; i < MIC_BUFFER_SIZE; i++) {
            const double window = 0.54 - 0.46 * cos(2.0 * M_PI * i / (MIC_BUFFER_SIZE - 1));
            buffer[i] *= window;
        }
    }

    void SignalProcessor::removeDCComponent(
        std::array<std::complex<double>, MIC_BUFFER_SIZE> &fftOutput
    ) {
        // Delete DC and low frequency
        fftOutput[0] = {0.0, 0.0};  // DC component
        fftOutput[1] = {0.0, 0.0};  // Very low frequency
    }
} // audio