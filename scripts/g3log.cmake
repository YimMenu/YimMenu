include(FetchContent)

set(ADD_FATAL_EXAMPLE OFF CACHE INTERNAL "")
set(INSTALL_G3LOG OFF CACHE INTERNAL "")
set(G3_SHARED_LIB OFF CACHE INTERNAL "")
set(G3_SHARED_RUNTIME OFF CACHE INTERNAL "")

FetchContent_Declare(
    g3log
    GIT_REPOSITORY https://github.com/YimMenu/g3log.git
    GIT_TAG        6ccf93c2e966e9ae13df75496a88e7b45214f7f8
    GIT_PROGRESS TRUE
)
message("g3log")
FetchContent_MakeAvailable(g3log)
set_property(TARGET g3log PROPERTY CXX_STANDARD 23)
