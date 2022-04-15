cmake_minimum_required(VERSION 3.21.1)

project(DestinyEngine)

set(CMAKE_CXX_STANDARD 20)

set(UNIVERSAL_FILES src/Destiny/Application.cpp include/DestinyEngine.hpp src/Destiny/EntryPoint.hpp src/Destiny/Application.hpp src/Destiny/Log.cpp src/Destiny/Log.hpp)

add_library(DestinyEngine STATIC ${UNIVERSAL_FILES})

if (WIN32)
    target_compile_definitions(DestinyEngine PUBLIC DT_PLATFORM_WINDOWS)
endif()
if (UNIX)
    target_compile_definitions(DestinyEngine PUBLIC DT_PLATFORM_UNIX)
endif()
if (UNIX AND NOT APPLE)
    target_compile_definitions(DestinyEngine PUBLIC DT_PLATFORM_LINUX)
endif()
if (APPLE)
    target_compile_definitions(DestinyEngine PUBLIC DT_PLATFORM_MACOS)
endif()

set(CMAKE_CONFIGURATION_TYPES Debug Release)

target_compile_definitions(DestinyEngine PRIVATE
  $<$<CONFIG:Debug>:DT_DEBUG>
  $<$<CONFIG:Release>:DT_RELEASE>
)

add_subdirectory(vendor/spdlog)

target_link_libraries(DestinyEngine PUBLIC spdlog::spdlog)

target_include_directories(DestinyEngine INTERFACE ./include)
target_include_directories(DestinyEngine PUBLIC ./src ./vendor/spdlog/include)