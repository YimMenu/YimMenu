cmake_minimum_required(VERSION 3.20)

if(UNIX)
    message(STATUS "Unix-like system detected. Using MinGW and uasm.")

    set(TOOLCHAIN_PREFIX "x86_64-w64-mingw32" CACHE STRING "Set toolchain. Default: x86_64-w64-mingw32")

    message(STATUS "Using ${TOOLCHAIN_PREFIX} toolchain")

    set(CMAKE_SYSTEM_NAME "Windows")

    set(CMAKE_ASM_MASM_COMPILER "uasm")
    set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}-gcc")
    set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}-g++")
endif()

project(YimMenu CXX ASM_MASM)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")


# Fetch modules
message("\nFetching modules")
include(scripts/minhook.cmake)
include(scripts/g3log.cmake)
include(scripts/pugixml.cmake)
include(scripts/json.cmake)
include(scripts/fmt.cmake)

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
set_property(TARGET YimMenu PROPERTY CXX_STANDARD 20)

source_group(TREE "${SRC_DIR}" PREFIX "YimMenu" FILES "${SRC_MAIN}" )

target_include_directories(YimMenu PRIVATE 
    "${SRC_DIR}"
    "${json_SOURCE_DIR}/single_include"
    "${gtav_classes_SOURCE_DIR}"
    "${minhook_SOURCE_DIR}/include"
    "${imgui_SOURCE_DIR}"
)


target_link_libraries(YimMenu PRIVATE fmt)

target_precompile_headers(YimMenu PRIVATE "${SRC_DIR}/common.hpp")
target_link_libraries(YimMenu PRIVATE pugixml minhook g3log imgui d3dcompiler dwmapi )

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # Warnings as errors
    set_property(TARGET YimMenu PROPERTY COMPILE_WARNING_AS_ERROR ON)
else()
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
