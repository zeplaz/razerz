
#pragma once
//écoute 	écoutera 	écoutait //écouterait /écoutât

#include "../basez/rez_utility_lib.hpp"
#include "shader_pipeline_CMD.hpp"
#include "mcp_lib.hpp"
#include "../basez/texture.hpp"
#include "../parserz/model_parser.hpp"

template<auto VFnPtr> struct
wrapper;

template<typename TResult, typename... TArgs, TResult ( * VFnPtr)(TArgs...)> struct
wrapper<VFnPtr>
{
    TResult
    operator ()(TArgs... args) const noexcept(noexcept((*VFnPtr)(::std::forward<TArgs>(args)...)))
    {
        return (*VFnPtr)(::std::forward<TArgs>(args)...);
    }
};

typedef std::tuple<std::string,std::string,glm::vec4,glm::vec2,int,GLfloat> distex_tuple;


static glm::vec4 font_colour_def = glm::vec4(1.0f,0.3f,0.6f,1.0f);
static glm::vec2 text_pos_def = glm::vec2(320.0f, 500.0f);

static distex_tuple deflut_trparmz = std::make_tuple("defult_text","../modualz/text_render/fonts/Maranallo.ttf",
                                        font_colour_def,text_pos_def,size_64,1.0);

static std::string def_display_text_path= "../data/extrn/text_display/base_text_display.xml";

/*
symid,priotry,blockID,drawfunc,ptr_paramz;
typedef int Block_ID;
std::<>
typedef std::priority_queue<,>;

typedef std::multimap<Block_ID,wrapper>;
*/
//template<classType>
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
      std::string log_update;
      log_update += "\n\n ##ZMCP_cmd/écouterions \n";

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
  class ecouter
{
  protected :

  //std::priority_queue<>
//  std::mutlimap<unigned int,>

  void input_event();

  std::vector<text_render_pak> text_pack_arry;

  std::unordered_map<unsigned int,std::shared_ptr<texture_2>> texture_map;
  //or
  std::unordered_map<unsigned int,std::shared_ptr<gl_shader_t>> shader_map;
  //or
  std::unordered_map<unsigned int,std::shared_ptr<shader_seprate>> separated_shdr_prgm_map;
  //std::unordered_map<unsigned int,std::shared_ptr<>> shdr_prgm_map;
  //std::unordered_map<unsigned int,,std::shared_ptr<>> pipeline_map;

  public :
  constexpr static  double D_ZERO = 0.0;
  double Current_Time= D_ZERO;
  float delta_time;


  void update_clock(double in_time)
  {
    Current_Time =in_time;
  }


  void add_text_pack(text_render_pak& in_trp)
  {
    text_pack_arry.push_back(in_trp);
  }

  inline unsigned int registar_texture(std::shared_ptr<texture_2> in_texture)
  {

    texture_map.insert(std::make_pair(in_texture->get_id(),in_texture));
    return in_texture->get_id();
  }

  inline unsigned int registar_shader(std::shared_ptr<gl_shader_t> in_shader)
  {

    shader_map.insert(std::make_pair(in_shader->get_id(),in_shader));
      return in_shader->get_id();
  }

  inline unsigned int registar_separated_shader(std::shared_ptr<shader_seprate> in_shader)
  {

    separated_shdr_prgm_map.insert(std::make_pair(in_shader->get_id(),in_shader));
    return in_shader->get_id();
  }

};
/*

class shader_ecouter : public singleton_exd
{
  protected :


  inline int registar_texture(unsigned int index,std::shared_ptr<gl_shader_t> in_texture)
  {
    shader_map.insert(std::make_pair(index,in_texture));
  }


};*/
/*
struct path_handler{
  std::unordered_map<unsigned int,std::string_view>
};*/

  struct rez_mgmt
  {
    public :

    ecouter  ecouterait;
    //texture_ecouter texture_ecouterait;
    //shader_ecouter  shader_ecouterait;
  //  shader_pipeline_CMD shpipe_cmd;
    //texture_xml_parser t_xml_parser;

  /*  void preform_texturexml_scan(pathz& in_path)
    {
      //t_path_map* t_path_m_ptr;

      int parsSTATUS = t_xml_lister.load_run(in_sv_xmlpath);

      if(parsSTATUS<0)
      {
          std::cerr << "parseerror::" << parsSTATUS << '\n';
          return;
      }

      t_path_m_ptr = t_xml_lister.pointer_mapreturn();
      gen_texture_from_tt(t_path_m_ptr);


    }

    void gen_texture_from_tt(t_path_map* t_path_m_ptr)
    {

    }*/

  };
