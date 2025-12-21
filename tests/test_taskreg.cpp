#include "TaskReg.hpp"
#include "Task.hpp"
#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <stdexcept>

void clearRegistry() {
    auto taskIds = {"reg_task1", "reg_task2", "reg_task3", "reg_task4", "reg_task5"};
    for (const auto& id : taskIds) {
        TaskReg::removeTask(id);
    }
}

void testRegisterTask() {
    clearRegistry();

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    auto task = std::make_shared<Task>("reg_task1", 5, expiry, std::chrono::milliseconds(100));

    TaskReg::registerTask(task);
    assert(TaskReg::contains("reg_task1"));

    std::cout << "✓ Register task test passed" << std::endl;
}

void testRegisterDuplicateTask() {
    clearRegistry();

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    auto task1 = std::make_shared<Task>("reg_task2", 3, expiry, std::chrono::milliseconds(50));
    auto task2 = std::make_shared<Task>("reg_task2", 4, expiry, std::chrono::milliseconds(75));

    TaskReg::registerTask(task1);

    try {
        TaskReg::registerTask(task2);
        assert(false);
    } catch (const std::invalid_argument& e) {
        std::cout << "✓ Register duplicate task test passed" << std::endl;
    }
}

void testGetTask() {
    clearRegistry();

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    auto task = std::make_shared<Task>("reg_task3", 7, expiry, std::chrono::milliseconds(200));
    TaskReg::registerTask(task);

    auto retrieved = TaskReg::getTask("reg_task3");
    assert(retrieved != nullptr);
    assert(retrieved->getId() == "reg_task3");
    assert(retrieved->getPriority() == 7);

    std::cout << "✓ Get task test passed" << std::endl;
}

void testGetNonExistentTask() {
    clearRegistry();

    auto retrieved = TaskReg::getTask("nonexistent");
    assert(retrieved == nullptr);

    std::cout << "✓ Get non-existent task test passed" << std::endl;
}

void testRemoveTask() {
    clearRegistry();

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    auto task = std::make_shared<Task>("reg_task4", 2, expiry, std::chrono::milliseconds(150));
    TaskReg::registerTask(task);

    assert(TaskReg::contains("reg_task4"));

    TaskReg::removeTask("reg_task4");
    assert(!TaskReg::contains("reg_task4"));

    auto retrieved = TaskReg::getTask("reg_task4");
    assert(retrieved == nullptr);

    std::cout << "✓ Remove task test passed" << std::endl;
}

void testContains() {
    clearRegistry();

    auto now = std::chrono::system_clock::now();
    auto expiry = now + std::chrono::hours(1);

    auto task = std::make_shared<Task>("reg_task5", 6, expiry, std::chrono::milliseconds(300));

    assert(!TaskReg::contains("reg_task5"));

    TaskReg::registerTask(task);
    assert(TaskReg::contains("reg_task5"));

    TaskReg::removeTask("reg_task5");
    assert(!TaskReg::contains("reg_task5"));

    std::cout << "✓ Contains test passed" << std::endl;
}

int main() {
    std::cout << "Running TaskReg tests..." << std::endl;

    testRegisterTask();
    testRegisterDuplicateTask();
    testGetTask();
    testGetNonExistentTask();
    testRemoveTask();
    testContains();

    clearRegistry();

    std::cout << "\nAll TaskReg tests passed! ✓✓✓" << std::endl;
    return 0;
}
