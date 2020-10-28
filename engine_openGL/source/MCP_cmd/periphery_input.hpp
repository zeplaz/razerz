#ifndef RZ_PER_IN_HPP
#define RZ_PER_IN_HPP

#include "écouterions_resourcer_CMD.hpp"

#include "../basez/screen.hpp"
sym_logger so_prif_loger;

namespace periphery{

 inline static int current_lenz_pos  =0 ;
inline static bool take_frame_video = false;
void (*vid_cap_callback)(GLFWwindow*,int,std::string);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void joystick_callback(int id,int event);
void displacment_callback(float dmap_depth);
void process_input_glfw(GLFWwindow* window);
};


typedef std::shared_ptr<Screen::view_monitor> sptr_screen;

class priphery_compoent
{
  public :

  //std::shared_ptr<int>
  float lastX = Screen::MAIN_SCREEN_WIDTH / 2.0f;
  float lastY = Screen::MAIN_SCREEN_HIGHT / 2.0f;
  bool firstMouse = true;
  bool firstStick = true;

  view_lenz* local_lenz =nullptr;

  int pad_present;
  const char* pad_name;

  std::string pad_log;
  int pad_count;
   const float* axes;

  int but_pad_count;
   const unsigned char* buttons;

  void set_current_lenz(int in_pos)
  {
    periphery::current_lenz_pos = in_pos;
  }


};




#endif
