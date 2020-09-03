
#ifndef RZ_ENGINE_HPP
#define RZ_ENGINE_HPP

#include "arrangments.hpp"
#include "periphery_input.hpp"
enum class Engine_State : unsigned char
{
  INITAL,
  CONFIGURED,
  IGNITION,
  RUNNING,
  SHUTDOWN,
  STALL
};

enum Cycle_Outs{
  S_SHUTDOWN =5
};

enum class Cmd_Mode{
  INITAL,
  COMMITTEE,
  USER_INPUT,
  WAITING
};

inline static constexpr GLfloat STAIC_ONE = 1.0f;
GLint frame_buf_width,frame_buf_hight;


struct rez_mgmt
{
  ecouter<text_render_glyph,character>  ecouterait_glyph;
  priphery_compoent priphery_input;
  multiframe_capturer mf_c;
      //ecouter<terrain,terrain_feture_tupl>  ecouterait_terrain;
  //  ecouter<std::shared_ptr<shader_seprate>,terrain_feture_tupl>  ecouterait_terrain;
    //  shader_pipeline_CMD shpipe_cmd;
    //texture_xml_parser t_xml_parser;
  //  std::array<view_lenz,6> lenz_array;
    //view_lenz* prim_lenz;
};

inline static rez_mgmt* global_r_mgmt=nullptr;

struct {
  glm::mat4 view_projection;
  glm::mat4 view_matrix;
  glm::mat4 Projection;
} gl_matrixz;

struct Engine
{
  Engine_State engine_state;
  Cmd_Mode cmd_mode;

  int gl_errocode;
  GLFWwindow* glfw_window;

  long double run_durration;
  unsigned long long int cycle_count;

  rez_mgmt r_mgmt;
  std::string terminal_cmd;

  ///scene||arrangments
  ///scene* active_scene;
//  arrangment_A1* arg_a1;
  Engine();

  void set_engine_state(Engine_State in_state);
  void set_cmd_mode(Cmd_Mode in_cmd_mode);
  void ignition();
  int cylce();
/*
  void configure(engine_config_pak& in_pak)
  {
    engine_state= Engine_State::CONFIGURED;
  }
  */
};

#endif
