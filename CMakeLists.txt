
set(CMAKE_CXX_COMPILER g++)
cmake_minimum_required(VERSION 3.6.3 FATAL_ERROR)

project(text_render LANGUAGES C CXX)
include(CheckCXXCompilerFlag)
include(ExternalProject)

set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/usr/include/freetype2")
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/..basez/3rdparty/freetype2")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(OpenGL_GL_PREFERENCE GLVND CACHE STRING "Linux-only: if GLVND, use the vendor-neutral GL libraries (default). If LEGACY, use the legacy ones (might be necessary to have optirun/primusrun work)")
set_property(CACHE OpenGL_GL_PREFERENCE PROPERTY STRINGS GLVND LEGACY)
# OpenGL
find_package(OpenGL REQUIRED)
# GLM
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

find_package(GLUT REQUIRED)
find_package(X11 REQUIRED)

find_package(GLFW REQUIRED)
message(STATUS "Found GLFW in ${GLFW_INCLUDE_DIR}")

# ASSIMP
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

find_package(GLEW REQUIRED)
message(STATUS "GLEW included at ${GLM_INCLUDE_DIR}")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(Freetype REQUIRED)
include_directories(/usr/include/freetype2)

find_package( OpenCV REQUIRED )
#Add any other header files
include_directories( ${CMAKE_SOURCE_DIR}/source/)
include_directories( ${CMAKE_SOURCE_DIR}/source/basez)
include_directories( ${CMAKE_SOURCE_DIR}/source/basez/3rdparty)
include_directories( ${CMAKE_SOURCE_DIR}/source/modualz/context)
include_directories( ${CMAKE_SOURCE_DIR}/source/modualz/geometry)
include_directories( ${CMAKE_SOURCE_DIR}/source/modualz/milieu)
include_directories( ${CMAKE_SOURCE_DIR}/source/modualz/phyziz)
include_directories( ${CMAKE_SOURCE_DIR}/source/parserz)
include_directories( ${CMAKE_SOURCE_DIR}/source/MCP_cmd)

add_subdirectory(source)
