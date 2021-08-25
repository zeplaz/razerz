
#ifndef RZ2_OPENGL_LIB_HPP
#define RZ2_OPENGL_LIB_HPP


#include <GL/glew.h>
#include <GL/gl.h>
#include "low_level_lib.hpp"


using namespace rz2; 
#define APIENTRY GLAPIENTRY
void APIENTRY GLAPIENTRY glDebugOutput(GLenum source,
                         GLenum type,
                         GLuint id,
                         GLenum severity,
                         GLsizei length,
                         const GLchar *message,
                         const void *userParam);

namespace rz2
{

constexpr int MAX_SCREENZ_DEBUG = 4;
constexpr int SCREEN_WIDTH_DEFULT = 800;
constexpr int SCREEN_HEIGHT_DEFULT = 600;
constexpr int CLEAR_COLOURS_DEFULT[] = {27,52,16,255};

//static bool screen_beenresized = false;
//



void resizeWindow(int w, int h);
void gl_configure();

class Opengl_MCP
{


};
}
#endif

