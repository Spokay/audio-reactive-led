//
// Created by spokay on 1/3/26.
//

#ifndef AUDIO_REACTIVE_LED_BUFFERMANAGER_H
#define AUDIO_REACTIVE_LED_BUFFERMANAGER_H

#include <array>
#include <complex>
#include "config/configuration.h"

namespace state {
    class BufferManager {
    public:
        BufferManager();

        void addSample(const std::complex<double> &sample);
        bool isBufferFull() const;
        void resetIndex();

        void swapBuffers();
        bool canSwapBuffers() const;
        void setProcessingInProgress(bool inProgress);

        const std::array<std::complex<double>, MIC_BUFFER_SIZE>& getProcessingBuffer() const;
        int getCurrentIndex() const;

    private:
        std::array<std::complex<double>, MIC_BUFFER_SIZE> inputBuffer1;
        std::array<std::complex<double>, MIC_BUFFER_SIZE> inputBuffer2;
        std::array<std::complex<double>, MIC_BUFFER_SIZE>* activeInputBuffer;
        std::array<std::complex<double>, MIC_BUFFER_SIZE>* processingInputBuffer;

        int inputBufferIndex;
        bool processingInProgress;
    };
} // state

#endif //AUDIO_REACTIVE_LED_BUFFERMANAGER_H