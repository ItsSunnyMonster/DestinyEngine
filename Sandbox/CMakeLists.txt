cmake_minimum_required(VERSION 3.21.1)

project(Sandbox)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES src/SandboxApp.cpp)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

add_executable(Sandbox ${SOURCE_FILES})

target_link_libraries(Sandbox DestinyEngine)