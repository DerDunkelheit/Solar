workspace "Solar"
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
IncludeDir["GLFW"] = "Solar/vendor/GLFW/include"
IncludeDir["Glad"] = "Solar/vendor/Glad/include"
IncludeDir["ImGui"] = "Solar/vendor/imgui"
IncludeDir["ImGuiBackends"] = "Solar/vendor/imgui/backends"
IncludeDir["glm"] = "Solar/vendor/glm"
IncludeDir["stb_image"] = "Solar/vendor/stb_image"

--Include for other premake lua files.
group "Dependencies"
    include "Solar/vendor/GLFW"
    include "Solar/vendor/Glad"
    include "Solar/vendor/imgui"
group ""

project "Solar"
    location "Solar"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "slpch.h"
    pchsource "Solar/source/slpch.cpp"

    files
    {
        "%{prj.name}/source/**.h",
        "%{prj.name}/source/**.cpp",
        "%{prj.name}/vendor/glm/**.hpp",
        "%{prj.name}/vendor/glm/**.inl",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/source",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.ImGuiBackends}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:Windows"
        systemversion "latest"

        defines
        {
            "SL_PLATFROM_WINDOWS",
            "SL_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
        }

    filter "configurations:Debug"
        defines
        {
            "SL_DEBUG",
            "SL_ENABLE_ASSERTS"
        }
        runtime "Debug"
        symbols "on"

    
    filter "configurations:Release"
    defines
    {
        "SL_RELEASE"
    }
    runtime "Release"
    optimize "on"

    filter "configurations:Dist"
    defines
    {
        "SL_DIST"
    }
    runtime "Release"
    optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

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
        "Solar/source",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "Solar"
    }

    filter "system:Windows"
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
    runtime "Debug"
    symbols "on"
    
    filter "configurations:Release"
    defines
    {
        "SL_RELEASE"
    }
    runtime "Release"
    optimize "on"

    filter "configurations:Dist"
    defines
    {
        "SL_DIST"
    }
    runtime "Release"
    optimize "on"
