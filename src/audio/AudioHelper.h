//
// Created by spokay on 12/6/25.
//

#ifndef AUDIO_REACTIVE_LED_AUDIOUTILS_H
#define AUDIO_REACTIVE_LED_AUDIOUTILS_H
#include <complex>
#include <array>
#include "config/configuration.h"

namespace audio {
    class AudioHelper {
    public:
        static std::complex<double> readOneSample();

        std::array<std::complex<double>, MIC_BUFFER_SIZE> iterativeFFT(
                const std::array<std::complex<double>, MIC_BUFFER_SIZE> &inputBuffer,
                std::array<std::complex<double>, MIC_BUFFER_SIZE> &outputBuffer
        ) const;

    private:
        void bitsReverseCopy(
            const std::array<std::complex<double>, MIC_BUFFER_SIZE> &inputBuffer,
            std::array<std::complex<double>, MIC_BUFFER_SIZE> &outputBuffer
        ) const;

        static unsigned int reverseBits(unsigned int n, int numBits);
    };
} // audio

#endif //AUDIO_REACTIVE_LED_AUDIOUTILS_H