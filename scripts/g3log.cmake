include(FetchContent)

set(ADD_FATAL_EXAMPLE OFF CACHE INTERNAL "")
set(INSTALL_G3LOG OFF CACHE INTERNAL "")
set(G3_SHARED_LIB OFF CACHE INTERNAL "")
set(G3_SHARED_RUNTIME OFF CACHE INTERNAL "")

FetchContent_Declare(
    g3log
    GIT_REPOSITORY https://github.com/tupoy-ya/g3log.git
    GIT_TAG        fdbdf0a75c5e3e0bac2f125a5bd902bb16eaa80b
    GIT_PROGRESS TRUE
)
message("g3log")
FetchContent_MakeAvailable(g3log)
set_property(TARGET g3log PROPERTY CXX_STANDARD 20)
