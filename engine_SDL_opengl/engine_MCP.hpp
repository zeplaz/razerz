

#ifndef RZ2_ENGINE_HPP
#define RZ2_ENGINE_HPP



#include <array>
#include <utility>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "renderer_MCP.hpp"

using namespace rz2; 

namespace rz2
{

enum class Engine_State : unsigned char
{
  INITAL,
  CONFIGURED,
  IGNITION,
  RUNNING,
  SHUTDOWN,
  STALL,
  FAILURE
};

enum Systems_Online 
{
  SYM_SDL,
  RENDERER,
  SYM_INPUTS
};



namespace globalz {
static float delta_time = 0.0f;	// time between current frame and last frame
static float lastFrame = 0.0f;
}


class Engine
{
  private : 

  std::array<bool,4> syms_array;
  Renderer renderer;

  public :
  Engine_State engine_status;
  OS_Type os; 
  Engine()
  {
    engine_status = Engine_State::INITAL;
    renderer.number_of_windows = 0;

    #ifdef __LINUX__
    os = OS_Type::LINUX;
    #endif // DEBUG

     #ifdef WIN
    os = OS_Type::WIN;
    #endif // DEBUG
  }
  
  void create_window();
  void configure(int argc, char* argv[]);

  int run();
  void shutdown();
  void ignition();

};
}

#endif