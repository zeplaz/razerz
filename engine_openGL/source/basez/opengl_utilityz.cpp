
#include "opengl_utilityz.hpp"

#include <ctime>
#include <stdio.h>
//#include "lenz.hpp"

//static view_lenz* prim_lenz =nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    screen_beenresized = true;
}

void capture_frame_buff_avi(GLFWwindow*window,void(*vid_cap_callback)(GLFWwindow*,int,std::string))
{
  int tocap_frame;
  std::string file_name;

  std::cout<< "\n\n |-Acttivating framebuf to avi-|\n"
           << "plz enter export_filename:";
  std::cin >> file_name;
  std::cout<<  "\n plz enter num of frames:";
  std::cin >>tocap_frame;

  (*vid_cap_callback)(window,tocap_frame,file_name);

  std::cout<< "\n will gen vide_"<< file_name<< "\n capting framecount::"<<tocap_frame <<'\n';

}

void take_screenshot_to_file(int& frame_buf_width,int& frame_buf_hieght)
{
  #pragma pack(push,1)
  struct {
    unsigned char idenity_size;
    unsigned char colour_map_type;
    unsigned char imagetype;
    short cmap_start;
    short cmap_size;
    unsigned char num_bits_palette;
    short xorigin;
    short yorigin;
    short width;
    short height;
    unsigned char bitzperpix;
    unsigned char descriptor_bit;

  }tga_header;
  #pragma pack(pop)

  int row_size  = ((frame_buf_width*3*3)& ~3);
  int data_size = row_size*frame_buf_hieght;
  unsigned char* data = new unsigned char [data_size];

glReadPixels(0,0,frame_buf_width,frame_buf_hieght,GL_BGR,GL_UNSIGNED_BYTE,data);

memset(&tga_header,0,sizeof(tga_header));
tga_header.imagetype =2;
tga_header.width =(short)frame_buf_width;
tga_header.height=(short)frame_buf_hieght;
tga_header.bitzperpix =24;

std::string file_name;
std::cout << "screenshotcaptured...what shall filenamebe?:";
std::cin >> file_name;

  time_t now = time(0);
 // convert now to string form
   char* dt = ctime(&now);
   std::string write_name = file_name+"_"+dt+".tga";

   FILE * screen_out = fopen(write_name.c_str(),"wb");
  fwrite(&tga_header,sizeof(tga_header),1,screen_out);
  fwrite(data,data_size,1,screen_out);
  fclose(screen_out);
  std::cout << "file writen to running dir::" << write_name <<'\n';
  delete []data;

}

void APIENTRY GLAPIENTRY glDebugOutput(GLenum source,
                         GLenum type,
                         GLuint id,
                         GLenum severity,
                         GLsizei length,
                         const GLchar *message,
                         const void *userParam)
{
  //ignore non-significant error/warning codes
 if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

 std::cout << "---------------" << std::endl;
 std::cout << "Debug message (" << id << "): " <<  message << std::endl;

 switch (source)
 {
     case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
     case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
     case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
     case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
     case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
     case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
 } std::cout << std::endl;

 switch (type)
 {
     case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
     case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
     case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
     case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
     case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
     case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
     case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
     case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
     case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
 } std::cout << std::endl;

 switch (severity)
 {
     case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
     case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
     case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
     case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
 } std::cout << std::endl;
 std::cout << std::endl;
}

int opengl_context_settup()
{
  glewExperimental = GL_TRUE;
  //launch gluitInit
  if (!glfwInit())
{
  std::cout << "flfwinit faild :()\n";
  return -1;
}

glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,5);
glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
return 0;
}

int run_opengl_setup(GLFWwindow* out_window)
{

if(!out_window)
{
  glfwTerminate();
  std::cout <<"windowfailureload\n";
  return -3;
}

glfwMakeContextCurrent(out_window);
glfwSetFramebufferSizeCallback(out_window, framebuffer_size_callback);

GLenum glewErr = glewInit();
std::cout << "glew_code::" << glewErr <<'\n' <<'\n';
glViewport( 0, 0, Screen::MAIN_SCREEN_WIDTH, Screen::MAIN_SCREEN_HIGHT );
GLint flags;
glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
{
std::cout <<"debug iniaizled\n";
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
glDebugMessageCallback(glDebugOutput, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}

  return 0;
}
