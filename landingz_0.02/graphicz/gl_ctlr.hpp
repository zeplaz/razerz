#ifndef LANDINGZ_OPENGL_SHADER_CTROLER_HPP
#define LANDINGZ_OPENGL_SHADER_CTROLER_HPP


#include <FL/Fl.H>
#include <FL/platform.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>

#define STBI_WINDOWS_UTF8

#include "gui_opengl_uility.hpp"
#include "shader_ctr/opengl_shader_base.hpp"


//defined in fl_base
static Fl_Double_Window* build_gui();

class gl_texturez;
class gl_shaderz;

class gl_ops
{

  public :
  struct {
    glm::mat4 view_projection;
    glm::mat4 view_matrix;
    glm::mat4 Projection;
  } gl_matrixz;

struct lenz_data{

  glm::vec3 world_up;
  glm::vec3 lenz_front;
  glm::vec3 lenz_pos;
  float fov;
  float near_plane;
  float far_plane;
  float lenz_radius;

  lenz_data() :  world_up(0.f,1.f,0.f),
  lenz_front(0.f,0.f,-1.f),
  lenz_pos(0.f,0.f,1.f)
  {

    fov= 90.f;
    near_plane = 0.1f;
    far_plane = 1000.f;
    lenz_radius = 10.0f;
  }

  lenz_data(glm::vec3 in_worldup, glm::vec3 in_lenz_front,
            glm::vec3 in_lenzpos,float in_fov, float in_nplan, float in_farp, float in_lezr)
  {
    world_up   = in_worldup;
    lenz_front = in_lenz_front;
    lenz_pos   = in_lenzpos;
    fov        = in_fov;
    near_plane = in_nplan;
    far_plane  = in_farp;
    lenz_radius= in_lezr;
  }
}m_lenz_data;

  protected :
  int id;
  int gl_version_major;
  int current_scene;

  std::unordered_map<std::string,GLint> shader_prgm_map;
  std::unordered_map<int,gl_texturez> texture_map;
  public :

  inline void set_scene(int in_scene) { current_scene = in_scene};
  inline void get_scene()
  {
    return current_scene;
  }

  void render_current_scene();

  void shader_setup();
  void change_shader_program(int window, GLint shaderProgram);

  bool load_active_textures();

  void view_matex_inilzation()
{
  gl_matrixz.view_projection =glm::mat4(1.f);
  gl_matrixz.view_matrix = glm::mat4(1.f);
  gl_matrixz.Projection = glm::mat4(1.f);
  m_lenz_data = lenz_data();
}

};

class gl_window_framework : public Fl_Gl_Window{

protected :

  static int gl_windows_active;
  bool opengl_context_startup();
    //GLint current_shader_program;
  Fl_Text_Display *output;
  void add_output(const char *format, ...);

public :

 double size_scale;
 std::shared_ptr<gl_ops> gl_instance;

 ~gl_window_framework(){gl_windows_active--;}
 void draw();
 virtual int handle(int event);

 gl_window_framework(int X, int Y, int W, int H, const char *L):  Fl_Gl_Window(X,Y,W,H,L)
  {
    this->mode(FL_OPENGL3|FL_DOUBLE|FL_ALPHA);
    gl_version_major = 0;
    gl_insiance = nullptr;
  }

 inline void bind_gl_instance(std::shared_ptr<gl_ops> in_opz)
  {
   gl_instance = in_opz;
  }


 inline  void run_viewdata_inialzation()
   {
    Fl::use_high_res_GL(true);
    if(gl_instance !=nullptr)
      {
       gl_instance->view_matex_inilzation();
      }
    else
      {
        std::cerr << "###\n##-->>WARNING gl_ops missing, gl_instinace is null can not set view marexz.
        plz bind gl_insiance to this window and run again..or drectly\n\n";
        }
    }

    //draw gemoetry.. calll
};

#endif
