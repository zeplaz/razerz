
#include "shader_parser.hpp"

shader_tupl* new_st_ptr()
{
    shader_tupl* shader_tuple_ptr = new shader_tupl();
    *shader_tuple_ptr = std::make_tuple("\0",shader_type::SHADER_NULL,pathz);

  return shader_tuple_ptr;
}

int shader_xml_parser::item_selection(std::vector<std::string>& in_substingz,
                                       int str_pos)
{
  shader_tupl* curr_shdr_tup;
  curr_shdr_tup=new_st_ptr();

  for(int i = str_pos; i<in_substingz.size();i++)
  {
    switch(str2int_run(in_substingz.at(i).c_str()))
      {
        case h_shad_title :
        {
          std::cout << "newSHADER!:\n";
          break;
        }
        case h_shad_type :
        {
          std::cout << "shaderType:::"<< in_substingz.at(i+1)  <<'\n';
          if (in_substingz.at(i+1) =="vertex")
          {
            std::get<ST_SHADER_TYPE>(*current_tuple_prt) = shader_type::VERTEX_SHADER;
          }
          else if (substingz.at(i+1) =="fragment")
          {
            std::get<ST_SHADER_TYPE>(*current_tuple_prt) = shader_type::FRAGMENT_SHADER;
          }
          else if (substingz.at(i+1) =="compute")
          {
            std::get<ST_SHADER_TYPE>(*current_tuple_prt) = shader_type::COMPUTE_SHADER;
          }
          else if (substingz.at(i+1) =="geometry")
          {
            std::get<ST_SHADER_TYPE>(*current_tuple_prt) = shader_type::GEOMETRY_SHADER;
          }

          else if (substingz.at(i+1) =="tess_eval")
          {
            std::get<ST_SHADER_TYPE>(*current_tuple_prt) = shader_type::TESS_EVAL_SHADER;
          }

          else if (substingz.at(i+1) =="tess_ctrl")
          {
            std::get<ST_SHADER_TYPE>(*current_tuple_prt) = shader_type::TESS_CONTROL_SHADER;
          }

          break;
        }
        case file_root :
         {
           std::cout << "shader_source_loc::"<< in_substingz.at(i+1) <<'\n';
           pathz new_path( in_substingz.at(i+1));
          std::get<ST_FILEPATH>(*current_tuple_prt) =new_path;
          break;
         }

         case name :
          {
            std::cout << "shadername::"<< in_substingz.at(i+1) <<'\n';
            unsigned int  temp_index = str2int_run(in_substingz.at(i+1));
          // std::get<ST_NAME>(*current_tuple_prt) = temp_index;//in_substingz.at(i+1);
           shader_tupl_map.insert(std::pair<unsigned int,shader_tupl*>(temp_index,current_tuple_prt));
           break;
          }
          /*
          default :
          {
          //endswitch
          std::cerr <<"did not hit flagz..error on file read...or somthing...\n"<< "##ERRORCODE::"<< PARSER_FAIL;
          exit(PARSER_FAIL);
        }*/

        }//end switch
}//end for
std::cout << "\n #####shader parser run compleate of vec size:final::" << shader_tupl_map.size() <<'\n' <<'\n';
}

/*  case index :
  {
    current_tuple_prt = return_new_shader_tuple();
     std::cout << "shaderrawindex::"<< in_substingz.at(i+1) <<'\n';
     std::cout << "shaderindexnum::"<< temp_index <<'\n';
     std::get<ST_INDEX>(*current_tuple_prt) = temp_index;
    break;
  }*/
