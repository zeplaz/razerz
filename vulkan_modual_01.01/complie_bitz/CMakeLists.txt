
project(vk_testmodual)

cmake_minimum_required(VERSION 3.10)

set(project_name 0vulkan_test)
Project(${project_name})

message("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
SET(OperatingSystem "Linux")
message(CHECK_PASS " ::linux os detected" )

else()
message(CHECK_START " ::None linux build.... windowz?")
endif()


set(VK_BUILD ${CMAKE_CURRENT_SOURCE_DIR}/build CACHE PATH "vl build directory")


set(GLSLANG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/glslang_linux_Release/glslang/ CACHE PATH "glslang directory")

set(GLSLANGLIBS ${GLSLANG_PATH}/lib/ CACHE PATH "glslang library directory")

set(GLSLANGINCLUDES ${GLSLANG_PATH}/include/glslang CACHE PATH "glslang include directory") 
link_directories(${GLSLANGLIBS} ${LLVMLIBS})



set(GLSLANGLIBS
    glslang
    HLSL
    OSDependent
    OGLCompiler
    SPIRV)

    list(APPEND GLSLANGLIBS SPVRemapper SPIRV-Tools SPIRV-Tools-opt)

    add_definitions(-std=c++17)

    find_library(GLSLANG_LIB NAMES glslang
    HINTS ${GLSLANG_SEARCH_PATH} )

find_library(OGLCompiler_LIB NAMES OGLCompiler
    HINTS ${GLSLANG_SEARCH_PATH} )

find_library(OSDependent_LIB NAMES OSDependent
    HINTS ${GLSLANG_SEARCH_PATH} )

find_library(HLSL_LIB NAMES HLSL
    HINTS ${GLSLANG_SEARCH_PATH} )

find_library(SPIRV_LIB NAMES SPIRV
    HINTS ${GLSLANG_SEARCH_PATH} )

find_library(SPIRV_REMAPPER_LIB NAMES SPVRemapper
    HINTS ${GLSLANG_SEARCH_PATH} )

find_library(SPIRV_TOOLS_LIB NAMES SPIRV-Tools
    HINTS ${SPIRV_TOOLS_SEARCH_PATH} )
    
    LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/cmake")

set(HAVE_LIBC TRUE)

set (src 
main.cpp
)

set(headers
)

set(modualz_filez
vulkan_api.cpp
vulkan_api.hpp
)
add_library(modualz ${modualz_filez})



add_executable(${project_name} ${src} ${headers})

target_link_libraries( ${PROJECT_NAME} modualz)


find_package(Vulkan REQUIRED FATAL_ERROR)

find_package(glslang REQUIRED)
message("glslang: ${glslang_FOUND}")

#find_package(GLSLang COMPONENTS GLSLang) #find_package(GLSLang COMPONENTS GLSLang SPRIV)
if(Vulkan_FOUND)

    message(CHECK_PASS "::VULKAN package found")
   
    if(WIN32)
        target_include_directories(${project_name} PRIVATE Vulkan::Vulkan)
        target_link_libraries(${project_name} Vulkan::vulkan)
    else()
        target_include_directories(${project_name} PUBLIC ${VULKAN_INCLUDE_DIRS})
        target_link_libraries(${project_name} ${VULKAN_LIB_LIST})
    endif()

endif()

#target_link_libraries(
    #target_name
    #PUBLIC
     #   libA
        #$<$<PLATFORM_ID:Windows>:wsock32>
    #PRIVATE
       # $<$<PLATFORM_ID:Linux>:libB>
 #       libC