#!/usr/bin/env bash

set -euo pipefail

cd external/poppler

mkdir -p build

cmake -S .  \
  -B ./build \
  -DGLFW_BUILD_DOCS=OFF \
  -DBUILD_GTK_TESTS=OFF \
  -DBUILD_QT5_TESTS=OFF \
  -DBUILD_QT6_TESTS=OFF \
  -DENABLE_GLIB=OFF \
  -DENABLE_GTK_DOC=OFF \
  -DENABLE_QT5=OFF \
  -DENABLE_QT6=OFF \
  -DENABLE_GOBJECT_INTROSPECTION=OFF \
  -G Ninja

ninja -C ./build