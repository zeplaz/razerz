#pragma once

#include "../../basez/texture.hpp"
#include "../../basez/lenz.hpp"
#include "../../basez/sym_object.hpp"
#include "../../parserz/geometry_parser.hpp"
#include "../../basez/shader_lib.hpp"
#include "../../MCP_cmd/shader_pipeline_CMD.hpp"
class wavefornt_parser2;

typedef struct model_ajustment_type
{
  glm::vec3 posz_ajust;
  glm::vec3 rotation_ajust;
  glm::vec3 scale_ajust;

  model_ajustment_type& operator +=(const model_ajustment_type& inmodel)
  {

    posz_ajust     += inmodel.posz_ajust;
    rotation_ajust += inmodel.rotation_ajust;
    scale_ajust    += inmodel.scale_ajust;
    return *this;
  }
}model_ajustment;

struct Meterialz
{
    glm::vec3 emission;
    glm::vec3 ambient_reflect;
    glm::vec3 diffuse_reflect;
    glm::vec3 specular_reflect;
    float shininess;
    bool is_normalmap= false;
    bool is_hightmap = false;
    float alpha;
    float hight_scale;
    //GLint diffuse_texture;
    //GLint spekular_texture;
};

struct render_state_cache
{
  bool is_elm;
  shader_seprate* shader;
  glm::mat4 view;
  glm::mat4 proj;
};

class mesh : public sym_object
{
  private :

  bool use_auto_texturez=false;

  glm::vec3 posz_base;
  glm::vec3 rotation_base;
  glm::vec3 scale_base;
  model_ajustment current_ajustmentz;

  glm::mat4 base_model_matrix;
  glm::mat4 m_v_p;

  Meterialz meterial;

  unsigned int VAO_mesh, buff_mesh, EBO;
  unsigned int vertex_buf, uv_buf, normal_buf,element_buf;
  std::string res_path;

  M_Tex_Flag tex_flagz     = M_Tex_Flag::TEXTYR_NULL;
  M_Model_Flag Model_flagz = M_Model_Flag::MODEL_NULL;

  bool cal_lightz= false;

  render_state_cache render_cache;

  public :


  std::shared_ptr<std::vector<mesh_vertex>> m_vertices;
  std::shared_ptr<std::vector<unsigned int>> m_v_indices;
  //std::pair<std::array<Texture_gl,3>,std::array<std::string,3>> textture_pair;
  std::array<Texture_gl,3> m_texture_array;
  std::array<std::string,3> m_tex_uniform_array;

  std::vector<ai_texture> ai_textures;

  mesh()
  {
    set_obj_type(Sym_Object_Type::MESH_OBJ);
  }
  void bindmesh_buf();
  inline void set_render_cache(shader_seprate* shader,glm::mat4& view,glm::mat4& proj, bool is_elm)
  {

    render_cache.shader= shader;
    render_cache.view=view;
    render_cache.proj=proj;
    render_cache.is_elm=is_elm;
  }

  inline void draw_via_cache()
  {
    if(render_cache.is_elm == true)
    {
      draw_element(render_cache.shader,render_cache.view,render_cache.proj);
    }
    else
    {
      draw(render_cache.shader,render_cache.view,render_cache.proj);
    }
  }
  void set_texture_via_assip(std::vector<ai_texture>& in_aitex)
  {
    use_auto_texturez = true;
    ai_textures = in_aitex;
  }
  constexpr static const GLchar * material_namez[9] =
  {
    "Meterialz.emission",
    "Meterialz.ambient_reflect"
    "Meterialz.diffuse_reflect"
    "Meterialz.specular_reflect"
    "Meterialz.shininess"
    "Meterialz.alpha"

    "Meterialz.is_normalmap"
    "Meterialz.is_hightmap"

    "Meterialz.hight_scale"
  };

  GLuint uniformMeterial_indicatz[9];
  GLuint meterial_index;
  void set_meterial_indicates(gl_shader_t* shader)
  {
    glGetUniformIndices(shader->program_ID,9,material_namez,uniformMeterial_indicatz);
    meterial_index= glGetUniformBlockIndex(shader->program_ID,"Meterialz");

  //  glBindBufferBase(GL_UNIFORM_BUFFER,meterial_index)
  }
/*  void write_mesh()
  {
    ofstream outmesh;

    outmesh.open("scene01.bin");

    if(std::FILE* outfile = std::fopen("scene01.bin","wb"))
    {
      std::fwrite(m_texture_array.data(),sizeof m_texture_array[0],m_texture_array.size(), outfile );
      std::fwrite(m_tex_uniform_array.data(),sizeof m_tex_uniform_array[0],m_tex_uniform_array.size(), outfile );
    }
  }*/
  void draw(shader_seprate* shader,glm::mat4& view,glm::mat4& proj);

  void draw(gl_shader_t* shader,glm::mat4& view,glm::mat4& proj);
  void draw_element(gl_shader_t* shader,glm::mat4& view,glm::mat4& proj);
  void draw_element(shader_seprate* shader,glm::mat4& view,glm::mat4& proj);
  void model_init();

  void update_mesh_model(model_ajustment ajust_in);
  void set_mesh_model_origin(model_ajustment intial_model);
  inline void update_motion_matrix(glm::mat4 in_mat)
  {
    base_model_matrix*= in_mat;
  }
  void buff_setup_viaAssimp();

  inline void set_tex_flags(M_Tex_Flag t_flag)
  {
    std::cout <<"flagsetter texture set::" << (int)t_flag <<'\n';
    tex_flagz  |=t_flag;
    std::cout << "current texture flagz::" << (int)tex_flagz <<'\n';
  }

  void init(wavefornt_parser2* wp, std::string res_path);

  void set_light_bool(bool is_light)
  {
    cal_lightz=is_light;
  }
  void set_model_flag(M_Model_Flag mm_flag)
  {
    Model_flagz |=mm_flag;
  }

  void compute_tangetspace();

  void create_mesh_via_assimp(std::vector<mesh_vertex> in_mesh_vertex, std::vector<unsigned int> in_indz)
  {
    std::shared_ptr<std::vector<mesh_vertex>> mesh_ptr = std::make_shared<std::vector<mesh_vertex>>(in_mesh_vertex);
    std::shared_ptr<std::vector<unsigned int>> mesh_indz =  std::make_shared<std::vector<unsigned int>>(in_indz);
    m_vertices = mesh_ptr;
    m_v_indices=mesh_indz;
    posz_base    =glm::vec3(1.5f,1.5,0.2);
    rotation_base=glm::vec3(-90.0,10.5,0.5);
    scale_base   =glm::vec3(0.8f);
    model_init();
    buff_setup_viaAssimp();
  }

  void init(std::pair<std::shared_ptr<std::vector<mesh_vertex>>,
            std::shared_ptr<std::vector<unsigned int>>> in_vertx_data,
            M_Model_Flag mm_flag,bool is_avec_lightz)
  {
    m_vertices =in_vertx_data.first;
    m_v_indices = in_vertx_data.second;
    Model_flagz |=mm_flag;
    posz_base    =glm::vec3(0.f);
    rotation_base=glm::vec3(0.f);
    scale_base   =glm::vec3(0.2f);
    cal_lightz = is_avec_lightz;
    model_init();
  }

  void texture_setup(texture_paramz_pak in_text_pak);

  void pack_mesh_vertex(parsed_paket_type* par_pak);

  void pack_mesh_vertex(std::vector<glm::vec3>&in_v,std::vector< glm::vec3>&in_n,
                        std::vector< glm::vec2>&in_tc);

  void pass_meterial_data(gl_shader_t* shader);
  void pass_meterial_data(shader_seprate* shader);
  void set_meterial(glm::vec3 emis, glm::vec3 amb_ref, glm::vec3 diff_ref,
                    glm::vec3 spektral_reflect, float shinyz,float alpha=1.0,float hight_scal =0.1)
  {
    meterial.emission=emis;
    meterial.ambient_reflect=amb_ref;
    meterial.diffuse_reflect=diff_ref;
    meterial.specular_reflect=spektral_reflect;
    meterial.shininess=shinyz;
    meterial.alpha = alpha;
    meterial.hight_scale = hight_scal;
  //  GLint diffuse_texture;
  //  GLint spekular_texture;

  }

  inline unsigned int return_elment_buf()
  {
    return element_buf;
  }

  inline size_t return_num_indices()
  {
    return m_v_indices->size();
  }

  inline void set_render_mode(P_Render_STYZ new_mode, Poly_face face)
  {
       if(new_mode==P_Render_STYZ::WIREFRAME)
         glPolygonMode(face,GL_LINE);

       if(new_mode==P_Render_STYZ::FILL)
         glPolygonMode(face,GL_FILL);

       if(new_mode==P_Render_STYZ::POINT)
        glPolygonMode(face,GL_POINT);
  }
};
