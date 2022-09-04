cmake_minimum_required(VERSION 3.21.1)

set(CMAKE_CONFIGURATION_TYPES "Debug;RelWithDebInfo;Release" CACHE STRING "" FORCE)

set(SOURCE_FILES 
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
    "src/Destiny/Renderer/Buffer.hpp"
    "src/Destiny/Renderer/Buffer.cpp"
    "src/Destiny/Platform/D3D11/D3D11Buffer.hpp"
    "src/Destiny/Platform/D3D11/D3D11Buffer.cpp"
)

add_library(DestinyEngine 
    ${SOURCE_FILES}
)

set_target_properties(
    DestinyEngine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}"
                             ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}"
                             ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_BINARY_DIR}"
                             ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_BINARY_DIR}"
)

set(SHADER_FILES 
    "src/Shaders/test_shader.glsl")
set(TARGET_SHADER_PATH assets/shaders)

if (WIN32)
    target_compile_definitions(DestinyEngine PUBLIC DT_PLATFORM_WINDOWS)
    target_link_libraries(DestinyEngine PUBLIC d3d11.lib Comctl32.lib D3DCompiler.lib dwmapi.lib)

    add_custom_target(Shaders)
    set_target_properties(Shaders PROPERTIES FOLDER "Shaders")
    add_custom_target(CleanShaders)
    set_target_properties(CleanShaders PROPERTIES FOLDER "Shaders")
    add_dependencies(DestinyEngine Shaders)

    foreach(FILE ${SHADER_FILES})
        get_filename_component(FILE_WE ${FILE} NAME_WE)
        add_custom_command(TARGET Shaders
                           COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/vendor/shader-compiling/fxc.exe /nologo /Emain /Tvs_5_0 $<$<CONFIG:Debug>:/Od> /Zi /Fo ${TARGET_SHADER_PATH}/hlsl/${FILE_WE}_vs.cso /Fd ${CMAKE_CURRENT_BINARY_DIR}/${FILE_WE}_vs.pdb ${TARGET_SHADER_PATH}/hlsl/${FILE_WE}_vs.hlsl
                           COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/vendor/shader-compiling/fxc.exe /nologo /Emain /Tps_5_0 $<$<CONFIG:Debug>:/Od> /Zi /Fo ${TARGET_SHADER_PATH}/hlsl/${FILE_WE}_fs.cso /Fd ${CMAKE_CURRENT_BINARY_DIR}/${FILE_WE}_fs.pdb ${TARGET_SHADER_PATH}/hlsl/${FILE_WE}_fs.hlsl
                           COMMAND_EXPAND_LISTS
                           MAIN_DEPENDENCY ${FILE}
                           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                           COMMENT "Compiling HLSL shader ${TARGET_SHADER_PATH}/hlsl/${FILE_WE}.hlsl"
                           VERBATIM)
        add_custom_command(TARGET CleanShaders
                           COMMAND ${CMAKE_COMMAND} -E rm -f ${TARGET_SHADER_PATH}/hlsl/${FILE_WE}_fs.cso 
                           COMMAND ${CMAKE_COMMAND} -E rm -f ${TARGET_SHADER_PATH}/hlsl/${FILE_WE}_fs.hlsl.json
                           COMMAND ${CMAKE_COMMAND} -E rm -f ${TARGET_SHADER_PATH}/hlsl/${FILE_WE}_vs.cso
                           COMMAND ${CMAKE_COMMAND} -E rm -f ${TARGET_SHADER_PATH}/hlsl/${FILE_WE}_vs.hlsl.json
                           MAIN_DEPENDENCY ${FILE}
                           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                           COMMENT "Deleting compiled shader output file ${TARGET_SHADER_PATH}/hlsl/${FILE_WE}"
                           VERBATIM)
        add_custom_command(TARGET Shaders
                           PRE_BUILD
                           COMMAND ${CMAKE_COMMAND} -E make_directory ${TARGET_SHADER_PATH}/hlsl
                           COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/vendor/shader-compiling/glslcc.exe ${FILE} --output=${TARGET_SHADER_PATH}/hlsl/${FILE_WE}.hlsl --lang=hlsl --reflect 
                           COMMENT "Generate HLSL from ${FILE}"
                           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                           VERBATIM)
        add_custom_command(TARGET Shaders
                           POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E rm ${TARGET_SHADER_PATH}/hlsl/${FILE_WE}_vs.hlsl
                           COMMAND ${CMAKE_COMMAND} -E rm ${TARGET_SHADER_PATH}/hlsl/${FILE_WE}_fs.hlsl
                           COMMENT "Generate HLSL ${FILE}"
                           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                           VERBATIM)
    endforeach(FILE)

    add_custom_target(CopyAssets COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/Sandbox/assets")
    set_target_properties(CopyAssets PROPERTIES FOLDER "Commands")
    add_dependencies(DestinyEngine CopyAssets)
endif()
if (UNIX AND NOT APPLE)
    target_compile_definitions(DestinyEngine PUBLIC DT_PLATFORM_LINUX)
    message(FATAL_ERROR "LINUX IS NOT SUPPORTED!")
endif()
if (APPLE)
    target_compile_definitions(DestinyEngine PUBLIC DT_PLATFORM_MACOS)
    message(FATAL_ERROR "MACOS IS NOT SUPPORTED!")
endif()
if (UNIX)
    target_compile_definitions(DestinyEngine PUBLIC DT_PLATFORM_UNIX)
    message(FATAL_ERROR "UNIX IS NOT SUPPORTED!")
endif()

target_compile_definitions(DestinyEngine PUBLIC
  $<$<CONFIG:Debug>:DT_DEBUG>
  $<$<NOT:$<CONFIG:Debug>>:DT_RELEASE>
)

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/utfcpp)
add_subdirectory(vendor/fmt)

set_target_properties(spdlog imgui fmt PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(spdlog PROPERTIES FOLDER "Dependencies")
set_target_properties(imgui PROPERTIES FOLDER "Dependencies")
set_target_properties(fmt PROPERTIES FOLDER "Dependencies")

target_link_libraries(DestinyEngine PUBLIC spdlog::spdlog imgui utf8::cpp fmt::fmt)

target_include_directories(DestinyEngine INTERFACE ./include)
target_include_directories(DestinyEngine PUBLIC ./src ./vendor/spdlog/include ./vendor/glm ./vendor/include)

target_precompile_headers(DestinyEngine PUBLIC src/dtpch.hpp)