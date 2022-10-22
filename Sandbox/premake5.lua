include "DestinyEngine/Dependencies.lua"

project "Sandbox"
    language "C++"
    cppdialect "C++20"

    files { "src/**.hpp", "src/**.cpp" }

    links { "DestinyEngine" }
    includedirs { 
        "../DestinyEngine/include", 
        "../DestinyEngine/src",
        "%{IncludeDir.fmt}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.utfcpp}"
    }

    filter "configurations:Debug"
        kind "ConsoleApp"

    filter "configurations:Release"
        kind "WindowedApp"

    filter "configurations:Dist"
        kind "WindowedApp"