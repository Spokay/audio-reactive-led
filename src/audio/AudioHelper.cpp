//
// Created by spokay on 12/6/25.
//

#include "AudioHelper.h"

#include <array>
#include <cmath>
#include <complex>
#include <esp32-hal-adc.h>

#include "AudioSampler.h"
#include "config/configuration.h"
namespace audio {

    AudioHelper::AudioHelper(
        const AudioSampler &audio_sampler
    ) : audioSampler(audio_sampler) {}

    std::complex<double> AudioHelper::readOneSample() {
        double sample = audioSampler.generateSample();
        return {sample, 0.0};
    }

    std::array<std::complex<double>, MIC_BUFFER_SIZE> AudioHelper::iterativeFFT(
        const std::array<std::complex<double>, MIC_BUFFER_SIZE> &inputBuffer,
        std::array<std::complex<double>, MIC_BUFFER_SIZE> &outputBuffer
    ) {
        const size_t n = inputBuffer.size();
        bitsReverseCopy(inputBuffer, outputBuffer);

        for (int s = 1; s <= std::log2(n); s++) {
            const int m = std::pow(2, s);
            const double angle = -2.0 * M_PI / m;
            std::complex<double> omega_m(cos(angle), sin(angle));
            for (int k = 0; k < n; k += m) {
                std::complex<double> omega(1.0, 0.0);
                for (int j = 0; j < m / 2; j++) {
                    std::complex<double> t = omega * outputBuffer[k + j + m / 2];
                    std::complex<double> u = outputBuffer[k + j];
                    outputBuffer[k + j] = u + t;
                    outputBuffer[k + j + m / 2] = u - t;
                    omega = omega * omega_m;
                }
            }
        }
        return outputBuffer;
    }

    void AudioHelper::bitsReverseCopy(
        const std::array<std::complex<double>, MIC_BUFFER_SIZE> &inputBuffer,
        std::array<std::complex<double>, MIC_BUFFER_SIZE> &outputBuffer
    ) {
        const int numBits = std::log2(inputBuffer.size());
        for (int i = 0; i < inputBuffer.size(); i++) {
            outputBuffer[reverseBits(i, numBits)] = inputBuffer[i];
        }
    }

    unsigned int AudioHelper::reverseBits(unsigned int n, const int numBits) {
        unsigned int ans = 0;
        for (int i = 0; i < numBits; ++i) {
            ans <<= 1;
            ans |= (n & 1);
            n >>= 1;
        }
        return ans;
    }
} // audio
