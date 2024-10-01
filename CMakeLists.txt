# Define the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and languages
project(OpenGLEngine LANGUAGES CXX)

# Force 64-bit architecture when using Visual Studio
# if (MSVC)
    set(CMAKE_GENERATOR_PLATFORM x64)
    #endif()

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/data/engine)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/data/engine)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/data/engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Debug and Release configurations" FORCE)

include_directories(
    ${CMAKE_SOURCE_DIR}/deps/GLM
    ${CMAKE_SOURCE_DIR}/deps/GLFW/include
    ${CMAKE_SOURCE_DIR}/deps/loguru
    ${CMAKE_SOURCE_DIR}/deps/OBJ_Loader
    ${CMAKE_SOURCE_DIR}/deps/openal-soft/OpenAL/include
    ${CMAKE_SOURCE_DIR}/deps/OpenGL/OpenGL/include
    ${CMAKE_SOURCE_DIR}/deps/stb_image
    ${CMAKE_SOURCE_DIR}/deps/tinyObjLoader
    ${CMAKE_SOURCE_DIR}/include
)

# Set library directories
link_directories(
  ${CMAKE_SOURCE_DIR}/deps/openal-soft/OpenAl/libs/Win64
  ${CMAKE_SOURCE_DIR}/data/engine/Debug
  ${CMAKE_SOURCE_DIR}/data/engine/Release
)

# Gather source files for Engine
file(GLOB ENGINE_SOURCES
    ${CMAKE_SOURCE_DIR}/src/engine/*.cpp
    ${CMAKE_SOURCE_DIR}/include/engine/*.h  # Include engine headers
)

# Define the Engine static library
add_library(Engine STATIC ${ENGINE_SOURCES})

# Set target-specific include directories (engine headers)
target_include_directories(Engine PRIVATE
    ${CMAKE_SOURCE_DIR}/include/engine
)

# Target properties for Engine
set_target_properties(Engine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/data/engine
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/data/engine
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/data/engine
)

# Gather source files for Example1
file(GLOB EXAMPLE1_SOURCES
    ${CMAKE_SOURCE_DIR}/src/examples/example1/*.cpp
    ${CMAKE_SOURCE_DIR}/include/examples/example1/*.h
)

# Define the executable for Example1
add_executable(Example1 ${EXAMPLE1_SOURCES})

# Link Engine to Example1 (loguru does not need to be linked as it's header-only)
target_link_libraries(Example1 PRIVATE ${CMAKE_SOURCE_DIR}/data/engine/Debug)
# Set target-specific include directories (for example1)
target_include_directories(Example1 PRIVATE
    ${CMAKE_SOURCE_DIR}/include/examples/example1
)

# Set specific flags for Debug and Release builds
target_compile_definitions(Engine PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_compile_definitions(Engine PRIVATE $<$<CONFIG:Release>:NDEBUG>)

# Output build directories for Example1
set_target_properties(Example1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Messages for build clarity
message(STATUS "CMake source directory: ${CMAKE_SOURCE_DIR}")
