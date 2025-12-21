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
            // pinMode(MIC_PIN, INPUT);
        }

        AudioState AudioStateMachine::getCurrentState() const {
            return this->currentState;
        }

        void AudioStateMachine::processState(const AudioState state) {
            switch (state) {
                case COLLECTING_SAMPLES:
                    this->collectSamples();
                    break;
                case PROCESSING_SAMPLES:
                    this->processSamples();
                    break;
                case DISPLAYING_LED:
                    this->displayLED();
                    break;
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
            audio::AudioHelper::iterativeFFT(inputBuffer, outputBuffer);
            currentState = DISPLAYING_LED;
        }

        void AudioStateMachine::displayLED() {
            const std::array<double, MATRIX_WIDTH> columnsValues = led::LEDHelper::mapFrequenciesToColumnsMagnitudes(outputBuffer);

            FastLED.clear();
            led::LEDHelper::updateLED(columnsValues, leds);
            FastLED.show();

            currentState = COLLECTING_SAMPLES;
        }

}// state