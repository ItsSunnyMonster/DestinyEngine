workspace "DestinyEngine"
    configurations { "Debug", "Release", "Dist" }
    system "Windows"
    architecture "x64"
    targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
    objdir "bin-int/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
    debugdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"
    startproject "Sandbox"

-- if compiler is MSVC
filter "toolset:msc*"
    buildoptions { "/utf-8", "/Zc:__cplusplus" }

filter "system:Windows"
    system "windows"
    staticruntime "On"
    systemversion "latest"
    defines { "DT_PLATFORM_WINDOWS" }

filter "configurations:Debug"
    defines { "DT_DEBUG" }
    symbols "On"

filter "configurations:Release"
    defines { "DT_RELEASE" }
    optimize "On"
    symbols "On"

filter "configurations:Dist"
    defines { "DT_DIST" }
    optimize "On"

newoption {
    trigger = "build-dll",
    description = "Builds Destiny Engine as a DLL instead of a static library."
}

filter "options:build-dll"
    defines { "DT_DLL" }

include "DestinyEngine"
include "Sandbox"