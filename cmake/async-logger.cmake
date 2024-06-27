include(FetchContent)

add_compile_definitions(CXX_FORMAT_SUPPORT)

message("AsyncLogger")
FetchContent_Declare(
    AsyncLogger
    GIT_REPOSITORY https://github.com/Yimura/AsyncLogger.git
    GIT_TAG 6fcfd90b3f4ca4dae09c4a96e9a506e6aea06472
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(AsyncLogger)

set_property(TARGET AsyncLogger PROPERTY CXX_STANDARD 23)
