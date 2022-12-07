cmake_minimum_required(VERSION 3.20)

project(TupoyeMenu CXX ASM_MASM)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

# Git commit embed
include(scripts/git.cmake)

# Fetch modules
message("\nFetching modules")
include(scripts/minhook.cmake)
include(scripts/g3log.cmake)
include(scripts/pugixml.cmake)
include(scripts/json.cmake)

message("\nFetching custom modules")
include(scripts/imgui.cmake)
include(scripts/gtav-classes.cmake)


# TupoyeMenu
message(STATUS "TupoyeMenu")
file(GLOB_RECURSE SRC_MAIN
    "${SRC_DIR}/**.hpp"
    "${SRC_DIR}/**.h"
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/**.cc"
    "${SRC_DIR}/**.cxx"
    "${SRC_DIR}/**.asm"
)
add_library(TupoyeMenu MODULE "${SRC_MAIN}")


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET TupoyeMenu PROPERTY CXX_STANDARD 23) # 23 Because std::format is not avalible in std:c++20 for some reason. Maybe it's because i use v142 toolset.

source_group(TREE ${SRC_DIR} PREFIX "src" FILES ${SRC_MAIN} )

target_include_directories(TupoyeMenu PRIVATE 
    "${SRC_DIR}"
    "${json_SOURCE_DIR}/single_include"
    "${gtav_classes_SOURCE_DIR}"
    "${imgui_SOURCE_DIR}"
)

target_precompile_headers(TupoyeMenu PRIVATE "${SRC_DIR}/common.hpp")
target_link_libraries(TupoyeMenu PRIVATE pugixml minhook g3log imgui)

option(GEN_PDB "Generate PDB. Can cause some AC problems Default: OFF")
if(GEN_PDB)
    target_compile_options(TupoyeMenu PRIVATE "$<$<CONFIG:Release>:/Z7>")
    target_link_options(TupoyeMenu PRIVATE "$<$<CONFIG:Release>:/DEBUG>")
    target_link_options(TupoyeMenu PRIVATE "$<$<CONFIG:Release>:/OPT:REF>")
    target_link_options(TupoyeMenu PRIVATE "$<$<CONFIG:Release>:/OPT:ICF>")
endif()

# Warnings as errors
set_property(TARGET TupoyeMenu PROPERTY COMPILE_WARNING_AS_ERROR ON)

add_compile_definitions(TupoyeMenu 
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX"
    "WIN32_LEAN_AND_MEAN"
)
