### Required dependencies

```bash
apt install pkg-config

apt-get install --yes --no-install-recommends build-essential cmake ninja-build libjpeg-dev libopenjp2-7-dev qtbase5-dev gobject-introspection libglib2.0-dev libgtk-3-dev libgirepository1.0-dev libnss3-dev ca-certificates libcurl4-nss-dev liblcms2-dev libboost-container-dev
```

### Clone with submodules

```bash
git clone --recurse-submodules git@github.com:bdurrani/poppler-wrapper.git
```

Also need popper-dev.
Instead of trying to build poppler from src, we're going
to use the dev package and rely on `pkg-config`

```bash
sudo apt install libpoppler-cpp-dev
```

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

### Install project output to custom location

From the build folder

```bash
cmake --install . --prefix ../_install --config Debug
```

This will install the debug config

### Running tests

From the build folder

```bash
ctest -C Debug
```
