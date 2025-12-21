#include "TaskReg.hpp"
#include <iostream>
#include <stdexcept>

std::unordered_map<std::string, std::shared_ptr<Task>> TaskReg::registry;

void TaskReg::registerTask(std::shared_ptr<Task> task) {
  if (task == nullptr) {
    throw std::invalid_argument("Cannot register null task");
  }

  std::string taskId = task->getId();
  if (registry.find(taskId) != registry.end()) {
    throw std::invalid_argument("Task ID must be unique; duplicate ID: " + taskId);
  }

  registry[taskId] = task;
}

std::shared_ptr<Task> TaskReg::getTask(std::string taskId) {
  auto it = registry.find(taskId);
  if (it != registry.end()) {
    return it->second;
  }
  return nullptr;
}

void TaskReg::removeTask(std::string taskId) { registry.erase(taskId); }

bool TaskReg::contains(std::string taskId) {
  return registry.find(taskId) != registry.end();
}
