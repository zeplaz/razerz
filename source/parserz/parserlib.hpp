
#ifndef PARSERLIB_HPP
#define PARSERLIB_HPP

#include "../basez/gl_lib_z.hpp"




namespace parser{
//string int handles
constexpr unsigned int str2int(const char* str, int h = 0)
{
return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

 unsigned int str2int_run(const char* str, int h );

//enumz for parserindexpos

enum Texture_Touple_pos{
  //TT_INDEX,      //uint
  TEXIMG_PARAMZ, //teximage2d_parmz
  TT_NAME,       //string
  TT_FILEPATH,   //string
  TT_FLAGZ       //0b00000etyc??
};

enum Teximg2d_Paramz_pos
{
TI2D_TARGET,       //GLenum
TI2D_COLOUR_COMP, //GLint
TI2D_PIX_FORMATE, //GLenum
TI2D_PIX_DATATYPE //GLenum
};




enum class Reg_Express{
  FILE_FIRST_LINE,
  OBJ_HEADER,
  OBJ_BODY
};

enum Reg_XML_Pos{
  XML_POS = 1,
  XML_VERSION = 2,
  XML_UTF = 5
};

enum Reg_Header_Pos
{
  REZ_TYPE = 2,
  ITEM_NUM = 3
};

enum class Parse_File_Type{
  SHADER_LIST,
  TEXTURE_LIST
};

constexpr char resource_dlim_char = '>';

//NULLtouples
constexpr teximage2d_parmz NULL_TI2D = std::make_tuple(0,0,0,0);

/*
DEFINEZ FOR Resource Types ->
to uint for parsing switch
*/

//forall
constexpr unsigned int index = str2int("INDEX");
constexpr unsigned int name  = str2int("NAME");
constexpr unsigned int file_root = str2int("file_root");
constexpr unsigned int flagz = str2int("FLAGZ");

//forobjz
constexpr unsigned int item_type = str2int("ITEM_TYPE");
constexpr unsigned int subtype   = str2int("SUB_TYPE");

//for shaderz
constexpr unsigned int h_shad_type  = str2int("SHADER_TYPE");
constexpr unsigned int h_shad_title = str2int("shader_glsl");

//for texture
constexpr unsigned int t_colour_comp   = str2int("gl_colour_components");
constexpr unsigned int t_pix_formate   = str2int("gl_formate_pix");
constexpr unsigned int t_pixdata_type  = str2int("gl_pixdata_type");

/*
XMLBASEPARSE FUNCTIONz
*/
  std::vector<std::string> run_xmlobj_parse(const pathz& in_xml_path);
  unsigned int index_pars(std::string& in_substring);

  struct parsed_file{
    Parse_File_Type pf_type;
    float version;
    unsigned int encodeing;
    std::vector<std::string> pf_substringz;
  };

  enum file_list_pos{
    SHADER_XML_POS,
    NEIL_OBJ_XML_LIST
  };
  const  pathz shaders_xml_path("../../shaderzglsl/file_list_shader.xml");
  const pathz neil_xml_path("../../data_extrn/neil/file_list_shader.xml");
  const static  std::array<pathz,25> file_list{shaders_xml_path,neil_xml_path};

/*class parser_sym_CMD
{
  shader_xml_parser shd_parser;

  void handle_shaders()
  {

  }
};*/
  class parser_base{

    public :
    int  load_run(const pathz& in_pathxml);
    void header_read(const pathz& in_path);
    void parse_data(const pathz& file_name);

    virtual int item_selection(std::vector<std::string>& in_substingz,int i) = 0;

    protected:
    std::unordered_map<std::string,parsed_file>file_map;
    //virtual void register_with_ecouterion(std::string& in_name,unsigned int in_index) =0;
    };

  }//endnamespace

#endif
