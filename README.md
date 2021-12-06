# YimMenu made possible by BigBaseV2
A mod menu base for Grand Theft Auto V.
Strictly for educational purposes.

I can't confirm if all hooks are correct as the report myself event hook probably is incorrect. All the other hooks should be correct and server their purpose.

## Structure

- `api/` contains some basic example of how I'd make REST api calls
- `backend/` all features that should be ran in a loop are in here sorted by category
- `gui/` includes everything related to UI elements
- `hooks/` function hooks
- `native_hooks/` hooks to natives, currently not implemented
- `services/` service files to interact and maintain stuff
- `util/` general utility functions to keep code as compact and as much in one place as possible

## Features

 - Return Native spoofing
 - Custom [settings](BigBaseV2/src/core/globals.hpp) with deep compare if changes were made include auto saving
 - Clear and well structured source code
 - Includes a thread pool to queue tasks that shouldn't block the game thread, very similar to fiber pool
 - Updated natives.hpp from https://nativedb.pieceof.art/natives
 - Includes basic code samples to interact with an api
 - ReClass.NET structures implemented, accessible from a global called g_local_player defined in `common.hpp`

To set up the build environment, run the following commands in a terminal:
```dos
git clone git@github.com:Yimura/YimMenu.git --recursive || echo You don't have git installed, install it from https://git-scm.com/download/win
cd YimMenu
GenerateProjects.bat
```
Now, you will be able to open the solution, and simply build it in Visual Studio.
