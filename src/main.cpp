#include <Arduino.h>

#include "state/AudioStateMachine.h"

auto *audioHelper = new audio::AudioHelper();
auto *ledHelper = new led::LEDHelper();
auto *audioStateMachine = new state::AudioStateMachine(*audioHelper, *ledHelper);

void setup() {
    Serial.begin(115200);
    delay(1000);  // Give serial time to initialize

    Serial.println("Starting audio-reactive LED matrix...");

    Serial.println("Initializing state machine");
    audioStateMachine->init();

    Serial.println("Initialization complete!");
}

void loop() {
    const state::AudioState currentState = audioStateMachine->getCurrentState();
    Serial.printf("Processing state : %d", currentState);
    audioStateMachine->processState(currentState);

    delay(10);  // Small delay for stability
}