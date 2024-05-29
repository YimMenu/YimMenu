include(FetchContent)

add_compile_definitions(CXX_FORMAT_SUPPORT)

message("AsyncLogger")
FetchContent_Declare(
    AsyncLogger
    GIT_REPOSITORY https://github.com/Yimura/AsyncLogger.git
    GIT_TAG 80ce938277acd44767f858099920ae20f1df42ca
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(AsyncLogger)

set_property(TARGET AsyncLogger PROPERTY CXX_STANDARD 23)
