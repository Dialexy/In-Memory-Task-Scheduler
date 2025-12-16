#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include "Task.hpp"

class TaskQueue {

    public:
        void push(std::shared_ptr<Task>);
        auto pop();
        auto peek();
        void remove(std::string TaskId);
        void size();

};

#endif
