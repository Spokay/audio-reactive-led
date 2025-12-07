//
// Created by spokay on 12/7/25.
//

#include "AudioStateMachine.h"

#include <complex>
#include <esp32-hal-adc.h>
#include <map>
#include <numeric>
#include <vector>

#include "FastLED.h"
#include "audio/AudioHelper.h"
#include "config/configuration.h"

namespace state {
        AudioStateMachine::AudioStateMachine(
            const audio::AudioHelper &audioHelper, const led::LEDHelper &ledHelper
        ) : audioHelper(audioHelper), ledHelper(ledHelper) {}

        void AudioStateMachine::init() {
             /* Initialize FastLED */
            Serial.println("State machine : Initializing LEDS");
            CFastLED::addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
            FastLED.setBrightness(START_BRIGHTNESS);
            FastLED.clear();
            FastLED.show();

            /* Configure microphone pin */
            Serial.println("State machine: Initializing Microphone Input");
            pinMode(MIC_PIN, INPUT);
        }

        AudioState AudioStateMachine::getCurrentState() const {
            return this->currentState;
        }

        void AudioStateMachine::processState(const AudioState state) {
            switch (state) {
                case COLLECTING_SAMPLES: this->collectSamples();

                case PROCESSING_SAMPLES: this->processSamples();

                case DISPLAYING_LED: this->displayLED();

            }
        }

        void AudioStateMachine::collectSamples() {
            inputBuffer[inputBufferIndex++] = audioHelper.readOneSample();

            if (inputBufferIndex >= MIC_BUFFER_SIZE) {
                currentState = PROCESSING_SAMPLES;
                inputBufferIndex = 0;
            }
        }

        void AudioStateMachine::processSamples() {
            audioHelper.iterativeFFT(inputBuffer, outputBuffer);
            currentState = DISPLAYING_LED;
        }

        void AudioStateMachine::displayLED() {

            /* Calculating average for each step of 8 magnitudes */
            std::array<double, MATRIX_WIDTH> columnsValues;

            for (int col = 0; col < MATRIX_WIDTH; ++col) {
                const int startIdx = col * 8;
                const int endIdx = startIdx + 8;

                double sum = 0.0;
                for (int i = startIdx; i < endIdx; ++i) {
                    sum += std::abs(outputBuffer[i]);
                }
                columnsValues[col] = sum / 8.0;
            }

            /* Clear matrix */
            FastLED.clear();

            //TODO: Remove after testing MAX_MAGNITUDE
            const double maxMag = *std::max_element(columnsValues.begin(), columnsValues.end());
            Serial.printf("Max magnitude: %.2f\n", maxMag);

            /* Draw VU meter bars */
            ledHelper.updateLED(columnsValues, leds);


            FastLED.show();
            currentState = COLLECTING_SAMPLES;
        }
} // state