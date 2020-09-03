
#include "soild_state_data.hpp"
#include "gl_ctlr.hpp"

 int gl_window_framework::gl_windows_active = 0;


constexpr int TEST_MAIN_WIN_WIDTH = 1190;
constexpr int TEST_MAIN_WIN_HIEGHT = 875;


static Fl_Double_Window* build_gui()
{
  Fl_Double_Window* re_window;
  {
    Fl_Double_Window* window_ptr_main =  new Fl_Double_Window(TEST_MAIN_WIN_WIDTH, TEST_MAIN_WIN_HIEGHT);
    re_window = window_ptr_main; if (re_window) {/* empty */}

  }



}















 bool gl_window_framework::opengl_context_startup()
 {
   if(gl_windows_active != 0)

   {
      make_current();
      gl_windows_active++;
   }
  else
   {
    gl_windows_active++;
    Fl::use_high_res_GL(1);
    glewExperimental = GL_TRUE;
    std::cout << "\n ##OPENGL_CONTEXT_STATUP...\n***********\n";

    make_current();
    GLenum err = glewInit();


     std::cout << "glew_code::" << err <<'\n' <<'\n';

    if (GLEW_OK != err)
    {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "glew_INitFAILDError: %s\n", glewGetErrorString(err));
      return false;
    }
    if(GL_ARB_vertex_buffer_object){
                    fprintf(stdout,"VBO SUPPORTED\n");
                 }

    if (glewGetExtension("GL_ARB_vertex_buffer_object")!=GL_TRUE){
          std::cout<<"GetExtension:glGenBuffersARB failed\n";
                      }

     #ifdef linux
     std::cout << "##USEING LINUX++OPENGL STUFF\n\n";
                    if(!glGenBuffersARB   ){glGenBuffersARB    = (PFNGLGENBUFFERSARBPROC   )glXGetProcAddress((const GLubyte*)"glGenBuffersARB");      std::cout<<"glew failed\n";}
                    if(!glBindBufferARB   ){glBindBufferARB    = (PFNGLBINDBUFFERARBPROC   )glXGetProcAddress((const GLubyte*)"glBindBufferARB");      std::cout<<"glew failed\n";}
                    if(!glBufferDataARB   ){glBufferDataARB    = (PFNGLBUFFERDATAARBPROC   )glXGetProcAddress((const GLubyte*)"glBufferDataARB ");     std::cout<<"glew failed\n";}
                    if(!glDeleteBuffersARB){glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)glXGetProcAddress((const GLubyte*)"glDeleteBuffersARB");   std::cout<<"glew failed\n";}
                    #endif


                    if(!glGenBuffersARB   )std::cout << "glGenBuffersARB    is not well loaded\n";
                    if(!glBindBufferARB   )std::cout << "glBindBufferARB    is not well loaded\n";
                    if(!glBufferDataARB   )std::cout << "glBufferDataARB    is not well loaded\n";
                    if(!glDeleteBuffersARB)std::cout << "glDeleteBuffersARB is not well loaded\n";

    fprintf(stdout, "\n#####->Status:\n Using GLEW %s, GL_VERSION %s, GL_SHADING_LANGUAGE_VERSION %s​, \n GL_VENDOR %s, \n GL_RENDERER %s  \n********\n\n",
                      glewGetString(GLEW_VERSION), glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION),glGetString(GL_VENDOR), glGetString(GL_RENDERER));

    //glGetIntegerv(GL_MAJOR_VERSION, *);
    //glGetIntegerv(GL_MINOR_VERSION, *);

glClearColor(10,0,10,1);
glEnable(GL_DEPTH_TEST);


GLint flags;
glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
{
std::cout <<"-->>####debug iniaizled\n";
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(glDebugOutput, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

}
/// use preposer maco #ifdef DEBUG_OPENGLFORCE...etc
#ifdef DEBUG_OPENGL_FORCE
  else {
    std::cout << "##WARNING DEBUGCONTEXT NOT ACTIVE ATEMPTING ANYWAYZ*DISABLE THIS!!!**:DEBUG_OPENGL_FORCE:defined->gui_opengl_ulity,hpp##\n";
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
  }
#endif
}
 return true;
}

void  gl_window_framework::draw()
  {

    static bool first_run = true;

    if(first_run)
    {

      if(!opengl_context_startup())
      {
        std::cerr << "####ERROR FAILURE TO LOAD GLHANDLE????\n";
        return;
      }

      glViewport(0,0,pixel_w(),pixel_h());
      first_run = false;
    }


    #ifndef MESA
    glDrawBuffer(GL_FRONT_AND_BACK);
    #endif // !MESA

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


/*    #ifndef MESA
    glDrawBuffer(GL_BACK);
    #endif // !MESA*/


    if(!valid())
    {
      //rest of ilisatiotion sutf..
      std::cout <<"DRAWCALL NOT VAILD ATEMPTIGN VIEWPORRT??\n";
      glViewport(0, 0, pixel_w(), pixel_h());
    }

    if(!context_valid())
    {
      std::cout<< "->##CONTEXT NOT VAILD IN DRAW CALL>>> LOAD TEXTURE && MAKE CURRENT?\n"; //texturez?
    }
    glClearColor(rValue, gValue, bValue, bAlpha);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    //glUseProgram();
    //glUniform...
    ///drawz//
}

/*make_current();
if(!valid())
{
  //setup projectionz
  valid(1);
}
//detection loading
*/

void gl_window_framework::add_output(const char *format, ...)
{
  std::cout <<"##DEBUG::glfmworkwindow:: addoutput...\n";
  va_list args;
  char line_buffer[10000];
  va_start(args, format);
  vsnprintf(line_buffer, sizeof(line_buffer)-1, format, args);
  va_end(args);
  //output->buffer()->append(line_buffer);
//  output->scroll(10000, 0);
//  output->redraw();
}



int gl_window_framework::handle(int event)
{
  std::cout << "DEBUG:: INSIDEHANDLE:glwindoframwork:event::"<<event << '\n' ;
  static int first = 1;
    if (first && event == FL_SHOW && shown()) {
      first = 0;
      make_current();

      const uchar *glv = glGetString(GL_VERSION);
      add_output("GL_VERSION=%s\n", glv);
      sscanf((const char *)glv, "%d", &gl_version_major);
      if (gl_version_major < 3) add_output("\nThis platform does not support OpenGL V3\n\n");
      redraw();
      }

  switch(event)
  {
    case FL_PUSH:
    {
      //Fl::event_x()//Fl::event_y()
      return 1;
    }

    case FL_DRAG :
    {
      return 1;
    }

    case FL_RELEASE :
    {

      return 1;
    }

    case FL_FOCUS :
    case FL_UNFOCUS :

    return 1;

    case FL_KEYBOARD:
    {
      //another swtich??
      switch(Fl::event_key())
      {

      }
      return 1;
    }
    default:
    return Fl_Gl_Window::handle(event);

  }}
