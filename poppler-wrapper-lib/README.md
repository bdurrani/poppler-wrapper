# CMake Notes

### Install latest CMake on Ubuntu

Source: https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line
Source: https://apt.kitware.com/

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

Ubuntu is using a year old version of poopler which has an issue with eating
linefeeds.

It's best to build the latest version of poppler locally and install that.
See [install-dev-deps.sh](install-dev-deps.sh) for instructions on how to set that up.

You can also use these steps to install poppler in a Ubunto docker image.

It's a good idea to keep the local build around in case you want to remove
the local build.

If you need to remove the local build, use the `install_manifest.txt` file found in the build
folder to remove the files

```bash
sudo xargs rm < install_manifest.txt
```

This will remove anything that was installed via your CMake poppler build

#### Mac os

When installed using brew, poppler on the Mac Os is more up to date and does not
have the same issues as poppler on Ubuntu.

```bash
brew install cmake pkg-config ninja poppler boost
```

You will also need XCode installed.

### Install wrapper library output to custom location

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

### Generate reference text for tests

You need `poppler-utils` installed for this to work.

```bash
pdftotext -f 1 -l -enc UTF-8 -layout -nopgbrk ../test.pdf
```

## References

Some good CMake examples

- http://ttroy50.github.io/cmake-examples/
- https://github.com/ttroy50/cmake-examples

Modern CMake

- https://www.youtube.com/watch?v=mn1ZnO3MtVk
- https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1
- https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/
- https://github.com/pabloariasal/modern-cmake-sample

This has an example of a Find\*\*\*.cmake module
https://github.com/boostcon/cppnow_presentations_2017/blob/master/05-19-2017_friday/effective_cmake__daniel_pfeifer__cppnow_05-19-2017.pdf

This is how CMake sets up PostgreSql
https://github.com/Kitware/CMake/blob/master/Modules/FindPostgreSQL.cmake

Good Youtube tutorial about "Superbuilds"
https://www.youtube.com/watch?v=nBptg3SHPGU
