#!/bin/bash

echo "Compiling..."
cmake -B build
echo "Building..."
cmake --build build
echo "Running..."
./build/BisquitExec
