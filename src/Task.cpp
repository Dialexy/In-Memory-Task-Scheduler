#include "Task.hpp"
#include <chrono>
#include <stdexcept>

Task::Task(std::string id, int priority,
           std::chrono::time_point<std::chrono::system_clock> expiry,
           std::chrono::milliseconds expectedDuration)
    : id(id), priority(priority), submitTime(std::chrono::system_clock::now()),
      expiry(expiry), expectedDuration(expectedDuration),
      state(State::Pending) {
  if (expiry < submitTime) {
    throw std::invalid_argument("Expiry time must be >= submit time");
  }
}

std::string Task::getId() const { return id; }

int Task::getPriority() const { return priority; }

State Task::getState() { return state; }

std::chrono::time_point<std::chrono::system_clock> Task::getSubmitTime() const {
  return submitTime;
}

void Task::markRunning() {
  if (state != State::Running && state == State::Pending) {
    state = State::Running;
  } else {
    throw std::invalid_argument("State could not be changed");
  }
}

void Task::markCompleted() {
  if (state != State::Completed && state == State::Running) {
    state = State::Completed;
  } else {
    throw std::invalid_argument("State could not be changed");
  }
}

void Task::markExpired() {
  if (state != State::Expired && state == State::Pending) {
    state = State::Expired;
  } else {
    throw std::invalid_argument("State could not be changed");
  }
}

std::chrono::time_point<std::chrono::system_clock> Task::getExpiry() const {
  return expiry;
}

std::chrono::time_point<std::chrono::system_clock> Task::getExpiryTime() const {
  return expiry;
}
