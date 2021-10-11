#!/usr/bin/env bash

set -euo pipefail

# Poppler versions
# https://gitlab.freedesktop.org/poppler/poppler/-/tags
# Use the same version as brew on the mac
readonly POPPLER_VERSION="21.09.0"
readonly POPPLER_DATA_VERSION="0.4.11"

POPPLER_PREFIX="poppler-"
POPPLER_DATA_PREFIX="poppler-data-"

POPPLER_DATA="${POPPLER_DATA_PREFIX}${POPPLER_DATA_VERSION}"
POPPLER="${POPPLER_PREFIX}${POPPLER_VERSION}"

pushd /tmp

DEBIAN_FRONTEND=noninteractive \
     sudo apt update && \
     sudo apt install --yes \
        --no-install-recommends \
        build-essential \
        cmake \
        ninja-build \
        libjpeg-dev \
        libnss3-dev \
        ca-certificates \
        libcurl4-nss-dev \
        liblcms2-dev \
        libboost-container-dev \
        pkg-config \
        wget \
        libopenjp2-7-dev \
        libfreetype-dev \
        libfontconfig1-dev
        
# on Ubuntu 18, you will install libfreetype6-dev instead of libfreetype-dev

wget "https://poppler.freedesktop.org/${POPPLER_DATA}.tar.gz"
tar -xvf "${POPPLER_DATA}.tar.gz"
pushd "${POPPLER_DATA}"
sudo make install
popd

wget "https://poppler.freedesktop.org/${POPPLER}.tar.xz"
tar -xvf "${POPPLER}.tar.xz"
pushd "${POPPLER}"
mkdir -p build && cd build && cmake -G Ninja \
        -DBUILD_GTK_TESTS=OFF \
        -DENABLE_QT5=OFF \
        -DENABLE_QT6=OFF \
        -DENABLE_GLIB=OFF \
        -DBUILD_QT5_TESTS=OFF \
        -DBUILD_QT6_TESTS=OFF \
        -DBUILD_MANUAL_TESTS=OFF \
        -DCMAKE_INSTALL_PREFIX:PATH=/usr \
        ..

ninja
sudo cmake --install . --prefix /usr
popd
