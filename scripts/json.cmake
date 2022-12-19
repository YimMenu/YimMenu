include(FetchContent)

set(JSON_MultipleHeaders OFF)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
    GIT_TAG        67e6070f9d9a44b4dec79ebe6b591f39d2285593
    GIT_PROGRESS TRUE
)
message("json")
FetchContent_MakeAvailable(json)
