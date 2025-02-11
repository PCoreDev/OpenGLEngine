cmake_minimum_required(VERSION 3.20)
project(OpenGLEngine)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/data/engine)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/data/engine)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(
    ../deps/glad/include
    ../deps/glew-2.1.0/include
    ../deps/GLFW/include
    ../deps/glm
    ../deps/openal-soft/include/
    ../deps/imgui/
    ../deps/imgui/backends/
    ../deps/OBJ-Loader/Source
    ../deps/minitrace
    ../include
    ../deps/
)

# Link directories
link_directories(
    ../deps/openal-soft/build/RelWithDebInfo
    ../deps/glew-2.1.0/lib/Release/x64
    ../deps/glfw/build/src/RelWithDebInfo
)

# Engine static library
add_library(Engine STATIC
    ../src/engine/*.cpp
    ../src/engine/components/*.cpp
    ../include/engine/*.h
    ../include/engine/components/*.h

    ../deps/glfw/glfw/src/*.c
    ../deps/glfw/src/win32_*.c
    ../deps/glfw/src/context.c
    ../deps/glfw/src/egl_context.c
    ../deps/glfw/src/wgl_context.c
    ../deps/glfw/src/init.c
    ../deps/glfw/src/input.c
    ../deps/glfw/src/monitor.c
    ../deps/glfw/src/osmesa_context.c
    ../deps/glfw/src/window.c
    ../deps/glfw/src/vulkan.c

    ../deps/glm/glm/**.hpp
    ../deps/glm/glm/**.h
    ../deps/glm/glm/**.c
    ../deps/glm/glm/**.cpp
    ../deps/glm/glm/**.inl

    ../deps/glad/src/*.c
    ../deps/glad/include/*.h

    ../deps/loguru/*.hpp
    ../deps/loguru/*.cpp

    ../deps/px/*.h

    ../deps/openal-soft/include/*.h
    ../deps/openal-soft/OpenAL/include/AL/*.h

    ../deps/imgui/*.c
    ../deps/imgui/*.cc
    ../deps/imgui/*.cpp
    ../deps/imgui/backends/imgui_impl_glfw.cpp
    ../deps/imgui/backends/imgui_impl_opengl3.cpp
    ../deps/imgui/*.h
    ../deps/imgui/guizmo/*.h
    ../deps/imgui/guizmo/*.cpp

    ../deps/lua/*.c
    ../deps/lua/*.h
    ../deps/lua/*.hpp

    ../deps/OBJ_Loader/OBJ_Loader/*.h

    ../deps/minitrace/minitrace.c
    ../deps/minitrace/minitrace.h
)

# Engine target configurations
target_compile_definitions(Engine PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_compile_definitions(Engine PRIVATE $<$<CONFIG:Release>:NDEBUG>)
target_compile_options(Engine PRIVATE $<$<CONFIG:Release>:-O3>)

# Platform-specific definitions
if(WIN32)
    target_compile_definitions(Engine PRIVATE _WIN32 _GLFW_WIN32 _GLFW_WGL _GLFW_USE_OPENGL _GLFW_OPENGL_LIBRARY MTR_ENABLED)
endif()

# Example1 executable
add_executable(Example1
    ../src/examples/example1/*.cpp
    ../include/engine/*.h
)

# Example1 target configurations
target_link_libraries(Example1 Engine)
target_compile_definitions(Example1 PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_compile_definitions(Example1 PRIVATE $<$<CONFIG:Release>:NDEBUG>)
target_compile_options(Example1 PRIVATE $<$<CONFIG:Release>:-O3>)

# Platform-specific definitions for Example1
if(WIN32)
    target_compile_definitions(Example1 PRIVATE _WIN32 _GLFW_WIN32 _GLFW_WGL _GLFW_USE_OPENGL _GLFW_OPENGL_LIBRARY)
endif()