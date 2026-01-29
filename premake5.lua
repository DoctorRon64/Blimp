workspace "Blimp"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Blimp/libs/GLFW/include"

include "Blimp/libs/GLFW"

project "Blimp"
    location "Blimp"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "On"

    targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h" 
    pchsource "{prj.name}/src/pch.cpp"

    files
    {
        "{prj.name}/src/**.h",
        "{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "{prj.name}/src",
        "{prj.name}/libs/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links{
        "GLFW"
        -- "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"
        buildoptions { "/utf-8" }
        defines
        {
            "BLIMP_PLATFORM_WINDOWS",
            "BLIMP_STATIC"
        }

    filter "system:linux"
        defines
        {
            "BLIMP_PLATFORM_LINUX",
            "BLIMP_STATIC"
        }

    filter "configurations:Debug"
        defines "BLIMP_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "BLIMP_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "BLIMP_DIST"
        optimize "Full"

    filter {}

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "On"

    targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "{prj.name}/src/**.h",
        "{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Blimp/src",
        "Blimp/libs/spdlog/include",
    }

    links
    {
        "Blimp"
    }

    filter "system:windows"
        systemversion "latest"
        buildoptions { "/utf-8" }
        defines
        {
            "BLIMP_PLATFORM_WINDOWS",
            "BLIMP_STATIC"
        }

    filter "system:linux"
        defines
        {
            "BLIMP_PLATFORM_LINUX",
            "BLIMP_STATIC"
        }

    filter "configurations:Debug"
        defines "BLIMP_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "BLIMP_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "BLIMP_DIST"
        optimize "Full"

    filter {}
