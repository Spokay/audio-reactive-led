//
// Created by spokay on 12/7/25.
//


#include "LEDHelper.h"

#include <Arduino.h>
#include <array>

#include "crgb.h"
#include "config/configuration.h"

namespace led {

    void LEDHelper::updateLED(const std::array<double, MATRIX_WIDTH> &columnValues, CRGB *leds) {
        for (int x = 0; x < columnValues.size(); x++) {
            int numLEDsToLight = map(columnValues[x],MIN_MAGNITUDE, MAX_MAGNITUDE,0, MATRIX_HEIGHT);
            /* For the sake of security : limited between 0 et MATRIX_HEIGHT */
            numLEDsToLight = constrain(numLEDsToLight, 0, MATRIX_HEIGHT);

            for (int y = 0; y < numLEDsToLight; ++y) {
                const uint8_t hue = map(y, 0, MATRIX_HEIGHT - 1, 0, 160);
                leds[resolveLEDIndex(x, y)] = CHSV(hue, 255, 255);
            }
        }

    }

    // Convert (x,y) to LED index (zigzag pattern)
    uint16_t LEDHelper::resolveLEDIndex(const uint8_t x, const uint8_t y) {
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