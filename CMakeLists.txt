cmake_minimum_required(VERSION 3.20)
project(TaskScheduler VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Optional: Enable testing
# enable_testing()
# add_subdirectory(tests)
