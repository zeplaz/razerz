
#include "periphery_input.hpp"
using namespace periphery;

bool is_cursor_captured = false;
bool active_user_stick =false;


bool string_callback = false;
//opencv capture to AVI REQUERD CALLBACKS


void periphery::joystick_status()
{
  pad_present  =GLFW_FALSE; //= glfwJoystickPresent(GLFW_JOYSTICK_1);

  std::cout<< "JOYSTICK_STATUZ::\n"<< pad_present;
 if( pad_present==GLFW_TRUE)
 {
    pad_name = glfwGetJoystickName(GLFW_JOYSTICK_1);

   std::string pad_log;
    pad_count;
  axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &pad_count);

    but_pad_count;
  buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &but_pad_count);

   pad_log = "\n*##->INPUTE_SENIZOR_DETECTED++Z<<::\n";
   pad_log += "pad_count::";
   pad_log+= std::to_string(pad_count);
   pad_log += "\n aexiz::";
   pad_log+= std::to_string(axes[0]);
   pad_log+= std::to_string(axes[1]);
   pad_log+="\n buttonzcount::";
   pad_log+=std::to_string(but_pad_count);
   pad_log+= "\n---**+\n\n";
   so_prif_loger(pad_log);

 }
}


void periphery::joystick_callback(int id, int event)
{
  std::string call_log;
  call_log= "\n\n___-INPUTCMDZ_DIVIZE_DETK:ZDI_->\n";
  call_log +=std::to_string(id);
  call_log +="\nto_string(event)::";
  call_log +=std::to_string(event);
  call_log +="\n";
  if (event == GLFW_CONNECTED)
{
call_log +="&*^CONNEION_ESTABLISHEDz^^|\n";
}
else if (event == GLFW_DISCONNECTED)
{
    call_log +="\n&*^LOSTCONNEION_ISHE_-^%Dz^^|\n";
}

//int axis_count;
//const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axis_count);

std::cout << "\nJOYSICK AXEZ::"<<axes[0] <<"   %%%:::"<< axes[1] <<'\n';
if(firstStick)
{
  lastX = (double)axes[0];
  lastY= (double) axes[1];
  firstStick = false;
}
float xoffset = (double)axes[0]- lastX;
float yoffset = lastY-(double) axes[1];
lastX=(double)axes[0];
lastY=(double) axes[1];
global_r_mgmt->lenz_array[current_lenz_pos].process_mouse(xoffset,yoffset);

so_prif_loger(call_log);
}

void periphery::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  if(firstMouse)
  {
    lastX = xpos;
    lastY= ypos;
    firstMouse = false;
  }
  float xoffset = xpos- lastX;
  float yoffset = lastY-ypos;
  lastX=xpos;
  lastY=ypos;
  global_r_mgmt->lenz_array[current_lenz_pos].process_mouse(xoffset,yoffset);
}

void periphery::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  global_r_mgmt->lenz_array[current_lenz_pos].process_scroll(yoffset);
}

void periphery::process_input_glfw(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {glfwSetWindowShouldClose(window, true);}

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
          {
            if(is_cursor_captured)
            {
              glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
              is_cursor_captured=false;
            }
            else
            {
              is_cursor_captured= true;
              glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            }
//  float lenz_speed = 2.5*delta_time;
  if(glfwGetKey(window,GLFW_KEY_F1) ==  GLFW_PRESS)
  {
    take_screenshot_to_file(frame_buf_width,frame_buf_hight);
  }

  if(glfwGetKey(window,GLFW_KEY_F2) ==  GLFW_PRESS)
  {
    capture_frame_buff_avi(window,vid_cap_callback);
    take_frame_video=true;
  }

  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    global_r_mgmt->lenz_array[current_lenz_pos].lenz_move(global_r_mgmt->emetteur.delta_time,'w');
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    global_r_mgmt->lenz_array[current_lenz_pos].lenz_move(global_r_mgmt->emetteur.delta_time,'s');
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    global_r_mgmt->lenz_array[current_lenz_pos].lenz_move(global_r_mgmt->emetteur.delta_time,'a');
  }
  if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    global_r_mgmt->lenz_array[current_lenz_pos].lenz_move(global_r_mgmt->emetteur.delta_time,'d');
  }

  if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
  {
    if(active_user_stick == true)
    {
      active_user_stick = false;
    }
    else  if(active_user_stick == false)
    {
      active_user_stick = true;
    }

  }
}
