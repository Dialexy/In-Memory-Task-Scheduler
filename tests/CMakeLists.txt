cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB LIB_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM LIB_SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")

add_executable(test_task test_task.cpp ${LIB_SOURCES})
add_executable(test_taskreg test_taskreg.cpp ${LIB_SOURCES})
add_executable(test_taskqueue test_taskqueue.cpp ${LIB_SOURCES})
add_executable(test_metrics test_metrics.cpp ${LIB_SOURCES})
add_executable(test_scheduler test_scheduler.cpp ${LIB_SOURCES})

enable_testing()

add_test(NAME TaskTests COMMAND test_task)
add_test(NAME TaskRegTests COMMAND test_taskreg)
add_test(NAME TaskQueueTests COMMAND test_taskqueue)
add_test(NAME MetricsTests COMMAND test_metrics)
add_test(NAME SchedulerTests COMMAND test_scheduler)
