
#ifndef RZ_TERRAIN_A_HPP
#define RZ_TERRAIN_A_HPP

#include "../../basez/texture.hpp"
#include "../../basez/shader_lib.hpp"
#include "../../MCP_cmd/shader_pipeline_CMD.hpp"

typedef std::tuple<glm::mat4,bool,bool,bool,float> terrain_feture_tupl;



class terrain : public sym_object
{
  private :

  GLuint           terrian_VAO;

  GLuint          gltexture_displacement_glID;
  GLuint          gltexture_matte_colour_glID;

  int terrain_indexUnit=1;
  glm::mat4            terrain_model_matrix;

  shader_seprate* ss_ptr;
  ecouter*        ecouterait;
  float           displacemap_depth;

  bool            enable_displacement;
  bool            wireframe;
  bool            enable_fog;

  bool            paused;
  struct
  {
      GLint       model_view_proj_matrix;
      GLint       model_view_matrix;
      GLint       proj_matrix;
      GLint       displacemap_depth;
      GLint       enable_fog;
      GLint       fog_colour;
  } terrian_uniforms;


  public :

  void set_ecouterait(ecouter* in_ecut)
  {
  ecouterait=  in_ecut;
  }
  void configure()
  {

    displacemap_depth = 6.0;
    enable_displacement= true;
    wireframe= true;
    enable_fog= true;
    paused =false;
  }



  void load_texturez(std::string& terrain_displacement,std::string& terrin_defuse)
  {
    //load tex dis_str
    gltexture_displacement_glID = TextureFromFile(terrain_displacement);
    gltexture_matte_colour_glID = TextureFromFile(terrin_defuse);

    //GLuint          gltexture_displacement_glID;
    //GLuint          ;
  //  glEnable(GL_CULL_FACE);
    glActiveTexture(GL_TEXTURE1);
  }
  void init()
  {
  glGenVertexArrays(1, &terrian_VAO);
  glBindVertexArray(terrian_VAO);
  glPatchParameteri(GL_PATCH_VERTICES, 4);
  glEnable(GL_CULL_FACE);
  }
  void locate_uniform()
  {
    terrian_uniforms.model_view_matrix = glGetUniformLocation(ss_ptr->gl_shaderprgm_ID, "model_view_matrix");
    terrian_uniforms.model_view_proj_matrix = glGetUniformLocation(ss_ptr->gl_shaderprgm_ID, "model_view_proj_matrix");
    terrian_uniforms.proj_matrix = glGetUniformLocation(ss_ptr->gl_shaderprgm_ID, "proj_matrix");
    terrian_uniforms.displacemap_depth = glGetUniformLocation(ss_ptr->gl_shaderprgm_ID, "displacemap_depth");
    terrian_uniforms.enable_fog = glGetUniformLocation(ss_ptr->gl_shaderprgm_ID, "enable_fog");
    terrian_uniforms.fog_colour = glGetUniformLocation(ss_ptr->gl_shaderprgm_ID, "fog_colour");
    displacemap_depth = 6.0f;
  }

  void set_shader(shader_seprate* in_ss)
  {
    ss_ptr=in_ss;
  }


  void draw(glm::mat4 Projection, glm::mat4 mv_matrix) //
  {

     glUseProgram(ss_ptr->gl_shaderprgm_ID);
       glBindVertexArray(terrian_VAO);

     glBindTexture(GL_TEXTURE_2D,gltexture_displacement_glID);
     glUniform1i(glGetUniformLocation(ss_ptr->gl_shaderprgm_ID, "tex_displacement"), terrain_indexUnit);
     glBindTexture(GL_TEXTURE_2D,gltexture_matte_colour_glID);
     glUniform1i(glGetUniformLocation(ss_ptr->gl_shaderprgm_ID, "tex_colour"), terrain_indexUnit);

     glActiveTexture(GL_TEXTURE0+terrain_indexUnit);
      //call currenttime!

      glPatchParameteri(GL_PATCH_VERTICES, 4);

      double currentTime = ecouterait->Current_Time;
        static double last_time = 0.0;
        static double total_time = 0.0;

        if (!paused)
        total_time += (currentTime - last_time);
        last_time = currentTime;

        float t = (float)total_time * 0.03f;
        float r = sinf(t * 5.37f) * 15.0f + 16.0f;
        float h = cosf(t * 4.79f) * 2.0f + 3.2f;

    //glEnable(GL_CULL_FACE);
  //  glActiveTexture(GL_TEXTURE1);

  //  glm::mat4 mv_matrix = // vmath::translate(0.0f, 0.0f, -1.4f) *
                            //   vmath::translate(0.0f, -0.4f, 0.0f) *
                               // vmath::rotate((float)currentTime * 6.0f, 0.0f, 1.0f, 0.0f) *
  //                             glm::lookAt(glm::vec3(sinf(t) * r, h, cosf(t) * r), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//call global progeions and view mtrix
    glm::mat4 ptmm =Projection * mv_matrix;


    glProgramUniformMatrix4fv(ss_ptr->gl_shaderprgm_ID,terrian_uniforms.model_view_matrix, 1, GL_FALSE, glm::value_ptr(mv_matrix));
    glProgramUniformMatrix4fv(ss_ptr->gl_shaderprgm_ID,terrian_uniforms.proj_matrix, 1, GL_FALSE,glm::value_ptr( Projection));
    glProgramUniformMatrix4fv(ss_ptr->gl_shaderprgm_ID,terrian_uniforms.model_view_proj_matrix, 1, GL_FALSE,glm::value_ptr(ptmm));
    glProgramUniform1f(       ss_ptr->gl_shaderprgm_ID,terrian_uniforms.displacemap_depth, enable_displacement ? displacemap_depth : 0.0f);
    glProgramUniform1f(       ss_ptr->gl_shaderprgm_ID,terrian_uniforms.enable_fog, enable_fog ? 1 : 0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

  //  if (wireframe)
          //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //else
          //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);
  }
};

#endif
