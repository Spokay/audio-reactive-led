//
// Created by spokay on 12/6/25.
//

#ifndef AUDIO_REACTIVE_LED_AUDIOUTILS_H
#define AUDIO_REACTIVE_LED_AUDIOUTILS_H
#include <complex>
#include <vector>

namespace audio {
    std::vector<std::complex<double>> iterativeFFT(
            const std::vector<std::complex<double>> &signalsSequenceValues,
            std::vector<std::complex<double>> &signalsFrequency
    );
} // audio

#endif //AUDIO_REACTIVE_LED_AUDIOUTILS_H