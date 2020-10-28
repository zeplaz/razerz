#ifndef TEXTURE_PARSER_HPP
#define TEXTURE_PARSER_HPP

#include "parserlib.hpp"

using namespace parser;

shader_tupl* return_new_shader_tuple();
void size_of_tuplevec();

class shader_xml_parser :  public parser_base{
protected :
st_map shader_tupl_map;
public :
virtual int item_selection(std::vector<std::string>& in_substingz,
                                       int str_pos);
};

#endif
