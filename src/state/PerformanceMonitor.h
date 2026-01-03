//
// Created by spokay on 1/3/26.
//

#ifndef AUDIO_REACTIVE_LED_PERFORMANCEMONITOR_H
#define AUDIO_REACTIVE_LED_PERFORMANCEMONITOR_H
#include <esp32-hal.h>

namespace state {
    class PerformanceMonitor {
    public:
        PerformanceMonitor() = default;
        void startFFTTimer();
        void stopFFTTimer();
        unsigned long getLastFFTTime() const;
        void printFFTTime() const;

    private:
        unsigned long fftStartTime = micros();
        unsigned long lastFFTTime = micros();
    };
} // state

#endif //AUDIO_REACTIVE_LED_PERFORMANCEMONITOR_H