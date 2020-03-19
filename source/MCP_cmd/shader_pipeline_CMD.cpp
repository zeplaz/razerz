

#include "shader_pipeline_CMD.hpp"
/*
  shader_base::load_file_single_shader_prgm(shader_type in_shd_type,std::string& in_shader_text)
  {
    std::cout <<"creating shader gl\n";

   if(shad_type == shader_type::VERTEX_SHADER)
   {
     std::cout << "NEW VERTEX SHADER GENREATING\n";
     gl_shader_ID =  glCreateShaderProgramv(GL_VERTEX_SHADER,1,in_shader_text.data());
     contained_shaders |=shader_type::VERTEX_SHADER;
   }

   else if(shad_type ==shader_type::FRAGMENT_SHADER)
   {
     std::cout << "NEW FRAGMENT SHADER GENREATING\n";
     gl_shader_ID =  glCreateShaderProgramv(GL_FRAGMENT_SHADER,1,in_shader_text.data());
     contained_shaders |=shader_type::FRAGMENT_SHADER;
   }

   else if(shad_type ==shader_type::COMPUTE_SHADER)
   {
     std::cout << "NEW COMPUTE SHADER GENREATING\n";
     gl_shader_ID =  glCreateShaderProgramv(GL_COMPUTE_SHADER,1,in_shader_text.data());
     contained_shaders |=shader_type::COMPUTE_SHADER;
   }

   else if(shad_type ==shader_type::TESS_EVAL_SHADER)
   {
     std::cout << "NEW COMPUTE SHADER GENREATING\n";
     gl_shader_ID =  glCreateShaderProgramv(GL_TESS_EVALUATION_SHADER,1,in_shader_text.data());
     contained_shaders |=shader_type::TESS_EVAL_SHADER;
   }

   else if(shad_type ==shader_type::GEOMETRY_SHADER)
   {
     std::cout << "NEW COMPUTE SHADER GENREATING\n";
     gl_shader_ID =  glCreateShaderProgramv(GL_GEOMETRY_SHADER,1,in_shader_text.data());
     contained_shaders |=shader_type::GEOMETRY_SHADER;
   }

}

/*
gl_shader_t FUNCTIONS
LA LA LA
*/
//

GLuint gl_shader_t::return_uniform(std::string name)
{
 auto shearcher = uniform_loc_map.find(name);
 if(shearcher!=uniform_loc_map.end())
 {
   return shearcher->second;
 }
 else{
   std::cerr <<"funtimez uniform not found goina cazedoom!";
   return 254;
 }
}

void gl_shader_t::create_shader(shader_type shad_type, int s_index)
{ std::cout <<"creating shader gl\n";
  if(shad_type == shader_type::VERTEX_SHADER)
  {

    GLuint shader_ID = glCreateShader(GL_VERTEX_SHADER);
    std::cout << "NEW VERTEX SHADER GENREATING\n";
    std::pair<shader_type,GLuint> temp_shard = std::make_pair(shad_type,shader_ID);
    std::cout << "->inserting shaderID intomap::" <<s_index << '\n';
    shader_IDz_map.insert(std::make_pair(s_index,temp_shard));
    contained_shaders |=shader_type::VERTEX_SHADER;
  }

  else if(shad_type ==shader_type::FRAGMENT_SHADER)
  {
    std::cout << "NEW FRAGMENT SHADER GENREATING\n";
    shader_IDz_map.insert(std::make_pair(s_index,std::make_pair(shader_type::FRAGMENT_SHADER,glCreateShader(GL_FRAGMENT_SHADER))));
    std::cout << "->inserting shaderID intomap::" <<s_index << '\n';
    contained_shaders |=shader_type::FRAGMENT_SHADER;
  }

  else if(shad_type ==shader_type::COMPUTE_SHADER)
  {
    std::cout << "NEW COMPUTE SHADER GENREATING\n";
    shader_IDz_map.insert(std::make_pair(s_index,std::make_pair(shader_type::COMPUTE_SHADER,glCreateShader(GL_COMPUTE_SHADER))));
    std::cout << "->inserting shaderID intomap::" <<s_index << '\n';
    contained_shaders |=shader_type::COMPUTE_SHADER;
  }

}

bool gl_shader_t::create_link_program(std::vector<int>& to_attach_shaders)
{
  program_ID = glCreateProgram();
  std::cout <<"shader# in to link" << to_attach_shaders.size() <<'\n';
  for (size_t i =0; i< to_attach_shaders.size(); i++)
  {
    int shader_index = to_attach_shaders.at(i);
    std::cout << "SHADER INDEX#:" << shader_index << '\n';
    auto it_sh_map = shader_IDz_map.find(shader_index);

    if (it_sh_map != shader_IDz_map.end())
    {
      std::pair<shader_type,GLuint> *temp_pair = &it_sh_map->second;
      glAttachShader(program_ID,temp_pair->second);
      std::cout <<"shader attached: ID " << temp_pair->second <<'\n';
    }
    else {std::cout << "#ERROR:Sfound no shader ID at that index\n";}
  }

  glLinkProgram(program_ID);
  GLint success;
  GLchar infoLog[1024];
  glGetProgramiv(program_ID, GL_LINK_STATUS, &success);
         if(!success)
         {
             glGetProgramInfoLog(program_ID, 1024, NULL, infoLog);
             std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: "  << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
             return false;
         }
         return true;
}

void gl_shader_t::setup_shader_code(shader_tupl* in_shader_tuple)
{
  std::cout << "->Loading shader tuple into shader\n";

  int s_index        = std::get<ST_INDEX>(*in_shader_tuple);
  shader_type s_type = std::get<ST_SHADER_TYPE>(*in_shader_tuple);
  std::string path   = std::get<ST_FILEPATH>(*in_shader_tuple);

  std::ifstream file(path);
  std::string ret = "";
  std::string line_buff ="";
  if(file.is_open())
  {
   ret= std::string(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>());
   std::cout << ret;
   file.close();
  }

  std::pair<shader_type,std::string> data_pair = std::make_pair(s_type,ret);
  shader_code_map.insert(std::make_pair(s_index,data_pair));
  std::cout << "->COMLEATED shader tuple into shader\n";
  std::cout << "INDEXINFO:"  << s_index <<"\n \n";
  this->create_shader(s_type,s_index);
  this->load_complie(s_index);
}

void gl_shader_t::load_complie(int map_index)
{
  GLchar* log_shader;
  std::cout << "compling newshader:\n";
  GLint complie_status;

  auto it_scm = shader_code_map.find(map_index);
  if (it_scm != shader_code_map.end())
  {
    std::pair<shader_type,std::string> code_pair =  it_scm->second;

    auto it_s_idz = shader_IDz_map.find(map_index);
    if (it_s_idz != shader_IDz_map.end())
          {
            std::pair<shader_type,GLuint>  temp_id_pair = it_s_idz->second;
            if (temp_id_pair.first == code_pair.first)
            {
              const GLchar*  sh_gl_code = code_pair.second.c_str();
              glShaderSource(temp_id_pair.second,1,&sh_gl_code,NULL);
              glCompileShader(temp_id_pair.second);
              glGetShaderiv(temp_id_pair.second, GL_COMPILE_STATUS, &complie_status);
              if(complie_status !=GL_TRUE)
              {
                GLint logsize;
                std::cout <<"falure to shader_compplie \n";
                glGetShaderiv(temp_id_pair.second,GL_INFO_LOG_LENGTH,&logsize);
                log_shader = new GLchar[logsize+1];

                glGetShaderInfoLog(temp_id_pair.second, logsize, NULL, log_shader);
                // Write the error to a log
                std::cout << log_shader<< '\n';
                delete log_shader;
              }
            }
            else {std::cout << "shader types do not match eep!\n";}

          }
          else { std::cout << "inviald index No opengl_shader in map perhaps forgot to gen one \n";}

  }
  else {std::cout <<"shader_code_map not found\n";}
  std::cout << "SHADER COMPLIED\n";
}
