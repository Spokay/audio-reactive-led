//
// Created by spokay on 12/21/25.
//

#include "AudioSampler.h"

#include <Arduino.h>
#include <cmath>

namespace audio {

    uint16_t AudioSampler::generateSample() {
        sampleCount++;
        phase = static_cast<float>(sampleCount);

        float signal = 0;

        // Basses (100-400 Hz) - 8 fréquences
        signal += sin(2.0 * PI * 100.0 * phase / sampleRate) * 400;
        signal += sin(2.0 * PI * 150.0 * phase / sampleRate) * 400;
        signal += sin(2.0 * PI * 200.0 * phase / sampleRate) * 400;
        signal += sin(2.0 * PI * 250.0 * phase / sampleRate) * 400;
        signal += sin(2.0 * PI * 300.0 * phase / sampleRate) * 400;
        signal += sin(2.0 * PI * 350.0 * phase / sampleRate) * 400;

        // Médiums bas (400-1000 Hz) - 6 fréquences
        signal += sin(2.0 * PI * 500.0 * phase / sampleRate) * 350;
        signal += sin(2.0 * PI * 650.0 * phase / sampleRate) * 350;
        signal += sin(2.0 * PI * 800.0 * phase / sampleRate) * 350;
        signal += sin(2.0 * PI * 950.0 * phase / sampleRate) * 350;

        // Médiums (1000-2000 Hz) - 5 fréquences
        signal += sin(2.0 * PI * 1100.0 * phase / sampleRate) * 300;
        signal += sin(2.0 * PI * 1300.0 * phase / sampleRate) * 300;
        signal += sin(2.0 * PI * 1500.0 * phase / sampleRate) * 300;
        signal += sin(2.0 * PI * 1700.0 * phase / sampleRate) * 300;
        signal += sin(2.0 * PI * 1900.0 * phase / sampleRate) * 300;

        // Aigus (2000-4000 Hz) - 4 fréquences
        signal += sin(2.0 * PI * 2200.0 * phase / sampleRate) * 250;
        signal += sin(2.0 * PI * 2700.0 * phase / sampleRate) * 250;
        signal += sin(2.0 * PI * 3200.0 * phase / sampleRate) * 200;
        signal += sin(2.0 * PI * 3700.0 * phase / sampleRate) * 200;

        return static_cast<uint16_t>(constrain(signal + 2048, 0, 4095));
    }

} // audio