
#ifndef RAZER_SHD_LIB_HPP
#define RAZER_SHD_LIB_HPP

#include "sym_object.hpp"
#include "gl_lib_z.hpp"

class shader_base :  public sym_object
{
  public :
  bool use_pipe;
  GLuint gl_shaderprgm_ID;
  void load_file_single_shader_prgm(shader_type in_shd_type,std::string& in_shader_text);

  void gl_shader_status(GLint shd_ID)
  {
    GLchar* log_shader;

    std::string constc_log = "\n\n#->shader statuz LOG::: FROMPRGM ID::";
    constc_log +=std::to_string(gl_shaderprgm_ID);
    constc_log +='\n';
    constc_log +="\n shaderID::"+std::to_string(shd_ID);
    constc_log +='\n';

    GLint logsize;

    glGetShaderiv(shd_ID,GL_INFO_LOG_LENGTH,&logsize);
    log_shader = new GLchar[logsize+1];
    glGetShaderInfoLog(shd_ID, logsize, NULL, log_shader);
    constc_log+=log_shader;
    //run_log(constc_log);
  }

  void gl_complie_status(GLint shd_ID)
  { GLchar* log_shader;
    GLint complie_status;
    glGetShaderiv(shd_ID, GL_COMPILE_STATUS, &complie_status);

    std::string constc_log = "\n\n#->COmplie LOG::: FROM ID::";
    constc_log +=std::to_string(gl_shaderprgm_ID);
    constc_log +='\n';

    if(complie_status !=GL_TRUE)
    {
      GLint logsize;
      std::cout <<"falure to shader_compplie \n";
      glGetShaderiv(shd_ID,GL_INFO_LOG_LENGTH,&logsize);
      log_shader = new GLchar[logsize+1];

      glGetShaderInfoLog(shd_ID, logsize, NULL, log_shader);
      // Write the error to a log

      constc_log+=log_shader;
    //  run_log(constc_log);

      std::cout << log_shader<< '\n';
      delete log_shader;
    }
      else if(complie_status ==GL_TRUE)
   { // run_log(constc_log+":)shaderCOmplie");
     std::cout << "\n:)shaderCOmplie\n";}

  }
  protected :
  shader_type contained_shaders=shader_type::SHADER_NULL;
};

class shader_seprate : public shader_base
  {
    protected :
    std::vector<GLuint> gl_shader_objkz_IDz;
    size_t number_of_shaders;
    GLbitfield stagez;
    public :

    shader_seprate()
    {
      std::cout <<"##constuctor ss\n";
      use_pipe=true;
      gl_shaderprgm_ID =glCreateProgram();

      std::string constc_log = "::-NEW SEPRATED SHADER CREATED ID::";
      constc_log +=std::to_string(gl_shaderprgm_ID);

      set_obj_type(Sym_Object_Type::SHADER_OBJ);
      //run_log(constc_log);

      std::cout <<"##end ss\n";
    }
    void complie_shader(GLuint in_shdr,GLchar* shder_code);
    GLbitfield get_glbit()
    {
      return stagez;
    }
    void sweep();
    void attach_pipline();
    void load_shader_file(shader_type in_shd_type, const GLchar* in_shader_text);
    inline void link()
    {
      GLint isLinked = 0;
      //GLint maxLength = 0;

      glLinkProgram(gl_shaderprgm_ID);
      glGetProgramiv(gl_shaderprgm_ID, GL_LINK_STATUS, &isLinked);
      if(isLinked ==GL_FALSE)
      {
        std::cerr<<"\n\n##**linkshadr_faild\n\n";
        gl_shader_status(gl_shaderprgm_ID);
        exit(SHADER_LINK_FAIL);
      }
    }

    /*void pre_link_setup()
    {
    /glBindAttribLocation
    glBindFragDataLocation
  }*/

  void set_uniforms();
  /*
  void glProgramUniform{1234}{fdi ui}(GLuint program,
                                       GLint location,
                                             TYPE value);
  void glProgramUniform{1234}{fdi ui}v(GLuint program,
                                         GLint location,
                                           GLsizei count,
                                      const TYPE * values);
  void glProgramUniformMatrix{234}{fd}v(GLuint program,
                                         GLint location,
                                           GLsizei count,
                                     GLboolean transpose,
                                   const GLfloat * values);
  void glProgramUniformMatrix{2x3,2x4,3x2,3x4,4x2,4x3}{fd}v(
                                                       GLuint program, GLint location,
                                                       GLsizei count,
                                                       GLboolean transpose,
                                                       const GLfloat * values);
vs glUniform*() and glUniformMatrix*()
  */

};
/*

class shader_default : public shader_base
{
  protected :
  std::shared_ptr<gl_shader_t>  gl_def_shd;

  public :

  inline void set_use_pipe()
  { use_pipe = false; }

  void gen_glshd_def()
  {
      std::shared_ptr<gl_shader_t> temp_ptr (new gl_shader_t);
  }

  std::pair<,std::shared_ptr<gl_shader_t>> return_data_pair()
  {
    return std::make_pair(get_id(),gl_def_shd);
  }
};*/

class gl_shader_t : public shader_base
{
  private :
  shader_type contained_shaders=shader_type::SHADER_NULL;
  unsigned char shader_flags;
  std::unordered_map<unsigned int,std::pair<shader_type,std::string>> shader_code_map;
  std::unordered_map<unsigned int,std::pair<shader_type,GLuint>> shader_IDz_map;

  public :
  GLuint program_ID = 0;
  int Global_shader_ID = 0;
  std::unordered_map<std::string,GLuint> uniform_loc_map;

  bool create_link_program(std::vector<int>& to_attach_shaders);
  void create_shader(shader_type shad_type, unsigned int s_index);
  void setup_shader_code(unsigned int s_index, shader_tupl* in_shader_tuple);
  void load_complie(unsigned int map_index);
  GLuint return_uniform(std::string name);

  gl_shader_t()
  {
    use_pipe = false;
  }

  shader_type get_contaned_shdertypes()
  {
    return contained_shaders;
  }

  inline void use_shader()
  {
    glUseProgram(program_ID);
  }

  inline void shutdown()
  {
    glDeleteShader(program_ID);
  }
  inline void set_glm_mat4(const std::string &name,const glm::mat4 &mat) const
  {
     glUniformMatrix4fv(glGetUniformLocation(program_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
  }

  inline void add_uniform(std::string name,GLuint uniform_loc)
  {
    uniform_loc_map.insert(std::make_pair(name,uniform_loc));
  }

   inline void test_flags()
  {
    //contained_shaders = shader_type::VERTEX_SHADER;

    std::cout << "contaned flags:" << (int)contained_shaders;
    //contained_shaders |= shader_type::FRAGMENT_SHADER;
    //std::cout << "contaned flags:" << (int)contained_shaders;
    //contained_shaders =contained_shaders& ~shader_type::VERTEX_SHADER;
    //  std::cout << "contaned flags:" << (int)contained_shaders;
    std::cout <<"\n \n";
  }

};
#endif

/*
  template<class...Ts>
  void add_shaders_to_pipeline(Shader_Pipeline to_set_pipe, Ts const&... inshader_pac)
  {
        ,;

      (()),...);
  }*/
