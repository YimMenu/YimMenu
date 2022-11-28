cmake_minimum_required(VERSION 3.20)

project(YimMenu CXX ASM_MASM)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")


# Fetch modules
message("\nFetching modules")
include(scripts/minhook.cmake)
include(scripts/g3log.cmake)
include(scripts/pugixml.cmake)
include(scripts/json.cmake)

message("\nFetching custom modules")
include(scripts/imgui.cmake)
include(scripts/gtav-classes.cmake)


# YimMenu
message(STATUS "YimMenu")
file(GLOB_RECURSE SRC_MAIN
    "${SRC_DIR}/**.hpp"
    "${SRC_DIR}/**.h"
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/**.cc"
    "${SRC_DIR}/**.cxx"
    "${SRC_DIR}/**.asm"
)
add_library(YimMenu MODULE "${SRC_MAIN}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET YimMenu PROPERTY CXX_STANDARD 23) # 23 Because std::format is not avalible in std:c++20 for some reason. Maybe it's because i use v142 toolset.

source_group(TREE ${SRC_DIR} PREFIX "src" FILES ${SRC_MAIN} )

target_include_directories(YimMenu PRIVATE 
    "${SRC_DIR}"
    "${json_SOURCE_DIR}/single_include"
    "${gtav_classes_SOURCE_DIR}"
    "${imgui_SOURCE_DIR}"
)

target_precompile_headers(YimMenu PRIVATE "${SRC_DIR}/common.hpp")
target_link_libraries(YimMenu PRIVATE pugixml minhook g3log imgui)

# Warnings as errors
set_property(TARGET YimMenu PROPERTY COMPILE_WARNING_AS_ERROR ON)

add_compile_definitions(YimMenu 
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX"
    "WIN32_LEAN_AND_MEAN"
)
