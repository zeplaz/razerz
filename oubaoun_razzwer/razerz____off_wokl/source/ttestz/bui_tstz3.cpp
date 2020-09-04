

#include "../MCP_cmd/engine.hpp"


int main(int argc, char* argv[])
{
  Engine engine;

  std::cout <<"#create_engine compleated lanuch igniton\n";
  engine.ignition();

  glClearColor(0.2f, 0.2f, 0.1f, 1.0f);


  std::cout <<"#####entering main loop setup compleate;\n \n";
  int cycle_status;
  //process keyz

  while(cycle_status != S_SHUTDOWN)
  {
    cycle_status =  engine.cylce();
     //modelmover.clear();
  }

 /*
 * SCENE setupz and load
 */

std::cout <<"\n #####compleate\n \n  \a";
return 0;
}
