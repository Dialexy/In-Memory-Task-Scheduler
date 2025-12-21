#include "Scheduler.hpp"
#include "TaskReg.hpp"
#include <cassert>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

void clearRegistry() {
    auto taskIds = {"sched_task1", "sched_task2", "sched_task3", "sched_task4",
                    "sched_task5", "sched_task6", "sched_task7", "sched_task8"};
    for (const auto& id : taskIds) {
        TaskReg::removeTask(id);
    }
}

void testSubmitTask() {
    clearRegistry();
    Scheduler scheduler;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    scheduler.submitTask("sched_task1", 5, expiry, std::chrono::milliseconds(100));

    assert(TaskReg::contains("sched_task1"));

    std::cout << "✓ Submit task test passed" << std::endl;
}

void testSubmitDuplicateTask() {
    clearRegistry();
    Scheduler scheduler;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    scheduler.submitTask("sched_task2", 3, expiry, std::chrono::milliseconds(50));

    try {
        scheduler.submitTask("sched_task2", 4, expiry, std::chrono::milliseconds(75));
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ Submit duplicate task test passed" << std::endl;
    }
}

void testExecuteNext() {
    clearRegistry();
    Scheduler scheduler;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    scheduler.submitTask("sched_task3", 7, expiry, std::chrono::milliseconds(200));

    scheduler.executeNext();

    auto task = TaskReg::getTask("sched_task3");
    assert(task != nullptr);
    assert(task->getState() == State::Completed);

    std::cout << "✓ Execute next test passed" << std::endl;
}

void testExecuteNextWithPriority() {
    clearRegistry();
    Scheduler scheduler;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    scheduler.submitTask("sched_task4", 3, expiry, std::chrono::milliseconds(100));
    scheduler.submitTask("sched_task5", 9, expiry, std::chrono::milliseconds(150));
    scheduler.submitTask("sched_task6", 5, expiry, std::chrono::milliseconds(200));

    scheduler.executeNext();

    auto task = TaskReg::getTask("sched_task5");
    assert(task != nullptr);
    assert(task->getState() == State::Completed);
    assert(task->getPriority() == 9);

    std::cout << "✓ Execute next with priority test passed" << std::endl;
}

void testExpireTasks() {
    clearRegistry();
    Scheduler scheduler;

    auto now = std::chrono::system_clock::now();
    auto pastExpiry = now - std::chrono::hours(1);
    auto futureExpiry = now + std::chrono::hours(1);

    scheduler.submitTask("sched_task7", 2, futureExpiry, std::chrono::milliseconds(50));

    auto expiredTime = now + std::chrono::hours(2);
    scheduler.expireTasks(expiredTime);

    auto task = TaskReg::getTask("sched_task7");
    assert(task == nullptr);

    std::cout << "✓ Expire tasks test passed" << std::endl;
}

void testExpireOnlyPendingTasks() {
    clearRegistry();
    Scheduler scheduler;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    scheduler.submitTask("sched_task8", 4, expiry, std::chrono::milliseconds(100));
    scheduler.executeNext();

    auto task = TaskReg::getTask("sched_task8");
    assert(task->getState() == State::Completed);

    auto laterTime = now + std::chrono::hours(2);
    scheduler.expireTasks(laterTime);

    assert(task->getState() == State::Completed);

    std::cout << "✓ Expire only pending tasks test passed" << std::endl;
}

void testGetMetrics() {
    clearRegistry();
    Scheduler scheduler;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    scheduler.submitTask("metrics_task1", 5, expiry, std::chrono::milliseconds(100));
    scheduler.submitTask("metrics_task2", 3, expiry, std::chrono::milliseconds(150));

    auto metrics1 = scheduler.getMetrics();
    assert(metrics1.currentQueueDepth == 2);

    scheduler.executeNext();

    auto metrics2 = scheduler.getMetrics();
    assert(metrics2.executionTimes.size() == 1);

    TaskReg::removeTask("metrics_task1");
    TaskReg::removeTask("metrics_task2");

    std::cout << "✓ Get metrics test passed" << std::endl;
}

void testCannotExecuteExpiredTask() {
    clearRegistry();
    Scheduler scheduler;

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::milliseconds(100);

    scheduler.submitTask("expired_exec", 5, expiry, std::chrono::milliseconds(50));

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    try {
        scheduler.executeNext();
        assert(false);
    } catch (const std::runtime_error& e) {
        std::cout << "✓ Cannot execute expired task test passed" << std::endl;
    }

    TaskReg::removeTask("expired_exec");
}

int main() {
    std::cout << "Running Scheduler tests..." << std::endl;

    testSubmitTask();
    testSubmitDuplicateTask();
    testExecuteNext();
    testExecuteNextWithPriority();
    testExpireTasks();
    testExpireOnlyPendingTasks();
    testGetMetrics();
    testCannotExecuteExpiredTask();

    clearRegistry();

    std::cout << "\nAll Scheduler tests passed! ✓✓✓" << std::endl;
    return 0;
}
