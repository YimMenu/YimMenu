cmake_minimum_required(VERSION 3.20)

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
include(scripts/cpr.cmake)
include(scripts/zydis.cmake)
include(scripts/lua.cmake)
include(scripts/imgui.cmake)
message("\nFetching custom modules")
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

if (MSVC)
  add_compile_options(/bigobj)
  add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
else ()
  add_compile_options(-Wa,-mbig-obj)
endif ()

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
target_link_libraries(YimMenu PRIVATE pugixml minhook AsyncLogger dbghelp imgui cpr Zydis lua_static)

# Warnings as errors
set_property(TARGET YimMenu PROPERTY COMPILE_WARNING_AS_ERROR ON)

add_compile_definitions(YimMenu 
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX"
    "WIN32_LEAN_AND_MEAN"
)

find_package(Python3 COMPONENTS Interpreter)
if(Python3_FOUND)
    set(SETTINGS_HPP_FILE "${SRC_DIR}/core/settings.hpp")
    set(SETTINGS_JSON_GEN_PY_SCRIPT "${SRC_DIR}/core/settings_json_serde_gen.py")
    set(SETTINGS_JSON_GEN_PY_SCRIPT_DUMMY_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/dummy_settings_json_output.txt")

    add_custom_command(
        OUTPUT ${SETTINGS_JSON_GEN_PY_SCRIPT_DUMMY_OUTPUT}
        COMMAND ${Python3_EXECUTABLE} ${SETTINGS_JSON_GEN_PY_SCRIPT} ${SETTINGS_HPP_FILE}
        DEPENDS ${SETTINGS_HPP_FILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM
    )

    add_custom_target(
        settings_json_gen ALL
        COMMENT "Running python settings.hpp json macro generator if settings.hpp was modified."
        DEPENDS ${SETTINGS_JSON_GEN_PY_SCRIPT_DUMMY_OUTPUT}
    )
else()
    message("Not generating settings.hpp json macros, Python not found.")
endif()
