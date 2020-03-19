#pragma once

//#include "../MCP_cmd/shader_pipeline_CMD.hpp"
#include "shader_lib.hpp"

struct ai_texture
{
  unsigned int id;
  std::string type;
  std::string path;
};
unsigned int TextureFromFile(const char *path, const std::string &directory,bool gamma = false);
unsigned int TextureFromFile(std::string& file_path, bool gamma = false);

struct image2 {
  int columns,rows,n;
  unsigned char* image;

  void load(std::string& path,int in_n);
  void cleanup();
  unsigned char* data()
  {
    return &image[0];
  }
};

class texture_2 : public sym_object
{
  private :
  GLenum t_target;
  GLuint textureObj;
  std::string t_filename;
  bool min_map;
  GLenum formate;

  public :

  texture_2()
  {
    //set_id();
    t_target = NULL;
    t_filename = '\0';
    set_obj_type(Sym_Object_Type::TEXTURE_OBJ);
  }
  void config(GLenum text, const std::string& in_path,int index =NULL, bool in_min_map = false, GLenum in_tform= GL_RGBA)
  {

      if(index == NULL)
      {
        set_id(NULL);
      }
      set_id(index);
      set_obj_type(Sym_Object_Type::TEXTURE_OBJ);

      t_target    = text;
      t_filename  = in_path;
      min_map     =  in_min_map;
      formate     =  in_tform;

  }

  void setup(image2& inimage)
  {
    if(t_target == GL_TEXTURE_2D || GL_TEXTURE_1D_ARRAY ||GL_TEXTURE_RECTANGLE)
    {
      glGenTextures(1, &textureObj);
      glBindTexture(t_target, textureObj);
      glTexImage2D(t_target, 0, GL_RGBA, inimage.columns, inimage.rows, 0,
                  GL_RGBA, GL_UNSIGNED_BYTE, inimage.data());
      glTexParameterf(t_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameterf(t_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glBindTexture(t_target, 0);
    }

  }
};


struct texture_paramz_pak
{
  WarpMode wm_s;
  WarpMode wm_t;
  Filter mag;
  Filter min;
  std::string path;
  int channels;
  std::string unform_name;
  M_Tex_Flag text_type_flag;
  int tex_unit_index;
};

struct Texture_gl
   {
       GLuint texture_ID;
       int texture_indexUnit = 0;
       unsigned char* image;

       unsigned int internal_ID;
       std::string type;
       std::string path;

       int width, height,n;

       GLint minFiler = GL_LINEAR;
       GLint magFiler = GL_LINEAR;
       GLint wrapMode_S = GL_CLAMP_TO_EDGE;
       GLint wrapMode_T = GL_CLAMP_TO_EDGE;

       Format formate_internal;
       Format formate_external;
       bool used_vglLoader = false;

       GLuint  TBO_Buffer_Handle;
       void init_texture();

       GLenum return_TextureFormat(Format formate);

       Texture_gl()
       {
         formate_external =  Format::Format_RGB;
         formate_internal =  Format::Format_RGB8;
         glGenTextures(1,&texture_ID);
       }

       inline void activate()
       {
         glActiveTexture(GL_TEXTURE0+texture_indexUnit);
       }

       inline void set_texture_sampler_uniform(gl_shader_t* s_in,std::string uniform_name,int unit)
       {
         glBindTexture(GL_TEXTURE_2D,texture_ID);
         glUniform1i(glGetUniformLocation(s_in->program_ID, uniform_name.c_str()), unit);
       }

       inline void set_texture_sampler_uniform(shader_seprate* s_in,std::string uniform_name,int unit)
       {
         glBindTexture(GL_TEXTURE_2D,texture_ID);
         glUniform1i(glGetUniformLocation(s_in->gl_shaderprgm_ID, uniform_name.c_str()), unit);
       }

       void set_Tex_paramz()
       {
         activate();
         glBindTexture(GL_TEXTURE_2D,texture_ID);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFiler);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFiler);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode_S); //GL_REPEAT//GL_CLAMP_TO_EDGE//GL_CLAMP_TO_BORDER//GL_MIRRORED_REPEAT
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode_T);
       }

       inline void  set_texture_unit_index(int index)
       {
         texture_indexUnit +=index;
       }

       void load_texture(std::string path,int force_channel,int text_unitindex);

       void set_min_Mag_Filter(Filter filt,char min_mag);

       void load_texture(std::string path)
       {
         //vglLoadTexture(path.c_str(),texture_ID,&vglimage);
         used_vglLoader = true;
       }

       void set_texture_ST(WarpMode mode, char st)
       {
         if(st =='t')
         {
           wrapMode_T =mode;
         }
         else{
           wrapMode_S =mode;
         }
       }
};
