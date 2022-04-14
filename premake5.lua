workspace "Solar"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Solar/vendor/GLFW/include"

--Include for other premake lua files.
include "Solar/vendor/GLFW"

project "Solar"
    location "Solar"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "slpch.h"
    pchsource "Solar/source/slpch.cpp"

    files
    {
        "%{prj.name}/source/**.h",
        "%{prj.name}/source/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/source",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:Windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "SL_PLATFROM_WINDOWS",
            "SL_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines
        {
            "SL_DEBUG",
            "SL_ENABLE_ASSERTS"
        }
        buildoptions "/MDd"
        symbols "On"

    
    filter "configurations:Release"
    defines
    {
        "SL_RELEASE"
    }
    buildoptions "/MD"
    optimize "On"

    filter "configurations:Dist"
    defines
    {
        "SL_DIST"
    }
    buildoptions "/MD"
    optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/source/**.h",
        "%{prj.name}/source/**.cpp"
    }

    includedirs
    {
        "Solar/vendor/spdlog/include",
        "Solar/source"
    }

    links
    {
        "Solar"
    }

    filter "system:Windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

    defines
    {
        "SL_PLATFROM_WINDOWS"
    }

    filter "configurations:Debug"
    defines
    {
        "SL_DEBUG"
    }
    buildoptions "/MDd"
    symbols "On"
    
    filter "configurations:Release"
    defines
    {
        "SL_RELEASE"
    }
    buildoptions "/MD"
    optimize "On"

    filter "configurations:Dist"
    defines
    {
        "SL_DIST"
    }
    buildoptions "/MD"
    optimize "On"
