
/// pars files
//setup opengl
///drivers.

//tool for map ediotr.

/*
/menu
//MAIN_MENUz
//LOAD.
//SAVE.
//add image to processing que
//
*/


#include "graphicz/gl_ctlr.hpp"

#include <array>
#include <utility>
/* Turn a NULL pointer string into an empty string */
#define NULLSTR(x) (((x)!=NULL)?(x):(""))
#define Log(x) { if(verbose) printf x; }



////mailoop

int comand_calback(std::string in_cmd)
{
  /*
  switch () {
    case :
  }*/
  return 1;
}
bool msg_waiting()
{
  //scann the memory for a update?
}

void background_callback(void*)
{

};
static void st_background_cb(void* in)
{
   background_callback(in);
}


using array_4INT = std::array<int,4>;
using str_arr4INT_pair = std::pair<std::string, array_4INT>;


int grab_cmd(std::string& out_cmd)
{
  std::cin >> out_cmd;
  std::cout << '\n*processingcmd;;;*\n';
  if(out_cmd == "0" || out_cmd== "yes" || out_cmd== "y")
  {
    std::cout << "##SHUTTTINGDOWN>>>**runquitcalled\n\n";
    return 0;
  }
  else
  {
   return comand_calback(out_cmd);
  }
}
//will catch each loop! and pause...able to quit..
#define DEBUG_11

int main(int argc, char* argv[])

{

  int run = 1;
  int wait_statuz = 0;
  std::string main_cmdbuff;

///tests for windows beofre moving to its proper place in the engine.

  const char*  gl_window_label_test= "label_fortest_move me!";

  /// setup wondows... this is all gui stuff.
  Fl_Window *topwin = new Fl_Window(800, 300);

  gl_window_framework* gl_fwork_test_window1 = new gl_window_framework(50,50,380,460,gl_window_label_test); // needs new consturctor for the pair..

  gl_fwork_test_window1->end();

  topwin->end();
  topwin->resizable(gl_fwork_test_window1);
  topwin->label("TOPWINDOW PANNEL TEST");
  topwin->show(argc, argv);

// add the callbacks here! or have engine do it lol
  Fl::add_idle(st_background_cb);


// main loop should also just been in eninge.cycle();
  while(run)
  {
//run updates
    gl_fwork_test_window1->draw();

    wait_statuz = Fl::wait();
    std::cout << " ##DEBUG:: runSAT::" << run << " wait_stauz::" << wait_statuz<< "\n ***************\n";
    if(wait_statuz == 0)
    {
      std::cout << "\n***->WINDOWS ARE CLOSED SHUTDOWN?:(y/other):";
      run =grab_cmd(main_cmdbuff);
      std::cout << "  DBG_lastcomd::" << main_cmdbuff <<'\n';
    }
    #ifdef DEBUG_11
    std::cout << "\n#DEBUGO::CYCLEINPUT:(y/other):";
    run =grab_cmd(main_cmdbuff);
    #endif
  }

  return 0;
}








/*

class geo_scene
{
  void set current_paramz()
  {

  }
  //std::list<> m_geo_list;
  void draw()
  {
    lClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  }
};

//show()
//redraw_overlay()



//#include <glatter/glatter.h>

#if defined(_WIN32) && !defined(__MINGW32__) && !defined(__CYGWIN__)
#pragma warning( push )
#pragma warning( disable : 4244)
#pragma warning( disable : 4305)
#endif

template<typename T_handle>
class handler
{
protected :
int id;
public:

  void trazmist_notice();
  int  handle_msg();
  int  cycle();
  void init();

};



*/
