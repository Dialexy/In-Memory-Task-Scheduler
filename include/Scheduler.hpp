#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Task.hpp"
#include "TaskQueue.hpp"
#include "Metrics.hpp"
#include <chrono>
#include <memory>

class Scheduler {
    private:
        TaskQueue taskQueue;
        Metrics metrics;

    public:
        void submitTask(std::string id, int priority,
                       std::chrono::time_point<std::chrono::system_clock> expiry,
                       std::chrono::milliseconds expectedDuration);
        void executeNext();
        void expireTasks(std::chrono::time_point<std::chrono::system_clock> currentTime);
        MetricsSnapshot getMetrics() const;
};

#endif
