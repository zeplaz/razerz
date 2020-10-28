
#pragma once
#include "shader_pipeline_CMD.hpp"

#include "../basez/3rdparty/frame_to_video.hpp"

#include "../basez/gl_lib_z.hpp"
#include "../basez/texture.hpp"
#include "../basez/shader_lib.hpp"
#include "../basez/rez_utility_lib.hpp"
#include "../basez/opengl_utilityz.hpp"

#include "../parserz/model_parser.hpp"
#include "../parserz/shader_parser.hpp"

#include "../modualz/text_render/text_render.hpp"

#include <memory>

static int next_cu_ID = 0;

typedef void (APIENTRYP PFN_EXT_Q)(const ex_base* __restrict ppreamz);

struct  ex_base
{
  PFN_EXT_Q ptr_ext_q_func;
};

 struct smp_cmd_PAK: public ex_base
 {
   GLfloat priority;
   GLenum pak_type_sream;

   static void APIENTRY exe_cute(constsmp_cmd_PAK* __restrict ppreamz)
   {
     //draw or other outside loficphsyze tc
   }
 };


 union PAKETTEZ_ALL
 {
   public :
   PFN_EXT_Q exe_cute;
   private :
   ex_base loc_base;
   smp_cmd_PAK smp_pk;
   ///othertypedef?packet typez!
 }
enum class FBO_type  : GLint
{
VIRTUAL,
TEXTURAL_BASE,
FLOATING,
INTEGER,
LAYERED,
MULTI_DRAW,
MULTI_TEXTURE,
MULTI_ATTACHMENT
};

enum Diplay_text_pos{
  POS_DTEXT,
  POS_DFONT,
  POS_DCOLOUR,
  POS_DPOS,
  POS_DSIZE,
  POS_DSCALE
};
enum Glyph_List
{
  DEF_MARANALLO =-1,
  DEF_BAR = -2
};

typedef std::tuple<std::string,std::string,glm::vec4,glm::vec2,int,GLfloat> distex_tuple;
static glm::vec4 font_colour_def = glm::vec4(1.0f,0.3f,0.6f,1.0f);
static glm::vec2 text_pos_def = glm::vec2(320.0f, 500.0f);
static distex_tuple deflut_trparmz = std::make_tuple("defult_text","../modualz/text_render/fonts/Maranallo.ttf",
                                        font_colour_def,text_pos_def,size_64,1.0);
static std::string def_display_text_path= "../data/extrn/text_display/base_text_display.xml";

template<>
struct EnableBitMaskOperators<FBO_type>
{
    static const bool enable = true;
};



struct text_render_pak
{
  Text_Update_Mask update_mask;
  std::vector<diply_tx_pair> deflttxt_vec=read_dispaly_text_file(def_display_text_path);
  std::string dis_text;
  glm::vec4 font_colour;
  glm::vec2 text_pos;
  std::string curr_font;
  int psize;
  GLfloat scale;
  std::shared_ptr<text_render_glyph> trg_prt;
  std::string log_update;


  std::vector<diply_tx_pair> read_dispaly_text_file(std::string file_nme)
  {
    std::ifstream infile(file_nme);
    std::vector<diply_tx_pair> text_list;
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        int meterial_id;
        std::string dis_str;
        if (!(iss >> meterial_id >> dis_str))
        { std::cerr << "FILE FAIL_TEXTDISPLAY"; break; } // error
        text_list.push_back(std::make_pair(meterial_id,dis_str));
      //  text_list.push_back(dis_str);
        // process pair (a,b)
    }
  return text_list;
  }

  void update()
  {
      //std::string log_update;
      log_update = "\n\n ##ZMCP_cmd/écouterions \n";

    if((Text_Update_Mask::UP_NONE & update_mask)==Text_Update_Mask::UP_NONE)
    {
      return;
    }
     if((Text_Update_Mask::UP_ALL & update_mask)==Text_Update_Mask::UP_ALL)
    {
      trg_prt->init(dis_text,curr_font,psize,font_colour,text_pos,scale);
      update_mask =Text_Update_Mask::UP_NONE;
      log_update += "#->#::Glphy::INIT()";
       //+ std::to_string(update_mask)+
       log_update +="\n";
      trg_prt->run_log(log_update);
      return;

    }
    //else if(update_mask ==)
    if((Text_Update_Mask::UP_TEXT & update_mask)==Text_Update_Mask::UP_TEXT)
    {
      trg_prt->set_text(dis_text);
      update_mask &= ~ Text_Update_Mask::UP_TEXT;
      log_update = "#->#::Glphy::set_text()" ;
      //+ std::to_string(update_mask)
      log_update += +"\n";
    }
    if((Text_Update_Mask::UP_POS & update_mask)==Text_Update_Mask::UP_POS)
    {
      std::cerr <<"@**fontchange not allowed at moment through this INTERFACE\n**\n\n";
      update_mask &= ~ Text_Update_Mask::UP_POS;
      log_update = "#->#::Glphy::cerr()" ;
      //+ std::to_string(update_mask)+
      log_update +="\n";
    }

    if((Text_Update_Mask::UP_COLOUR & update_mask)==Text_Update_Mask::UP_COLOUR)
    {
      trg_prt->set_colour(font_colour);
      update_mask &= ~ Text_Update_Mask::UP_COLOUR;
    //  log_update = "#->#::Glphy::set_colour()" + to_string(update_mask);
    }

    if((Text_Update_Mask::UP_POS & update_mask)==Text_Update_Mask::UP_POS)
    {
      trg_prt->set_pos(text_pos);
      update_mask &= ~ Text_Update_Mask::UP_POS;
    }

    if((Text_Update_Mask::UP_SCALE & update_mask)==Text_Update_Mask::UP_SCALE)
    {
      trg_prt->set_scale(scale);
      update_mask &= ~ Text_Update_Mask::UP_SCALE;
    }

      //log_update += std::to_string(update_mask);
      log_update += "\n";
      trg_prt->run_log(log_update);
  }

  void set_pak(distex_tuple& in_parmpack)
  {
     dis_text   =std::get<POS_DTEXT>(in_parmpack);
     curr_font  =std::get<POS_DFONT>(in_parmpack);
     font_colour=std::get<POS_DCOLOUR>(in_parmpack);
     text_pos   =std::get<POS_DPOS>(in_parmpack);
     scale      =std::get<POS_DSCALE>(in_parmpack);
     psize      =std::get<POS_DSIZE>(in_parmpack);
     update_mask = Text_Update_Mask::UP_ALL;
  }

  void set_pak(std::string& in_tlist,std::string& infont, glm::vec4 in_font_colour
              ,glm::vec2 in_text_pos, GLfloat in_scale =1.0f)
  {
     dis_text=in_tlist;
     curr_font =infont;
     font_colour=in_font_colour;
     text_pos=in_text_pos;
     scale=in_scale;
     update_mask = Text_Update_Mask::UP_ALL;
  }
  void set_curr_glph_ptr(text_render_glyph& in_trg)
  {
    trg_prt= std::make_shared<text_render_glyph> (in_trg);
  }
  void update_text(std::string& in_str)
  {
    dis_text=in_str;
    update_mask |= Text_Update_Mask::UP_TEXT;
  }

  void update_size(int in_ps)
  {
    psize =in_ps;
  }
  void update_colour(glm::vec4 in_colur)
  {
    font_colour=in_colur;
    update_mask |= Text_Update_Mask::UP_COLOUR;
  }
  void update_pos(glm::vec2 in_pos)
  {
    text_pos= in_pos;
    update_mask |= Text_Update_Mask::UP_POS;
  }
  void clear_mask()
  {
    update_mask = Text_Update_Mask::UP_NONE;
  }
  void inialz_glphy_from_loc_data()
  {
    trg_prt->init(dis_text,curr_font,size_64,font_colour,text_pos,scale);
  }

  void load_text_procedure()
  {

    for(size_t i =0; i<deflttxt_vec.size();i++ )
    {
      diply_tx_pair* tmp_par = &deflttxt_vec.at(i);
      distex_tuple new_dtup;
      text_render_pak n_td_pak;


      if(DEF_MARANALLO==tmp_par->first)
      {
      new_dtup = deflut_trparmz;
      }
      //text_render_pak.
       std::get<POS_DTEXT>(new_dtup) = tmp_par->second;
       n_td_pak.set_pak(new_dtup);
    }
  }
};


/*
template<typename Inher_type>
class singleton_exd
{
  protected :

  static std::weak_ptr<Inher_type> _singleton;

  public :
  int cmd_unit_ID;
  singleton_exd(const singleton_exd&) = delete;
  singleton_exd(singleton_exd&&) = delete;
  singleton_exd& operator=(const singleton_exd&) = delete;
  singleton_exd& operator=(singleton_exd&&) = delete;

  static std::shared_ptr<Inher_type> singleton_exd()
  {
    std::shared_ptr<Inher_type> singleton = _singleton.lock();
    if(!singleton)
    {
      singleton.reset(new Inher_type());
      _singleton =singleton;
    }
    init();
    return singleton;
  }

  inline void init()
  {
    cmd_unit_ID =next_cu_ID;
    next_cu_ID++;
  }
};
template<typename Inher_type>
std::weak_ptr<Inher_type> singleton_exd<Inher_type>::_singleton;
*/


template<typename Inher_type>
class singleton
{
  protected :
  singleton()
  {
    init();
  };

  public :
  int cmd_unit_ID;
  singleton(const singleton&) = delete;
  singleton &operator = (const singleton&)=delete;

  inline void init()
  {
    cmd_unit_ID =next_cu_ID;
    next_cu_ID++;
  }

  static Inher_type& get_instance()
  {
    static Inher_type instance;
    return instance;
  }
};
