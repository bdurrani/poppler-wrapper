# CMake Notes

### Install latest CMake on Ubuntu

Source: https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line

```bash
sudo apt purge --auto-remove cmake

wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null

sudo apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"

sudo apt update
sudo apt install kitware-archive-keyring
sudo rm /etc/apt/trusted.gpg.d/kitware.gpg

sudo apt install cmake
```

### Required dependencies

#### Ubuntu
```bash
apt install pkg-config

apt-get install --yes --no-install-recommends build-essential cmake ninja-build libjpeg-dev libopenjp2-7-dev qtbase5-dev gobject-introspection libglib2.0-dev libgtk-3-dev libgirepository1.0-dev libnss3-dev ca-certificates libcurl4-nss-dev liblcms2-dev libboost-container-dev  libpoppler-cpp-dev
```

Instead of trying to build poppler from src, we're going to use the dev package and rely on `pkg-config`

```bash
sudo apt install libpoppler-cpp-dev
```

#### Mac os

```bash
brew install cmake pkg-config ninja poppler
```

You will also need XCode installed.

### Install project output to custom location

From the build folder

```bash
cmake --install . --prefix ../_install --config Debug
```

This will install the debug config to the `_install` folder.
This also installs the library built under the correct folder for the .NET project.

### Running tests

```bash
./run-tests.sh
```

## References

Some good CMake examples
http://ttroy50.github.io/cmake-examples/
https://github.com/ttroy50/cmake-examples

Modern CMake
https://www.youtube.com/watch?v=mn1ZnO3MtVk
https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1
https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/
https://github.com/pabloariasal/modern-cmake-sample

This has an example of a Find\*\*\*.cmake module
https://github.com/boostcon/cppnow_presentations_2017/blob/master/05-19-2017_friday/effective_cmake__daniel_pfeifer__cppnow_05-19-2017.pdf

This is how CMake sets up PostgreSql
https://github.com/Kitware/CMake/blob/master/Modules/FindPostgreSQL.cmake
