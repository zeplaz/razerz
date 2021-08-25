


#ifndef RZ2_RENDERER_MCP_HPP
#define RZ2_RENDERER_MCP_HPP

//render_MCP
#include "opengl_lib.hpp"

using namespace rz2; 

namespace rz2
{


enum COLOUR_SPACE_POS {
  RED_POS,
  GREEN_POS,
  BLUE_POS,
  ALPHA_POS
};

enum class RENDER_API{
      OPENGL,
      VULKAN,
      DEBUG_OPENGL,
      DEBUG_VULKAN
    
};




class Windows_sdl
{
public:
 
    int mwindowID;
    int mwindow_displayID;

    Windows_sdl();
    bool init();
    void handle_event(SDL_Event& e);
    void focus();
    void render();
    void free_window();

    int get_width();
    int get_height();

    bool hasMouseFocus();
    bool hasKeyboardFocus();
    bool isMinimized();

private :
    //Window data
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SDL_GLContext gContext;
   //Window dimensions
    int mWidth;
    int mHeight;

    //Window focus
    bool mMouseFocus;
    bool mKeyboardFocus;
    bool mFullScreen;
    bool mMinimized;
    bool mShown;
};

class Renderer{

private : 
RENDER_API render_api;
public :

inline void set_render_api(RENDER_API in_apitype)
{
 render_api= in_apitype;
}
std::unordered_map<int,Windows_sdl> window_map;


int number_of_windows;

void setup()
{
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
      SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
 
  for(int i = 0; i < number_of_windows; i++)
  {
    std::cout <<"settingup window number::"<< i+1 << '\n';
    Windows_sdl new_window; 
    new_window.init();
    window_map.insert(std::make_pair(new_window.mwindowID,new_window));
  }

  if(render_api == RENDER_API::OPENGL)
  {
      rz2::gl_configure();
  }
}

};

}

#endif