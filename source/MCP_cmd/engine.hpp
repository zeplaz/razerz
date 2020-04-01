
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


struct Engine
{
  Engine_State engine_state;
  Cmd_Mode cmd_mode;

  int gl_errocode;
  GLFWwindow* glfw_window;

  long double run_durration;
  unsigned long long int cycle_count;

  multiframe_capturer mf_c;
  rez_mgmt r_mgmt;
  std::string terminal_cmd;

  ///scene||arrangments
  ///scene* active_scene;
  arrangment_A1* arg_a1;

  struct {
    glm::mat4 view_projection;
    glm::mat4 view_matrix;
    glm::mat4 Projection;
  } gl_matrixz;

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
