cmake_minimum_required(VERSION 3.20)
include(FetchContent)

project(BigBaseV2 CXX ASM_MASM)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/BigBaseV2/src")

set(CMAKE_CONFIGURATION_TYPES
    Release
    MinSizeRel
)

# g3log config
set(ADD_FATAL_EXAMPLE OFF CACHE INTERNAL "")
set(INSTALL_G3LOG OFF CACHE INTERNAL "")
set(G3_SHARED_LIB OFF CACHE INTERNAL "")
set(G3_SHARED_RUNTIME OFF CACHE INTERNAL "")

# json config
set(JSON_MultipleHeaders OFF CACHE INTERNAL "")

# Fetch content
FetchContent_Declare(
    minhook
    GIT_REPOSITORY https://github.com/YimMenu/minhook.git
    GIT_TAG        902ab63e0a771547961e132ccc0700d62e2a1423
	GIT_PROGRESS TRUE
)
FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG        a0e064336317c9347a91224112af9933598714e9
	GIT_PROGRESS TRUE
)
FetchContent_Declare(
    g3log
    GIT_REPOSITORY https://github.com/YimMenu/g3log.git
    GIT_TAG        6ccf93c2e966e9ae13df75496a88e7b45214f7f8
	GIT_PROGRESS TRUE
)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
    GIT_TAG        67e6070f9d9a44b4dec79ebe6b591f39d2285593
	GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(minhook pugixml g3log json)

# Show json project
add_library(json INTERFACE ${json_SOURCE_DIR}/single_include/nlohmann/json.hpp)


# Custom modules
message(STATUS "\nCustom modules")
# ImGui
message(STATUS "ImGui")
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/YimMenu/imgui.git
    GIT_TAG        a241dc7990b631fde6575771173c2442d43d2812
	GIT_PROGRESS TRUE
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)

    file(GLOB SRC_IMGUI
		"${imgui_SOURCE_DIR}/*.cpp"
		"${imgui_SOURCE_DIR}/*.h"
		"${imgui_SOURCE_DIR}/backends/imgui_impl_win32.*"
		"${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.*"
		"${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.*"
    )
	
	add_library(ImGui ${SRC_IMGUI})
	
	source_group(TREE ${imgui_SOURCE_DIR} PREFIX "imgui" FILES ${SRC_IMGUI} )
	
	target_include_directories(ImGui PRIVATE
		"${imgui_SOURCE_DIR}"
		"${imgui_SOURCE_DIR}/backends"
		"${imgui_SOURCE_DIR}/misc"
	)
endif()

message(STATUS "GTAV-Classes")
# GTAV-Classes
FetchContent_Declare(
    gtav_classes
    GIT_REPOSITORY https://github.com/Yimura/GTAV-Classes.git
    GIT_TAG        37361b421f70cf2a0cce33f2c7d277116474b7cd
	GIT_PROGRESS TRUE
	CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)
if(NOT gtav_classes_POPULATED)
    FetchContent_Populate(gtav_classes)

    file(GLOB_RECURSE SRC_GTAV_CLASSES "${gtav_classes_SOURCE_DIR}/*.hpp")
	
	# Show GTAV-Classes project
	add_library(gtav_classes INTERFACE ${SRC_GTAV_CLASSES})
	
	source_group(TREE ${gtav_classes_SOURCE_DIR} PREFIX "GTAV-Classes" FILES ${SRC_GTAV_CLASSES})
endif()

# Set CXX STABDRD
set_property(GLOBAL PROPERTY CXX_STANDARD 23)

# BigBaseV2
message(STATUS "BigBaseV2")
file(GLOB_RECURSE SRC_MAIN
    "${SRC_DIR}/**.hpp"
    "${SRC_DIR}/**.h"
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/**.cc"
    "${SRC_DIR}/**.cxx"
    "${SRC_DIR}/**.asm"
)
add_library(BigBaseV2 MODULE ${SRC_MAIN})

set_property(TARGET BigBaseV2 PROPERTY CXX_STANDARD 23) # 23 Because std::format is not avalible in std:c++20 for some reason. Maybe it's because i use v142 toolset.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

source_group(TREE ${SRC_DIR} PREFIX "YimMenu" FILES ${SRC_MAIN} )

target_include_directories(BigBaseV2 PRIVATE 
    ${SRC_DIR}
	"${json_SOURCE_DIR}/single_include"
	${gtav_classes_SOURCE_DIR}
	${imgui_SOURCE_DIR}
)

target_precompile_headers(BigBaseV2 PRIVATE "${SRC_DIR}/common.hpp")
target_link_libraries(BigBaseV2 PRIVATE pugixml minhook g3log ImGui d3dcompiler)

add_compile_definitions(BigBaseV2 
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX"
    "WIN32_LEAN_AND_MEAN"
)
