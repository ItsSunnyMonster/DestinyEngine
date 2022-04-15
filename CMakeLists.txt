cmake_minimum_required(VERSION 3.21.1)

project(DestinyEngine)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(DestinyEngine)
add_subdirectory(Sandbox)

message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")