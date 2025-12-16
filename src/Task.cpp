#include "Task.hpp"
#include <chrono>
#include <iostream>


Task::Task(std::string id, int priority, std::chrono::time_point<std::chrono::system_clock> expiry, std::chrono::milliseconds expectedDuration)
    : id(id),
    priority(priority),
    expiry(expiry),
    expectedDuration(expectedDuration),
    state(0)
{}


std::string Task::getId() const {
    return id;
}

int Task::getPriority() {
    return 0;
}

State getState() {
    State state;
    return state;
}

void Task::markRunning() {

}

void Task::markCompleted() const {

}

void Task::markExpired() const {

}


