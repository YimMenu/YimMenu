cmake_minimum_required(VERSION 3.20)

project(BigBaseV2 CXX ASM_MASM)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/BigBaseV2/src")
set(IMGUI_DIR "${PROJECT_SOURCE_DIR}/vendor/ImGui")


# MinHook
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/MinHook minhook)
set_property(TARGET minhook PROPERTY CXX_STANDARD 23)


# pugixml
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/pugixml pugixml)
set_property(TARGET pugixml PROPERTY CXX_STANDARD 23)


# g3log
set(ADD_FATAL_EXAMPLE OFF CACHE INTERNAL "")
set(INSTALL_G3LOG OFF CACHE INTERNAL "")
set(G3_SHARED_LIB OFF CACHE INTERNAL "")
set(G3_SHARED_RUNTIME OFF CACHE INTERNAL "")

add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/g3log g3log)
set_property(TARGET g3log PROPERTY CXX_STANDARD 23)


# ImGui
file(GLOB SRC_IMGUI
    "${IMGUI_DIR}/*.cpp"
	${IMGUI_DIR}/backends/imgui_impl_win32.cpp
    ${IMGUI_DIR}/backends/imgui_impl_dx11.cpp
	${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp
)
add_library(ImGui ${SRC_IMGUI})

target_include_directories(ImGui PRIVATE
	${IMGUI_DIR}
	${IMGUI_DIR}/backends
	${IMGUI_DIR}/misc
)
set_property(TARGET ImGui PROPERTY CXX_STANDARD 23)


# BigBaseV2
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

source_group(TREE "${SRC_DIR}" PREFIX "src" FILES ${SRC_MAIN} )

target_include_directories(BigBaseV2 PRIVATE 
    "${SRC_DIR}"
    "${PROJECT_SOURCE_DIR}/vendor"
    "${PROJECT_SOURCE_DIR}/vendor/g3log/src"
    "${PROJECT_SOURCE_DIR}/vendor/GTAV-Classes"
    "${PROJECT_SOURCE_DIR}/vendor/ImGui"
    "${PROJECT_SOURCE_DIR}/vendor/json/single_include"
    "${PROJECT_SOURCE_DIR}/vendor/MinHook/include"
    "${PROJECT_SOURCE_DIR}/vendor/pugixml/src"
)

target_precompile_headers(BigBaseV2 PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${SRC_DIR}/common.hpp>")
target_link_libraries(BigBaseV2 PRIVATE pugixml minhook g3log ImGui d3dcompiler)

add_compile_definitions(BigBaseV2 
	"_CRT_SECURE_NO_WARNINGS"
	"NOMINMAX"
	"WIN32_LEAN_AND_MEAN"
)
