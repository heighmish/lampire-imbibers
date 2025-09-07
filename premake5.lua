workspace "lampire-imbibers"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "lampire-imbibers"

project "lampire-imbibers"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/**.h", "src/**.cpp" }

    -- Include Raylib installed via Homebrew
    includedirs { "/usr/local/include", "/opt/homebrew/include" }
    libdirs { "/usr/local/lib", "/opt/homebrew/lib" }

    links { "raylib", "m", "pthread", "c++" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
