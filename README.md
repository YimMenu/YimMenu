# BigBaseV2
A mod menu base for Grand Theft Auto V.
Strictly for educational purposes.

## Features
* ImGui–based user interface
* Unloading at runtime
* Log console
* Script fibers
* Fiber pool
* Access to YSC script globals
* scrProgram–based native hook

## Building
To build BigBaseV2 you need:
* Visual Studio 2019
* [Premake 5.0](https://premake.github.io/download.html) in your PATH

To set up the build environment, run the following commands in a terminal:
```dos
git clone https://github.com/Pocakking/BigBaseV2.git --recurse-submodules
cd BigBaseV2
GenerateProjects.bat
```
Now, you will be able to open the solution, and simply build it in Visual Studio.

It is reccomended you generate the project each time you add a file instead of adding it directly to Visual Studio.

## Credits
Pocakking - Original creator.

gir489 - Implementer and wrote the g3log crash handler and added test cases.

datlimabean04 - Wrote the g3log and settings implementation.