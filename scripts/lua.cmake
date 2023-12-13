include(FetchContent)

message("Lua")
FetchContent_Declare(
    Lua
    GIT_REPOSITORY https://github.com/walterschell/Lua.git
    GIT_TAG a2e0125df529894f5e25d7d477b2df4e37690e0f
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(Lua)

set_property(TARGET lua_static PROPERTY CXX_STANDARD 23)
