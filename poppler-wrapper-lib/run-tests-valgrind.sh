#!/usr/bin/env bash

set -euo pipefail

ctest -T memcheck --test-dir ./build -C Debug --rerun-failed --output-on-failure