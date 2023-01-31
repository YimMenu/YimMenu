include(FetchContent)

message("zydis")

set(ZYDIS_BUILD_DOXYGEN OFF CACHE BOOL "Zydis Build Doxygen")
set(ZYDIS_FEATURE_ENCODER OFF CACHE BOOL "Zydis Feature Encoder")

FetchContent_Declare(
    zydis
    GIT_REPOSITORY https://github.com/zyantific/zydis.git
    GIT_TAG        8948d9a8f493330d27a0e7bbebf40f0391e45f1b
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(zydis)
set_property(TARGET Zydis PROPERTY CXX_STANDARD 23)
