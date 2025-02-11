# Define the minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Set the project name and languages
project(OpenGLEngine LANGUAGES CXX)

# Set the C++ standard explicitly
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Force 64-bit architecture when using Visual Studio
if (MSVC)
    set(CMAKE_GENERATOR_PLATFORM x64)
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Debug and Release configurations" FORCE)

# Include directories for dependencies and engine
include_directories(
    ${CMAKE_SOURCE_DIR}/deps/GLFW/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/deps/GLM
    ${CMAKE_SOURCE_DIR}/deps/OpenGL/OpenGL/include
    ${CMAKE_SOURCE_DIR}/deps/PX_Sched
    ${CMAKE_SOURCE_DIR}/deps/loguru
    ${CMAKE_SOURCE_DIR}/deps/stb_image
    ${CMAKE_SOURCE_DIR}/deps/openal-soft
    ${CMAKE_SOURCE_DIR}/deps/imgui
    ${CMAKE_SOURCE_DIR}/deps/Lua
    ${CMAKE_SOURCE_DIR}/deps/Guizmo
    ${CMAKE_SOURCE_DIR}/deps/tinyObjLoader
    ${CMAKE_SOURCE_DIR}/deps/minitrace
    ${CMAKE_SOURCE_DIR}/deps/glad/include
)

# Set library directories for linking
link_directories(
    ${CMAKE_SOURCE_DIR}/deps/openAL/libs/Win64
)

# Gather source files for Engine
file(GLOB ENGINE_SOURCES
    ${CMAKE_SOURCE_DIR}/deps/GLFW/glfw/src/*.c
    ${CMAKE_SOURCE_DIR}/src/engine/*.cpp
    ${CMAKE_SOURCE_DIR}/include/engine/*.h
    ${CMAKE_SOURCE_DIR}/deps/GLFW/src/win32_*.c
    ${CMAKE_SOURCE_DIR}/deps/GLFW/src/context.c
    ${CMAKE_SOURCE_DIR}/deps/GLFW/src/egl_context.c
    ${CMAKE_SOURCE_DIR}/deps/GLFW/src/wgl_context.c
    ${CMAKE_SOURCE_DIR}/deps/GLFW/src/init.c
    ${CMAKE_SOURCE_DIR}/deps/GLFW/src/input.c
    ${CMAKE_SOURCE_DIR}/deps/GLFW/src/monitor.c
    ${CMAKE_SOURCE_DIR}/deps/GLFW/src/osmesa_context.c
    ${CMAKE_SOURCE_DIR}/deps/GLFW/src/window.c
    ${CMAKE_SOURCE_DIR}/deps/GLFW/src/vulkan.c
    ${CMAKE_SOURCE_DIR}/deps/GLM/glm/**.hpp
    ${CMAKE_SOURCE_DIR}/deps/GLM/glm/**.h
    ${CMAKE_SOURCE_DIR}/deps/GLM/glm/**.c
    ${CMAKE_SOURCE_DIR}/deps/GLM/glm/**.cpp
    ${CMAKE_SOURCE_DIR}/deps/GLM/glm/**.inl
    ${CMAKE_SOURCE_DIR}/deps/OpenGL/OpenGL/src/*.c
    ${CMAKE_SOURCE_DIR}/deps/loguru/loguru/*.hpp
    ${CMAKE_SOURCE_DIR}/deps/loguru/loguru/*.cpp
    ${CMAKE_SOURCE_DIR}/deps/PX_Sched/px_sched/*.h
    ${CMAKE_SOURCE_DIR}/deps/openal-soft/include/*.h
    ${CMAKE_SOURCE_DIR}/deps/imgui/*.c
    ${CMAKE_SOURCE_DIR}/deps/imgui/*.cc
    ${CMAKE_SOURCE_DIR}/deps/imgui/*.cpp
    ${CMAKE_SOURCE_DIR}/deps/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/deps/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/deps/imgui/*.h
    ${CMAKE_SOURCE_DIR}/deps/imgui/guizmo/*.h
    ${CMAKE_SOURCE_DIR}/deps/imgui/guizmo/*.cpp
    ${CMAKE_SOURCE_DIR}/deps/Guizmo/*.h
    ${CMAKE_SOURCE_DIR}/deps/Lua/*.c
    ${CMAKE_SOURCE_DIR}/deps/Lua/*.h
    ${CMAKE_SOURCE_DIR}/deps/Lua/*.hpp
    ${CMAKE_SOURCE_DIR}/deps/OBJ_Loader/OBJ_Loader/*.h
    ${CMAKE_SOURCE_DIR}/deps/openal-soft/OpenAL/include/AL/*.h
    ${CMAKE_SOURCE_DIR}/deps/tinyObjLoader/tinyObjLoader/*.h
    ${CMAKE_SOURCE_DIR}/deps/tinyObjLoader/tinyObjLoader/*.cc
    ${CMAKE_SOURCE_DIR}/deps/minitrace/minitrace.c
    ${CMAKE_SOURCE_DIR}/deps/minitrace/minitrace.h
    ${CMAKE_SOURCE_DIR}/deps/glad/src/glad.c
)

# Define the Engine static library
add_library(Engine STATIC ${ENGINE_SOURCES})

# Include engine's headers for external users, but hide GLFW internally
target_include_directories(Engine PUBLIC
    ${CMAKE_SOURCE_DIR}/include/engine
)

# Link GLFW and GLAD libraries
target_link_libraries(Engine PRIVATE glfw ${CMAKE_SOURCE_DIR}/deps/glad/src/glad.c)

# Set target properties for Engine to output in appropriate directories
set_target_properties(Engine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/data/engine/Debug/
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/data/engine/Release/
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/data/engine/Debug/
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/data/engine/Release/
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug/
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release/
)

# Gather source files for Example1
file(GLOB EXAMPLE1_SOURCES
    ${CMAKE_SOURCE_DIR}/src/examples/example1/*.cpp
)

# Define the Example1 executable
add_executable(Example1 ${EXAMPLE1_SOURCES})

# Include directories for Example1
target_include_directories(Example1 PRIVATE
    ${CMAKE_SOURCE_DIR}/include/examples/example1
    ${CMAKE_SOURCE_DIR}/include/engine  # Only include Engine headers, not OpenGL or GLFW
)

# Link the Example1 executable with the Engine library, but Example1 shouldn't be aware of GLFW
target_link_libraries(Example1 PRIVATE Engine)

# Set target properties for Example1 to output in the appropriate directories
set_target_properties(Example1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/Debug/
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/Release/
)

# Define configurations and platforms
if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DDEBUG /Zi /Od /RTC1")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /DNDEBUG /O2")
endif()

# Define platform-specific settings
if (WIN32)
    add_definitions(-D_WIN32 -D_GLFW_WIN32 -D_GLFW_WGL -D_GLFW_USE_OPENGL -D_GLFW_OPENGL_LIBRARY -DMTR_ENABLED)
elseif (UNIX)
    add_definitions(-D_GLFW_COCOA -D_GLFW_X11 -D_GLFW_WAYLAND -D_GLFW_OSMESA)
elseif (APPLE)
    add_definitions(-D_GLFW_COCOA)
endif()
