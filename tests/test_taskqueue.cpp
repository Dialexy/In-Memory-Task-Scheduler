#include "TaskQueue.hpp"
#include "TaskReg.hpp"
#include "Task.hpp"
#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <stdexcept>

void clearRegistry() {
    auto taskIds = {"q_task1", "q_task2", "q_task3", "q_task4", "q_task5", "q_task6", "q_task7"};
    for (const auto& id : taskIds) {
        TaskReg::removeTask(id);
    }
}

void testPushTask() {
    clearRegistry();
    TaskQueue queue;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    auto task = std::make_shared<Task>("q_task1", 5, expiry, std::chrono::milliseconds(100));

    queue.push(task);
    assert(queue.size() == 1);

    std::cout << "✓ Push task test passed" << std::endl;
}

void testPushNonPendingTask() {
    clearRegistry();
    TaskQueue queue;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    auto task = std::make_shared<Task>("q_task2", 3, expiry, std::chrono::milliseconds(50));
    task->markRunning();

    try {
        queue.push(task);
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ Push non-pending task test passed" << std::endl;
    }
}

void testPushDuplicateTask() {
    clearRegistry();
    TaskQueue queue;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    auto task1 = std::make_shared<Task>("q_task3", 4, expiry, std::chrono::milliseconds(75));
    auto task2 = std::make_shared<Task>("q_task3", 6, expiry, std::chrono::milliseconds(100));

    queue.push(task1);

    try {
        queue.push(task2);
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ Push duplicate task test passed" << std::endl;
    }
}

void testPopTask() {
    clearRegistry();
    TaskQueue queue;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    auto task = std::make_shared<Task>("q_task4", 7, expiry, std::chrono::milliseconds(200));
    queue.push(task);

    assert(queue.size() == 1);
    auto popped = queue.pop();
    assert(queue.size() == 0);
    assert(popped->getId() == "q_task4");

    std::cout << "✓ Pop task test passed" << std::endl;
}

void testPopEmptyQueue() {
    clearRegistry();
    TaskQueue queue;

    try {
        queue.pop();
        assert(false);
    } catch (const std::runtime_error& e) {
        std::cout << "✓ Pop empty queue test passed" << std::endl;
    }
}

void testPriorityOrdering() {
    clearRegistry();
    TaskQueue queue;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    auto task1 = std::make_shared<Task>("q_task5", 3, expiry, std::chrono::milliseconds(50));
    auto task2 = std::make_shared<Task>("q_task6", 9, expiry, std::chrono::milliseconds(75));
    auto task3 = std::make_shared<Task>("q_task7", 5, expiry, std::chrono::milliseconds(100));

    queue.push(task1);
    queue.push(task2);
    queue.push(task3);

    auto popped1 = queue.pop();
    assert(popped1->getPriority() == 9);

    auto popped2 = queue.pop();
    assert(popped2->getPriority() == 5);

    auto popped3 = queue.pop();
    assert(popped3->getPriority() == 3);

    std::cout << "✓ Priority ordering test passed" << std::endl;
}

void testPeekTask() {
    clearRegistry();
    TaskQueue queue;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    auto task1 = std::make_shared<Task>("peek_task1", 2, expiry, std::chrono::milliseconds(150));
    auto task2 = std::make_shared<Task>("peek_task2", 8, expiry, std::chrono::milliseconds(200));

    queue.push(task1);
    queue.push(task2);

    assert(queue.size() == 2);
    auto peeked = queue.peek();
    assert(peeked->getPriority() == 8);
    assert(queue.size() == 2);

    std::cout << "✓ Peek task test passed" << std::endl;
}void testRemoveTask() {
    clearRegistry();
    TaskQueue queue;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    auto task1 = std::make_shared<Task>("rem_task1", 4, expiry, std::chrono::milliseconds(100));
    auto task2 = std::make_shared<Task>("rem_task2", 6, expiry, std::chrono::milliseconds(150));
    auto task3 = std::make_shared<Task>("rem_task3", 2, expiry, std::chrono::milliseconds(200));

    queue.push(task1);
    queue.push(task2);
    queue.push(task3);

    assert(queue.size() == 3);

    queue.remove("rem_task2");
    assert(queue.size() == 2);

    auto popped1 = queue.pop();
    assert(popped1->getId() == "rem_task1");

    auto popped2 = queue.pop();
    assert(popped2->getId() == "rem_task3");

    std::cout << "✓ Remove task test passed" << std::endl;
}

int main() {
    std::cout << "Running TaskQueue tests..." << std::endl;

    testPushTask();
    testPushNonPendingTask();
    testPushDuplicateTask();
    testPopTask();
    testPopEmptyQueue();
    testPriorityOrdering();
    testPeekTask();
    testRemoveTask();

    clearRegistry();

    std::cout << "\nAll TaskQueue tests passed! ✓✓✓" << std::endl;
    return 0;
}
