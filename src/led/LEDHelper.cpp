//
// Created by spokay on 12/7/25.
//


#include "LEDHelper.h"
#include "MagnitudeFilter.h"
#include <Arduino.h>
#include <array>
#include <complex>
#include <algorithm>

namespace led {
    void LEDHelper::updateLED(
        const std::array<double, MATRIX_WIDTH> &columnValues,
        CRGB *leds
    ) {
        for (int x = 0; x < MATRIX_WIDTH; x++) {
            int numLEDsToLight = static_cast<int>(
                map(
                    static_cast<long>(columnValues[x]),
                    MIN_MAGNITUDE,
                    MAX_MAGNITUDE,
                    0,
                    MATRIX_HEIGHT
                )
            );
            numLEDsToLight = constrain(numLEDsToLight, 0, MATRIX_HEIGHT);

            for (int y = 0; y < MATRIX_HEIGHT; y++) {
                const int ledIndex = resolveLeftRightLEDIndex(x, y);

                if (y >= (MATRIX_HEIGHT - numLEDsToLight)) {
                    const uint8_t hue = map(y, 0, MATRIX_HEIGHT - 1, 0, 160);
                    leds[ledIndex] = CHSV(hue, 255, 255);
                } else {
                    leds[ledIndex] = CRGB::Black;
                }
            }
        }
    }

    std::array<double, MATRIX_WIDTH> LEDHelper::mapFrequenciesToColumnsMagnitudes(
        const std::array<std::complex<double>, MIC_BUFFER_SIZE> &outputBuffer
    ) {
        std::array<double, MATRIX_WIDTH> columnsValues{};
        constexpr int usableBins = MIC_BUFFER_SIZE / 2;

        // Dynamic threshold
        const double noiseFloor = MagnitudeFilter::calculateNoiseFloor(outputBuffer);
        const double threshold = MagnitudeFilter::calculateDynamicThreshold(noiseFloor);

        for (int col = 0; col < MATRIX_WIDTH; ++col) {
            const float colRatio = static_cast<float>(col) / MATRIX_WIDTH;
            const float nextColRatio = static_cast<float>(col + 1) / MATRIX_WIDTH;

            // Ignore DC and very low-frequency bins
            const int startIdx = std::max(
                MIN_FREQ_BIN,
                static_cast<int>(colRatio * colRatio * usableBins)
            );
            int endIdx = static_cast<int>(nextColRatio * nextColRatio * usableBins);

            if (endIdx <= startIdx) endIdx = startIdx + 1;
            if (endIdx > usableBins) endIdx = usableBins;

            double sum = 0.0;
            int count = 0;
            for (int i = startIdx; i < endIdx; ++i) {
                const double magnitude = std::abs(outputBuffer[i]);

                if (MagnitudeFilter::isAboveThreshold(magnitude, threshold)) {
                    sum += magnitude;
                    count++;
                }
            }

            columnsValues[col] = (count > 0) ? (sum / count) : 0.0;
        }

        return columnsValues;
    }

    uint16_t LEDHelper::resolveLeftRightLEDIndex(const uint8_t x, const uint8_t y) {
        return y * MATRIX_WIDTH + x;
    }

    uint16_t LEDHelper::resolveZigzagLEDIndex(const uint8_t x, const uint8_t y) {
        uint16_t index;

        if (y % 2 == 0) {
            // Even rows: left to right
            index = y * MATRIX_WIDTH + x;
        } else {
            // Odd rows: right to left (zigzag)
            index = y * MATRIX_WIDTH + (MATRIX_WIDTH - 1 - x);
        }

        return index;
    }

} // led