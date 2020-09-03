#ifndef LANDINGZ_OPEN_FL_UTILITY_HPP
#define LANDINGZ_OPEN_FL_UTILITY_HPP

//Link with libGLEW.so (on Unix/Linux), libglew32.a (with MinGW)
// or glew32.lib (with MS Visual Studio)
#include <memory>
#include <iostream>
#define GLEW_STATIC 1
#include <GL/glew.h>

#include <glm/glm.hpp> // glm::mat4
#include <glm/ext.hpp> // perspective, translate, rotate

//#ifndef DEBUG_01
#define DEBUG_01
#define DEBUG_OPENGL_FORCE
#define APIENTRY GLAPIENTRY

constexpr GLfloat bAlpha = 1.0f;
constexpr GLfloat rValue= 14.0 / 255.0;
constexpr GLfloat gValue= 23.0 / 255.0;
constexpr GLfloat bValue= 28.0 / 255.0;

static bool screen_beenresized = false;

void APIENTRY GLAPIENTRY glDebugOutput(GLenum source,
                         GLenum type,
                         GLuint id,
                         GLenum severity,
                         GLsizei length,
                         const GLchar *message,
                         const void *userParam);

/*
struct open_gl_context_pak{

  int id;

  int x;
  int y;
  int w;
  int h;
  std::string label;

  void read_pak(std::string file_name, int paknum);
  void read_pak(const char* raw_pak)
    {
    std::string delimiter = ",";
    std::string s(raw_pak);
    size_t pos = 0;
    std::string token;
    std::string temp_arry[6];
    int i=0;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
      token = s.substr(0, pos);
      temp_arry[i] = s;
      s.erase(0, pos + delimiter.length());
      i++;
    }
  }

  freind std::istream&   operator >>(std::istream& is,open_gl_context_pak);
};


std::istream& operator>> (std::istream& is,open_gl_context_pak cpak)
{
  is>> cpak.id >> cpak.x >> cpak.y >> cpak.w >> cpak.h >> cpak.label;
  return is;
}*/


//static std::shared_ptr<sharegl_driver_framework>


/*
class handler_glatter
{
protected:
static HDC hDC;
static HGLRC hRC;
static HWND hWnd;
static HINSTANCE hInst;
static RECT winrect;

  //public :

};

*/

#endif
