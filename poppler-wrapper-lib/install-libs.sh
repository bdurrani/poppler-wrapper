#!/usr/bin/env bash

set -euo pipefail
pushd build > /dev/null
cmake --install . --prefix ../_install --config Debug
popd > /dev/null

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
	echo "Copying linux-x64 runtime"
	mkdir -p ../dotnet/console-app/runtimes/linux-x64
	cp ./_install/lib/libwrapper.so ../dotnet/poppler-lib/runtimes/linux-x64/
elif [[ "$OSTYPE" == "darwin"* ]]; then
	echo "Copying mac os runtime"
	mkdir -p ../dotnet/console-app/runtimes/osx-x64
	cp ./_install/lib/libwrapper.dylib ../dotnet/poppler-lib/runtimes/osx-x64/
fi