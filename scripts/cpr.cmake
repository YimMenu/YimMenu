include(FetchContent)

set(BUILD_TESTING_BEFORE ${BUILD_TESTING})
set(CURL_DISABLE_TESTS OFF)
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG        67e2a4d2a76ed520e352f10e651a6f98e220dbd7
    GIT_PROGRESS TRUE
) 
message("cpr")
FetchContent_MakeAvailable(cpr)

set(BUILD_TESTING ${BUILD_TESTING_BEFORE} CACHE INTERNAL "" FORCE)