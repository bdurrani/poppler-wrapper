#!/usr/bin/env bash

set -euo pipefail

ctest --test-dir ./build -C Debug --rerun-failed --output-on-failure