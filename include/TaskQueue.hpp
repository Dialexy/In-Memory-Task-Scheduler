#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include "Task.hpp"
#include "TaskReg.hpp"
#include <memory>
#include <queue>
#include <vector>

class TaskQueue {
    private:
        struct TaskComparator {
            bool operator()(const std::shared_ptr<Task>& a, const std::shared_ptr<Task>& b) const {
                return a->getPriority() < b->getPriority();
            }
        };

        std::priority_queue<std::shared_ptr<Task>,
                          std::vector<std::shared_ptr<Task>>,
                          TaskComparator> queue;

    public:
        void push(std::shared_ptr<Task> task);
        std::shared_ptr<Task> pop();
        std::shared_ptr<Task> peek();
        void remove(std::string taskId);
        size_t size();

};

#endif
