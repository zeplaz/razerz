#pragma once

#include "gl_lib_z.hpp"
#include "lenz.hpp"
static bool screen_beenresized = false;



void APIENTRY GLAPIENTRY glDebugOutput(GLenum source,
                         GLenum type,
                         GLuint id,
                         GLenum severity,
                         GLsizei length,
                         const GLchar *message,
                         const void *userParam);


void process_input_glfw(GLFWwindow* window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int opengl_context_settup();

int run_opengl_setup(GLFWwindow* out_window);

void  capture_frame_buff_avi(GLFWwindow*window,void(*vid_cap_callback)(GLFWwindow*,int,std::string));


/*namespace context_callbacks{
void process_input_glfw(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
}*/



void take_screenshot_to_file(int& frame_buf_width,int& frame_buf_hieght);

struct offset_table
{
  static const size_t struc_internal_offset = 16;
  static const size_t bool_offset = sizeof(GLboolean);
  static const size_t float_offset = sizeof(GLfloat);
  static const size_t int_offset = sizeof(GLint);
  static const size_t vec3_offset = 16;

  struct light_offsetz
  {
    size_t enbl= 0;
    size_t l_pos     = bool_offset;
    size_t l_intz    = l_pos+vec3_offset;
    size_t l_amb     = l_intz+vec3_offset;
    size_t l_spotcon = l_amb+struc_internal_offset;

    size_t dr_srengh=l_spotcon+struc_internal_offset;
    size_t con_atten=dr_srengh+struc_internal_offset;
    size_t qadr_atten=con_atten+struc_internal_offset;
    size_t lin_atten=qadr_atten+struc_internal_offset;
    size_t spot_cut=lin_atten+struc_internal_offset;
    size_t spot_exp =spot_cut+struc_internal_offset;
    size_t gamma_c =spot_exp+struc_internal_offset;
    size_t l_type = gamma_c+struc_internal_offset;
  }l_offset;
};
