#ifndef TEXTURE_PARSER_HPP
#define TEXTURE_PARSER_HPP

#include "parserlib.hpp"

using namespace parser;


shader_tupl* return_new_shader_tuple();
void size_of_tuplevec();

class shader_xml_parser :  public parser_sym{


protected :
st_map shader_tupl_map;
int  load_run(std::string in_pathxml);
void header_read(std::string& in_path);

int item_selection(std::vector<std::string>& in_substingz,int str_pos);
public :


};


#endif
