#include "Scheduler.hpp"
#include "TaskReg.hpp"
#include <chrono>
#include <stdexcept>
#include <vector>

void Scheduler::submitTask(
    std::string id, int priority,
    std::chrono::time_point<std::chrono::system_clock> expiry,
    std::chrono::milliseconds expectedDuration) {
  if (TaskReg::contains(id)) {
    throw std::invalid_argument("Task with ID: " + id + " already exists");
  }

  auto task = std::make_shared<Task>(id, priority, expiry, expectedDuration);
  taskQueue.push(task);

  metrics.incrementQueueDepth(1);
}

void Scheduler::executeNext() {
  if (taskQueue.size() == 0) {
    return;
  }

  auto task = taskQueue.pop();

  auto now = std::chrono::system_clock::now();
  if (task->getExpiryTime() < now) {
    throw std::runtime_error("Cannot execute expired task: " + task->getId());
  }

  auto startTime = std::chrono::system_clock::now();
  task->markRunning();

  task->markCompleted();
  auto endTime = std::chrono::system_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
      endTime - startTime);
  metrics.recordExecution(duration);
}

void Scheduler::expireTasks(
    std::chrono::time_point<std::chrono::system_clock> currentTime) {
  std::vector<std::string> toExpire;

  size_t queueSize = taskQueue.size();
  std::vector<std::shared_ptr<Task>> temp;

  for (size_t i = 0; i < queueSize; i++) {
    auto task = taskQueue.pop();

    if (task->getState() == State::Pending &&
        task->getExpiryTime() < currentTime) {
      task->markExpired();
      toExpire.push_back(task->getId());
      metrics.recordExpiration();
    } else {
      temp.push_back(task);
    }
  }

  for (auto &task : temp) {
    taskQueue.push(task);
  }

  for (const auto &taskId : toExpire) {
    TaskReg::removeTask(taskId);
  }
}

MetricsSnapshot Scheduler::getMetrics() const { return metrics.snapshot(); }
