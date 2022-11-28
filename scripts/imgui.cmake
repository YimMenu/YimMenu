include(FetchContent)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/YimMenu/imgui.git
    GIT_TAG        a241dc7990b631fde6575771173c2442d43d2812
    GIT_PROGRESS TRUE
)
message("ImGui")
FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
endif()