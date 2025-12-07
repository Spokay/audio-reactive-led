//
// Created by spokay on 12/6/25.
//

#include "AudioHelper.h"

#include <cmath>
#include <complex>
#include <esp32-hal-adc.h>
#include <vector>

#include "config/configuration.h"

namespace audio {
    std::complex<double> AudioHelper::readOneSample() {
        const uint16_t sample = analogRead(MIC_PIN);
        return std::complex<double>(sample, 0.0);
    }

    std::vector<std::complex<double>> AudioHelper::iterativeFFT(
        const std::vector<std::complex<double> > &signalsSequenceValues,
        std::vector<std::complex<double> > &signalsFrequency
    ) const {
        const int n = signalsSequenceValues.size();
        this->bitsReverseCopy(signalsSequenceValues, signalsFrequency);
        for (int s = 1; s <= std::log2(n); s++) {
            const int m = std::pow(2, s);
            const double angle = -2.0 * M_PI / m;
            std::complex<double> omega_m(cos(angle), sin(angle));
            for (int k = 0; k < n; k += m) {
                std::complex<double> omega(1.0, 0.0);
                for (int j = 0; j < m / 2; j++) {
                    std::complex<double> t = omega * signalsFrequency[k + j + m / 2];
                    std::complex<double> u = signalsFrequency[k + j];
                    signalsFrequency[k + j] = u + t;
                    signalsFrequency[k + j + m / 2] = u - t;
                    omega = omega * omega_m;
                }
            }
        }
        return signalsFrequency;
    }

    void AudioHelper::bitsReverseCopy(
        const std::vector<std::complex<double> > &signalsSequenceValues,
        std::vector<std::complex<double> > &signalsFrequency
    ) const {
        const int numBits = std::log2(signalsSequenceValues.size());;
        for (int i = 0; i < signalsSequenceValues.size(); i++) {
            signalsFrequency[this->reverseBits(i, numBits)] = signalsSequenceValues[i];
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
