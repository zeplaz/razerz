
#include "../basez/opengl_utilityz.hpp"
#include "../basez/3rdparty/frame_to_video.hpp"

//swtup
float delta_time = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//callbayckfunz
void process_input_glfw(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//callbackglbalvars
float lastX = MAIN_SCREEN_WIDTH / 2.0f;
float lastY = MAIN_SCREEN_HIGHT / 2.0f;
bool firstMouse = true;
bool is_cursor_captured = false;

//opencv capture to AVI globals
bool take_frame_video = false;
void (*vid_cap_callback)(GLFWwindow*,int,std::string);

//lenZ_screan
GLint frame_buf_width,frame_buf_hight;
view_lenz* prim_lenz =nullptr;
//auto prt_set_pramz = std::mem_fn(&multiframe_capturer::set_paramz); (multiframe_capturer::set_paramz)
/*
* MAIN!
*/
int main(int argc, char* argv[])
{
  /*
  STARTUP
  */
  int errocode;
  GLFWwindow* glfw_window;

  std::cout << "launching Main Window\n";
  errocode = opengl_context_settup();

  std::cout << "###openglcontexcode::"<< errocode <<'\n';
  prim_lenz = new view_lenz();

  glfw_window = glfwCreateWindow(MAIN_SCREEN_WIDTH,MAIN_SCREEN_HIGHT,"cmdz_tooltext_teser",NULL,NULL);
  glfwSetCursorPosCallback(glfw_window,mouse_callback);
  glfwSetScrollCallback(glfw_window, scroll_callback);

  errocode = run_opengl_setup(glfw_window);
  std::cout << "\n ###openglsetupcode::"<< errocode << "\n";

  /*
  BEGIN SHADER WORK
  */

  //  gl_shader_t* etc =  new  gl_shader_t(); or other method
  int errcode = run_parse();
  std::map<unsigned int,shader_tuple_type*>* shder_tup_map =  return_shdrmap_ptr_TV();

  //std::vector<int> have shaderlists...for paticlarporgams...

  bool is_complie = true;
  /*
  inailzes shaders
  */

  //->setup_shader_code(shder_tup_map->at(gl_lib_enum));
  //shaderlist.push_back(gl_lib_enum);
  //is_complie = NAMEOFSHADER->create_link_program(----);
  //->test_flags();
  if(is_complie == false)
  {
    std::cerr <<"ERROR compute COMPLIE FAILD\n";
    exit(-1);
  }


  std::cout << "##SHADER settup COMPLEATE\n";

/*
FINAL SETUP BEFORE MAINLOOP
*/
    glClearColor(0.2f, 0.0f, 0.1f, 1.0f);
    //if want videocallback
    multiframe_capturer mf_c;
    vid_cap_callback = &multiframe_capturer::set_paramz;

    /*
    PIMARY WHILE LOOP... move to own class?
    */
std::cout <<"#####entering main loop setup compleate;\n \n";

    while(!glfwWindowShouldClose(glfw_window))
    {

      float currentFrame = glfwGetTime();
      delta_time = currentFrame - lastFrame;
      lastFrame = currentFrame;

      process_input_glfw(glfw_window);
      glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
      glfwGetFramebufferSize(glfw_window,&frame_buf_width,&frame_buf_hight);

      /*
      DRAW
      */





      //swap
      glfwSwapBuffers(glfw_window);

      //ifvideo
      if(take_frame_video == true)
      { bool compleate;

        mf_c.export_framebuff_avi(&compleate);
        if(compleate ==true)
        {
          take_frame_video = false;
        }
      }

      glfwPollEvents();
    }

  //should have cleanup!
return 0;
}

/*
CALLBACK FUNCTIONS..
figureout how to move these...
*/
///boilplate move to utilitiz
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
    prim_lenz->lenz_move(delta_time,'w');
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    prim_lenz->lenz_move(delta_time,'s');
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    prim_lenz->lenz_move(delta_time,'a');
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    prim_lenz->lenz_move(delta_time,'d');
  }
}
