//
// Created by spokay on 1/3/26.
//

#ifndef AUDIO_REACTIVE_LED_MAGNITUDEFILTER_H
#define AUDIO_REACTIVE_LED_MAGNITUDEFILTER_H

#include <array>
#include <complex>
#include "config/configuration.h"

namespace led {
    class MagnitudeFilter {
    public:
        static double calculateNoiseFloor(
            const std::array<std::complex<double>, MIC_BUFFER_SIZE> &fftOutput
        );

        static double calculateDynamicThreshold(double noiseFloor);

        static bool isAboveThreshold(double magnitude, double threshold);

    private:
        static constexpr double THRESHOLD_MULTIPLIER = 2.0;
    };
} // led

#endif //AUDIO_REACTIVE_LED_MAGNITUDEFILTER_H