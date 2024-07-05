include(FetchContent)

message("asmjit")
FetchContent_Declare(
    asmjit
    GIT_REPOSITORY https://github.com/asmjit/asmjit.git
    GIT_TAG        ffac9f36fb045dd2c6a81e1b5b9ccc115e5ef924
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(asmjit)
set_property(TARGET asmjit PROPERTY CXX_STANDARD 23)
