#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <chrono>
void submitTask(...);
void executeNext();
void expireTasks(std::chrono::time_point<std::chrono::system_clock> currentTime);
auto getMetrics();
#endif
