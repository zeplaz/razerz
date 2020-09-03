

#ifndef LANDINGZ_OPEN_GL_BASE_HPP
#define LANDINGZ_OPEN_GL_BASE_HPP

#include "../../MCP_cmd/basez/errorhandler.hpp"
#include "../../MCP_cmd/basez/flag_templatez.hpp"


enum class shader_type : unsigned char {
     SHADER_NULL         = 0x00,
     COMPUTE_SHADER      = 0x02,
     VERTEX_SHADER       = 0x04,
     FRAGMENT_SHADER     = 0x08,
     TESS_CONTROL_SHADER = 0x10,
     TESS_EVAL_SHADER    = 0x20,
     GEOMETRY_SHADER     = 0x40,
     ALL_PIPE            = 0x80
};
template<>
struct EnableBitMaskOperators<shader_type>
{
    static const bool enable = true;
};

enum SHDtype_index : uint8_t
{
  SHD_BASICA02_VERTEX     = 6,
  SHD_BASICA01_VERTEX     = 4,
  SHD_BASIC_FRAG          = 5,

  SHD_LIGHTA1_VERTEX      = 7,
  SHD_LIGHTA1_FRAG        = 8,

  SHD_ANIM_VERTEX         = 9,
  SHD_AMIN_FRAG           = 10,
  SHD_GLYPH1_VERTEX       = 11,
  SHD_GLYPH1_FRAG         = 12,

  SHD_PARTIC_A_COMPUTE    = 13,
  SHD_PARTIC_VIZ_VERTEX   = 14,
  SHD_PARTIC_VIZ_FRAG     = 15,

  SHD_PARTIC_B_SIM_VERTEX =16,
  SHD_PARTIC_B_SIM_FRAG   =17,
  SHD_PARTIC_B_GEO_VERTEX =18,
  SHD_PARTIC_B_GEO_FRAG   =19
};



//using ss_shader_array  = std::array<shader_seprate,5>;

class shader_landingz_base
{
  protected :
  shader_type contained_shaders=shader_type::SHADER_NULL;
  public :
  GLuint gl_shaderprgm_ID;

  void load_file_single_shader_prgm(shader_type in_shd_type,std::string& in_shader_text);
  void complie_shader(GLuint in_shdr,GLchar* shder_code);

  shader_landingz_base()
  {
    std::cout <<"##constuctor ss\n";
    gl_shaderprgm_ID =glCreateProgram();
  }

  inline void gl_shader_status(GLint shd_ID)
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

  inline void gl_complie_status(GLint shd_ID)
  {
    GLchar* log_shader;
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
};

#endif
