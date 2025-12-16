#include "Task.hpp"
#include <chrono>


Task::Task(std::string id, int priority, std::chrono::time_point<std::chrono::system_clock> expiry, std::chrono::milliseconds expectedDuration)
    : id(id),
    priority(priority),
    expiry(expiry),
    expectedDuration(expectedDuration),
    state(State::Pending)
{}


std::string Task::getId() const {
    return id;
}

int Task::getPriority() {
    //TODO: finish taskQueue first
    return 0;
}

State Task::getState() {
    return state;
}

auto Task::getSubmitTime() {
    //TODO: finish taskQueue first
}

void Task::markRunning() {
    if (state != State::Running) {
        state = State::Running;
    }
}

void Task::markCompleted() {
    if (state != State::Completed) {
        state = State::Completed;
    }
}

void Task::markExpired() {
    if (state != State::Expired) {
        state = State::Expired;
    }
}
