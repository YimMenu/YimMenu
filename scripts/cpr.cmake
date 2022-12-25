include(FetchContent)

set(BUILD_TESTING_BEFORE ${BUILD_TESTING})
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG        a6b214914d4d320bbff0c6cf4a753c018235b0c0
    GIT_PROGRESS TRUE
) 
message("cpr")
FetchContent_MakeAvailable(cpr)

set(BUILD_TESTING ${BUILD_TESTING_BEFORE} CACHE INTERNAL "" FORCE)