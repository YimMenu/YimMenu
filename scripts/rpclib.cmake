include(FetchContent)

FetchContent_Declare(
    rpclib
    GIT_REPOSITORY https://github.com/rpclib/rpclib.git
    GIT_TAG        463887f16ffcc4cf9ee0421bf25d49165b5e36f9
    GIT_PROGRESS TRUE
)
message("rpclib")
FetchContent_MakeAvailable(rpclib)
