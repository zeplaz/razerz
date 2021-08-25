



#include "engine_MCP.hpp"

//import test_mod;

//#include "static_interface.hpp"
#include <thread>
int main(int argc, char* argv[])
{

  //std::jthread threadj;
  std::jthread j1;

  std::cout << "hardwarethread::" << std::jthread::hardware_concurrency() <<'\n';
  Engine engine; 
  engine.configure(argc,argv);
  engine.ignition();

  engine.shutdown();  
  std::cout <<"\n #####compleate\n \n  \a";
  return 0;
}
