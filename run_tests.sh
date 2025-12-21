#!/bin/bash

cd "$(dirname "$0")/build"

echo "Building tests..."
make

if [ $? -eq 0 ]; then
    echo ""
    echo "Running all tests..."
    ctest --output-on-failure
else
    echo "Build failed!"
    exit 1
fi
