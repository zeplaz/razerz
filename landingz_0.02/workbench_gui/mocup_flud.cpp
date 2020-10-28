



static Fl_Image *image_sectoricon()
{
  static Fl_Image *image = new Fl_RGB_Image(idata_sectoricon, 50, 50, 4, 0);
  return image;
}

Fl_Double_Window* make_window() {
   Fl_Double_Window* w;
  {
    Fl_Double_Window* o = new Fl_Double_Window(1190, 875);
    w = o; if (w) {/* empty */}
    o->align(Fl_Align(224));
    {
      Fl_Box* o = new Fl_Box(105, 45, 875, 715, "view_map");
      o->box(FL_BORDER_BOX);
      o->image( image_clod_withrailr3kut() );
      o->align(Fl_Align(96|FL_ALIGN_INSIDE));
    } // Fl_Box* o
    { Fl_Group* o = new Fl_Group(975, 45, 215, 715, "over_view_crl_group");
      o->box(FL_ENGRAVED_BOX);
      o->color((Fl_Color)105);
      o->labeltype(FL_ENGRAVED_LABEL);
      o->labelfont(8);
      o->labelcolor((Fl_Color)168);
      o->align(Fl_Align(33|FL_ALIGN_INSIDE));
      { Fl_Button* o = new Fl_Button(990, 75, 80, 75, "sector_ctrl");
        o->image( image_sectoricon() );
      } // Fl_Button* o
      o->end();
    } // Fl_Group* o
    {
      Fl_Box* o = new Fl_Box(0, -2, 1195, 49, "main_menu");
      o->box(FL_SHADOW_FRAME);
    } // Fl_Box* o

    { Fl_Box* o = new Fl_Box(0, 42, 105, 716, "toolbar");
      o->box(FL_ENGRAVED_BOX);
      o->color((Fl_Color)97);
      o->labeltype(FL_EMBOSSED_LABEL);
      o->labelfont(8);
      o->labelcolor((Fl_Color)62);
      o->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
    } // Fl_Box* o
    {
      Fl_Box* o = new Fl_Box(0, 759, 1190, 118, "terminal...etc");
      o->box(FL_THIN_DOWN_BOX);
      o->color((Fl_Color)36);
      o->labelcolor((Fl_Color)62);
      o->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
    } // Fl_Box* o
    o->end();
  } // Fl_Double_Window* o
  return w;
}
