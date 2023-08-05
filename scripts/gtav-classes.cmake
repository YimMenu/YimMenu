include(FetchContent)

FetchContent_Declare(
    gtav_classes
    GIT_REPOSITORY https://github.com/gir489returns/GTAV-Classes.git
    GIT_TAG        2b5023e50b83077ceef504f449372ec806f0ef69
    GIT_PROGRESS TRUE
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
message("GTAV-Classes")
if(NOT gtav_classes_POPULATED)
    FetchContent_Populate(gtav_classes)
endif()
