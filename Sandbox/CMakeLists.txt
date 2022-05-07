cmake_minimum_required(VERSION 3.21.1)

project(Sandbox)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES src/SandboxApp.cpp)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

add_executable(Sandbox ${SOURCE_FILES})
set_target_properties(Sandbox PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>)
set_property(TARGET Sandbox PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>")

target_link_libraries(Sandbox DestinyEngine)