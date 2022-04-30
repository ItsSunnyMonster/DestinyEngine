cmake_minimum_required(VERSION 3.21.1)

project(DestinyEngine)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES "src/Destiny/Application.cpp" 
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
    "src/Destiny/Layer/Layer.cpp"
    "src/Destiny/Layer/Layer.hpp"
    "src/Destiny/Layer/LayerStack.hpp"
    "src/Destiny/Layer/LayerStack.cpp"
    "src/Destiny/Renderer/GraphicsContext.hpp"
    "src/Destiny/Platform/D3D11/D3D11Context.hpp"
    "src/Destiny/Platform/D3D11/D3D11Context.cpp"
    "src/Destiny/ImGui/ImGuiLayer.cpp"
    "src/Destiny/ImGui/ImGuiLayer.hpp"
    "src/Destiny/ImGui/ImGuiBuild.cpp"
    "src/Destiny/Exception.hpp"
    "src/Destiny/Exception.cpp"
    "src/Destiny/Platform/Windows/Win32Exception.hpp"
    "src/Destiny/Platform/Windows/Win32Exception.cpp"
    "src/Destiny/Input.hpp"
    "src/Destiny/Platform/Windows/WindowsInput.hpp"
    "src/Destiny/Platform/Windows/WindowsInput.cpp"
    "src/Destiny/Platform/Windows/Win32KeyCodes.hpp"
	"src/Destiny/Platform/Windows/Win32MouseCodes.hpp"
    "src/Destiny/Platform/D3D11/D3D11Exception.hpp"
    "src/Destiny/Platform/D3D11/D3D11Exception.cpp"
    "src/Destiny/Platform/D3D11/DxgiInfoManager.hpp"
    "src/Destiny/Platform/D3D11/DxgiInfoManager.cpp"
)

add_library(DestinyEngine STATIC 
    ${SOURCE_FILES}
)

if (WIN32)
    target_compile_definitions(DestinyEngine PUBLIC DT_PLATFORM_WINDOWS)
    target_link_libraries(DestinyEngine PUBLIC d3d11.lib Comctl32.lib)
endif()
if (UNIX)
    target_compile_definitions(DestinyEngine PUBLIC DT_PLATFORM_UNIX)
    message(FATAL_ERROR "UNIX IS NOT SUPPORTED!")
endif()
if (UNIX AND NOT APPLE)
    target_compile_definitions(DestinyEngine PUBLIC DT_PLATFORM_LINUX)
    message(FATAL_ERROR "LINUX IS NOT SUPPORTED!")
endif()
if (APPLE)
    target_compile_definitions(DestinyEngine PUBLIC DT_PLATFORM_MACOS)
    message(FATAL_ERROR "MACOS IS NOT SUPPORTED!")
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

target_compile_definitions(DestinyEngine PUBLIC
  $<$<CONFIG:Debug>:DT_DEBUG>
  $<$<CONFIG:Release>:DT_RELEASE>
)

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/imgui)

set_target_properties(spdlog imgui PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(spdlog PROPERTIES FOLDER "Dependencies")
set_target_properties(imgui PROPERTIES FOLDER "Dependencies")

target_link_libraries(DestinyEngine PUBLIC spdlog::spdlog imgui)

target_include_directories(DestinyEngine INTERFACE ./include)
target_include_directories(DestinyEngine PUBLIC ./src ./vendor/spdlog/include ./vendor/glm)

target_precompile_headers(DestinyEngine PUBLIC src/dtpch.hpp)