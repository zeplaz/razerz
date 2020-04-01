

#include "engine.hpp"


void (*terrain_depth_callback)(float in_depth);

//float r_mgmt.ecouterait. = 0.0f;        // time between current frame and last frame
float lastFrame = 0.0f;
sym_logger so_engine_loger;

//void (*vid_cap_callback)(GLFWwindow*,int,std::string);




  //static constexpr GLfloat STAIC_ONE = 1.0f;

  void Engine::set_engine_state(Engine_State in_state)
  {
    engine_state = in_state;
  }

  void Engine::set_cmd_mode(Cmd_Mode in_cmd_mode)
  {
    cmd_mode = in_cmd_mode;
  }

  Engine::Engine()
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

  void Engine::ignition()
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

    //prim_lenz = new view_lenz();
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
     periphery::glfwSetCursorPosCallback(glfw_window, periphery::mouse_callback);
     periphery::glfwSetScrollCallback(glfw_window, periphery::scroll_callback);
     periphery::glfwSetJoystickCallback(periphery::joystick_callback);

    so_engine_loger(i_log);

    std::cout << "load_lenz\n";

    std::cout <<"###setting defult lenz 0...\n";
    gl_matrixz.view_matrix     =  r_mgmt.lenz_array[0].return_lenz_view();
    gl_matrixz.Projection      =  r_mgmt.lenz_array[0].lenz_projection();
    gl_matrixz.view_projection = gl_matrixz.Projection*gl_matrixz.view_matrix;

    periphery::vid_cap_callback = &multiframe_capturer::set_paramz;
    arg_a1 = new arrangment_A1();

    arg_a1->set_local_pointerz(&r_mgmt.lenz_array[0],global_r_mgmt);
    arg_a1->load_complie_test_shaderz();
    arg_a1->init();
    arg_a1->process_local_data();
    //test_Arng_A1.
  }

  int Engine::cylce()
  { if(glfwWindowShouldClose(glfw_window))
    {
      engine_state = Engine_State::SHUTDOWN;
      return S_SHUTDOWN;
    }
    while(!glfwWindowShouldClose(glfw_window))
    {
        std::cout << "\n**********engine_cycle::" << cycle_count <<'\n';
/*

      if(active_user_stick)
      {
        axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &pad_count);
        prim_lenz->process_joystick(axes[0],axes[1]);
      }
*/
    cycle_count++;
    r_mgmt.ecouterait.update_clock(glfwGetTime());

    float currentFrame = glfwGetTime();
    r_mgmt.ecouterait.delta_time = currentFrame - lastFrame;
    lastFrame = currentFrame;
    process_input_glfw(glfw_window);


    std::cout << "\n*ecy2:"<<'\n';

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
    gl_matrixz.view_matrix =  r_mgmt.lenz_array[0].return_lenz_view();
    gl_matrixz.Projection  = r_mgmt.lenz_array[0].lenz_projection();

    gl_matrixz.view_projection = glm::mat4(1.f);
    gl_matrixz.view_projection = gl_matrixz.Projection*gl_matrixz.view_matrix;

std::cout << "\n*ecy3:"<<'\n';

  /*
  #############################  update ######################
  */
    arg_a1->update();
  glfwGetFramebufferSize(glfw_window,&frame_buf_width,&frame_buf_hight);
  std::cout << "\n*^updatecompleateecy3:"<<'\n';
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
          std::cout << "\n*^render_com:"<<'\n';
      glfwPollEvents();
    //  std::cout << "\nJOYSICK AXEZ::"<<axes[0] <<"   %%%:::"<< axes[1] <<'\n';
  }
  return 0;
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
