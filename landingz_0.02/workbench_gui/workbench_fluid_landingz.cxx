// generated by Fast Light User Interface Designer (fluid) version 1.0400

#include "workbench_fluid_landingz.h"

Fl_Menu_Item opengl_windowUI::menu_menu_bar_main[] = {
 {"file/i/o", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"save", 0,  (Fl_Callback*)file_menu_cb, (void*)("save"), 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"load", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"quit", 0,  (Fl_Callback*)file_menu_cb, (void*)("quit"), 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};

opengl_windowUI::opengl_windowUI() {
  { main_window = new Fl_Double_Window(1165, 840, "main_window");
    main_window->user_data((void*)(this));
    { Fl_Group* o = new Fl_Group(0, 0, 1180, 725);
      o->align(Fl_Align(FL_ALIGN_BOTTOM_LEFT));
      { Fl_Group* o = new Fl_Group(5, 53, 1155, 672, "main_view");
        o->align(Fl_Align(FL_ALIGN_TOP_RIGHT));
        { Fl_Box* o = new Fl_Box(45, 53, 535, 629, "gl_frame");
          o->box(FL_BORDER_FRAME);
          o->color(FL_GREEN);
          o->align(Fl_Align(FL_ALIGN_BOTTOM_LEFT));
          Fl_Group::current()->resizable(o);
        } // Fl_Box* o
        { gl_wfwk = new gl_window_framework(60, 53, 520, 619, "gl_wfwk_view");
          gl_wfwk->box(FL_SHADOW_FRAME);
          gl_wfwk->color((Fl_Color)143);
          gl_wfwk->selection_color(FL_BACKGROUND_COLOR);
          gl_wfwk->labeltype(FL_NORMAL_LABEL);
          gl_wfwk->labelfont(0);
          gl_wfwk->labelsize(14);
          gl_wfwk->labelcolor(FL_FOREGROUND_COLOR);
          gl_wfwk->align(Fl_Align(FL_ALIGN_TOP_LEFT));
          gl_wfwk->when(FL_WHEN_RELEASE);
        } // gl_window_framework* gl_wfwk
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(0, 0, 1180, 40, "main_menu");
        o->align(Fl_Align(33));
        { Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 1180, 20, "menu_bar_main");
          o->menu(menu_menu_bar_main);
        } // Fl_Menu_Bar* o
        o->end();
      } // Fl_Group* o
      o->end();
    } // Fl_Group* o
    main_window->end();
  } // Fl_Double_Window* main_window
}

void opengl_windowUI::show(int argc,char **argv) {
  main_window->show(argc,argv);
}

void opengl_windowUI::file_menu_cb(Fl_Widget*,void*) {
  printf("##DEBUG::file_menu_callback\n");
}
