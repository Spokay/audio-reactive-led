#include <Arduino.h>
#include <FastLED.h>
#include <config/configuration.h>

CRGB leds[NUM_LEDS];

// Convert (x,y) to LED index (zigzag pattern)
uint16_t resolveLEDIndex(const uint8_t x, const uint8_t y) {
    uint16_t index;

    if (y % 2 == 0) {
        // Even rows: left to right
        index = y * MATRIX_WIDTH + x;
    } else {
        // Odd rows: right to left (zigzag)
        index = y * MATRIX_WIDTH + (MATRIX_WIDTH - 1 - x);
    }

    return index;
}

void setup() {
    Serial.begin(115200);
    delay(1000);  // Give serial time to initialize

    Serial.println("Starting audio-reactive LED matrix...");

    // Initialize FastLED
    Serial.println("Initializing LEDS");
    CFastLED::addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(START_BRIGHTNESS);
    FastLED.clear();
    FastLED.show();

    // Configure microphone pin
    Serial.println("Initializing Microphone Input");
    pinMode(MIC_PIN, INPUT);

    Serial.println("Initialization complete!");
}

void loop() {
    // Read microphone (ESP32 ADC is 12-bit: 0-4095)
    const int audioLevel = analogRead(MIC_PIN);

    Serial.print("Audio level: ");
    Serial.println(audioLevel);

    // Map the audio level to the scale of the number of columns (0-32)
    const int numColumns = map(audioLevel, AUDIO_LOWER_BOUND, AUDIO_UPPER_BOUND, 0, MATRIX_WIDTH);

    // Clear matrix
    FastLED.clear();

    // Draw VU meter bars
    for (int x = 0; x < numColumns; x++) {
        for (int y = 0; y < MATRIX_HEIGHT; y++) {
            // Color gradient: red (bottom) to blue (top)
            const uint8_t hue = map(y, 0, MATRIX_HEIGHT - 1, 0, 160);
            leds[resolveLEDIndex(x, y)] = CHSV(hue, 255, 255);
        }
    }

    FastLED.show();
    delay(10);  // Small delay for stability
}