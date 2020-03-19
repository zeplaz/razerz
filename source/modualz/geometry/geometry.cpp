

#include <stddef.h>
#include "geometry.hpp"

std::ostream& operator << (std::ostream &out, const M_Tex_Flag &f)
{
     unsigned char  flag;
    flag  =(unsigned char) f;
    out << flag <<'\n';
    return out;
}




void mesh::pack_mesh_vertex(std::vector<glm::vec3>&in_v,std::vector< glm::vec3>&in_n,
                        std::vector< glm::vec2>&in_tc)
  {
    for(size_t i = 0; i<in_v.size(); i++ )
    {
      mesh_vertex temp_mv;
      temp_mv.v_position = in_v[i];
      temp_mv.v_normal = in_n[i];
      temp_mv.v_textcord = in_tc[i];
      m_vertices->push_back(temp_mv);
    }
  }

  void mesh::pass_meterial_data(shader_seprate* shader)
  {
    glUniform3fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"meterial.emission")        ,1,glm::value_ptr(meterial.emission));
    glUniform3fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"meterial.ambient_reflect") ,1,glm::value_ptr(meterial.ambient_reflect));
    glUniform3fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"meterial.diffuse_reflect") ,1,glm::value_ptr(meterial.diffuse_reflect));
    glUniform3fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"meterial.specular_reflect"),1,glm::value_ptr(meterial.specular_reflect));
    glUniform1f (glGetUniformLocation(shader->gl_shaderprgm_ID,"meterial.shininess")       ,meterial.shininess);
    glUniform1f (glGetUniformLocation(shader->gl_shaderprgm_ID,"meterial.alpha")           ,meterial.alpha);
    glUniform1f (glGetUniformLocation(shader->gl_shaderprgm_ID,"meterial.hight_scale")     ,meterial.hight_scale);
    glUniform1i (glGetUniformLocation(shader->gl_shaderprgm_ID,"meterial.is_normalmap")    ,meterial.is_normalmap);
    glUniform1i (glGetUniformLocation(shader->gl_shaderprgm_ID,"meterial.is_hightmap")     ,meterial.is_hightmap);
  }

  void mesh::pass_meterial_data(gl_shader_t* shader)
  {
    glUniform3fv(glGetUniformLocation(shader->program_ID,"meterial.emission")        ,1,glm::value_ptr(meterial.emission));
    glUniform3fv(glGetUniformLocation(shader->program_ID,"meterial.ambient_reflect") ,1,glm::value_ptr(meterial.ambient_reflect));
    glUniform3fv(glGetUniformLocation(shader->program_ID,"meterial.diffuse_reflect") ,1,glm::value_ptr(meterial.diffuse_reflect));
    glUniform3fv(glGetUniformLocation(shader->program_ID,"meterial.specular_reflect"),1,glm::value_ptr(meterial.specular_reflect));
    glUniform1f (glGetUniformLocation(shader->program_ID,"meterial.shininess")       ,meterial.shininess);
    glUniform1f (glGetUniformLocation(shader->program_ID,"meterial.alpha")           ,meterial.alpha);
    glUniform1f (glGetUniformLocation(shader->program_ID,"meterial.hight_scale")     ,meterial.hight_scale);
    glUniform1i (glGetUniformLocation(shader->program_ID,"meterial.is_normalmap")    ,meterial.is_normalmap);
    glUniform1i (glGetUniformLocation(shader->program_ID,"meterial.is_hightmap")     ,meterial.is_hightmap);
  }


void mesh::draw_element(shader_seprate* shader,glm::mat4& view,glm::mat4& proj)
{
    glUseProgram(shader->gl_shaderprgm_ID);
  glBindVertexArray(VAO_mesh);

  glm::mat4 proj_view(1.f);
  //model drawing
  if(cal_lightz == true)
  {
     glm::mat4 model_view(1.f);
     glm::mat3 normal_matrix(1.f);
     m_v_p = glm::mat4(1.f);

     model_view = view*base_model_matrix;
    //glm::mat3 normal_matrix = glm::transpose(glm::inverse(model_view.xyz));
    normal_matrix = glm::inverse(glm::mat3(model_view));

    proj_view = proj*view;

    m_v_p = proj_view*base_model_matrix;
    glUniformMatrix4fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"model"),1,GL_FALSE,glm::value_ptr(base_model_matrix));
    glUniformMatrix3fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"normal_matrix"),1,GL_TRUE,glm::value_ptr(normal_matrix));
    glUniformMatrix4fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"model_view"),1,GL_FALSE,glm::value_ptr(model_view));
    glUniformMatrix4fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"model_proj_View"),1,GL_FALSE,glm::value_ptr(m_v_p));

    pass_meterial_data(shader);
}
else
{
  m_v_p = glm::mat4(1.f);
  proj_view = proj*view;

  m_v_p = proj_view*base_model_matrix;
  glUniformMatrix4fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"model_view_projection"),1,GL_FALSE,glm::value_ptr(m_v_p));
}

if(use_auto_texturez ==true)
{

        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr   = 1;
        unsigned int heightNr   = 1;
        for(unsigned int i = 0; i < ai_textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = ai_textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if(name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
             else if(name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader->gl_shaderprgm_ID, (name + number).c_str()), i);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, ai_textures[i].id);
        }
}
// texture drawing
if(tex_flagz == M_Tex_Flag::TEXTYR_DEFFUSE)
{ //std::cout <<"only basic texutre" << '\n';
  m_texture_array[0].activate();
  m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);

}
else if ((tex_flagz & (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL))
        == (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL))
{
  m_texture_array[0].activate();
  m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
  m_texture_array[1].activate();
  m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
}
else if ((tex_flagz & (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_PARALLAX))
        == (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_PARALLAX))
{
  m_texture_array[0].activate();
  m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
  m_texture_array[1].activate();
  m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
  m_texture_array[2].activate();
  m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
}

else if ((tex_flagz & (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_PARALLAX))
        == (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_PARALLAX))
{
  m_texture_array[0].activate();
  m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
  m_texture_array[2].activate();
  m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
}

glDrawElements(GL_TRIANGLES, m_v_indices->size(),GL_UNSIGNED_INT,0);
glBindVertexArray(0);
}
///////////////////////////////////////////////////
void mesh::draw_element(gl_shader_t* shader,glm::mat4& view,glm::mat4& proj)
{
    shader->use_shader();

  glBindVertexArray(VAO_mesh);

  glm::mat4 proj_view(1.f);
  //model drawing
  if(cal_lightz == true)
  {
     glm::mat4 model_view(1.f);
     glm::mat3 normal_matrix(1.f);
     m_v_p = glm::mat4(1.f);

     model_view = view*base_model_matrix;
    //glm::mat3 normal_matrix = glm::transpose(glm::inverse(model_view.xyz));
    normal_matrix = glm::inverse(glm::mat3(model_view));

    proj_view = proj*view;

    m_v_p = proj_view*base_model_matrix;
    glUniformMatrix4fv(glGetUniformLocation(shader->program_ID,"model"),1,GL_FALSE,glm::value_ptr(base_model_matrix));
    glUniformMatrix3fv(shader->return_uniform("normal_matrix"),1,GL_TRUE,glm::value_ptr(normal_matrix));
    glUniformMatrix4fv(shader->return_uniform("model_view"),1,GL_FALSE,glm::value_ptr(model_view));
    glUniformMatrix4fv(shader->return_uniform("model_proj_View"),1,GL_FALSE,glm::value_ptr(m_v_p));

    pass_meterial_data(shader);
  }
    else
  {
    m_v_p = glm::mat4(1.f);
    proj_view = proj*view;

    m_v_p = proj_view*base_model_matrix;
    glUniformMatrix4fv(glGetUniformLocation(shader->program_ID,"model_view_projection"),1,GL_FALSE,glm::value_ptr(m_v_p));
  }

  // texture drawing
  if(tex_flagz == M_Tex_Flag::TEXTYR_DEFFUSE)
  { //std::cout <<"only basic texutre" << '\n';
    m_texture_array[0].activate();
    m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);

  }
  else if ((tex_flagz & (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL))
          == (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL))
  {
    m_texture_array[0].activate();
    m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
    m_texture_array[1].activate();
    m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
  }
  else if ((tex_flagz & (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_PARALLAX))
          == (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_PARALLAX))
  {
    m_texture_array[0].activate();
    m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
    m_texture_array[1].activate();
    m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
    m_texture_array[2].activate();
    m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
  }

  else if ((tex_flagz & (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_PARALLAX))
          == (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_PARALLAX))
  {
    m_texture_array[0].activate();
    m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
    m_texture_array[2].activate();
    m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
  }

  glDrawElements(GL_TRIANGLES, m_v_indices->size(),GL_UNSIGNED_INT,0);
  glBindVertexArray(0);

}
///////////////////
void mesh::draw(shader_seprate* shader,glm::mat4& view,glm::mat4& proj)
{
  glUseProgram(shader->gl_shaderprgm_ID);

  glBindVertexArray(VAO_mesh);

  glm::mat4 proj_view(1.f);
  //model drawing
  if(cal_lightz == true)
  {
     glm::mat4 model_view(1.f);
     glm::mat3 normal_matrix(1.f);
     m_v_p = glm::mat4(1.f);

     model_view = view*base_model_matrix;
    //glm::mat3 normal_matrix = glm::transpose(glm::inverse(model_view.xyz));
    normal_matrix = glm::inverse(glm::mat3(model_view));

    proj_view = proj*view;

    m_v_p = proj_view*base_model_matrix;
    glUniformMatrix4fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"model"),1,GL_FALSE,glm::value_ptr(base_model_matrix));
    glUniformMatrix3fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"normal_matrix"),1,GL_TRUE,glm::value_ptr(normal_matrix));
    glUniformMatrix4fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"model_view"),1,GL_FALSE,glm::value_ptr(model_view));
    glUniformMatrix4fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"model_proj_View"),1,GL_FALSE,glm::value_ptr(m_v_p));

    pass_meterial_data(shader);
  }

  else
  {
    m_v_p = glm::mat4(1.f);
    proj_view = proj*view;

    m_v_p = proj_view*base_model_matrix;
    glUniformMatrix4fv(glGetUniformLocation(shader->gl_shaderprgm_ID,"model_view_projection"),1,GL_FALSE,glm::value_ptr(m_v_p));
  }

  // texture drawing
  if(tex_flagz == M_Tex_Flag::TEXTYR_DEFFUSE)
  { //std::cout <<"only basic texutre" << '\n';
    m_texture_array[0].activate();
    m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);

  }
  else if ((tex_flagz & (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL))
          == (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL))
  {
    m_texture_array[0].activate();
    m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
    m_texture_array[1].activate();
    m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
  }
  else if ((tex_flagz & (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_PARALLAX))
          == (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_PARALLAX))
  {
    m_texture_array[0].activate();
    m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
    m_texture_array[1].activate();
    m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
    m_texture_array[2].activate();
    m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
  }

  else if ((tex_flagz & (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_PARALLAX))
          == (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_PARALLAX))
  {
    m_texture_array[0].activate();
    m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
    m_texture_array[2].activate();
    m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
  }

  glDrawArrays(GL_TRIANGLES, 0, m_vertices->size());

}
/////////////////////////////////////
  void mesh::draw(gl_shader_t* shader,glm::mat4& view,glm::mat4& proj)
  {
    shader->use_shader();
    glBindVertexArray(VAO_mesh);

    glm::mat4 proj_view(1.f);
    //model drawing
    if(cal_lightz == true)
    {
       glm::mat4 model_view(1.f);
       glm::mat3 normal_matrix(1.f);
       m_v_p = glm::mat4(1.f);

       model_view = view*base_model_matrix;
      //glm::mat3 normal_matrix = glm::transpose(glm::inverse(model_view.xyz));
      normal_matrix = glm::inverse(glm::mat3(model_view));

      proj_view = proj*view;

      m_v_p = proj_view*base_model_matrix;
      glUniformMatrix4fv(glGetUniformLocation(shader->program_ID,"model"),1,GL_FALSE,glm::value_ptr(base_model_matrix));
      glUniformMatrix3fv(shader->return_uniform("normal_matrix"),1,GL_TRUE,glm::value_ptr(normal_matrix));
      glUniformMatrix4fv(shader->return_uniform("model_view"),1,GL_FALSE,glm::value_ptr(model_view));
      glUniformMatrix4fv(shader->return_uniform("model_proj_View"),1,GL_FALSE,glm::value_ptr(m_v_p));

      pass_meterial_data(shader);
    }

    else
    {
      m_v_p = glm::mat4(1.f);
      proj_view = proj*view;

      m_v_p = proj_view*base_model_matrix;
      glUniformMatrix4fv(glGetUniformLocation(shader->program_ID,"model_view_projection"),1,GL_FALSE,glm::value_ptr(m_v_p));
    }

    // texture drawing
    if(tex_flagz == M_Tex_Flag::TEXTYR_DEFFUSE)
    { //std::cout <<"only basic texutre" << '\n';
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);

    }
    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL))
            == (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
      m_texture_array[1].activate();
      m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
    }
    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_PARALLAX))
            == (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_NORMAL|M_Tex_Flag::TEXTYR_PARALLAX))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
      m_texture_array[1].activate();
      m_texture_array[1].set_texture_sampler_uniform(shader,m_tex_uniform_array[1],m_texture_array[1].texture_indexUnit);
      m_texture_array[2].activate();
      m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
    }

    else if ((tex_flagz & (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_PARALLAX))
            == (M_Tex_Flag::TEXTYR_DEFFUSE|M_Tex_Flag::TEXTYR_PARALLAX))
    {
      m_texture_array[0].activate();
      m_texture_array[0].set_texture_sampler_uniform(shader,m_tex_uniform_array[0],m_texture_array[0].texture_indexUnit);
      m_texture_array[2].activate();
      m_texture_array[2].set_texture_sampler_uniform(shader,m_tex_uniform_array[2],m_texture_array[2].texture_indexUnit);
    }

    glDrawArrays(GL_TRIANGLES, 0, m_vertices->size());

  }


void mesh::pack_mesh_vertex(parsed_paket_type* par_pak)
{
  mesh_vertex temp_mv;
  for(size_t i = 0; i<par_pak->vertices.size(); i++ )
  {
    temp_mv.v_position   =par_pak->vertices[i];
    temp_mv.v_normal     =par_pak->normals[i];
    temp_mv.v_textcord   =par_pak->uvs[i] ;
    m_vertices->push_back(temp_mv);
  }
}

  void mesh::model_init()
  {
    base_model_matrix = glm::mat4(1.0f);
    base_model_matrix = glm::translate(base_model_matrix, posz_base);
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.x),glm::vec3(1.f,0.f,0.f));
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.y),glm::vec3(0.f,1.f,0.f));
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.z),glm::vec3(1.f,0.f,1.f));
    base_model_matrix = glm::scale(base_model_matrix,scale_base);
  }

  void mesh::update_mesh_model(model_ajustment ajust_in)
  {
    rotation_base.x +=ajust_in.rotation_ajust.x;
    rotation_base.y +=ajust_in.rotation_ajust.y;
    rotation_base.z +=ajust_in.rotation_ajust.z;
    posz_base.x     +=ajust_in.posz_ajust.x;
    posz_base.y     +=ajust_in.posz_ajust.y;
    posz_base.z     +=ajust_in.posz_ajust.z;
    scale_base.x    +=ajust_in.scale_ajust.x;
    scale_base.y    +=ajust_in.scale_ajust.y;
    scale_base.z    +=ajust_in.scale_ajust.z;

    base_model_matrix = glm::mat4(1.f);
    base_model_matrix = glm::translate(base_model_matrix, posz_base);
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.x),glm::vec3(1.f,0.f,0.f));
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.y),glm::vec3(0.f,1.f,0.f));
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.z),glm::vec3(1.f,0.f,1.f));
    base_model_matrix = glm::scale(base_model_matrix,scale_base);

  }

  void mesh::set_mesh_model_origin(model_ajustment intial_model)
  {
    rotation_base.x =intial_model.rotation_ajust.x;
    rotation_base.y =intial_model.rotation_ajust.y;
    rotation_base.z =intial_model.rotation_ajust.z;
    posz_base.x     =intial_model.posz_ajust.x;
    posz_base.y     =intial_model.posz_ajust.y;
    posz_base.z     =intial_model.posz_ajust.z;
    scale_base.x    =intial_model.scale_ajust.x;
    scale_base.y    =intial_model.scale_ajust.y;
    scale_base.z    =intial_model.scale_ajust.z;

    base_model_matrix =glm::mat4(1.f);
    base_model_matrix = glm::translate(base_model_matrix, posz_base);
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.x),glm::vec3(1.f,0.f,0.f));
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.y),glm::vec3(0.f,1.f,0.f));
    base_model_matrix = glm::rotate(base_model_matrix,glm::radians(rotation_base.z),glm::vec3(1.f,0.f,1.f));
    base_model_matrix = glm::scale(base_model_matrix,scale_base);
  }

  void mesh::buff_setup_viaAssimp()
  {
    glGenVertexArrays(1,&VAO_mesh);
    glGenBuffers(1,&buff_mesh);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO_mesh);
    glBindBuffer(GL_ARRAY_BUFFER,buff_mesh);

    glBufferData(GL_ARRAY_BUFFER,m_vertices->size()*sizeof(mesh_vertex),&m_vertices->front(),GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_v_indices->size()*sizeof(unsigned int), &m_v_indices->front(),GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)offsetof(mesh_vertex,v_normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)offsetof(mesh_vertex,v_textcord));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)offsetof(mesh_vertex,v_tangent));

    //glEnableVertexAttribArray(4);
    //glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)offsetof(mesh_vertex,v_bitagent));

    glBindVertexArray(0);
  }

  void mesh::bindmesh_buf()
  {
    glGenVertexArrays(1, &VAO_mesh);
    glBindVertexArray(VAO_mesh);

    glGenBuffers(1,&buff_mesh);

    glBindBuffer(GL_ARRAY_BUFFER, buff_mesh);

    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh_vertex)*m_vertices->size(),
                 &m_vertices->front(),GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,sizeof(mesh_vertex), 0);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,sizeof(mesh_vertex),BUFFER_OFFSET(sizeof(glm::vec3)));
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,sizeof(mesh_vertex),BUFFER_OFFSET(sizeof(glm::vec3)+sizeof(glm::vec3)));
   glEnableVertexAttribArray(2);

   glEnableVertexAttribArray(3);
   glVertexAttribPointer(3,4,GL_FLOAT,GL_FALSE,sizeof(mesh_vertex),(void*)offsetof(mesh_vertex,v_tangent));

   glBindVertexArray(0);

  }

void mesh::compute_tangetspace()
  {
    size_t vtrxcount = m_vertices->size();
    std::vector<glm::vec3> tanA(vtrxcount,glm::vec3(0.0f));
    std::vector<glm::vec3> tanB(vtrxcount,glm::vec3(0.0f));

    size_t indic_count = m_v_indices->size();
     for(size_t i=0; i<vtrxcount/3;i++)
      {
        size_t i0 =m_v_indices->at(i);
        size_t i1 =m_v_indices->at(i+1);
        size_t i2 =m_v_indices->at(i+2);

        glm::vec3 point0 = m_vertices->at(i0).v_position;
        glm::vec3 point1 = m_vertices->at(i1).v_position;
        glm::vec3 point2 = m_vertices->at(i2).v_position;

        glm::vec2 tex0 = m_vertices->at(i0).v_textcord;
        glm::vec2 tex1 = m_vertices->at(i1).v_textcord;
        glm::vec2 tex2 = m_vertices->at(i2).v_textcord;

        glm::vec3 edge1 = point1-point0;
        glm::vec3 edge2 = point2-point0;

        glm::vec2 deltauv1 = tex1-tex0;
        glm::vec2 deltauv2 = tex2-tex0;

        glm::vec3 normal = glm::cross((point1-point0),(point2-point0));
        float r = 1.0f/(tex1.x*tex2.y-tex1.y*tex2.x);

        glm::vec3 tan;
        glm::vec3 bintan;

        if(deltauv1.s!=0)
        {
          tan= glm::vec3 (((edge1.x*tex2.y)-(edge2.x*tex1.y))*r,
               ((edge1.y*tex2.y)-(edge2.y*tex1.y))*r,
               ((edge1.z*tex2.y)-(edge2.z*tex1.y))*r);

          bintan = glm::vec3 (((edge1.x*tex2.x)-(edge2.x*tex1.x))*r,
                   ((edge1.y*tex2.x)-(edge2.y*tex1.x))*r,
                   ((edge1.z*tex2.x)-(edge2.z*tex1.x))*r);

           //tan= edge1/deltauv1.s
         }
         else
         {
           tan=edge1/1.0f;
           tan = glm::normalize(tan-glm::dot(normal,tan)*normal);
         }

        tanA[i0] +=tan;
        tanA[i1] +=tan;
        tanA[i2] +=tan;

        tanB[i0] +=bintan;
        tanB[i1] +=bintan;
        tanB[i2] +=bintan;

    }
      for(size_t i =0; i<vtrxcount;i++)
      {
        glm::vec3 normz =m_vertices->at(i).v_normal;
        glm::vec3 t0z = tanA[i];
        glm::vec3 t1z = tanB[i];
        glm::vec3 c = glm::cross(normz,t0z);
        glm::vec3 t= t0z-(normz*glm::dot(normz,t0z));
        float w = (glm::dot(c, t1z) < 0) ? -1.0f : 1.0f;
        m_vertices->at(i).v_tangent = glm::vec4(t.x,t.y,t.z,w);
      }
    }

      void mesh::texture_setup(texture_paramz_pak in_text_pak)
      {
        std::cout << "##begin_textureLoad \n";

        Texture_gl new_texture;
        set_tex_flags(in_text_pak.text_type_flag);

        new_texture.set_texture_ST(in_text_pak.wm_s,'s');
        new_texture.set_texture_ST(in_text_pak.wm_t,'t');
        new_texture.set_min_Mag_Filter(in_text_pak.mag,'i');
        new_texture.set_min_Mag_Filter(in_text_pak.min,'a');

        std::cout << "\n##cmtple_config_beingLOAD::\n";
        new_texture.load_texture(in_text_pak.path,in_text_pak.channels,in_text_pak.tex_unit_index);
          std::cout << "##loadtexture_compleate \n";
        new_texture.init_texture();
          std::cout << "##init texture \n";
      //  new_texture.load_texture(in_text_pak.path);
        new_texture.set_Tex_paramz();
        std::cout << "##set_Tex pramz finished \n \n";
        if(in_text_pak.text_type_flag ==M_Tex_Flag::TEXTYR_DEFFUSE)
        {
          m_texture_array[0]    = new_texture;
          m_tex_uniform_array[0]= in_text_pak.unform_name;
        }
        else if(in_text_pak.text_type_flag==M_Tex_Flag::TEXTYR_NORMAL)
        {
          m_texture_array[1]      = new_texture;
          m_tex_uniform_array[1]  =in_text_pak.unform_name;
          meterial.is_normalmap = true;
        }
        else if(in_text_pak.text_type_flag==M_Tex_Flag::TEXTYR_PARALLAX)
        {
          m_texture_array[2]    = new_texture;
          m_tex_uniform_array[2]=  in_text_pak.unform_name;
          meterial.is_hightmap = true;
        }
      }
