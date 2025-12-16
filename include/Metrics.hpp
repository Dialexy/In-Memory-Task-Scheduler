#ifndef METRICS_H
#define METRICS_H

#include <chrono>
class Metrics {
    void recordExecution(std::chrono::milliseconds milliseconds);
    void recordExpiration();
    void incrementQueueDepth(size_t inc);
    void snapshot();
};

#endif
