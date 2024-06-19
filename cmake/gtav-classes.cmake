include(FetchContent)

add_compile_definitions(CXX_FORMAT_SUPPORT)

FetchContent_Declare(
    gtav_classes
    GIT_REPOSITORY https://github.com/maybegreat48/GTAV-Classes.git
    GIT_TAG        aa973216cc5215ff9ff70f467b96637f417c9bdd
    GIT_PROGRESS TRUE
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
message("GTAV-Classes")
if(NOT gtav_classes_POPULATED)
    FetchContent_Populate(gtav_classes)
endif()
