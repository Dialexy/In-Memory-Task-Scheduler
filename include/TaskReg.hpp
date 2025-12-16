#ifndef TASKREG_HPP
#define TASKREG_HPP

#include "Task.hpp"
#include <memory>

class TaskReg {
    void registerTask(std::shared_ptr<Task>);
    Task getTask(std::string taskId);
    void removeTask(std::string taskId);
    void contains(std::string taskId);
};

#endif
