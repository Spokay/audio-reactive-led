//
// Created by spokay on 12/7/25.
//

#ifndef AUDIO_REACTIVE_LED_STATEMACHINE_H
#define AUDIO_REACTIVE_LED_STATEMACHINE_H
#include <complex>
#include <vector>

#include "crgb.h"
#include "audio/AudioHelper.h"
#include "config/configuration.h"
#include "led/LEDHelper.h"

namespace state {
        enum AudioState {
                COLLECTING_SAMPLES,
                PROCESSING_SAMPLES,
                DISPLAYING_LED
        };

        class AudioStateMachine {
        public:
                AudioStateMachine(const audio::AudioHelper &audioHelper, const led::LEDHelper &ledHelper);
                void init();
                AudioState getCurrentState() const;
                void processState(AudioState state);
        private:
                /* State */
                AudioState currentState = COLLECTING_SAMPLES;

                /* Helpers */
                audio::AudioHelper audioHelper;
                led::LEDHelper ledHelper;

                /* Samples */
                std::array<std::complex<double>, MIC_BUFFER_SIZE> inputBuffer;
                std::array<std::complex<double>, MIC_BUFFER_SIZE> outputBuffer;
                int inputBufferIndex = 0;

                /* LEDS */
                CRGB leds[NUM_LEDS];

                void collectSamples();
                void processSamples();
                void displayLED();
        };
} // state

#endif //AUDIO_REACTIVE_LED_STATEMACHINE_H