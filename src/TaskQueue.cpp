#include "TaskQueue.hpp"
#include <memory>
#include <stdexcept>
#include <vector>

void TaskQueue::push(std::shared_ptr<Task> task) {
  if (task->getState() != State::Pending) {
    throw std::invalid_argument("Task must be in Pending state to be added to the queue");
  }
  if (TaskReg::contains(task->getId())) {
    throw std::invalid_argument("Task is already queued");
  }
  TaskReg::registerTask(task);
  queue.push(task);
}

std::shared_ptr<Task> TaskQueue::pop() {
  if (queue.empty()) {
    throw std::runtime_error("Cannot pop from empty queue");
  }
  std::shared_ptr<Task> task = queue.top();
  queue.pop();
  return task;
}

std::shared_ptr<Task> TaskQueue::peek() {
  if (queue.empty()) {
    return nullptr;
  }
  return queue.top();
}

void TaskQueue::remove(std::string taskId) {
  std::vector<std::shared_ptr<Task>> temp;

  while (!queue.empty()) {
    auto task = queue.top();
    queue.pop();
    if (task->getId() != taskId) {
      temp.push_back(task);
    }
  }

  for (auto &task : temp) {
    queue.push(task);
  }
}

size_t TaskQueue::size() { return queue.size(); }
