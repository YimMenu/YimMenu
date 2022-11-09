# TupoyeMenu

![](https://img.shields.io/badge/dynamic/json?color=ffab00&label=Online%20Version&query=%24.game.online&url=https%3A%2F%2Fraw.githubusercontent.com%2FYimMenu%2FYimMenu%2Fmaster%2Fmetadata.json&style=flat-square&labelColor=000000) ![](https://img.shields.io/badge/dynamic/json?color=ffab00&label=Game%20Build&query=%24.game.build&url=https%3A%2F%2Fraw.githubusercontent.com%2FYimMenu%2FYimMenu%2Fmaster%2Fmetadata.json&style=flat-square&labelColor=000000)

A garbage fork of YimMenu made by an idiot

This fork aims to make the game more enjoyable by adding untested broken features that crash your game.
Strictly for educational purposes.

YimMenu is originally based of off [BigBaseV2](https://github.com/Pocakking/BigBaseV2) which was an amazing base at the time but nowadays is a bit dated.
So here I am with an up-to-date menu focusses on protecting the user from toxic modders.

## Table of contents

 * [How to build](#how-to-build)
 * [Staying Up To Date](#staying-up-to-date)
 * [Project Structure](#project-structure)
 * [Features](#features)
 * [Contributing](#contributing)

## How to build

Requirements:

 * [Git](#Git)
 * [CMake](#CMake)

If you have both of the above requirements you can skip to [cloning the git repo and generating the project files](#cloning-and-generating-project-files).

### Git

If you haven't installed git on your system go and do so it is **REQUIRED** for setting up a working build environment.

[Download Link](https://git-scm.com/download/win)

### CMake

CMake is used to generate our project files, if you haven't used it before we will need to download and install it.

[Download Link](https://cmake.org/download/)

### Cloning and generating project files

Clone the repository:
```bash
git clone https://github.com/tupoy-ya/TupoyeMenu.git || echo "You don't have git installed, install it from https://git-scm.com/download/win"
```

Go into the directory you just cloned:
```bash
cd TupoyeMenu
```

#### Generate project files:

```bash
mkdir build && cd build
cmake ..
```

Now you have `YimMenu.sln`? you can open it in "Gay Studio" or run "BSbuild.exe" in your GS Dev Cmd.
You can also use other ide's like VC Code and CodeLite if you want to.

## Staying Up To Date
```bash
git pull https://github.com/tupoy-ya/TupoyeMenu.git
cd build
cmake ..
```


## Project Structure
- `native_hooks/` hooks to natives
- `backend/` all features that should be ran in a loop are in here sorted by category
- `gui/` includes everything related to UI elements
- `hooks/` function hooks
- `native_hooks/` hooks to natives
- `services/` service files to interact and maintain stuff
- `util/` general utility functions to keep code as compact and as much in one place as possible
- `views/` all gui windows are, except handling windows for some reason

## Features

Below is an incomplete list of feature that I believe are notable to this "base" or menu.

 - Return Native spoofing
 - Custom [settings](BigBaseV2/src/core/globals.hpp) with deep compare if changes were made include auto saving
 - Clear and well structured source code
 - Includes a thread pool to queue tasks that shouldn't block the game thread, very similar to fiber pool
 - Updated natives.hpp from https://nativedb.spyral.dev/natives
 - Includes basic code samples to interact with an api
 - ReClass.NET structures implemented, accessible from a global called g_local_player defined in `common.hpp`

## Contributing

You're free to contribute to TupoyeMenu as long as the features are useful, "non-toxic" and do not contain anything money related that might get the menu targetted by Take2.

Make sure to read the [CONTRIBUTING.md](CONTRIBUTING.md) file.
