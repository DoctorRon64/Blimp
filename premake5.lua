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

project "Blimp"
    location "Blimp"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "On"

    targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/int/" .. outputdir .. "/%{prj.name}")

    pchheader "pch.h" 
    pchsource "Blimp/src/pch.cpp"

    files
    {
        "Blimp/src/**.h",
        "Blimp/src/**.cpp"
    }

    includedirs
    {
        "Blimp/src",
        "Blimp/libs/spdlog/include"
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
        "Sandbox/src/**.h",
        "Sandbox/src/**.cpp"
    }

    includedirs
    {
        "Blimp/src",
        "Blimp/libs/spdlog/include"
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
