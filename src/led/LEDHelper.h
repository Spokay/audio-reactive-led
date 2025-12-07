//
// Created by spokay on 12/7/25.
//

#ifndef AUDIO_REACTIVE_LED_LEDHELPER_H
#define AUDIO_REACTIVE_LED_LEDHELPER_H


#include <array>
#include "crgb.h"
#include "config/configuration.h"  // pour MATRIX_WIDTH


namespace led {
    class LEDHelper {
    public:
        static void updateLED(const std::array<double, MATRIX_WIDTH> &columnValues, CRGB *leds);

        static uint16_t resolveLEDIndex(uint8_t x, uint8_t y);
    };
} // led

#endif //AUDIO_REACTIVE_LED_LEDHELPER_H