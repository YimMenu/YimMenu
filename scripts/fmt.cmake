include(FetchContent)


FetchContent_Declare(
    FMT
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        fc07217d85e6dcec52878807d6bbd89a9d9156a5
    GIT_PROGRESS TRUE
)
message("fmt")
FetchContent_MakeAvailable(FMT)
