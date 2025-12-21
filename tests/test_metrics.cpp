#include "Metrics.hpp"
#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

void testMetricsConstruction() {
    Metrics metrics;

    auto snapshot = metrics.snapshot();
    assert(snapshot.executionTimes.size() == 0);
    assert(snapshot.expirationCount == 0);
    assert(snapshot.peakQueueDepth == 0);
    assert(snapshot.currentQueueDepth == 0);

    std::cout << "✓ Metrics construction test passed" << std::endl;
}

void testRecordExecution() {
    Metrics metrics;

    metrics.recordExecution(std::chrono::milliseconds(100));
    metrics.recordExecution(std::chrono::milliseconds(250));
    metrics.recordExecution(std::chrono::milliseconds(75));

    auto snapshot = metrics.snapshot();
    assert(snapshot.executionTimes.size() == 3);
    assert(snapshot.executionTimes[0].count() == 100);
    assert(snapshot.executionTimes[1].count() == 250);
    assert(snapshot.executionTimes[2].count() == 75);

    std::cout << "✓ Record execution test passed" << std::endl;
}

void testRecordExpiration() {
    Metrics metrics;

    metrics.recordExpiration();
    metrics.recordExpiration();
    metrics.recordExpiration();

    auto snapshot = metrics.snapshot();
    assert(snapshot.expirationCount == 3);

    std::cout << "✓ Record expiration test passed" << std::endl;
}

void testIncrementQueueDepth() {
    Metrics metrics;

    metrics.incrementQueueDepth(5);
    auto snapshot1 = metrics.snapshot();
    assert(snapshot1.currentQueueDepth == 5);
    assert(snapshot1.peakQueueDepth == 5);

    metrics.incrementQueueDepth(3);
    auto snapshot2 = metrics.snapshot();
    assert(snapshot2.currentQueueDepth == 8);
    assert(snapshot2.peakQueueDepth == 8);

    metrics.incrementQueueDepth(2);
    auto snapshot3 = metrics.snapshot();
    assert(snapshot3.currentQueueDepth == 10);
    assert(snapshot3.peakQueueDepth == 10);

    std::cout << "✓ Increment queue depth test passed" << std::endl;
}

void testPeakQueueDepth() {
    Metrics metrics;

    metrics.incrementQueueDepth(10);
    auto snapshot1 = metrics.snapshot();
    assert(snapshot1.currentQueueDepth == 10);
    assert(snapshot1.peakQueueDepth == 10);

    metrics.incrementQueueDepth(5);
    auto snapshot2 = metrics.snapshot();
    assert(snapshot2.currentQueueDepth == 15);
    assert(snapshot2.peakQueueDepth == 15);

    std::cout << "✓ Peak queue depth test passed" << std::endl;
}

void testSnapshotConsistency() {
    Metrics metrics;

    metrics.recordExecution(std::chrono::milliseconds(100));
    metrics.recordExpiration();
    metrics.incrementQueueDepth(7);

    auto snapshot1 = metrics.snapshot();
    auto snapshot2 = metrics.snapshot();

    assert(snapshot1.executionTimes.size() == snapshot2.executionTimes.size());
    assert(snapshot1.expirationCount == snapshot2.expirationCount);
    assert(snapshot1.peakQueueDepth == snapshot2.peakQueueDepth);
    assert(snapshot1.currentQueueDepth == snapshot2.currentQueueDepth);

    std::cout << "✓ Snapshot consistency test passed" << std::endl;
}

void testThreadSafety() {
    Metrics metrics;

    auto worker1 = [&metrics]() {
        for (int i = 0; i < 100; i++) {
            metrics.recordExecution(std::chrono::milliseconds(i));
        }
    };

    auto worker2 = [&metrics]() {
        for (int i = 0; i < 100; i++) {
            metrics.recordExpiration();
        }
    };

    auto worker3 = [&metrics]() {
        for (int i = 0; i < 100; i++) {
            metrics.incrementQueueDepth(1);
        }
    };

    std::thread t1(worker1);
    std::thread t2(worker2);
    std::thread t3(worker3);

    t1.join();
    t2.join();
    t3.join();

    auto snapshot = metrics.snapshot();
    assert(snapshot.executionTimes.size() == 100);
    assert(snapshot.expirationCount == 100);
    assert(snapshot.currentQueueDepth == 100);

    std::cout << "✓ Thread safety test passed" << std::endl;
}

int main() {
    std::cout << "Running Metrics tests..." << std::endl;

    testMetricsConstruction();
    testRecordExecution();
    testRecordExpiration();
    testIncrementQueueDepth();
    testPeakQueueDepth();
    testSnapshotConsistency();
    testThreadSafety();

    std::cout << "\nAll Metrics tests passed! ✓✓✓" << std::endl;
    return 0;
}
