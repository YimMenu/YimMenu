cmake_minimum_required(VERSION 3.20)

add_compile_definitions(USE_FMT) # Hello async logger.

# Crosscompiling
include(scripts/crosscompile.cmake)

project(YimMenu CXX ASM_MASM)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

# Git commit embed
include(scripts/git.cmake)

# Fetch modules
message("\nFetching modules")
include(scripts/minhook.cmake)
include(scripts/async-logger.cmake)
include(scripts/pugixml.cmake)
include(scripts/json.cmake)
include(scripts/fmt.cmake)
include(scripts/zydis.cmake)
include(scripts/lua.cmake)
if(NOT CROSSCOMPILE) # https://github.com/libcpr/cpr/issues/860
    include(scripts/cpr.cmake) 
endif()

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
set_property(TARGET YimMenu PROPERTY CXX_STANDARD 23)

source_group(TREE ${SRC_DIR} PREFIX "src" FILES ${SRC_MAIN} )

target_include_directories(YimMenu PRIVATE 
    "${SRC_DIR}"
    "${json_SOURCE_DIR}/single_include"
    "${gtav_classes_SOURCE_DIR}"
    "${imgui_SOURCE_DIR}"
)


target_link_libraries(YimMenu PRIVATE )

target_precompile_headers(YimMenu PRIVATE "${SRC_DIR}/common.hpp")
if(CROSSCOMPILE)
    target_link_libraries(YimMenu PRIVATE pugixml minhook AsyncLogger dbghelp imgui fmt Zydis lua_static d3dcompiler dwmapi winmm psapi)
else()
    target_link_libraries(YimMenu PRIVATE pugixml minhook AsyncLogger dbghelp imgui fmt Zydis cpr lua_static d3dcompiler dwmapi winmm psapi)
endif()

# Warnings as errors
if(NOT CROSSCOMPILE)
    set_property(TARGET YimMenu PROPERTY COMPILE_WARNING_AS_ERROR ON)
endif()


add_compile_definitions(
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX"
    "WIN32_LEAN_AND_MEAN"
)