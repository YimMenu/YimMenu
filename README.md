# YimMenu

![](https://img.shields.io/badge/dynamic/json?color=ffab00&label=Online%20Version&query=%24.game.online&url=https%3A%2F%2Fraw.githubusercontent.com%2FYimMenu%2FYimMenu%2Fmaster%2Fmetadata.json&style=flat-square&labelColor=000000) ![](https://img.shields.io/badge/dynamic/json?color=ffab00&label=Game%20Build&query=%24.game.build&url=https%3A%2F%2Fraw.githubusercontent.com%2FYimMenu%2FYimMenu%2Fmaster%2Fmetadata.json&style=flat-square&labelColor=000000)

A mod menu base for Grand Theft Auto V.
Strictly for educational purposes.

YimMenu is originally based of off [BigBaseV2](https://github.com/Pocakking/BigBaseV2) which was an amazing base at the time but nowadays is a bit dated.
So here I am with an up-to-date menu focusing on protecting the user from toxic modders.

## Table of contents

 * [How to build](#how-to-build)
    * [Curl](#curl)
    * [Git](#git)
    * [CMake](#CMake)
    * [Cloning and generating project files](#cloning-and-generating-project-files)
 * [Staying Up To Date](#staying-up-to-date)
 * [Project Structure](#project-structure)
 * [Features](#features)
 * [Contributing](#contributing)
 
## How to build

Requirements:

 * [Git](#git)
 * [CMake](#cmake)

If you have both of the above requirements you can skip to [cloning the git repo and generating the project files](#cloning-and-generating-project-files).

### Curl

Curl should be already installed on your computer, but if you are having issues with building the project, you will need to download and install
it.

[Download Link](https://curl.se/download.html)

### Git

If you haven't installed git on your system go and do so as it is **REQUIRED** for setting up a working build environment.

[Download Link](https://git-scm.com/download/win)

### CMake

CMake is used to generate our project files, if you haven't used it before you will need to download and install it.

[Download Link](https://cmake.org/download/)

### Cloning and generating project files

- Make sure that you have installed Git and CMake.

- Clone the repository:
  ```bash
  git clone https://github.com/YimMenu/YimMenu.git
  ```

-  Go into the directory you just cloned:
  ```bash
  cd YimMenu
  ```

#### Generate project files 

> **Note**
> You will have cd build and cmake again if you add any files or you will get an error when building.

- Windows Only

  - Visual Studio

    If you only use Visual Studio and don't want to mess with command lines, Visual Studio has a CMake extension that does all the work.

    Make sure it is [installed](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170#installation).

    Then, just open Visual Studio, open a local folder, and select the `YimMenu` folder that the `git clone` command just created.

    Let the CMake extension generate the needed files for building, you can follow the progress in the Output tab of Visual Studio.

    Then, you can just build by using the Build menu at the top and clicking Build All.


- Other OSs / IDEs

  If you use something else or prefer using the console on Windows, just follow this:

  ```bash
  mkdir build
  cd build
  cmake ..
  ```

  Now, you will be able to open the solution, and build it.
  
## Staying Up To Date

Pull the latest changes from this repository.

With a command line it is as easy as:

```bash
git pull
```

CMake should be handling removed / added files automatically without any user input.

If this is not the case for some reason you'll have to redo the steps in the [Generate project files](#generate-project-files) section above.

If you are doing custom modifications to the codebase and have a fork you are on your own for staying up to date with upstream (this repository), google stuff like "merge from upstream" and learn how to use Git.

## Project Structure

- `backend/` all features that should be ran in a loop are in here sorted by category
- `gui/` includes everything related to UI elements
- `hooks/` function hooks
- `native_hooks/` hooks to natives
- `services/` service files to interact and maintain stuff
- `util/` general utility functions to keep code as compact and as much in one place as possible

## Features

Below is an incomplete list of feature that I believe are notable to this "base" or menu.

 - Return Native spoofing
 - Custom [settings](src/core/globals.hpp) with deep compare if changes were made, including auto saving
 - Clear and well structured source code
 - Includes a thread pool to queue tasks that shouldn't block the game thread, very similar to fiber pool
 - Updated natives.hpp from https://nativedb.spyral.dev
 - ReClass.NET structures implemented, accessible from a global called g_local_player defined in `common.hpp`

## Contributing

You're free to contribute to YimMenu as long as the features are useful, not overly toxic and do not contain anything money related that might get the menu targeted by Take2.

Make sure to read the [CONTRIBUTING.md](CONTRIBUTING.md) file.
