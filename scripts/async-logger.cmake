include(FetchContent)

message("AsyncLogger")
FetchContent_Declare(
    AsyncLogger
    GIT_REPOSITORY https://github.com/Yimura/AsyncLogger.git
    GIT_TAG v0.0.5
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(AsyncLogger)

set_property(TARGET AsyncLogger PROPERTY CXX_STANDARD 23)
