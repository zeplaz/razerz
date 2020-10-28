
#ifndef TEXTURE_PARSER_HPP
#define TEXTURE_PARSER_HPP

#include "parserlib.hpp"

using namespace parser;

//forward delcrations
class texture_ecouter;

texture_tupl* new_tt_ptr();

GLenum subtype_toGLenumtex_target(const std::string& in_substring) ;
GLenum pix_datatype_toGLenum(const std::string& in_substring);
GLenum pix_formate_toGLenum(const std::string& in_substring);
GLint  colour_comp_toGLint(const std::string& in_substring);
GLenum subtypetexture_toGLenum(const std::string& in_substring);


class texture_xml_parser : public parser_sym{

  protected :
  tt_map texture_tupl_map;
  //texture_ecouter* t_ecouter_ptr;
  public :
  int item_selection(std::vector<std::string>& in_substingz,int str_pos);

  //int gen_teximage(std::string& in_substring,unsigned int index,int str_pos);
  //void report_nameto_index(unsigned int in_index, const std::string& name);
  //void register_with_ecouterion(std::string& in_name,unsigned int in_index);

  inline int  registar_texture_tupl(unsigned int id, texture_tupl* in_tex_tup )
  {
    texture_tupl_map.insert(std::make_pair(id,in_tex_tup));
  }

  inline tt_map* pointer_mapreturn()
  {
    return &texture_tupl_map;
  }

  void remove_tt(unsigned int id)
  {
    //texture_tupl_map.find(id);
    auto it = texture_tupl_map.find(id);
    if (it != texture_tupl_map.end())
    {
      texture_tupl* tt_ptr = it->second;
      delete [] tt_ptr;
      texture_tupl_map.erase (it);
    }
  }
};
 //std::unique_ptr<t_path_map>  ptr_map = std::make_unique<t_path_map>(texture_path_map);
#endif
