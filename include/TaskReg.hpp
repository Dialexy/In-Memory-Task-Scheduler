#ifndef TASKREG_HPP
#define TASKREG_HPP

#include "Task.hpp"
#include <memory>
#include <unordered_map>
#include <string>

class TaskReg {
    private:
        static std::unordered_map<std::string, std::shared_ptr<Task>> registry;
    public:
        static void registerTask(std::shared_ptr<Task> task);
        static std::shared_ptr<Task> getTask(std::string taskId);
        static void removeTask(std::string taskId);
        static bool contains(std::string taskId);
};

#endif
