#!/usr/bin/env bash

set -euo pipefail
pushd build
cmake --install . --prefix ../_install --config Debug
popd

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
	mkdir -p ./dotnet/console-app/runtimes/linux-x64
	cp ./_install/lib/libwrapper.so ./dotnet/console-app/runtimes/linux-x64/
elif [[ "$OSTYPE" == "darwin"* ]]; then
	mkdir -p ./dotnet/console-app/runtimes/osx-x64
	cp ./_install/lib/libwrapper.dylib ./dotnet/console-app/runtimes/osx-x64/
fi