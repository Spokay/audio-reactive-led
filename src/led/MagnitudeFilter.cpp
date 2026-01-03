//
// Created by spokay on 1/3/26.
//

#include "MagnitudeFilter.h"
#include <cmath>

namespace led {
    double MagnitudeFilter::calculateNoiseFloor(
        const std::array<std::complex<double>, MIC_BUFFER_SIZE> &fftOutput
    ) {
        constexpr int usableBins = MIC_BUFFER_SIZE / 2;
        double noiseFloor = 0.0;

        for (int i = MIN_FREQ_BIN; i < usableBins; ++i) {
            noiseFloor += std::abs(fftOutput[i]);
        }

        return noiseFloor / (usableBins - MIN_FREQ_BIN);
    }

    double MagnitudeFilter::calculateDynamicThreshold(const double noiseFloor) {
        return noiseFloor * THRESHOLD_MULTIPLIER;
    }

    bool MagnitudeFilter::isAboveThreshold(const double magnitude, const double threshold) {
        return magnitude > threshold;
    }
} // led