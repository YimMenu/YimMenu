cmake_minimum_required(VERSION 3.20)

option(USE_MINGW "Use MinGW toolchain and uasm compiler.")
if(USE_MINGW)
    message(STATUS "Unix-like system detected. Using MinGW-gcc and uasm.")

    set(TOOLCHAIN_PREFIX "x86_64-w64-mingw32" CACHE STRING "Set toolchain. Default: x86_64-w64-mingw32")

    message(STATUS "Using ${TOOLCHAIN_PREFIX} toolchain")

    set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

    set(CMAKE_SYSTEM_NAME "Windows")

    set(CMAKE_ASM_MASM_COMPILER "uasm")
    set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}-gcc")
    set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}-g++")
endif()

project(YimMenu CXX ASM_MASM)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

# Git commit embed
include(scripts/git.cmake)

# Fetch modules
message("\nFetching modules")
include(scripts/minhook.cmake)
include(scripts/g3log.cmake)
include(scripts/pugixml.cmake)
include(scripts/json.cmake)
include(scripts/fmt.cmake)
if(NOT USE_MINGW) # https://github.com/libcpr/cpr/issues/860
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
if(USE_MINGW)
    target_link_libraries(YimMenu PRIVATE pugixml minhook g3log imgui fmt d3dcompiler dwmapi winmm)
else()
    target_link_libraries(YimMenu PRIVATE pugixml minhook g3log imgui fmt cpr d3dcompiler dwmapi winmm)
endif()

# Warnings as errors
if(NOT USE_MINGW)
    set_property(TARGET YimMenu PROPERTY COMPILE_WARNING_AS_ERROR ON)
endif()

if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_ASM_MASM_COMPILER "uasm" CACHE INTERNAL "")
    target_compile_options(YimMenu PRIVATE 
        $<$<COMPILE_LANGUAGE:CXX>:-municode -fpermissive ${CXX_FLAGS}>
        $<$<COMPILE_LANGUAGE:ASM_MASM>:-win64 ${ASM_MASM_FLAGS}>
    )
    target_link_options(YimMenu PRIVATE -static -s)
endif()

add_compile_definitions(YimMenu 
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX"
    "WIN32_LEAN_AND_MEAN"
)
