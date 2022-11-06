include(FetchContent)

set(JSON_MultipleHeaders OFF CACHE INTERNAL "")

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
    GIT_TAG        67e6070f9d9a44b4dec79ebe6b591f39d2285593
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(json)

# Show json project
add_library(json INTERFACE ${json_SOURCE_DIR}/single_include/nlohmann/json.hpp)
