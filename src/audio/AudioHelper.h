//
// Created by spokay on 12/6/25.
//

#ifndef AUDIO_REACTIVE_LED_AUDIOUTILS_H
#define AUDIO_REACTIVE_LED_AUDIOUTILS_H
#include <complex>
#include <array>

#include "AudioSampler.h"
#include "config/configuration.h"

namespace audio {
    class AudioHelper {
    public:
        explicit AudioHelper(const AudioSampler &audio_sampler);

        static std::complex<double> readOneSample();

        static std::array<std::complex<double>, MIC_BUFFER_SIZE> iterativeFFT(
            const std::array<std::complex<double>, MIC_BUFFER_SIZE> &inputBuffer,
            std::array<std::complex<double>, MIC_BUFFER_SIZE> &outputBuffer
        );

    private:
        AudioSampler audioSampler;

        static void bitsReverseCopy(
            const std::array<std::complex<double>, MIC_BUFFER_SIZE> &inputBuffer,
            std::array<std::complex<double>, MIC_BUFFER_SIZE> &outputBuffer
        );

        static unsigned int reverseBits(unsigned int n, int numBits);
    };
} // audio

#endif //AUDIO_REACTIVE_LED_AUDIOUTILS_H