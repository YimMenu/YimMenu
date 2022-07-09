# YimMenu made possible by [BigBaseV2](https://github.com/Pocakking/BigBaseV2)
A mod menu base for Grand Theft Auto V.
Strictly for educational purposes.

this is my personal fork of YimMenu
nothing good here

## Table of contents

 * [How to build](#how-to-build)
 * [Staying Up To Date](#staying-up-to-date)
 * [Project Structure](#project-structure)
 * [Features](#features)
 * [Contributing](#contributing)

## How to build

```bash
git clone https://github.com/tupoy-ya/YimMenu.git --recursive
premake5 vs2019

```

## Staying Up To Date

Pull the latest changes from Github:
```bash
git pull && git submodule update
premake5 vs2019
```

## Project Structure

- `api/` contains some basic example of how I'd make REST api calls
- `backend/` all features that should be ran in a loop are in here sorted by category
- `gui/` includes everything related to UI elements
- `hooks/` function hooks
- `native_hooks/` hooks to natives
- `services/` service files to interact and maintain stuff
- `util/` general utility functions to keep code as compact and as much in one place as possible
- `views/` shitty ui that i'm to lazy to get rid of

## Features

Below is an incomplete list of feature that I believe are notable to this "base" or menu.

 - Return Native spoofing
 - Custom [settings](BigBaseV2/src/core/globals.hpp) with deep compare if changes were made include auto saving
 - Clear and well structured source code
 - Includes a thread pool to queue tasks that shouldn't block the game thread, very similar to fiber pool
 - Updated natives.hpp from https://nativedb.pieceof.art/natives
 - Includes basic code samples to interact with an api
 - ReClass.NET structures implemented, accessible from a global called g_local_player defined in `common.hpp`

## TODO

[x] jump ragdol
[x] phone animation
[] phone selection
[] pie menu
[] imgui ui
[] animals
[] blimps and planes
[] cable cars
[] Ambient ufos

[] better esp
[x] crash
[] godmode kill
[] protection

[] port to C++

## Contributing

You're free to contribute to YimMenu as long as the features are useful, non-toxic and do not contain anything money related that might get the menu targetted by Take2.

Make sure to read the [CONTRIBUTING.md](CONTRIBUTING.md) file.
