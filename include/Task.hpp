#ifndef TASK_H
#define TASK_H

#include <chrono>


class Task {

    private:
        const std::string id;
        int priority;
        const std::chrono::time_point<std::chrono::system_clock> expiry;
        std::chrono::milliseconds expectedDuration;
        std::string state;
    public:
        Task(std::string id, int priority, std::chrono::time_point<std::chrono::system_clock> expiry, std::chrono::milliseconds expectedDuration);
        std::string getId() const;
        int getPriority();
        auto getState();
        void markRunning();
        void markCompleted() const;
        void markExpired() const;
        //TODO: set "getSubmitTime in constructor as const"
        std::chrono::time_point<std::chrono::system_clock> getExpiry();

};

enum class State {
    Pending = 1,
    Running = 2,
    Completed = 3,
    Expired = 4,
};

#endif
