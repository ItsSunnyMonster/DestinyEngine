cmake_minimum_required(VERSION 3.21.1)
cmake_policy(SET CMP0091 NEW)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(DestinyEngine)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus /utf-8")
endif()



add_subdirectory(DestinyEngine)
add_subdirectory(Sandbox)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set_target_properties(DestinyEngine Sandbox PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

target_compile_definitions(Sandbox PUBLIC UNICODE _UNICODE)
target_compile_definitions(DestinyEngine PUBLIC UNICODE _UNICODE)