require "export-compile-commands"

workspace "OpenGL Engine"
filename "Engine"
configurations{"Debug", "Release"}
location "../build/solution"
libdirs{"../deps/openal-soft/build/RelWithDebInfo", "../deps/glew-2.1.0/lib/Release/x64", "opengl32.lib", "../deps/glfw/build/src/RelWithDebInfo","../deps/freetype/release static/vs2015-2022/win64",} 

links {
  "glfw3",
  "opengl32",
}

includedirs {
  --GLAD
  "../deps/glad/include",
  --GLEW
  "../deps/glew-2.1.0/include",
  --GLFW
  "../deps/GLFW/include",
  --GLM
  "../deps/glm",
  --PX_Sched
  --"../deps/px",
  --Loguru
  --"../deps/loguru",
  --STB
  --"../deps/stb",
  --OpenAL
  "../deps/openal-soft/include/",
  --Imgui
  "../deps/imgui/",
  "../deps/imgui/backends/",
  --LUA
  --"../deps/Lua",
  --OBJ LOADER
  "../deps/OBJ-Loader/Source",
  --Fast_OBJ
  "../deps/fast_obj",
  --Minitrace
  "../deps/minitrace",
  --Include
  "../include",
  --Deps
  "../deps/",
  --freetype
  "../deps/freetype/include",
}

platforms {"Win64"}
startproject "Example1"

----------------------------------------------------------
--------------------PROJECT ENGINE------------------------
----------------------------------------------------------
project "Engine"
  kind "StaticLib"
  language "C++"
  cppdialect "C++20"  -- Establece el est�ndar de C++ a C++20
  location "../build/engine"
  targetdir"../data/engine"
  objdir "../build/engine"
  libdirs ""

  files {
    "../src/engine/*.cpp",
    "../src/engine/components/*.cpp",
    "../include/engine/*.h",
    "../include/engine/components/*.h",

    "../deps/glfw/glfw/src/*.c",
    "../deps/glfw/src/win32_*.c",
    "../deps/glfw/src/context.c",
    "../deps/glfw/src/egl_context.c",
    "../deps/glfw/src/wgl_context.c",
    "../deps/glfw/src/init.c",
    "../deps/glfw/src/input.c",
    "../deps/glfw/src/monitor.c",
    "../deps/glfw/src/osmesa_context.c",
    "../deps/glfw/src/window.c",
    "../deps/glfw/src/vulkan.c",

    "../deps/glm/glm/**.hpp",
    "../deps/glm/glm/**.h",
    "../deps/glm/glm/**.c",
    "../deps/glm/glm/**.cpp",
    "../deps/glm/glm/**.inl",

    "../deps/glad/src/*.c",
    "../deps/glad/include/*.h",

    "../deps/loguru/*.hpp",
    "../deps/loguru/*.cpp",

    "../deps/px/*.h",

    "../deps/openal-soft/include/*.h",
    "../deps/openal-soft/OpenAL/include/AL/*.h",

    "../deps/imgui/*.c",
    "../deps/imgui/*.cc",
    "../deps/imgui/*.cpp",
    "../deps/imgui/backends/imgui_impl_glfw.cpp",
    "../deps/imgui/backends/imgui_impl_opengl3.cpp",
    "../deps/imgui/*.h",
    "../deps/imgui/guizmo/*.h",
    "../deps/imgui/guizmo/*.cpp",

    "../deps/lua/*.c",
    "../deps/lua/*.h",
    "../deps/lua/*.hpp",

    "../deps/OBJ_Loader/OBJ_Loader/*.h",

    "../deps/minitrace/minitrace.c",
    "../deps/minitrace/minitrace.h",

    "../deps/fast_obj/fast_obj.h",
    "../deps/fast_obj/fast_obj.c",
  }

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
    defines { "_WIN32", "_GLFW_WIN32", "_GLFW_WGL", "_GLFW_USE_OPENGL", "_GLFW_OPENGL_LIBRARY", "MTR_ENABLED"}

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
  cppdialect "C++20"  -- Establece el est�ndar de C++ a C++20
  location "../build/example1"
  targetdir "../bin/example/example1"
  libdirs { "../data/engine" }
  links { "Engine" }

  files {   
    "../src/examples/example1/*.cpp",
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
    defines { "_WIN32", "_GLFW_WIN32", "_GLFW_WGL", "_GLFW_USE_OPENGL", "_GLFW_OPENGL_LIBRARY"}

project "Example1"
  configmap{
    ["Development"] = "Debug",
    ["Profile"] = "Release"
  }
