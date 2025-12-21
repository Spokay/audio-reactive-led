//
// Created by spokay on 12/21/25.
//

#ifndef AUDIO_REACTIVE_LED_AUDIOSIMULATOR_H
#define AUDIO_REACTIVE_LED_AUDIOSIMULATOR_H
#include <cstdint>

namespace audio {
    class AudioSampler {
    private:
        float phase = 0.0;
        float sampleRate = 8000.0;
        unsigned long sampleCount = 0;

    public:
        uint16_t generateSample();
    };
} // audio

#endif //AUDIO_REACTIVE_LED_AUDIOSIMULATOR_H