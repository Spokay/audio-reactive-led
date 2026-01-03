//
// Created by spokay on 1/3/26.
//

#include "BufferManager.h"
#include <Arduino.h>
#include <algorithm>

namespace state {
    BufferManager::BufferManager()
        : inputBufferIndex(0), processingInProgress(false) {
        activeInputBuffer = &inputBuffer1;
        processingInputBuffer = &inputBuffer2;
    }

    void BufferManager::addSample(const std::complex<double> &sample) {
        (*activeInputBuffer)[inputBufferIndex++] = sample;
    }

    bool BufferManager::isBufferFull() const {
        return inputBufferIndex >= MIC_BUFFER_SIZE;
    }

    void BufferManager::resetIndex() {
        inputBufferIndex = 0;
    }

    void BufferManager::swapBuffers() {
        if (!processingInProgress) {
            std::swap(activeInputBuffer, processingInputBuffer);
            resetIndex();
            processingInProgress = true;
        } else {
            // Le traitement précédent n'est pas terminé
            resetIndex();
            Serial.println("Warning: FFT processing too slow, dropping frame");
        }
    }

    bool BufferManager::canSwapBuffers() const {
        return !processingInProgress;
    }

    void BufferManager::setProcessingInProgress(bool inProgress) {
        processingInProgress = inProgress;
    }

    const std::array<std::complex<double>, MIC_BUFFER_SIZE>&
    BufferManager::getProcessingBuffer() const {
        return *processingInputBuffer;
    }

    int BufferManager::getCurrentIndex() const {
        return inputBufferIndex;
    }
} // state