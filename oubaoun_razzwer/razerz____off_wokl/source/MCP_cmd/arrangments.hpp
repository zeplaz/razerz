
#ifndef RZ_ARRANG_HPP
#define RZ_ARRANG_HPP

#include "../basez/shader_lib.hpp"
#include "../modualz/milieu/partical_env.hpp"

#include "../basez/3rdparty/frame_to_video.hpp"
#include "../basez/rez_utility_lib.hpp"
#include "../basez/opengl_utilityz.hpp"
#include "../parserz/shader_parser.hpp"
#include "../modualz/text_render/text_render.hpp"
#include "../MCP_cmd/écouterions_resourcer_CMD.hpp"
#include "../modualz/geometry/terrain.hpp"

  struct arrangment_A1{
    arrangment_A1()
    {
       sp_01= new shader_pipeline();
       ss_milieu_dispayA=new shader_seprate();
      ss_milieu_compA=new shader_seprate();
    ss_model_dispayA=new shader_seprate();
     ss_texrender_A=new shader_seprate();
    ss_terrain_A= new shader_seprate();
    }
    shader_pipeline* sp_01;
    shader_seprate*  ss_milieu_dispayA;
    shader_seprate*  ss_milieu_compA;
    shader_seprate*  ss_model_dispayA;
    shader_seprate* ss_texrender_A;
    shader_seprate* ss_terrain_A;

    compute_partic_attracto comp_part_fire;
    text_render_glyph glphy_render_Maranallo;

    std::vector<model*> model_list;
    std::vector<mesh*> mesh_list;

    glm::vec4 comp_part_orginA;

    wavefornt_parser2 wp2;

    model_ajustment ajust_tree02A;
    model_ajustment test_ajustship;
    model_ajustment test_ajustship2;
    model_ajustment ship_2_orgin;
    model_ajustment dog_orgin;
    model_ajustment column6_orgin;
    model_ajustment tree02_orgin;

    mesh* tree02;
    mesh* column6;
    mesh* dog;
    mesh* shipA3;
    mesh* ship_basic;

    texture_paramz_pak ship_tex_A3_parmz;
    texture_paramz_pak ship_tex_A3_normal_parmz;
    texture_paramz_pak tree02_tx_parmz;

    /*
    OBJECK SHIP TESTZ
    */
     model* ship2_model;
     model* tree02_model;
     model* neil_boatA_model;

     terrain test_terrain;

     std::vector<model_ajustment> modelmover;


    view_lenz* local_lenz =nullptr;
    rez_mgmt*  local_r_mgmt=nullptr;

    void set_local_pointerz(view_lenz*  vl,rez_mgmt* rm);
    void load_complie_test_shaderz();
    void init();
    void process_local_data();
    void update();
    void render(glm::mat4 view_matrix, glm::mat4 Projection);


  };

  #endif
