include(FetchContent)

set(ADD_FATAL_EXAMPLE OFF CACHE INTERNAL "")
set(INSTALL_G3LOG OFF CACHE INTERNAL "")
set(G3_SHARED_LIB OFF CACHE INTERNAL "")
set(G3_SHARED_RUNTIME OFF CACHE INTERNAL "")

FetchContent_Declare(
    g3log
    GIT_REPOSITORY https://github.com/YimMenu/g3log.git
    GIT_TAG        346502dd578c7b885970fb8a6ff4ceabae69fb35
    GIT_PROGRESS TRUE
)
message("g3log")
FetchContent_MakeAvailable(g3log)
set_property(TARGET g3log PROPERTY CXX_STANDARD 20)
