include "Dependencies.lua"
include "ShaderCompiler.lua"

group "Dependencies"
    include "vendor/fmt"
    include "vendor/imgui"
    include "vendor/spdlog"
group ""

group "Clean"
project "CleanShaderOutputs"
    kind "Utility"

    postbuildcommands {
        "{RMDIR} assets/shaders"
    }
group ""

project "DestinyEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    files { "src/**.hpp", "src/**.cpp", "include/**.hpp", "src/Shaders/**.glsl" }

    includedirs { 
        "include", 
        "src",
        "%{IncludeDir.fmt}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.utfcpp}"
    }

    links {
        "fmt",
        "imgui",
        "spdlog"
    }

    rules {
        "ShaderCompiler"
    }

    postbuildcommands {
        "{COPY} assets ../bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/Sandbox/assets"
    }