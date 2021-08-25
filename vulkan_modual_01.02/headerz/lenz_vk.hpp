
#ifndef VULKANI_LENZ_HPP
#define VULKANI_LENZ_HPP

#include "vk_defintions.hpp"


namespace Screen {
static const int MAIN_SCREEN_WIDTH = 1000;
static const int MAIN_SCREEN_HIGHT = 800;

enum Pos_Lenz{
  POS_LENZ0,
  POS_LENZ1,
  POS_LENZ2,
  POS_LENZ3,
  POS_LENZ4,
  POS_LENZ5
};


  struct view_monitor{
    std::array<uint32_t,6> Lenz_ID;
    std::array<uint32_t,6> viewports_glID;
//make sure to put renbers and a function guff here.
  };
};
using namespace Screen;

struct  screenz{
  int total_width;
  int total_hieght;
  view_monitor* active_view_monitors;

};

class view_lenz
{
  private :

  glm::vec3 lenz_pos = glm::vec3(0.0f,0.0f,3.0f);
  glm::vec3 lenz_target =  glm::vec3(0.0f,0.0f,0.0f);
  glm::vec3 lenz_up = glm::vec3(0.0f,1.0f,0.0f);
  glm::vec3 lenz_front = glm::vec3(0.0f,0.0f,-1.0f);
  glm::vec3 lenz_right;
  glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::mat4 view = glm::mat4(1.0f);

  float MovementSpeed = 2.5;
  float Yaw =-90.0f;
  float Pitch = 0.0f;
  float Zoom =45.0f;
  float mouse_sesitivity =0.1f;
  float joystick_sesitivity = 1.9f;

  float feild_of_view;
  float near_plane;
  float far_plane;
  float view_aspec_ratio;

  glm::vec3 get_lenz_reverse_drection()
  {
    return glm::normalize(lenz_pos-lenz_target);
  }

  void set_view_movement()
  {
    view = glm::lookAt(lenz_pos,lenz_pos+lenz_front,lenz_up);
  }

  void update_lenz()
  {
    glm::vec3 updatefront;
    updatefront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    updatefront.y = sin(glm::radians(Pitch));
    updatefront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    lenz_front = glm::normalize(updatefront);
    lenz_right = glm::normalize(glm::cross(lenz_front,world_up));
    lenz_up = glm::normalize(glm::cross(lenz_right, lenz_front));
  }
  public :

  void set_postion();
  glm::mat4  translation_rotation();
  void set_lenz();
  //void Process_keyboard(Camera_Movement direction_move, float delta_time);
  view_lenz()
  {
    feild_of_view=50.0f;
    near_plane=0.01f;
    far_plane = 1000.0f;
    view_aspec_ratio=(float)MAIN_SCREEN_WIDTH/(float)MAIN_SCREEN_HIGHT;
    update_lenz();
  }
  void update_aspec_ratio(GLint frame_buf_width,GLint frame_buf_hight)
  {
    view_aspec_ratio =(float)frame_buf_width/(float)frame_buf_hight;
  }

  void process_joystick(float xoff, float yoff)
  {
    xoff*=joystick_sesitivity;
    yoff*=joystick_sesitivity;
    Yaw +=xoff;
    Pitch +=yoff;
    if(Pitch>89.0f)
    Pitch = 89.0f;
    else if(Pitch <-89.0f)
    {
      Pitch = -89.0f;
    }
    update_lenz();
    std::cout << "joypickup>:" << Yaw <<"   pitch::" << Pitch <<'\n';
  }
  void process_mouse(float xoff, float yoff)
  {
    xoff*=mouse_sesitivity;
    yoff*=mouse_sesitivity;
    Yaw +=xoff;
    Pitch +=yoff;
    if(Pitch>89.0f)
    Pitch = 89.0f;
    else if(Pitch <-89.0f)
    {
      Pitch = -89.0f;
    }
    update_lenz();
  }

  void process_scroll(float yoff)
  {
    if(Zoom>=1.0f && Zoom<=45.0f)
    {
      Zoom-=yoff;
    }
    else if(Zoom<=1.0f)
    {
      Zoom = 1.0f;
    }
    else if (Zoom>= 45.0f)
    {Zoom = 45.0f;}


  }
  void lenz_move(float delta_time, char key_press)
  {   float velocity = delta_time* MovementSpeed;
      switch(key_press)
      {
        case 'w' :
        {
          lenz_pos += velocity*lenz_front;
          break;
        }

        case 's' :
        {
         lenz_pos -=velocity*lenz_front;
          break;
        }

        case 'a' :
        {
          lenz_pos-= glm::normalize(glm::cross(lenz_front, lenz_up)) * velocity;
          break;
        }

        case 'd' :
        {
          lenz_pos+=glm::normalize(glm::cross(lenz_front, lenz_up)) * velocity;
          break;
        }
        default : break;
      }


  }

  glm::mat4 return_lenz_view()
  {
    glm::mat4 view_matrix(1.f);
    view_matrix = glm::lookAt(lenz_pos, lenz_pos + lenz_front, lenz_up);
     return view_matrix;
  }


  void normalize_anglez()
  {
    Pitch = fmodf(Pitch,360.0f);
    if(Pitch<0.0f)
    {
      Pitch+360.0f;
    }
    if(Yaw>MAX_V_ANGLE)
    {
      Yaw = MAX_V_ANGLE;
    }
      else if (Yaw<-MAX_V_ANGLE)
      {
        Yaw =-MAX_V_ANGLE;
      }
    }

  void set_feild_of_view(float fov)
  {
    feild_of_view=fov;
  }

  inline float aspect_ratio_cal()
  {
    return view_aspec_ratio;
  }

  glm::mat4 return_orientation() const
  {
      glm::mat4 orientation;
      orientation = glm::rotate(orientation, glm::radians(Pitch), glm::vec3(1,0,0));
      orientation = glm::rotate(orientation, glm::radians(Yaw), glm::vec3(0,1,0));
    return orientation;
  }


  void update_cam_front()
  {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw))*cos(glm::radians(Pitch));
  }

  glm::mat4 lenz_projection()
  {
    glm::mat4 Projection(1.f);
    Projection = glm::perspective(glm::radians(feild_of_view),
                                            view_aspec_ratio, near_plane, far_plane);
   return Projection;
  }

};
