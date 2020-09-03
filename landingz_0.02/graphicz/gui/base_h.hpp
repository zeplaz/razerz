


GLContext context();

Fl_Gl_Window ()

float ppu=pixels_per_unit()

FL_Mode
mode();

make_current()
make_overlay_current();

Fl_Gl_Window_Driver * ptr_flgldriver gl_driver();


template<typename gk_frame>
class framework
{
  freind void draw(framework<gk_frame>)
  {

  }
  freind void handle(framework<gk_frame>)
  {

  }

};

class m_crl_tasker{

  //inline  static constexpr float F_ZERO = 0.0f;

  template<typename Type>
  freind class task;

  template<typename Type>
  freind void conductor<Type>::dispatch_task(task<Type>*);

  template<typename Type>
  freind int que_num(){
    return ++m_ctl_tasker::counter;
  }
  static int counter;
}
