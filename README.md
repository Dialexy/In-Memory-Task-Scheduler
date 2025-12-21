# In-Memory Task Scheduler

## Overview

This is a lightweight, thread-safe task scheduling system designed to manage and execute tasks in memory. It provides aframework for scheduling, executing, and tracking tasks with support for priority-based execution, expiration handling and runtime metrics.

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

2. **Build the project**:
   ```bash
   mkdir build && cd build
   cmake ..
   make

3. **Run the validation harness**:
   ```bash
   ./InMemoryTaskScheduler

---

## Disclaimer

All Tests in the test directory were created by claude sonnet 4.5.
