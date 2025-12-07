//
// Created by spokay on 12/6/25.
//

#ifndef AUDIO_REACTIVE_LED_AUDIOUTILS_H
#define AUDIO_REACTIVE_LED_AUDIOUTILS_H
#include <complex>
#include <vector>

namespace audio {
    class AudioHelper {
    public:
        static std::complex<double> readOneSample();

        std::vector<std::complex<double>> iterativeFFT(
                const std::vector<std::complex<double>> &signalsSequenceValues,
                std::vector<std::complex<double>> &signalsFrequency
        ) const;

    private:
        void bitsReverseCopy(
            const std::vector<std::complex<double> > &signalsSequenceValues,
            std::vector<std::complex<double> > &signalsFrequency
        ) const;

        static unsigned int reverseBits(unsigned int n, int numBits);
    };
} // audio

#endif //AUDIO_REACTIVE_LED_AUDIOUTILS_H