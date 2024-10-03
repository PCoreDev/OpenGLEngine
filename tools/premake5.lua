workspace "OpenGL Engine"
filename "Engine"
configurations{"Debug", "Release"}
location "../build/solution"
libdirs{"../deps/openAL/libs/Win64"}
includedirs {
--GLFW
"../deps/GLFW/include",
"../include",
--GLM
"../deps/GLM",
--OpenGL
"../deps/OpenGL/OpenGL/include",
--PX_Sched
"../deps/PX_Sched/",
--Loguru
"../deps/loguru/",
--STB
"../deps/stb_image/",
--OpenAL
"../deps/openal-soft/",
--Imgui
"../deps/imgui/",
--LUA
"../deps/Lua",
--OBJ LOADER (DELETE)
"../deps/OBJ_Loader",
--Guizmo
"../deps/Guizmo",
--Tiny OBJ
"../deps/tinyObjLoader",
--Minitrace
"../deps/minitrace"}

platforms { "Win32", "Win64", "Unix32", "Unix64", "MacOS" }
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
  libdirs ""

  files { "..deps/GLFW/glfw/src/*.c",
	        "../src/engine/*.cpp",
	        "../include/engine/*.h",
	        "../deps/GLFW/src/win32_*.c",
	        "../deps/GLFW/src/context.c",
	        "../deps/GLFW/src/egl_context.c",
	        "../deps/GLFW/src/wgl_context.c",
	        "../deps/GLFW/src/init.c",
	        "../deps/GLFW/src/input.c",
	        "../deps/GLFW/src/monitor.c",
	        "../deps/GLFW/src/osmesa_context.c",
	        "../deps/GLFW/src/window.c",
	        "../deps/GLFW/src/vulkan.c",
	        "../deps/GLM/glm/**.hpp",
	        "../deps/GLM/glm/**.h",
	        "../deps/GLM/glm/**.c",
	        "../deps/GLM/glm/**.cpp",
	        "../deps/GLM/glm/**.inl",
	        "../deps/OpenGL/OpenGL/src/*.c",
          "../deps/loguru/loguru/*.hpp",
          "../deps/loguru/loguru/*.cpp",
          "../deps/PX_Sched/px_sched/*.h",
          "../deps/openal-soft/include/*.h",
          "../deps/imgui/*.c",
          "../deps/imgui/*.cc",
          "../deps/imgui/*.cpp",
          "../deps/imgui/backends/imgui_impl_glfw.cpp",
          "../deps/imgui/backends/imgui_impl_opengl3.cpp",
          "../deps/imgui/*.h",
          "../deps/imgui/guizmo/*.h",
          "../deps/imgui/guizmo/*.cpp",
          "../deps/Guizmo/*.h",
          "../deps/Lua/*.c",
          "../deps/Lua/*.h",
          "../deps/Lua/*.hpp",
          "../deps/OBJ_Loader/OBJ_Loader/*.h",
          "../deps/openal-soft/OpenAL/include/AL/*.h",
          "../deps/tinyObjLoader/tinyObjLoader/*.h",
          "../deps/tinyObjLoader/tinyObjLoader/*.cc",
          "../deps/minitrace/minitrace.c",
          "../deps/minitrace/minitrace.h",
        }
filter "configurations:Debug"
    defines{"DEBUG"}
    symbols "On"

filter "configurations:Release"
    defines{"NDEBUG"}
    symbols "Off"
    optimize "On"

filter{"platforms:Win32"}
    system "windows"
    architecture "x86"
    defines { "_WIN32", "_GLFW_WIN32", "_GLFW_WGL", "_GLFW_USE_OPENGL", "_GLFW_OPENGL_LIBRARY", "MTR_ENABLED"}

filter{"platforms:Win64"}
    system "windows"
    architecture "x64"
    defines { "_WIN32", "_GLFW_WIN32", "_GLFW_WGL", "_GLFW_USE_OPENGL", "_GLFW_OPENGL_LIBRARY", "MTR_ENABLED"}

filter{"platforms:Unix32"}
    system "linux"
    architecture "x86"
    defines {"_GLFW_COCOA ", "_GLFW_X11", "_GLFW_WAYLAND", "_GLFW_OSMESA"}

filter{"platforms:Unix64"}
    system "linux"
    architecture "x64"
    defines {"_GLFW_COCOA ", "_GLFW_X11", "_GLFW_WAYLAND", "_GLFW_OSMESA"}

filter{"platforms:MacOS"}
    system "macosx"
    architecture "x64"
    defines { "_GLFW_COCOA"}

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
links { "Engine" }

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

filter{"platforms:Win32"}
    system "windows"
    architecture "x86"
    defines { "_WIN32", "_GLFW_WIN32", "_GLFW_WGL", "_GLFW_USE_OPENGL", "_GLFW_OPENGL_LIBRARY"}

filter{"platforms:Win64"}
    system "windows"
    architecture "x64"
    defines { "_WIN32", "_GLFW_WIN32", "_GLFW_WGL", "_GLFW_USE_OPENGL", "_GLFW_OPENGL_LIBRARY"}

filter{"platforms:Unix32"}
    system "linux"
    architecture "x86"

filter{"platforms:Win64"}
    system "linux"
    architecture "x64"

filter{"platforms:MacOS"}
    system "macosx"
    architecture "x64"

project "Example1"
    configmap{
        ["Development"] = "Debug",
        ["Profile"] = "Release"
    }
