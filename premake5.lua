workspace "GEngine2"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder(solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "GEngine2/vendor/GLFW/include"

--include premake.lua file of glfw
include "GEngine2/vendor/GLFW"

project "GEngine2"
    location "GEngine2"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "gepch.h"
    pchsource "GEngine2/scr/gepch.cpp"

    files
    {
        "%{prj.name}/scr/**.h",
        "%{prj.name}/scr/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/scr",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    defines
    {
        "GE_PLATFORM_WINDOWS",
        "GE_BUILD_DLL"
    }

    postbuildcommands
    {
        ("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir .."/Sandbox")
    }

    filter "configurations:Debug"
        defines "GE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "GE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "GE_DIST"
        optimize "On"

project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/scr/**.h",
        "%{prj.name}/scr/**.cpp"
    }

    includedirs
    {
        "GEngine2/vendor/spdlog/include",
        "GEngine2/scr"
    }

    links
    {
        "GEngine2"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    defines
    {
        "GE_PLATFORM_WINDOWS"
    }

    filter "configurations:Debug"
        defines "GE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "GE_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "GE_DIST"
        optimize "On"
