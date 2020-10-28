


#ifndef RZ_ENGINE_HPP
#define RZ_ENGINE_HPP


#include "../MCP_cmd/arrangments.hpp"

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

//float r_mgmt.ecouterait. = 0.0f;        // time between current frame and last frame
float lastFrame = 0.0f;
sym_object so_engine_loger;
void process_input_glfw(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void joystick_callback(int id,int event);
bool string_callback = false;

float lastX = MAIN_SCREEN_WIDTH / 2.0f;
float lastY = MAIN_SCREEN_HIGHT / 2.0f;
bool firstMouse = true;
bool firstStick = true;
bool is_cursor_captured = false;
bool active_user_stick =false;
GLint frame_buf_width,frame_buf_hight;

view_lenz* prim_lenz =nullptr;

//opencv capture to AVI REQUERD CALLBACKS
bool take_frame_video = false;
void (*vid_cap_callback)(GLFWwindow*,int,std::string);
rez_mgmt* global_r_mgmt=nullptr;

int pad_present;
const char* pad_name;

std::string pad_log;
int pad_count;
 const float* axes;

int but_pad_count;
 const unsigned char* buttons;


struct Engine
{
  Engine_State engine_state;
  Cmd_Mode cmd_mode;
  long double run_durration;
  unsigned long long int cycle_count;

  arrangment_A1* arg_a1;

  multiframe_capturer mf_c;
  rez_mgmt r_mgmt;
  std::string terminal_cmd;

  //scene* active_scene;
  //
  int gl_errocode;
  GLFWwindow* glfw_window;
  //arrangment_A1 test_Arng_A1;

  struct {
    glm::mat4 view_projection;
    glm::mat4 view_matrix;
    glm::mat4 Projection;
  } gl_matrixz;




  static constexpr GLfloat STAIC_ONE = 1.0f;

  void set_engine_state(Engine_State in_state)
  {
    engine_state = in_state;
  }

  void set_cmd_mode(Cmd_Mode in_cmd_mode)
  {
    cmd_mode = in_cmd_mode;
  }

  Engine()
  {
    std::cout <<"\n#->engine constructor~\n";
     engine_state   =Engine_State::INITAL;
     cmd_mode =  Cmd_Mode::INITAL;
     run_durration = 0.0;;
     cycle_count   =0;
    global_r_mgmt = &r_mgmt;
     gl_matrixz.view_projection =glm::mat4(1.f);
     gl_matrixz.view_matrix = glm::mat4(1.f);
     gl_matrixz.Projection = glm::mat4(1.f);
  }
/*
  void configure(engine_config_pak& in_pak)
  {

    engine_state= Engine_State::CONFIGURED;
  }
  */

  void ignition()
  {
    cycle_count =0;
    std::string i_log;
    engine_state = Engine_State::IGNITION;

    std::cout<<"->#engine_IGNITIONz";
    i_log+="\n\n->#engine_IGNITIONz\n";

    gl_errocode = opengl_context_settup();
    std::cout << "###openglcontexcode::"<< gl_errocode <<'\n';
    i_log += "###openglcontexcode::";
    i_log += std::to_string(gl_errocode);

    std::cout << "launching Main Window\n";

    prim_lenz = new view_lenz();
    glfw_window = glfwCreateWindow(MAIN_SCREEN_WIDTH,MAIN_SCREEN_HIGHT,"cmdz_toolz_CMDWINDOWz",NULL,NULL);
    gl_errocode = run_opengl_setup(glfw_window);

    std::cout << "\n ###openglsetupcode::"<< gl_errocode << "\n";
    i_log += "\n###openglsetupcode::";
    i_log += std::to_string(gl_errocode);

     std::cout << "GLVIERSION::" << glGetString(GL_VERSION) <<'\n';
     std::cout << "GLVIERSION::" << glGetString(GL_SHADING_LANGUAGE_VERSION)<<'\n';
     i_log += "\n GLVIERSION::";
     /*std::string gl_v(glGetString(GL_VERSION));
     i_log += gl_v;
     i_log +="\n GL_SHADING_LANGUAGE_VIERSION::";
     std::string   gl_v2 (glGetString(GL_SHADING_LANGUAGE_VERSION));
     i_log += gl_v2;
*/
     glfwSetCursorPosCallback(glfw_window, mouse_callback);
     glfwSetScrollCallback(glfw_window, scroll_callback);
     glfwSetJoystickCallback(joystick_callback);

    so_engine_loger.run_log(i_log);

    std::cout << "load_lenz\n";
    gl_matrixz.view_matrix =  prim_lenz->return_lenz_view();
    gl_matrixz.Projection  = prim_lenz->lenz_projection();
    gl_matrixz.view_projection = gl_matrixz.Projection*gl_matrixz.view_matrix;

     pad_present = glfwJoystickPresent(GLFW_JOYSTICK_1);

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
      so_engine_loger.run_log(pad_log);


    }
      vid_cap_callback = &multiframe_capturer::set_paramz;
    arg_a1 = new arrangment_A1();

    arg_a1->set_local_pointerz(prim_lenz,global_r_mgmt);
    arg_a1->load_complie_test_shaderz();
    arg_a1->init();
    arg_a1->process_local_data();
    //test_Arng_A1.
  }




  int cylce()
  { if(glfwWindowShouldClose(glfw_window))
    {
      engine_state = Engine_State::SHUTDOWN;
      return S_SHUTDOWN;
    }
    while(!glfwWindowShouldClose(glfw_window))
    {




      if(active_user_stick)
      {
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &pad_count);
      /*  if(firstStick)
        {
          lastX = axes[0];
          lastY=  axes[1];
          firstStick = false;
        }
        float xoffset = axes[0]- lastX;
        float yoffset = lastY- axes[1];
        lastX=axes[0];
        lastY=axes[1];
*/
        prim_lenz->process_joystick(axes[0],axes[1]);
      }

    cycle_count++;
    r_mgmt.ecouterait.update_clock(glfwGetTime());

    float currentFrame = glfwGetTime();
    r_mgmt.ecouterait.delta_time = currentFrame - lastFrame;
    lastFrame = currentFrame;
    process_input_glfw(glfw_window);

    if(engine_state ==Engine_State::CONFIGURED)
    {
      std::cerr << "ERROR_engine is cold. plz run igintion engine is configured but not ignited!" << '\n';
      return -5;
    }
    else if(engine_state ==Engine_State::STALL)
    {

      std::cerr<< "###ENGINE IS STALLED"<<'\n';

      std::cout << "enter cmd...{none yet}:" <<'\n';
      std::cin  >> terminal_cmd;
      return 3;
    }
  //  else if(engine_state ==Engine_State::RUNNING ||engine_state ==Engine_State::IGNITION)
    engine_state=Engine_State::RUNNING;

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearBufferfv(GL_DEPTH, 0, &STAIC_ONE);
    gl_matrixz.view_matrix =  prim_lenz->return_lenz_view();
    gl_matrixz.Projection  = prim_lenz->lenz_projection();

    gl_matrixz.view_projection = glm::mat4(1.f);
    gl_matrixz.view_projection = gl_matrixz.Projection*gl_matrixz.view_matrix;


  /*
  #############################  update ######################
  */
    arg_a1->update();
  glfwGetFramebufferSize(glfw_window,&frame_buf_width,&frame_buf_hight);

  /*
  DRAW
  */
  arg_a1->render(gl_matrixz.view_matrix,gl_matrixz.Projection );
    glfwSwapBuffers(glfw_window);

    if(take_frame_video == true)
        { bool compleate;

          mf_c.export_framebuff_avi(&compleate);
          if(compleate ==true)
          {
            take_frame_video = false;
          }
        }

      glfwPollEvents();
      std::cout << "\nJOYSICK AXEZ::"<<axes[0] <<"   %%%:::"<< axes[1] <<'\n';
  }
  return 0;
}
};



///boilplate move to utilitiz

void joystick_callback(int id, int event)
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
prim_lenz->process_mouse(xoffset,yoffset);

so_engine_loger.run_log(call_log);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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
  prim_lenz->process_mouse(xoffset,yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  prim_lenz->process_scroll(yoffset);
}

void process_input_glfw(GLFWwindow* window)
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
    prim_lenz->lenz_move(global_r_mgmt->ecouterait.delta_time,'w');
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    prim_lenz->lenz_move(global_r_mgmt->ecouterait.delta_time,'s');
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    prim_lenz->lenz_move(global_r_mgmt->ecouterait.delta_time,'a');
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
    prim_lenz->lenz_move(global_r_mgmt->ecouterait.delta_time,'d');
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

//std::unordered_map<std::string,engine_config_pak> engine_pak_map;

  //std::string = "Orgburoz";
  //std::string = ""


/*
simple_engine_cmdz(std::string  in_cmd)
{
if(in_cmd=="init")
{

}
if(in_cmd=="ignite")
{

}

if(in_cmd=="configure")
{
  std::sting config_patch;

  std::cout <<"enter configure patch:";
  std::cint >> config_patch;

}
}

struct engine_config_pak
{

};*/

#endif
