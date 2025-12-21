#include "Task.hpp"
#include <chrono>

Task::Task(std::string id, int priority,
           std::chrono::time_point<std::chrono::system_clock> expiry,
           std::chrono::milliseconds expectedDuration)
    : id(id), priority(priority), expiry(expiry),
      expectedDuration(expectedDuration), state(State::Pending) {}

std::string Task::getId() const { return id; }

int Task::getPriority() const {
  // TODO: finish taskQueue first
  return 0;
}

State Task::getState() {
  return state; // TODO: change the type to void
                // add terminal output showing which state it's in
}

auto Task::getSubmitTime() {
  // TODO: finish taskQueue first
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

std::chrono::time_point<std::chrono::system_clock> Task::getExpiry() {
  return expiry;
}
