#pragma once
#include "partical_lib.hpp"

class comput_partic_sim
{

  protected :
  GLint  dt_location;
  bool in_envro;
  view_lenz* active_lenz;

  GLuint  render_vao;
  GLuint  render_vbo;

  GLuint comput_prog_ID;
  GLuint render_prog_ID;
  glm::vec3 pos;
  public :

  static long frame_count;
  GLuint last_ticks=0;
  GLuint start_ticks=0;
  GLuint current_time=0;

  float time;
  float delta_time;

  glm::vec4 orgin;
  GLuint   orgin_ID;
  GLuint orgin_loc;

  virtual void init() =0;
  virtual void partical_dispaly()=0;
  virtual void  set_uniform_loc() = 0;



  inline void set_orgin(glm::vec4 in_orgin)
  {
    orgin=in_orgin;
  }

  inline  void set_lenz(view_lenz* in_lenz)
    {
      active_lenz = in_lenz;
    }

    void set_renderz_ID(const GLuint& in_comp_shd, const GLuint& in_rend_shd)
    {
      comput_prog_ID =in_comp_shd;
      render_prog_ID =in_rend_shd;
    }

  void set_renderz_ID(gl_shader_t* in_comp_shd,gl_shader_t* in_rend_shd)
  {
    comput_prog_ID =in_comp_shd->program_ID;
    render_prog_ID =in_rend_shd->program_ID;
  }

};


class  compute_partic_attracto : public comput_partic_sim
{
  protected :
  union
      {
        struct
          {
              GLuint position_buffer;
              GLuint velocity_buffer;
          };
          GLuint p_buffz[PARTC_ENV_BUFFZ];
      };

      union
  {
      struct
      {
          GLuint position_tbo;
          GLuint velocity_tbo;
      };
      GLuint tbos[2];
  };

  public :
  void set_pos(glm::vec3 in_pos)
  {
    pos = in_pos;
  }
  compute_partic_attracto() : in_envro(false)
  {};

  compute_partic_attracto(bool in_envro, glm::vec3 in_pos) : in_envro(in_envro), pos(in_pos) 
  {};
  GLuint attractor_buffer;
  float attractor_masses[MAX_ATTRACTORS];

   void init();
   void partical_dispaly();

   void  set_uniform_loc()
  {
   dt_location = glGetUniformLocation(comput_prog_ID, "dt");
   orgin_loc = glGetUniformLocation(comput_prog_ID, "orgin");
  }

};
