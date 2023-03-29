include(FetchContent)

FetchContent_Declare(
    libcef
    GIT_REPOSITORY https://github.com/YimMenu/cef.git
    GIT_TAG        fa49d4e833e95844a734e54d44f17b4bd936c930
    GIT_PROGRESS TRUE
)
message("libcef")
FetchContent_MakeAvailable(libcef)
