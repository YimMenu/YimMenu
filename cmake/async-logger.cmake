include(FetchContent)

add_compile_definitions(CXX_FORMAT_SUPPORT)

message("AsyncLogger")
FetchContent_Declare(
    AsyncLogger
    GIT_REPOSITORY https://github.com/maybegreat48/AsyncLogger.git
    GIT_TAG 2a9b5b176ec3c07a40f42269414211037871ac27
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(AsyncLogger)

set_property(TARGET AsyncLogger PROPERTY CXX_STANDARD 23)
