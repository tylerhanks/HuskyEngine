workspace "HuskyEngine"
    architecture "x86_64"
    startproject "SandboxGame"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

group "submodules"
    include "Husky/vendor/imgui"

group ""

project "Husky"
    location "Husky"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/imgui_sdl/imgui_sdl.h",
        "%{prj.name}/vendor/imgui_sdl/imgui_sdl.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/SDL2/include",
        "%{prj.name}/vendor/imgui",
        "%{prj.name}/vendor/imgui_sdl"
    }

    libdirs
    {
        "%{prj.name}/vendor/SDL2/lib/x64"
    }

    links
    {
        "SDL2.lib",
        "SDL2main.lib",
        "ImGui"
    }

    filter "system:windows"
        systemversion "latest"

        postbuildcommands
        {
            "{COPY} %{prj.location}vendor\\SDL2\\lib\\x64\\SDL2.dll %{wks.location}bin\\%{cfg.buildcfg}\\SandboxGame"
        }

    filter "configurations:Debug"
        defines "HS_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "HS_RELEASE"
        runtime "Release"
        optimize "on"

project "SandboxGame"
    location "SandboxGame"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
    objdir "bin-int/%{cfg.buildcfg}/%{prj.name}"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Husky/vendor/SDL2/include",
        "Husky/src"
    }

    libdirs
    {
        "Husky/vendor/SDL2/lib/x64"
    }

    links
    {
        "Husky"
    }

    filter "configurations:Debug"
        defines "HS_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "HS_RELEASE"
        runtime "Release"
        optimize "on"
