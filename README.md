# In-Memory Task Scheduler

## Overview

This is a lightweight, thread-safe task scheduling system designed to manage and execute tasks in memory. It provides a framework for scheduling, executing, and tracking tasks with support for priority-based execution, expiration handling and runtime metrics.

This project is designed to demonstrate key principles of task scheduling, including immutability, thread safety, and modular design.

---

## Features

- **Task Lifecycle Management**:
  - Supports task states: `Pending`, `Running`, `Completed`, and `Expired`.
  - Enforces state transitions: `Pending → Running → Completed` or `Pending → Expired`.

- **Priority-Based Scheduling**:
  - Tasks are executed based on priority, with submission time as a tie-breaker.

- **Task Registry**:
  - Centralised ownership and fast lookup of tasks.
  - Prevents duplicate task IDs.

- **Metrics Collection**:
  - Tracks runtime statistics such as completed tasks, expired tasks, average execution time, and queue depth.

- **Thread Safety**:
  - All public methods are thread-safe.
  - Designed to avoid deadlocks and partial updates.

- **Validation Harness**:
  - Demonstrates system behavior through various scenarios.

---

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/Dialexy/In-Memory-Task-Scheduler.git
   cd In-Memory-Task-Scheduler
   ```

2. **Build the project**:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

3. **Run the validation harness**:
   ```bash
   ./TaskScheduler
   ```

4. **Run the tests**:
   ```bash
   cd build
   ctest --verbose
   ```

---

## License

MIT License

Copyright (c) 2025 Dialexy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

## Disclaimer

All Tests in the test directory were created by claude sonnet 4.5.
