//
// Created by spokay on 12/7/25.
//

#ifndef AUDIO_REACTIVE_LED_LEDHELPER_H
#define AUDIO_REACTIVE_LED_LEDHELPER_H


#include <array>
#include <complex>

#include "crgb.h"
#include "config/configuration.h"  // pour MATRIX_WIDTH


namespace led {
    class LEDHelper {
    public:
        static void updateLED(const std::array<double, MATRIX_WIDTH> &columnValues, CRGB *leds);

        static std::array<double, MATRIX_WIDTH> mapFrequenciesToColumnsMagnitudes(const std::array<std::complex<double>, MIC_BUFFER_SIZE> &outputBuffer);

        static uint16_t resolveLeftRightLEDIndex(uint8_t x, uint8_t y);
        static uint16_t resolveZigzagLEDIndex(uint8_t x, uint8_t y);
    };
} // led

#endif //AUDIO_REACTIVE_LED_LEDHELPER_H