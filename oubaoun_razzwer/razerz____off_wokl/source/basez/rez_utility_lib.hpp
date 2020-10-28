
#ifndef  REZ_UTIL_HPP
#define REZ_UTIL_HPP

#include <string>
#include <array>
#include <string_view>


/*
//entities
#include "texture.hpp"

//parsers
#include "../parserz/texture_pasrser.hpp"
#include "../parserz/shader_parser.hpp"
*/


//pars paramz >- some can be moved into own xmlfiles later..
enum Xml_path_index{
  TEXTURE_BIN_DEFULT,
};

const std::string Deful_texture_pathlist = {"../data_extrn/DEFUL_file_list_texture.xml"};
//constexpr std::string_view Def_tex_path_view(Deful_texture_pathlist);
//constexpr std::array<std::string_view,1> text_xml_paths{Deful_texture_pathlist};


#endif
