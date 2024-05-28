workspace "OpenGL Engine"
filename "Engine"
configurations{"Debug", "Release"}
location "../build/solution"
libdirs{"../deps/openAL/libs/Win64"}
includedirs { 
--Imgui
"../deps/imgui",
--Minitrace
"../deps/minitrace",
--OpenAL
"../deps/openAL/include/AL",
--PXsched
"../deps/px_sched",
--TinyOBJLoader
"../deps/tinyObjLoader",
--GLFW
"../deps/glfw/include",
--GLM
"../deps/glm",
--OpenGL
"../deps/openGL/include",
--Loguru
"../deps/loguru/",
--Guizmo
"../deps/guizmo/",
--Engine
"../include/engine"
}
platforms { "Win64" }
startproject "Example1"

----------------------------------------------------------
--------------------PROJECT ENGINE------------------------
----------------------------------------------------------
project "Engine"
  kind "StaticLib"

  language "C++"
  location "../build/engine"
  targetdir"../data/engine"
  objdir "../build/engine"

  files { "..deps/**.c",
          "..deps/**.cc",
          "..deps/**.cpp",
          "..deps/**.h",
          "..deps/**.hpp",
	        "../src/engine/**.c",
	        "../src/engine/**.cc",
	        "../src/engine/**.cpp",
	        "../include/engine/*.h",
	        "../include/engine/*.hpp"}

filter "configurations:Debug"
    defines{"DEBUG"}
    symbols "On"

filter "configurations:Release"
    defines{"NDEBUG"}
    symbols "Off"
    optimize "On"

filter{"platforms:Win64"}
    system "windows"
    architecture "x64"
    defines { "_WIN64", "_GLFW_WIN64", "_GLFW_WGL", "_GLFW_USE_OPENGL", "_GLFW_OPENGL_LIBRARY", "MTR_ENABLED"}

project "Engine"
    configmap{
        ["Development"] = "Debug",
        ["Profile"] = "Release"
    }


----------------------------------------------------------
--------------------PROJECT WINDOW------------------------
----------------------------------------------------------
project "Example1"
kind "ConsoleApp"
language "C++"
location "../build/example1"
targetdir "../bin/example/example1"
  libdirs { "../data/engine" }
links { "engine" }

files {   "../src/examples/example1/*.cpp",
  "../include/engine/*.h"
}

removefiles {}

filter "configurations:Debug"
    defines{"DEBUG"}
    symbols "On"

filter "configurations:Release"
    defines{"NDEBUG"}
    symbols "Off"
    optimize "On"

filter{"platforms:Win64"}
    system "windows"
    architecture "x64"
    defines { "_WIN64", "_GLFW_WIN64", "_GLFW_WGL", "_GLFW_USE_OPENGL", "_GLFW_OPENGL_LIBRARY", "MTR_ENABLED"}

project "Example1"
    configmap{
        ["Development"] = "Debug",
        ["Profile"] = "Release"
    }
