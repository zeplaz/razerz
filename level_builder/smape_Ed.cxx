// generated by Fast Light User Interface Designer (fluid) version 1.0400

#include "smape_Ed.h"
static bool invert_threshold; 
int current_threshold; 

void mapcc_cb(Fl_Widget* widget,void* user_data) {
  if ((const char*)user_data == "t_slider") {
    double val = (double)(((Fl_Slider*)widget)->value());
    current_threshold = (int)val;
    printf("new threhholdvalue:: %f",val);
  }
  if ((const char*)user_data == "scan_thresh") {
    printf("threshold_processing...at %d \n",current_threshold);
  }
  if ((const char*)user_data == "inv_sign") {
    if(invert_threshold ==false)
    {
    invert_threshold = true;
    }
    else 
    {
    invert_threshold = false;
    }
    printf("sign_inverted::%d \n",invert_threshold);
  }
}

void menu_cb(Fl_Widget*,void* user_data) {
  if ((const char*)user_data == "save_all") {
    printf("menu::%s\n",(const char*)user_data);
  }
  if ((const char*)user_data == "quit") {
    printf("via_menu::%s \n", (const char*) user_data);
    exit(0);
  }
}

Fl_Menu_Bar *main_menu=(Fl_Menu_Bar *)0;

Fl_Menu_Item menu_main_menu[] = {
 {"File", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 9, 15, 0},
 {"quit", 0,  (Fl_Callback*)menu_cb, (void*)("quit"), 0, (uchar)FL_NORMAL_LABEL, 8, 14, 0},
 {"save", 0,  (Fl_Callback*)menu_cb, (void*)("save_all"), 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};

static Fl_Group *map_connected_comp=(Fl_Group *)0;

Fl_Value_Slider *scan_threshold=(Fl_Value_Slider *)0;

Fl_Button *invert_sign=(Fl_Button *)0;

int main(int argc, char **argv) {
  Fl_Window* w;
  { Fl_Window* o = new Fl_Window(960, 905, "main_window");
    w = o; if (w) {/* empty */}
    { main_menu = new Fl_Menu_Bar(0, 0, 960, 20, "main_menu");
      main_menu->color((Fl_Color)225);
      main_menu->selection_color((Fl_Color)80);
      main_menu->labelfont(8);
      main_menu->textfont(8);
      main_menu->textsize(15);
      main_menu->textcolor((Fl_Color)58);
      main_menu->menu(menu_main_menu);
    } // Fl_Menu_Bar* main_menu
    { map_connected_comp = new Fl_Group(5, 659, 685, 175, "map_connect_comp");
      { Fl_Pack* o = new Fl_Pack(10, 668, 665, 110);
        { scan_threshold = new Fl_Value_Slider(10, 668, 665, 17, "scan_threshold");
          scan_threshold->type(1);
          scan_threshold->box(FL_BORDER_BOX);
          scan_threshold->color(FL_GREEN);
          scan_threshold->labelfont(8);
          scan_threshold->maximum(255);
          scan_threshold->step(1);
          scan_threshold->textfont(8);
          scan_threshold->textsize(14);
          scan_threshold->callback((Fl_Callback*)mapcc_cb, (void*)("t_slider"));
        } // Fl_Value_Slider* scan_threshold
        { Fl_Button* o = new Fl_Button(550, 690, 125, 24, "run_thresh_scan");
          o->box(FL_THIN_UP_BOX);
          o->color(FL_DARK2);
          o->selection_color((Fl_Color)80);
          o->labelfont(13);
          o->labelcolor((Fl_Color)176);
          o->callback((Fl_Callback*)mapcc_cb, (void*)("scan_thresh"));
        } // Fl_Button* o
        { invert_sign = new Fl_Button(570, 715, 100, 20, "invert_sign");
          invert_sign->callback((Fl_Callback*)mapcc_cb, (void*)("inv_sign"));
        } // Fl_Button* invert_sign
        o->end();
      } // Fl_Pack* o
      map_connected_comp->end();
    } // Fl_Group* map_connected_comp
    o->end();
  } // Fl_Window* o
  w->show(argc, argv);
  return Fl::run();
}
