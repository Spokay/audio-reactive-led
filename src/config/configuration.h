//
// Created by spokay on 12/6/25.
//

#ifndef AUDIO_REACTIVE_LED_LEDCONFIGURATION_H
#define AUDIO_REACTIVE_LED_LEDCONFIGURATION_H

namespace config {

// LED Matrix configuration
#define LED_PIN 23       // Using GPIO 23 (safe pin)
#define NUM_LEDS 256     // 8x32 matrix
#define MATRIX_WIDTH 32
#define MATRIX_HEIGHT 8
#define START_BRIGHTNESS 10     // Start at 10% brightness
#define LED_TYPE WS2812B
#define COLOR_ORDER  GRB


// Microphone configuration
#define MIC_PIN 34      // GPIO 34 (ADC1_0)
#define AUDIO_LOWER_BOUND 0
#define AUDIO_UPPER_BOUND 4095
#define MIC_BUFFER_SIZE 256
#define MIN_MAGNITUDE 0
#define MAX_MAGNITUDE 10000

#define MIN_FREQ_BIN 2

}
#endif //AUDIO_REACTIVE_LED_LEDCONFIGURATION_H