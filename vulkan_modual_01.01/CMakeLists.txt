
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(project_name 0vulkan_test)

Project(${project_name} LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/cmake")


#SET(GCC_COVERAGE_LINK_FLAGS   "-lvulkan" "-ldl" "-lpthread" "-lX11" "-lXxf86vm" "-lXrandr" "-lXi" "-lxcb")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
#add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
SET(OperatingSystem "Linux")
message(CHECK_PASS " ::linux os detected" )

else()
message(CHECK_START " ::None linux build.... windowz?")
endif()

find_package(Vulkan REQUIRED FATAL_ERROR)
find_package(glslang REQUIRED FATAL_ERROR)

find_package(Threads)
#find_package(Threads REQUIRED)
message("glslang: ${glslang_FOUND}")
set(GLSLANG_SEARCH_PATH "/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/libglslang.a")

find_library(GLSLANG_LIB NAMES glslang HINTS ${GLSLANG_SEARCH_PATH} REQUIRED)
message("kuvrat: ${GLSLANG_LIB}")
find_library(OGLCompiler_LIB NAMES OGLCompiler HINTS ${GLSLANG_SEARCH_PATH})

find_library(OSDependent_LIB NAMES OSDependent HINTS ${GLSLANG_SEARCH_PATH})

find_library(HLSL_LIB NAMES HLSL HINTS ${GLSLANG_SEARCH_PATH})

find_library(SPIRV_LIB NAMES SPIRV HINTS ${GLSLANG_SEARCH_PATH})

find_library(SPIRV_REMAPPER_LIB NAMES SPVRemapper HINTS ${GLSLANG_SEARCH_PATH})

find_library(SPIRV_TOOLS_LIB NAMES SPIRV-Tools HINTS ${SPIRV_TOOLS_SEARCH_PATH})

find_library(SPIRV_TOOLS_OPT_LIB NAMES SPIRV-Tools-opt HINTS ${SPIRV_TOOLS_OPT_SEARCH_PATH})

set(SPIRV_TOOLS_LIBRARIES ${SPIRV_TOOLS_OPT_LIB} ${SPIRV_TOOLS_LIB})
set(GLSLANG_LIBRARIES
    ${GLSLANG_LIB}
    ${OGLCompiler_LIB}
    ${OSDependent_LIB}
    ${HLSL_LIB}
    ${SPIRV_LIB}
    ${SPIRV_REMAPPER_LIB}
    ${SPIRV_TOOLS_LIBRARIES})


if(UNIX)
include(FindPkgConfig)
option(BUILD_WSI_XCB_SUPPORT "Build XCB WSI support" ON)
#option(BUILD_WSI_XLIB_SUPPORT "Build Xlib WSI support" ON)
#find_package(XCB REQUIRED)
#message("  pakcage::: XCB: ${xcb_FOUND}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_XCB_KHR")
find_package(X11 REQUIRED)

find_package(PkgConfig)
pkg_check_modules(xcb REQUIRED IMPORTED_TARGET xcb)
#pkg_check_modules(glslang REQUIRED IMPORTED_TARGET glslang)

add_definitions(-DVK_USE_PLATFORM_XCB_KHR)
endif()




set(SOURCE_FILEZ 
vk_abstracionz.cpp
  vulkan_api.cpp
  vk_shaderz.cpp
  exrtn_vulkan.cpp
  main.cpp)

  set(LIBRARIES PUBLIC
  Vulkan::Vulkan
  Threads::Threads
  glslang::glslang
  glslang::SPIRV
  glslang
  HLSL
  OSDependent
  OGLCompiler
  SPIRV
  )

set(SOURCES ${SOURCES} platform/unix/Xcb_Window.cpp)
set(LIBRARIES ${LIBRARIES} PRIVATE PkgConfig::xcb)


#add_library(${project_name} ${HEADERS} ${SOURCES})

add_executable (${project_name} 
${SOURCE_FILEZ})

target_include_directories (${project_name}
PUBLIC ${VULKAN_INCLUDE_DIRS}
PUBLIC ${XCB_INCLUDE_DIRS}
PUBLIC ${X11_INCLUDE_DIRS}
PUBLIC ${THREADS_INCLUDE_DIRS}
PUBLIC ${GLSLANG_INCLUDE_DIRS}
) 

#target_link_libraries (${project_name} ${VULKAN_LIB_LIST})
#target_link_libraries (${project_name} ${XCB_LIB_LIST})
#target_link_libraries (${project_name} ${X11_LIB_LIST})
#target_link_libraries (${project_name} ${THREADS_LIB_LIST})
#target_link_libraries (${project_name} ${GLSLANG_LIB_LIST})
target_link_libraries(${project_name}  ${LIBRARIES} ${GLSLANG_LIBRARIES})

#target_link_options(${project_name} PUBLIC "LINKER: -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lxcb")