include(FetchContent)

FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG        1986262ba4e0cb052161e9e7919aef5ef08217f0
    GIT_PROGRESS TRUE
)
  
FetchContent_GetProperties(cpr)
if(NOT cpr_POPULATED)
  FetchContent_Populate(cpr)
  set(BUILD_CPR_TESTS OFF CACHE INTERNAL "")
  set(BUILD_CPR_TESTS_SSL OFF CACHE INTERNAL "")
  set(BUILD_CPR_TESTS_HTTP2 OFF CACHE INTERNAL "")
endif()
 
message("cpr")
FetchContent_MakeAvailable(cpr)
