 cmake_minimum_required(VERSION 3.6.0)

# Find includes in corresponding build directories
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)
set(CMAKE_BUILD_DIR ${PROJECT_SOURCE_DIR}/build)

#Add any other src file you may write
set(razerz_SRC
    "ttestz/sysm_test.cpp"
)

add_library(3rdparty STATIC
  #"/basez/3rdparty/sb7ktx.h"
#  "/basez/3rdparty/sb7ktx.cpp"
  "basez/3rdparty/stb_image.h"
  "basez/3rdparty/frame_to_video.cpp"
  "basez/3rdparty/frame_to_video.hpp"
)

add_library(basez STATIC
"basez/cpp_libz_base.hpp"
"basez/errorhandler.hpp"
"basez/gl_lib_z.hpp"
"basez/io_utilityz.hpp"
"basez/io_utilityz.cpp"
"basez/lenz.hpp"
"basez/mathII.hpp"
"basez/mathz.hpp"
"basez/opengl_utilityz.hpp"
"basez/opengl_utilityz.cpp"
"basez/sym_object.cpp"
"basez/sym_object.hpp"
)
#Rename the source files that will create the library, to a proper name!
#set(razerz_basez_LIB
#   -lib.cpp
#)

#Add any other header files
#set(razerz_INCLUDES
#    headers/_facilities.h
#)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
set(LIBS glfw3 assimp GLEW  freetype 3rdparty basez)



if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
	execute_process(
		COMMAND git rev-parse HEAD
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_BRANCH
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
else()
	set(GIT_BRANCH "Unknown")
endif()
add_definitions(-DGIT_BRANCH=${GIT_BRANCH})
#set build dir for your executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BUILD_DIR}/lib)
message( STATUS "EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH} )
message( STATUS "LIBRARY_OUTPUT_PATH: " ${LIBRARY_OUTPUT_PATH} )

file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
file(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH})

# Tell CMake to create the  executable and/or shared libs
#add_library(somename SHARED ${_LIB})
add_executable(razerz_SRC ${razerz_SRC})
#target_link_libraries(  somename )

#If your app, links to an external lib -ie Boost
target_link_libraries(razerz_SRC ${LIBS} ${OPENGL_LIBRARIES} Threads::Threads OpenGL::GL ${CMAKE_DL_LIBS} ${FREETYPE_LIBRARY} ${OpenCV_LIBS} ${GLUT_LIBRARY} ${X11_LIBRARIES})
# Install the executable and libraries (don't forget to uncomment the lib line if you want)
install(TARGETS razerz_SRC DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
#install(TARGETS somename DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
