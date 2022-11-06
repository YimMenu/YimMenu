include(FetchContent)

FetchContent_Declare(
    minhook
    GIT_REPOSITORY https://github.com/YimMenu/minhook.git
    GIT_TAG        902ab63e0a771547961e132ccc0700d62e2a1423
    GIT_PROGRESS TRUE
)
message("MinHook")
FetchContent_MakeAvailable(minhook)
set_property(TARGET minhook PROPERTY CXX_STANDARD 23)
