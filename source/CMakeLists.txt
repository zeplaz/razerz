 cmake_minimum_required(VERSION 3.6.0)

# Find includes in corresponding build directories
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)
set(CMAKE_BUILD_DIR ${PROJECT_SOURCE_DIR}/build)

#Add any other src file you may write
set(razerz
    "ttestz/func_par_test.cpp"
)

add_library(3rdparty STATIC
  "basez/3rdparty/frame_to_video.cpp"
  "basez/3rdparty/b3Logging.cpp"
  "basez/3rdparty/b3ResourcePath.cpp"
    #"basez/3rdparty/frame_to_video.hpp"
    #"/basez/3rdparty/sb7ktx.h"
  #  "/basez/3rdparty/sb7ktx.cpp"
    #"basez/3rdparty/stb_image.h"
)
#add_library(MCP_cmd STATIC
#"MCP_cmd/shader_pipeline_CMD.hpp"
#"MCP_cmd/shader_pipeline_CMD.cpp"
#)
add_library(parserz STATIC
  #"parserz/geometry_parser.cpp"
  "parserz/parserlib.cpp"
  #  "parserz/geometry_parser.hpp"
  #  "parserz/parserlib.hpp"
)

#add_library(modualz STATIC
#"modualz/geometry/geometry.cpp"
#"modualz/geometry/assimp_model.cpp"
#"modualz/phyziz/collision_AI.cpp"
#"modualz/phyziz/bullet_collision.cpp"
#"modualz/phyziz/pysic_lib.cpp"
# )

add_library(basez STATIC
  "basez/opengl_utilityz.cpp"
  #"basez/shader_lib.cpp"
#"basez/sym_object.cpp"
  #"basez/texture.cpp"
  "basez/io_utilityz.cpp"

#"basez/lenz.hpp"
#"basez/mathII.hpp"
#"basez/mathz.hpp"
#"basez/opengl_utilityz.hpp"
#"basez/shader_lib.hpp"
#"basez/sym_object.hpp"
#"basez/cpp_libz_base.hpp"
#"basez/errorhandler.hpp"
#"basez/gl_lib_z.hpp"
#"basez/io_utilityz.hpp"
#"basez/texture.hpp"
)
#Rename the source files that will create the library, to a proper name!
#set(razerz_basez_LIB
#   -lib.cpp
#)

#Add any other header files
#set(razerz_INCLUDES
#    headers/_facilities.h
#)
link_directories(lib/basez)
include_directories( ${OPENGL_INCLUDE_DIRS} ${BULLET_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )
#set(LIBS glfw3 assimp GLEW freetype 3rdparty basez modualz parserz MCP_cmd)
set(LIBS glfw3 assimp GLEW freetype 3rdparty basez parserz )


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
add_executable(razerz ${razerz})
#target_link_libraries(  somename )

#If your app, links to an external lib -ie Boost
target_link_libraries(razerz ${LIBS} ${OPENGL_LIBRARIES} Threads::Threads OpenGL::GL ${GLEW_LIBRARIES} ${CMAKE_DL_LIBS} ${GLFW_LIBRARY} ${FREETYPE_LIBRARY} ${OpenCV_LIBS} ${GLUT_LIBRARY} ${BULLET_LIBRARIES} ${X11_LIBRARIES})
# Install the executable and libraries (don't forget to uncomment the lib line if you want)
install(TARGETS razerz DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
#install(TARGETS somename DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
