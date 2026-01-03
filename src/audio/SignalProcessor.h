//
// Created by spokay on 1/3/26.
//

#ifndef AUDIO_REACTIVE_LED_SIGNALPROCESSOR_H
#define AUDIO_REACTIVE_LED_SIGNALPROCESSOR_H

#include <array>
#include <complex>
#include "config/configuration.h"

namespace audio {
    class SignalProcessor {
    public:
        static void calibrateDCOffset();
        static double getDCOffset();
        static bool isDCOffsetCalculated();

        static void applyHammingWindow(
            std::array<std::complex<double>, MIC_BUFFER_SIZE> &buffer
        );

        static void removeDCComponent(
            std::array<std::complex<double>, MIC_BUFFER_SIZE> &fftOutput
        );

    private:
        static constexpr int DC_OFFSET_SAMPLES = 100;
        static double dcOffset;
        static bool dcOffsetCalculated;
    };
} // audio

#endif //AUDIO_REACTIVE_LED_SIGNALPROCESSOR_H