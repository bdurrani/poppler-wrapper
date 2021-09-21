#!/usr/bin/env bash

set -euo pipefail
pushd build
cmake --install . --prefix ../_install --config Debug
popd
mkdir -p ./dotnet/console-app/runtimes/linux-x64
cp ./_install/lib/libwrapper.so ./dotnet/console-app/runtimes/linux-x64/