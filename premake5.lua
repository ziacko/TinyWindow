if os.host() == "linux" then
    local cmake = require "cmake"
    cmake.workspace_directory = _SCRIPT_DIR
    cmake.write_settings = { CMAKE_CURRENT_SOURCE_DIR = _SCRIPT_DIR }

    location "proj/make"
elseif os.host() == "windows" then
    location "proj/vs"
end


local RD = path.getabsolute("./") .. "/"

includedirs(RD .. "Include/")
includedirs(RD .. "Example")
includedirs(RD .. "Example/include")

intermediateDir = RD .. "Intermediate"

local sources = {
    RD .. "Example/Example.cpp"
}
filter {"system:linux"}
    links { "GL", "X11", "Xrandr", "Xinerama" }

solution "TinyWindow"
    configurations { "Debug", "Release" }
    filter "system:linux"
        platforms { "Linux" }
    filter "system:windows"
        platforms { "Windows" }
    architecture "x64"

    project "Example"
        kind "ConsoleApp"
        language "C++"
        files { sources }
        cppdialect "C++20"
        toolset "clang"
        
    filter {"configurations:Debug"}
    defines {"DEBUG"}
    symbols "On"
    targetname "Example_Debug"
    optimize "Off"
    targetdir "bin/Debug"
    debugdir "bin/Debug"

    filter {"configurations:Release"}
    defines {}
    symbols "off"
    optimize "on"
    targetname "Example"
    targetdir "bin/Release"
    debugdir "bin/Release"


    filter {"platforms:Win64"}
    system "Windows"
    filter {"platforms:Linux"}
    system "Linux"
