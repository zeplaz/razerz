
#include "shader_lib.hpp"


    void shader_seprate::attach_pipline()
    {
      for(size_t i =0;i<number_of_shaders;i++)
      {
        glAttachShader(gl_shaderprgm_ID,gl_shader_objkz_IDz.at(i));
      }
    }

    void shader_seprate::sweep()
    {
      for(size_t i =0;i<number_of_shaders;i++)
      {
        glDetachShader(gl_shaderprgm_ID,gl_shader_objkz_IDz.at(i));
        glDeleteShader(gl_shader_objkz_IDz.at(i));
      }
    }

    //GL_VERTEX_SHADER_BIT, GL_TESS_CONTROL_SHADER_BIT,
  //   GL_TESS_EVALUATION_SHADER_BIT, GL_GEOMETRY_SHADER_BIT, GL_FRAGMENT_SHADER_BIT
//    and GL_COMPUTE_SHADER_BIT. Additionally, the special value GL_ALL_SHADER_BITS
    void shader_seprate::load_shader_file(shader_type in_shd_type,const GLchar* in_shader_text)
    {
      if(in_shd_type == shader_type::VERTEX_SHADER)
      {
        std::cout << "NEW VERTEX SHADER GENREATING\n";
        std::cout << "#\n##SHADER_SOURCE::" << in_shader_text <<'\n'<<'\n';
        GLuint tempid = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(tempid,1,&in_shader_text,NULL);
        gl_shader_objkz_IDz.push_back(tempid);

        glCompileShader(tempid);
        gl_complie_status(tempid);
        glAttachShader(gl_shaderprgm_ID,tempid);
        gl_shader_status(tempid);
        glProgramParameteri(gl_shaderprgm_ID, GL_PROGRAM_SEPARABLE, GL_TRUE);

        number_of_shaders++;

        stagez  |=GL_VERTEX_SHADER_BIT;
        contained_shaders |=shader_type::VERTEX_SHADER;
      }

      else if(in_shd_type ==shader_type::FRAGMENT_SHADER)
      {
        std::cout << "NEW FRAGMENT SHADER GENREATING\n";
        std::cout << "#\n##SHADER_SOURCE::" << in_shader_text <<'\n'<<'\n';
        GLuint tempid  =  glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(tempid,1,(const char**)&in_shader_text,NULL);
        gl_shader_objkz_IDz.push_back(tempid);

        glCompileShader(tempid);
        gl_complie_status(tempid);
        glAttachShader(gl_shaderprgm_ID,tempid);
        gl_shader_status(tempid);
        glProgramParameteri(gl_shaderprgm_ID, GL_PROGRAM_SEPARABLE, GL_TRUE);

        number_of_shaders++;

        stagez  |=GL_FRAGMENT_SHADER_BIT;
        contained_shaders |=shader_type::FRAGMENT_SHADER;
      }

      else if(in_shd_type ==shader_type::COMPUTE_SHADER)
      {
        std::cout << "NEW COMPUTE SHADER GENREATING\n";
        std::cout << "#\n##SHADER_SOURCE::" << in_shader_text <<'\n'<<'\n';
        GLuint tempid  =  glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(tempid,1,(const char**)&in_shader_text,NULL);
        gl_shader_objkz_IDz.push_back(tempid);

        glCompileShader(tempid);
        gl_complie_status(tempid);
        glAttachShader(gl_shaderprgm_ID,tempid);
        gl_shader_status(tempid);
        glProgramParameteri(gl_shaderprgm_ID, GL_PROGRAM_SEPARABLE, GL_TRUE);
        number_of_shaders++;

        stagez  |=GL_COMPUTE_SHADER_BIT;
        contained_shaders |=shader_type::COMPUTE_SHADER;
      }

      else if(in_shd_type ==shader_type::TESS_EVAL_SHADER)
      {
        std::cout << "NEW TESS_EVAL SHADER GENREATING\n";
        std::cout << "#\n##SHADER_SOURCE::" << in_shader_text <<'\n'<<'\n';
        GLuint tempid  =  glCreateShader(GL_TESS_EVALUATION_SHADER);
        glShaderSource(tempid,1,(const char**)&in_shader_text,NULL);
        gl_shader_objkz_IDz.push_back(tempid);

                glCompileShader(tempid);
                gl_complie_status(tempid);
                glAttachShader(gl_shaderprgm_ID,tempid);
                gl_shader_status(tempid);
                glProgramParameteri(gl_shaderprgm_ID, GL_PROGRAM_SEPARABLE, GL_TRUE);
        number_of_shaders++;

        stagez  |=GL_TESS_EVALUATION_SHADER_BIT;
        contained_shaders |=shader_type::TESS_EVAL_SHADER;
      }

      else if(in_shd_type ==shader_type::TESS_CONTROL_SHADER)
      {
        std::cout << "NEW TESS_CTL SHADER GENREATING\n";
        std::cout << "#\n##SHADER_SOURCE::" << in_shader_text <<'\n'<<'\n';
        GLuint tempid  =  glCreateShader(GL_TESS_CONTROL_SHADER);
        glShaderSource(tempid,1,(const char**)&in_shader_text,NULL);
        gl_shader_objkz_IDz.push_back(tempid);

                glCompileShader(tempid);
                gl_complie_status(tempid);
                glAttachShader(gl_shaderprgm_ID,tempid);
                gl_shader_status(tempid);
                glProgramParameteri(gl_shaderprgm_ID, GL_PROGRAM_SEPARABLE, GL_TRUE);
        number_of_shaders++;

        stagez  |=GL_TESS_CONTROL_SHADER_BIT;
        contained_shaders |=shader_type::TESS_CONTROL_SHADER;
      }

      else if(in_shd_type ==shader_type::GEOMETRY_SHADER)
      {
        std::cout << "NEW GEOMETRYZ SHADER GENREATING\n";
        std::cout << "#\n##SHADER_SOURCE::" << in_shader_text <<'\n'<<'\n';
        GLuint tempid  =  glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(tempid,1,&in_shader_text,NULL);
        gl_shader_objkz_IDz.push_back(tempid);

                glCompileShader(tempid);
                gl_complie_status(tempid);
                glAttachShader(gl_shaderprgm_ID,tempid);
                gl_shader_status(tempid);
                glProgramParameteri(gl_shaderprgm_ID, GL_PROGRAM_SEPARABLE, GL_TRUE);

        number_of_shaders++;

        stagez  |=GL_GEOMETRY_SHADER_BIT;
        contained_shaders |=shader_type::GEOMETRY_SHADER;
      }
    }
