workspace "Blimp"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Blimp"
    location "Blimp"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "%{prj.name}/external/spdlog/include",
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        
        defines 
        {
            "BLIMP_PLATFORM_WINDOWS",
            "BLIMP_BUILD_DLL"
        }

        postbuildcommands 
        {
            ("{MKDIR} ../bin/" .. outputdir .. "/Sandbox"),
            ("{COPYFILE} %{cfg.buildtarget.abspath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "BLIMP_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "BLIMP_RELEASE"
        symbols "On"
    
    filter "configurations:Dist"
        defines "BLIMP_DIST"
        symbols "On"

    -- filters { "system:windows", "configurations:Release" }
    --     buildoptions "/MT"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("int/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs 
    {
        "Blimp/external/spdlog/include",
        "Blimp/src",
    }
    
    links 
    {
        "Blimp"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        
        defines 
        {
            "BLIMP_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "BLIMP_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "BLIMP_RELEASE"
        symbols "On"
    
    filter "configurations:Dist"
        defines "BLIMP_DIST"
        symbols "On"
