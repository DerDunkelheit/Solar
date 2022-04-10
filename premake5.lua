workspace "Solar"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
        "%{prj.name}/source"
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
            "SL_DEBUG"
        }
        symbols "On"

    
    filter "configurations:Release"
    defines
    {
        "SL_RELEASE"
    }
    optimize "On"

    filter "configurations:Dist"
    defines
    {
        "SL_DIST"
    }
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
    symbols "On"
    
    filter "configurations:Release"
    defines
    {
        "SL_RELEASE"
    }
    optimize "On"

    filter "configurations:Dist"
    defines
    {
        "SL_DIST"
    }
    optimize "On"
