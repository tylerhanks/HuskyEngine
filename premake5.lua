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
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/SDL2/include"
    }

    libdirs
    {
        "%{prj.name}/vendor/SDL2/lib/x64"
    }

    links
    {
        "SDL2.lib",
        "SDL2main.lib"
    }

    filter "system:windows"
        systemversion "latest"

        postbuildcommands
        {
            "copy %{prj.location}\\vendor\\SDL2\\lib\\x64\\SDL2.dll %{wks.location}\\bin\\%{cfg.buildcfg}\\SandboxGame"
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
