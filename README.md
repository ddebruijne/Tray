# Cross-platform Linux/Windows/MacOS Tray
Cross-platform, super tiny implementation of a system tray icon with a popup menu.

Works well on:
* Linux/Gtk (libappindicator) - Gnome3 may need an [extension](https://extensions.gnome.org//extension/2890/tray-icons-reloaded/)
* Windows XP or newer (shellapi.h)
* MacOS (Cocoa/AppKit)

This fork is a different implementation based on [Dmitry Mikushin's fork.](https://github.com/dmikushin/tray) using more modern c++ and standard library.
He brought together the [original work of Serge Zaitsev](https://github.com/zserge/tray) and the most interesting forks and PRs of respectable contributors:
* [Only process messages coming from the tray window on Windows](https://github.com/zserge/tray/pull/18)
* [Become C++-friendly](https://github.com/zserge/tray/pull/16)
* [Fix all menu items have a check box](https://github.com/zserge/tray/pull/11)
* [Add support for tooltip](https://github.com/zserge/tray/pull/11)
* Darwin implementation translated from C to Objective C adapted from [@trevex fork](https://github.com/trevex/tray)

<img src="screenshot_macosx.png" width=400> <img src="screenshot_windows.png" width=400>

## Prerequisites
* CMake
* [Ninja](https://ninja-build.org/), in order to have the same build commands on all platforms
* AppIndicator on Linux:

Debian-based:
```
sudo apt install libappindicator3-dev
```

Arch-based:
```
sudo pacman -S libappindicator-gtk3
```

## Building
```
mkdir build
cd build
cmake -G Ninja ..
ninja
```

Personally, I open the folder in VSCode with CMake and CMake Tools extensions, that auto configures everything.
Had some issues with the flatpak version, so I recommend installing from AUR or using Microsoft's .deb file on linux.

## Demo
Execute the `tray_example` application:
```
./tray_example
```

## Usage
Needs updating. For now check example.cpp

## License
This software is distributed under [MIT license](http://www.opensource.org/licenses/mit-license.php), so feel free to integrate it in your commercial products.