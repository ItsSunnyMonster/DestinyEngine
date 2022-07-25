cmake_minimum_required(VERSION 3.21.1)

project(Sandbox)

set(SOURCE_FILES src/SandboxApp.cpp)

add_executable(Sandbox ${SOURCE_FILES})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_sources(Sandbox PRIVATE resources/manifest.rc)
endif()
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR MSVC)
    target_sources(Sandbox PRIVATE resources/manifest.manifest)
endif()

set_target_properties(
    Sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}"
                       RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}"
                       RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_BINARY_DIR}"
                       RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_BINARY_DIR}"
)

set_target_properties(Sandbox PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>)
set_property(TARGET Sandbox PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(Sandbox DestinyEngine)