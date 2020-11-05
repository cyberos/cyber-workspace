# Cyber WorkSpace

System backend and start session and more.

## Dependencies

```shell
sudo pacman -S extra-cmake-modules pkgconf qt5-base qt5-quickcontrols2 qt5-x11extras qt5-tools kidletime kwindowsystem polkit polkit-qt5 pulseaudio polkit-qt5
```

## Build

```shell
mkdir build
cd build
cmake ..
make
```

## Install

```shell
sudo make install
```