#include "Metrics.hpp"
#include <chrono>
#include <iostream>

Metrics::Metrics()
    : expirationCount(0), peakQueueDepth(0), currentQueueDepth(0) {}

void Metrics::recordExecution(std::chrono::milliseconds milliseconds) {
    std::lock_guard<std::mutex> lock(mtx);
    executionTimes.push_back(milliseconds);
}

void Metrics::recordExpiration() {
    std::lock_guard<std::mutex> lock(mtx);
    expirationCount++;
}

void Metrics::incrementQueueDepth(size_t inc) {
    std::lock_guard<std::mutex> lock(mtx);
    currentQueueDepth += inc;
    if (currentQueueDepth > peakQueueDepth) {
        peakQueueDepth = currentQueueDepth;
    }
}

MetricsSnapshot Metrics::snapshot() const {
    std::lock_guard<std::mutex> lock(mtx);
    return MetricsSnapshot{
        executionTimes,
        expirationCount,
        peakQueueDepth,
        currentQueueDepth
    };
}
