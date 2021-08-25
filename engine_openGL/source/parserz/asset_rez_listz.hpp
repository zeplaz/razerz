#ifndef ASSET_REZ_LIST_HPP
#define ASSET_REZ_LIST_HPP

#include "../basez/io_utilityz.hpp"

enum file_list_pos{
  SHADER_XML_POS,
  NEIL_OBJ_XML_LIST,
  EMISSION_METERIAL_ATTR_BASE,
  SOLESTIAL_SOL_A
};

enum class Parse_File_Type{
  REZ_LIST_MASTER,
  SHADER_LIST,
  TEXTURE_LIST,
  MODEL_LIST,
  MESH_LIST,
  SCENE_LIST,
  ORBITAL_EMITTERZ,
  EMISSION_ATTRZ
};

const  pathz em_attr_BASE_sol_A_xml_path("../scene_gen/emission_meterial_attr_A.xml");
const  pathz solesital_light_sol_A_xml_path("../../scene_gen/emission_meterial_attr_A.xml");
const  pathz shaders_xml_path("../../shaderzglsl/file_list_shader.xml");
const pathz neil_xml_path("../../data_extrn/neil/local_asset_list.xml");
const static  std::array<pathz,25> file_list{shaders_xml_path,neil_xml_path,em_attr_BASE_sol_A_xml_path,solesital_light_sol_A_xml_path};

#endif

/*
Distance 	Constant 	Linear 	Quadratic
7 	1.0 	0.7 	1.8
13 	1.0 	0.35 	0.44
20 	1.0 	0.22 	0.20
32 	1.0 	0.14 	0.07
50 	1.0 	0.09 	0.032
65 	1.0 	0.07 	0.017
100 	1.0 	0.045 	0.0075
160 	1.0 	0.027 	0.0028
200 	1.0 	0.022 	0.0019
325 	1.0 	0.014 	0.0007
600 	1.0 	0.007 	0.0002
3250 	1.0 	0.0014 	0.000007
*/
