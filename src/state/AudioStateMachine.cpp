//
// Created by spokay on 12/7/25.
//

#include "AudioStateMachine.h"
#include "audio/SignalProcessor.h"
#include <esp32-hal-adc.h>
#include "FastLED.h"

namespace state {
    AudioStateMachine::AudioStateMachine(
        const audio::AudioHelper &audioHelper,
        const led::LEDHelper &ledHelper
    ) : audioHelper(audioHelper), ledHelper(ledHelper) {}

    void AudioStateMachine::init() {
        Serial.println("State machine: Initializing LEDS");
        CFastLED::addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
        FastLED.setBrightness(START_BRIGHTNESS);
        FastLED.clear();
        FastLED.show();

        Serial.println("State machine: Initializing Microphone Input");
        pinMode(MIC_PIN, INPUT);
        analogReadResolution(12);
        analogSetAttenuation(ADC_11db);

        Serial.println("State machine: Calibrating DC offset");
        audio::SignalProcessor::calibrateDCOffset();
    }

    AudioState AudioStateMachine::getCurrentState() const {
        return currentState;
    }

    void AudioStateMachine::processState(const AudioState state) {
        switch (state) {
            case COLLECTING_SAMPLES:
                collectSamples();
                break;
            case PROCESSING_SAMPLES:
                processSamples();
                break;
            case DISPLAYING_LED:
                displayLED();
                break;
        }
    }

    void AudioStateMachine::collectSamples() {
        const std::complex<double> sample = audio::AudioHelper::readOneSample();
        bufferManager.addSample(sample);

        if (bufferManager.isBufferFull()) {
            bufferManager.swapBuffers();
            currentState = PROCESSING_SAMPLES;
        }
    }

    void AudioStateMachine::prepareBufferForFFT() {
        // Copy processing buffer
        const auto& sourceBuffer = bufferManager.getProcessingBuffer();
        for (int i = 0; i < MIC_BUFFER_SIZE; i++) {
            processingBuffer[i] = sourceBuffer[i];
        }

        // Apply hamming window
        audio::SignalProcessor::applyHammingWindow(processingBuffer);
    }

    void AudioStateMachine::processSamples() {
        performanceMonitor.startFFTTimer();

        prepareBufferForFFT();
        audio::AudioHelper::iterativeFFT(processingBuffer, outputBuffer);
        audio::SignalProcessor::removeDCComponent(outputBuffer);

        performanceMonitor.stopFFTTimer();
        performanceMonitor.printFFTTime();

        bufferManager.setProcessingInProgress(false);
        currentState = DISPLAYING_LED;
    }

    void AudioStateMachine::displayLED() {
        const std::array<double, MATRIX_WIDTH> columnsValues =
            led::LEDHelper::mapFrequenciesToColumnsMagnitudes(outputBuffer);

        FastLED.clear();
        led::LEDHelper::updateLED(columnsValues, leds);
        FastLED.show();

        currentState = COLLECTING_SAMPLES;
    }
} // state