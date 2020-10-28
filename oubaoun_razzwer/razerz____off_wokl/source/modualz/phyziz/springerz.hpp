
#pragma once
#include "pysic_lib.hpp"
//#lnculude

struct spring_parmz{

  P_Render_STYZ r_style;

  int points_x;
  int points_y;
  const total_points = points_x *points_y;
  const connections_total = (points_x-1)*(points_y-1)*points_x;
  int num_textures;
  int num_buffer_obj;
  int num_vertx_arr_obj;


};
constexpr int DEFULT_X = 32;
constexpr int DEFULT_y = 32;

class springer{

  protected :
  glm::vec4* inital_pos;
  glm::vec3* intial_velocities;
  glm::ivec4* connection_vec;

  bool config=false;
  spring_parmz spiring_prmz;

  GLuint index_buffer;
  GLuint* pos_tbo;
  GLuint*  spring_vArryObj;
  GLuint*  spring_buffobj;

springer(int x, int y)
  {
    spiring_prmz.points_x=x;
    spiring_prmz.points_y=y;

  }
  springer()
    {
      spiring_prmz.points_x=DEFULT_X;
      spiring_prmz.points_y=DEFULT_y;
    }

  void set_configure_pak(  int num_text, int num_bo, int num_vao;)
  {
    spiring_prmz.num_textures=num_text;
    spiring_prmz.num_buffer_obj=num_bo;
    spiring_prmz.num_vertx_arr_obj=num_vao;

    config = true;
  }

  void shutdown()
  {
    delete[] m_pos_tbo;
  }

  void init()
  {
    if(config == true)
    {
      pos_tbo          = new GLuint[spiring_prmz.num_textures];
      inital_pos       = new glm::vec4(spiring_prmz.total_points);
      intial_velocities= new glm::vec4(spiring_prmz.total_points);
      connection_vec   = new glm::vec4(spiring_prmz.total_points);

    spring_buffobj  = new GLuint[num_buffer_obj];
    spring_vArryObj  = new GLuint[num_vertx_arr_obj];
    //  = new GLuint[num_textures];

      int n;
      int i;

      for(int j = 0; j<spiring_prmz.points_y;j++)
      {
        float fj = (float)j/(float)spiring_prmz.points_y;
        for(i=0;i<spiring_prmz.points_z;i++)
        {
          float fi = (float)i/(float)points_x;
          inital_pos[n] = glm::vec4()

          n++;
        }
      }
    }

    glGenVertexArrays(2, spring_vArryObj);
    glGenBuffer(5, spring_buffobj);

    for(i=0;i<2;i++)
    {
      glBindVertexArray(spring_vArryObj[i]);

    glBindBuffer(GL_ARRAY_BUFFER,spring_buffobj[POS_A+1]);
      glBufferData(GL_ARRAY_BUFFER,spiring_prmz.total_points*sizeof(glm::vec4),inital_pos,GL_DYNAMIC_COPY);
      glVertexAttribPointer(POS_AB,4,GL_FLOAT,GL_FALSE,0,NULL);
      glEnableVertexAttribArray(POS_AB);

    glBindBuffer(GL_ARRAY_BUFFER,spring_buffobj[VELOCITY_A+1]);
      glBufferData(GL_ARRAY_BUFFER,spiring_prmz.total_points*sizeof(glm::vec3),intial_velocities,GL_DYNAMIC_COPY);
      glVertexAttribPointer(VELO_AB,3,GL_FLOAT,GL_FALSE,0,NULL);
      glEnableVertexAttribArray(VELO_AB);

    glBindBuffer(GL_ARRAY_BUFFER,spring_buffobj[CONNECTIONS+1]);
      glBufferData(GL_ARRAY_BUFFER,spiring_prmz.total_points*sizeof(glm::vec4),inital_pos,GL_DYNAMIC_COPY);
      glVertexAttribPointer(CONNECTERZ,4,GL_FLOAT,GL_FALSE,0,NULL);
      glEnableVertexAttribArray(CONNECTERZ);

    }
      delete [] inital_pos;
      delete [] initial_velocities;
      delete [] connection_vec;

    glGenTextures(spiring_prmz.num_textures,pos_tbo);
    glBindTexture(GL_TEXTURE_BUFFER,pos_tbo[0]);
    glTexBuffer(GL_TEXTURE_BUFFER,GL_RGB32F,spring_buffobj[POS_A]);
    glBindTexture(GL_TEXTURE_BUFFER,pos_tbo[1]);
    glTexBuffer(GL_TEXTURE_BUFFER,GL_RGB32F,spring_buffobj[POS_B]);

    int linez = (spiring_prmz.points_x-1)




    index_buffer

  }
};
