
#include "shader_parser.hpp"



shader_tuple_type* new_st_ptr()
{
    shader_tuple_type* shader_tuple_ptr = new shader_tuple_type();
    *shader_tuple_ptr = std::make_tuple(0,shader_type::SHADER_NULL,"","");

  return shader_tuple_ptr;
}
int shader_xml_parser::item_selection(std::vector<std::string>& in_substingz,
                                       int str_pos)
{
  shader_tuple_type* curr_shdr_tup;
  curr_shdr_tup=new_st_ptr();

  for(int i = str_pos; i<in_substingz.size();i++)
  {
    switch(str2int_run(substingz.at(i).c_str()))
      {
        case h_shad_title :
        {

          std::cout << "newSHADER!:\n";
          break;
        }
        case index :
        {
          current_tuple_prt = return_new_shader_tuple();
          unsigned int  temp_index = index_pars(sub_string_view);
            //std::get<0>(*current_tuple_prt) =temp_index;

           std::cout << "shaderrawindex::"<< substingz.at(i+1) <<'\n';
           std::cout << "shaderindexnum::"<< temp_index <<'\n';
           std::get<ST_INDEX>(*current_tuple_prt) = temp_index;
           shader_tuple_map.insert(std::pair<unsigned int,shader_tuple_type*>(temp_index,current_tuple_prt));

          break;
        }

        case h_shad_type :
        {
          std::cout << "shaderType:::"<< substingz.at(i+1)  <<'\n';
          if (substingz.at(i+1) =="vertex")
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
           std::cout << "shader_source_loc::"<< substingz.at(i+1) <<'\n';
          std::get<ST_FILEPATH>(*current_tuple_prt) = substingz.at(i+1);
          break;
         }

         case name :
          {
            std::cout << "shadername::"<< substingz.at(i+1) <<'\n';
           std::get<ST_NAME>(*current_tuple_prt) = substingz.at(i+1);
           break;
          }

          default :
          {
          //endswitch
          std::cerr <<"did not hit flagz..error on file read...or somthing...\n"<< "##ERRORCODE::"<< PARSER_FAIL;
          exit(PARSER_FAIL);
          }

        }//end switch
}//end for
std::cout << "\n #####shader parser run compleate of vec size:final::" << shader_tuple_map.size() <<'\n' <<'\n';
}
