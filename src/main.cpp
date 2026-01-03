#include <Arduino.h>

#include "state/AudioStateMachine.h"

auto *audioSampler = new audio::AudioSampler();
auto *audioHelper = new audio::AudioHelper(*audioSampler);
auto *ledHelper = new led::LEDHelper();
auto *audioStateMachine = new state::AudioStateMachine(*audioHelper, *ledHelper);

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Starting audio-reactive LED matrix...");

    Serial.println("Initializing state machine");
    audioStateMachine->init();

    Serial.println("Initialization complete!");
}

void loop() {
    const state::AudioState currentState = audioStateMachine->getCurrentState();
    audioStateMachine->processState(currentState);
}