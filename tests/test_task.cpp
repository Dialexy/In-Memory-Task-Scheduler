#include "Task.hpp"
#include <cassert>
#include <chrono>
#include <iostream>
#include <stdexcept>

void testTaskConstruction() {
    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    Task task("task1", 5, expiry, std::chrono::milliseconds(100));

    assert(task.getId() == "task1");
    assert(task.getPriority() == 5);
    assert(task.getState() == State::Pending);
    assert(task.getExpiryTime() == expiry);

    std::cout << "✓ Task construction test passed" << std::endl;
}

void testTaskExpiryValidation() {
    auto now = std::chrono::system_clock::now();
    auto pastExpiry = now - std::chrono::hours(1);

    try {
        Task task("task2", 3, pastExpiry, std::chrono::milliseconds(50));
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ Task expiry validation test passed" << std::endl;
    }
}

void testTaskStateTransitions() {
    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    Task task("task3", 2, expiry, std::chrono::milliseconds(200));

    assert(task.getState() == State::Pending);

    task.markRunning();
    assert(task.getState() == State::Running);

    task.markCompleted();
    assert(task.getState() == State::Completed);

    std::cout << "✓ Task state transitions test passed" << std::endl;
}

void testTaskInvalidStateTransition() {
    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    Task task("task4", 1, expiry, std::chrono::milliseconds(150));

    try {
        task.markCompleted();
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ Task invalid state transition test passed" << std::endl;
    }
}

void testTaskExpiration() {
    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    Task task("task5", 4, expiry, std::chrono::milliseconds(300));

    assert(task.getState() == State::Pending);
    task.markExpired();
    assert(task.getState() == State::Expired);

    std::cout << "✓ Task expiration test passed" << std::endl;
}

void testTaskImmutability() {
    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    Task task("task6", 7, expiry, std::chrono::milliseconds(250));

    std::string id1 = task.getId();
    std::string id2 = task.getId();
    assert(id1 == id2);

    int priority1 = task.getPriority();
    int priority2 = task.getPriority();
    assert(priority1 == priority2);
    assert(priority1 == 7);

    auto submitTime1 = task.getSubmitTime();
    auto submitTime2 = task.getSubmitTime();
    assert(submitTime1 == submitTime2);

    std::cout << "✓ Task immutability test passed" << std::endl;
}

int main() {
    std::cout << "Running Task tests..." << std::endl;

    testTaskConstruction();
    testTaskExpiryValidation();
    testTaskStateTransitions();
    testTaskInvalidStateTransition();
    testTaskExpiration();
    testTaskImmutability();

    std::cout << "\nAll Task tests passed! ✓✓✓" << std::endl;
    return 0;
}
