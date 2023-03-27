# Visual Studio Code

We will use Winget to grab all the required packages without needing to touch Visual Studio IDE to handle installing the C++ compiler and other stuff.

## Installing the packages

Install Visual Studio Code if you haven't already
```bash
winget install Microsoft.VisualStudioCode
```

Install C++ Desktop Development (we have to do this through VS Community as Microsoft doesn't offer any other methods)

## Installing required extensions

These extensions are required to properly develop YimMenu on Visual Studio Code.

- CMake `twxs.cmake`
- CMake Tools Fork `maxmitti.cmake-tools-fork`
- C/C++ Extension Pack `ms-vscode.cpptools-extension-pack`

## Optional extensions

These extensions are optional but offer extra tools to help you code on YimMenu or other C++ projects.

- CMake Language Support `josetr.cmake-language-support-vscode` : I use this for "intellisense" in CMake files
- C-mantic `tdennis4496.cmantic` : Extra helper functionality while working
- Hex Editor `ms-vscode.hexeditor` : Can be used to investigated registers and memory while debugging an app