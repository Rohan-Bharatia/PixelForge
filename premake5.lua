workspace "PixelForge"
    startproject "PixelForgeGL"
    architecture "x64"

    configuarations
    {
        "Debug",
        "Release"
    }

project "PixelForgeGL"
    location "PixelForgeGL"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    flags
    {
        "FatalWarnings"
    }
