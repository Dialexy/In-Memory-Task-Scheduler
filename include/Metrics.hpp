#ifndef METRICS_H
#define METRICS_H

#include <chrono>
#include <mutex>
#include <vector>

struct MetricsSnapshot {
    std::vector<std::chrono::milliseconds> executionTimes;
    size_t expirationCount;
    size_t peakQueueDepth;
    size_t currentQueueDepth;
};

class Metrics {
    private:
        mutable std::mutex mtx;
        std::vector<std::chrono::milliseconds> executionTimes;
        size_t expirationCount;
        size_t peakQueueDepth;
        size_t currentQueueDepth;

    public:
        Metrics();
        void recordExecution(std::chrono::milliseconds milliseconds);
        void recordExpiration();
        void incrementQueueDepth(size_t inc);
        MetricsSnapshot snapshot() const;
};

#endif
