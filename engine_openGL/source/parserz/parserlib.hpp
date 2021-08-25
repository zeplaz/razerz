
#ifndef PARSERLIB_HPP
#define PARSERLIB_HPP

#include "asset_rez_listz.hpp"
#include "basez/lighting_lib.hpp"


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


constexpr char resource_dlim_char = '>';

//NULLtouples
//constexpr teximage2d_parmz NULL_TI2D = std::make_tuple(0,0,0,0);

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


//for emmission meterailz
constexpr unsigned int em_flagz       = str2int("emission_flagz");
constexpr unsigned int em_colourz     = str2int("emission_colourz");
constexpr unsigned int em_modiferz     = str2int("e_modiferz");
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

template <class resource_, typename out_data_pak>

  class parser_base<resource_>{

    public :
    int  load_run(const pathz& in_pathxml);
    void header_read(const pathz& in_path);
    resource_ parse_data(const std::string& file_name);
  //virtual int item_selection(std::vector<std::string>& in_substingz,int i) = 0;
    protected:
    std::vector<out_data_pak> handle_shader(const parsed_file& in_pf);
    std::vector<out_data_pak> handle_emission_material(const parsed_file& in_pf);
    std::vector<out_data_pak> handle_orbital_emitterz(const parsed_file& in_pf);

    //out_data_pak handle_e_modiferz(const parsed_file& in_pf);
    static std::unordered_map<std::string,parsed_file>file_map;
    //virtual void register_with_ecouterion(std::string& in_name,unsigned int in_index) =0;
    };

    template <class resource_, typename out_data_pak>
    std::vector<out_data_pak> handle_return_data_pak(const parsed_file& in_pf)
    {
      std::vector<out_data_pak> out_pak;

      for(int i = str_pos; i<in_pf.pf_substringz.size();i++)
      {
        switch(str2int_run(in_pf.pf_substringz.at(i).c_str()))

        case em_flagz :
        {
          std::valarray<bool> emissio_flagz_mask(8);
          std::get<BOOL_FLAGZ>(out_pak) = emissio_flagz_mask;

          break;
        }

        case subtype :
        {

          break;
        }

        case file_root :
         {
           //std::cout << "shader_source_loc::"<< in_pf.pf_substringz.at(i+1) <<'\n';
           //pathz new_path( in_pf.pf_substringz.at(i+1));
           //std::get<FILEPATH>(*current_tuple_prt) =new_path;
          break;
         }

      }
    }

    template <class resource_, typename out_data_pak>
    resource_ parser_base::parse_data(const std::string& file_name)
    {
      //
      std::vector<out_data_pak>
      auto it = file_map.find(file_name);
      if (it != file_map.end())
      {

        swtich(it->second.pf_type)
        {

          case Parse_File_Type::ORBITAL_EMITTERZ :
          {
            handle_orbital_emitterz(it->second);
            break;
          }
          case Parse_File_Type::EMISSION_ATTRZ :
          {
            handle_emission_material(it->second);
            break;
          }

        }
      }
      else
      {
        std::cerr<<"PARSEFILE NOT FOUND IN MAP!\n";

        #ifdef DEBUG_1
        exit(PARSER_FAIL);
        #endif
      }
    };

  }//endnamespace

#endif



/*class parser_sym_CMD
{
  shader_xml_parser shd_parser;

  void handle_shaders()
  {

  }
};*/
