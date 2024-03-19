# CMake Scripts

This folder contains all external dependencies that YimMenu requires, this README should explain some of the things you should know.

## Updating dependencies

Most cmake files in this folder will look a bit as follows:
```cmake
include(FetchContent)

FetchContent_Declare(
    dependency_name
    GIT_REPOSITORY https://github.com/example/repo.git
    GIT_TAG        902ab63e0a771547961e132ccc0700d62e2a1423
    GIT_PROGRESS TRUE
)
message("<dependency_name>")
FetchContent_MakeAvailable(dependency_name)
set_property(TARGET dependency_target PROPERTY CXX_STANDARD 23)
```

There's a `GIT_TAG` in there that defines which specific version of the dependency we rely on, for some dependencies this will be a hash `902ab63e0a771547961e132ccc0700d62e2a1423` for others it will be just a version number (it's important to note that there must be a tag/release associated with it).

Examples on when to use what, for dependencies like ImGui we're best off using actually versioned releases as these have been "vetted" by the developer as release worthy, it will prevent us from relying on some random experimental release that exists on the ImGui master branch at that date and time. Others like Yimura/GTAV-Classes are updated frequently (rolling releases) and it would prove pointless to rely on versioning in this environment as such we rely on commit hashes directly.

## Different Dependencies

YimMenu contains many different dependencies and not all CMake scripts under this folder are used to fetch dependencies, some server a utilitarian function.

- `async-logger.cmake` : Library based on glog updated to support more modern C++ syntax
- `cpr.cmake` : Allows YimMenu to make connections to the internet and fetch data (mainly used for translations)
- `git.cmake` : Not a dependency, it's responsible for updating the git commit hash and git commit date the binary was built on
- `gtav-classes.cmake` : A collection of GTA V classes reverse engineered by the community
- `imgui.cmake` : The UI library used by YimMenu
- `json.cmake` : Allows YimMenu to parse json files and load them in as native C++ objects
- `lua.cmake` : Self-explanatory, implements a Lua runtime and allows YimMenu to expose functions to Lua directly
- `minhook.cmake` : Allows us to detour hook functions in GTA V
- `piguxml.cmake` : Xml parser used for XML vehicles and maps
