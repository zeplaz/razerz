
#include "texture_parser.hpp"

texture_tupl  NULL_TT(NULL_TI2D,"","",'\0');

texture_tupl* new_tt_ptr()
{
    texture_tupl* tt_ptr = new texture_tupl(NULL_TT);
    //  shader_tuple_vec.push_back(shader_tuple_ptr);
    //inteximage2d* inti2d = new inteximage2d();
    //*tt_ptr = ;
  //shader_tuple_map.insert(pair<unsigned int,shader_tuple_type*>(,shader_tuple_ptr));
  //std::cout << "\n genreating tuple pointer at" << shader_tuple_ptr << " " << "size:" << shader_tuple_vec.size() <<'\n';
  return tt_ptr;
}

int texture_xml_parser::item_selection(std::vector<std::string>& in_substingz,
                                       int str_pos)
{
  texture_tupl* curr_text_tup;
  curr_text_tup = new_tt_ptr();


  teximage2d_parmz* current_ti2d_prmz =&std::get<TEXIMG_PARAMZ>(*curr_text_tup);

  for(int i = str_pos; i<in_substingz.size();i++)
  {
    switch(str2int_run(in_substingz.at(i).c_str(),0))
    {
      case subtype :
       {
        std::get<TI2D_TARGET>(*current_ti2d_prmz) = subtypetexture_toGLenum(in_substingz.at(i+1));
       break;
       }

      case t_colour_comp :
       {
        std::get<TI2D_COLOUR_COMP>(*current_ti2d_prmz) = colour_comp_toGLint(in_substingz.at(i+1));
       break;
       }

      case t_pix_formate :
        {
         std::get<TI2D_PIX_FORMATE>(*current_ti2d_prmz)  = pix_formate_toGLenum(in_substingz.at(i+1));
        break;
        }
      case t_pixdata_type :
        {
         std::get<TI2D_PIX_DATATYPE>(*current_ti2d_prmz) = pix_datatype_toGLenum(in_substingz.at(i+1));
        break;
        }

      case name :
        {
         std::get<TT_NAME>(*curr_text_tup) = in_substingz.at(i+1);
         unsigned int nindex =  str2int_run(in_substingz.at(i+1).c_str(),0);
         texture_tupl_map.insert(std::make_pair(nindex,curr_text_tup));
        break;
        }

       case file_root :
         {
          std::get<TT_FILEPATH>(*curr_text_tup) = in_substingz.at(i+1);
         break;
         }

       case flagz :
         {
            std::string flag_string = in_substingz.at(i+1);
            //

          std::get<TT_FLAGZ>(*curr_text_tup) =(unsigned char)flag_string.at(0);
          return i;
         break;
         }

         default :
         {
           //endswitch
           std::cerr <<"did not hit flagz..error on file read...or somthing...\n"<< "##ERRORCODE::"<< PARSER_FAIL;
           exit(PARSER_FAIL);
         }
      }

    }//end//for
}

GLenum pix_datatype_toGLenum(const std::string& in_substring)
{
  if(in_substring =="datat_ubyte")
  {
    return GL_UNSIGNED_BYTE;
  }

  else if(in_substring =="datat_byte")
  {
    return GL_BYTE;
  }

  else if(in_substring =="datat_uint210")
  {
    return GL_UNSIGNED_INT_2_10_10_10_REV;
  }

  else if(in_substring =="datat_uint")
  {
    return GL_UNSIGNED_INT;
  }

  else if(in_substring =="datat_int")
  {
    return GL_INT;
  }

  else if(in_substring =="datat_hfloat")
  {
    return GL_HALF_FLOAT;
  }

  else if(in_substring =="datat_float")
  {
    return GL_FLOAT;
  }

  std::cerr<<"pix_datatype not regonized.\n";
  return NULL;

}


GLenum pix_formate_toGLenum(const std::string& in_substring)
{
  if(in_substring == "form_sten_index")
  {
    return GL_STENCIL_INDEX;
  }

  else if(in_substring == "form_depth")
  {
    return GL_DEPTH_COMPONENT;
  }

  else if(in_substring == "form_depth+sten")
  {
    return GL_DEPTH_STENCIL;
  }

  else if(in_substring == "form_grba")
  {
    return GL_RGBA;
  }

  else if(in_substring == "form_rgbai")
  {
    return GL_RGBA_INTEGER;
  }

  std::cerr<<"pix_formate not regonized.\n";
  return NULL;
}

GLint colour_comp_toGLint(const std::string& in_substring)
{
  if(in_substring=="inf_depth")
  {
    return GL_DEPTH_COMPONENT;
  }

  else if(in_substring=="inf_depth+sten")
  {
    return GL_DEPTH_STENCIL;
  }
  else if(in_substring=="inf_rgba")
  {
    return GL_RGBA;
  }
  else if(in_substring=="inf_red")
  {
    return GL_RED;
  }
  else if(in_substring=="inf_srgba8")
  {
    return GL_SRGB8_ALPHA8;
  }
  else if(in_substring=="inf_rgba16")
  {
    return GL_RGBA16;
  }
  else if(in_substring=="inf_rgba32f")
  {
    return GL_RGBA32F;
  }
  else if(in_substring=="inf_inf_rgba16f")
  {
    return GL_RGBA16F;
  }
  std::cerr<<"colourcomp not regonized.\n";
  return NULL;

}

 GLenum subtypetexture_toGLenum(const std::string& in_substring)
{
  if(in_substring== "texture1d")
  {
    return GL_TEXTURE_1D;
  }
  else if(in_substring== "texture2d")
  {
    return GL_TEXTURE_2D;
  }
  else if(in_substring== "texture3d")
  {
    return GL_TEXTURE_3D;
  }
 else if(in_substring== "texturerec")
  {
    return GL_TEXTURE_RECTANGLE;
  }
  else if(in_substring== "texturebuff")
  {
    return GL_TEXTURE_BUFFER;
  }
  else if(in_substring== "texturecubmap")
  {
    return GL_TEXTURE_CUBE_MAP;
  }
  else if(in_substring== "texture1d_array")
  {
    return GL_TEXTURE_1D_ARRAY;
  }
  else if(in_substring== "texture2d_array")
  {
    return GL_TEXTURE_2D_ARRAY;
  }
  else if(in_substring== "texturecubmap_array")
  {
    return GL_TEXTURE_CUBE_MAP_ARRAY;
  }

  else if(in_substring== "texture2d_multi")
  {
    return GL_TEXTURE_2D_MULTISAMPLE;
  }

  else if(in_substring== "texture2d_multi_array")
  {
    return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
  }
  std::cerr<<"subtype not regonized.\n";
  return NULL;
}
