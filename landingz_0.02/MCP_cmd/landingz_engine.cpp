

#include "landingz_engine.hpp"
#include "openGL_CMDer.hpp"



Engine::Engine()
{
  std::cout <<"\n#->engine constructor~\n";
  engine_state   =Engine_State::INITAL;
  cmd_mode =  Cmd_Mode::INITAL;
  run_durration = 0.0;;
  cycle_count   =0;
  //global_r_mgmt = &r_mgmt;
}


void Engine::ignition();
int Engine::cylce();
