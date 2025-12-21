#ifndef TASK_H
#define TASK_H

#include <chrono>

enum class State {
    Pending = 1,
    Running = 2,
    Completed = 3,
    Expired = 4,
};


class Task {

    private:
        const std::string id;
        const int priority;
        const std::chrono::time_point<std::chrono::system_clock> submitTime;
        const std::chrono::time_point<std::chrono::system_clock> expiry;
        std::chrono::milliseconds expectedDuration;
        State state;
    public:
        Task(std::string id, int priority, std::chrono::time_point<std::chrono::system_clock> expiry, std::chrono::milliseconds expectedDuration);
        std::string getId() const;
        int getPriority() const;
        State getState();
        std::chrono::time_point<std::chrono::system_clock> getSubmitTime() const;
        void markRunning();
        void markCompleted();
        void markExpired();
        std::chrono::time_point<std::chrono::system_clock> getExpiry() const;
        std::chrono::time_point<std::chrono::system_clock> getExpiryTime() const;

};

#endif
