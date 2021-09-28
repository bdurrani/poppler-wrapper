#!/usr/bin/env bash

set -euo pipefail
cmake -S . -B ./build -G "Ninja Multi-Config"
cmake --build ./build --config Debug --target all