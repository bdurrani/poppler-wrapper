### Clone with submodules

```bash
git clone --recurse-submodules git@github.com:bdurrani/poppler-wrapper.git
```

Also need popper-dev

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
