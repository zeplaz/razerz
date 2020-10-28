
#ifndef RZ_SCREEN_CONTEXT_HPP
#define RZ_SCREEN_CONTEXT_HPP

#include "../basez/screen.hpp"
#include "../basez/gl_lib_z.hpp"
#include "../basez/sym_object.hpp"

class screen_window_context : public sym_object{
  screenz current_screen;
  int current_lenz;
  GLuint current_viewport;
};

#endif
