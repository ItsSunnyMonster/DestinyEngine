cmake_minimum_required(VERSION 3.21.1)

project(DestinyEngine)

set(CMAKE_CXX_STANDARD 20)

add_library(DestinyEngine STATIC 
    "src/Destiny/Application.cpp" 
    "include/DestinyEngine.hpp" 
    "src/Destiny/EntryPoint.hpp" 
    "src/Destiny/Application.hpp"
    "src/Destiny/Log.cpp"
    "src/Destiny/Log.hpp"
    "src/Destiny/Events/Event.hpp"
    "src/Destiny/Macros.hpp"
    "src/Destiny/Events/WindowEvent.hpp"
    "src/Destiny/Events/KeyboardEvent.hpp"
    "src/Destiny/KeyCodes.hpp"
    "src/Destiny/Events/MouseEvent.hpp"
    "src/Destiny/MouseCodes.hpp"
    "src/dtpch.hpp" 
    "src/Destiny/Events/EventListener.hpp"
    "src/Destiny/Window.hpp"
    "src/Destiny/Platform/Windows/WindowsWindow.cpp"
    "src/Destiny/Platform/Windows/WindowsWindow.hpp"
)

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

target_precompile_headers(DestinyEngine PUBLIC src/dtpch.hpp)