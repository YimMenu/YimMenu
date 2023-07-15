include(FetchContent)

FetchContent_Declare(
    gtav_classes
    GIT_REPOSITORY https://github.com/Yimura/GTAV-Classes.git
    GIT_TAG        95dadd6e7ee7bfa15d66bb2c597d13e97c631727
    GIT_PROGRESS TRUE
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
message("GTAV-Classes")
if(NOT gtav_classes_POPULATED)
    FetchContent_Populate(gtav_classes)
endif()
