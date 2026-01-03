//
// Created by spokay on 12/7/25.
//

// state/AudioStateMachine.h
#ifndef AUDIO_REACTIVE_LED_STATEMACHINE_H
#define AUDIO_REACTIVE_LED_STATEMACHINE_H

#include <complex>
#include <array>
#include "crgb.h"
#include "audio/AudioHelper.h"
#include "config/configuration.h"
#include "led/LEDHelper.h"
#include "BufferManager.h"
#include "PerformanceMonitor.h"

namespace state {
        enum AudioState {
                COLLECTING_SAMPLES,
                PROCESSING_SAMPLES,
                DISPLAYING_LED
            };

        class AudioStateMachine {
        public:
                AudioStateMachine(
                    const audio::AudioHelper &audioHelper,
                    const led::LEDHelper &ledHelper
                );

                void init();
                AudioState getCurrentState() const;
                void processState(AudioState state);

        private:
                AudioState currentState = COLLECTING_SAMPLES;

                /* Helpers */
                audio::AudioHelper audioHelper;
                led::LEDHelper ledHelper;
                BufferManager bufferManager;
                PerformanceMonitor performanceMonitor;

                std::array<std::complex<double>, MIC_BUFFER_SIZE> processingBuffer;
                std::array<std::complex<double>, MIC_BUFFER_SIZE> outputBuffer;

                CRGB leds[NUM_LEDS];

                void collectSamples();
                void processSamples();
                void displayLED();

                void prepareBufferForFFT();
        };
} // state

#endif //AUDIO_REACTIVE_LED_STATEMACHINE_H