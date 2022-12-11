include(FetchContent)
FetchContent_Declare(
    wren
    GIT_REPOSITORY https://github.com/YimMenu/wren.git
    GIT_TAG        096b6ca56284d3f27cc29c559221d280ee8a0921
    GIT_PROGRESS TRUE
)
message("wren")
FetchContent_GetProperties(wren)
if(NOT wren_POPULATED)
    FetchContent_Populate(wren)

    file(GLOB_RECURSE SRC_WREN
        "${wren_SOURCE_DIR}/src/vm/*.c"
        "${wren_SOURCE_DIR}/src/optional/*.c"
    )

    add_library(wren STATIC ${SRC_WREN})
    source_group(TREE ${wren_SOURCE_DIR} PREFIX "wren" FILES ${SRC_WREN} )
    target_include_directories(wren PRIVATE
        "${wren_SOURCE_DIR}/src/include"
        "${wren_SOURCE_DIR}/src/optional"
        "${wren_SOURCE_DIR}/src/vm"
    )
endif()
