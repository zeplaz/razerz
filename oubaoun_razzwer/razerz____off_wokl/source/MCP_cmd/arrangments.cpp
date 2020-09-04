

#include "arrangments.hpp"
    void arrangment_A1::set_local_pointerz(view_lenz*  vl,rez_mgmt* rm)
    {
      local_lenz= vl;
      local_r_mgmt= rm;
    }

    void arrangment_A1::load_complie_test_shaderz()
    {
      std::cout <<"openfileshader\n";
      sym_object arrangment_log;
    //terrainz

     std::ifstream file_trran_vtx("../shaderzglsl/elemental/terrain/vertex_terranpass_A.glsl");
     std::string str_trran_vtx((std::istreambuf_iterator<char>(file_trran_vtx)),
                           std::istreambuf_iterator<char>());

    std::cout << "convert to glchar*\n";
    const GLchar* in_trran_vtx_code = str_trran_vtx.c_str();
    //

    std::ifstream file_trran_frg("../shaderzglsl/elemental/terrain/frag_terran_A.glsl");
    std::string str_trran_frg((std::istreambuf_iterator<char>(file_trran_frg)),
                          std::istreambuf_iterator<char>());

    std::cout << "convert to glchar*\n";
    const GLchar* in_trran_frg_code = str_trran_frg.c_str();
    //

    std::ifstream file_trran_tcs("../shaderzglsl/elemental/terrain/tessctrl_terran_A.glsl");
    std::string str_trran_tcs((std::istreambuf_iterator<char>(file_trran_tcs)),
                          std::istreambuf_iterator<char>());

    std::cout << "convert to glchar*\n";
    const GLchar* in_trran_tcs_code = str_trran_tcs.c_str();
    //

    std::ifstream file_trran_tes("../shaderzglsl/elemental/terrain/tesseval_terran_A.glsl");
    std::string str_trran_tes((std::istreambuf_iterator<char>(file_trran_tes)),
                          std::istreambuf_iterator<char>());

    std::cout << "convert to glchar*\n";
    const GLchar* in_trran_tes_code = str_trran_tes.c_str();
    //

    //text_glph

      std::ifstream file_tr_v("../shaderzglsl/gui_base/vertex_glyph_shaderbase_A.glsl");
       std::string str_tr_v((std::istreambuf_iterator<char>(file_tr_v)),
                             std::istreambuf_iterator<char>());

      std::cout << "convert to glchar*\n";
      const GLchar* in_trv_code = str_tr_v.c_str();

      std::ifstream file_tr_f("../shaderzglsl/gui_base/frag_glyph_shaderbase_A.glsl");
       std::string str_tr_f((std::istreambuf_iterator<char>(file_tr_f)),
                             std::istreambuf_iterator<char>());

      std::cout << "convert to glchar*\n";
      const GLchar* in_trf_code = str_tr_f.c_str();

      std::ifstream file_cmp("../shaderzglsl/elemental/compute_partical/comput_expanse_BASE_A.glsl");
       std::string str_cmp((std::istreambuf_iterator<char>(file_cmp)),
                             std::istreambuf_iterator<char>());

      std::cout << "convert to glchar*\n";
      const GLchar* in_comp_code = str_cmp.c_str();

       std::ifstream file_verx("../shaderzglsl/elemental/compute_partical/vertex_partical_BASE_A.glsl");
      std::string  str_vrtx((std::istreambuf_iterator<char>(file_verx)),
                             std::istreambuf_iterator<char>());

      std::cout << "convert to glchar*\n";
      const GLchar* in_vrtx_code = str_vrtx.c_str();

      std::ifstream file_fpA("../shaderzglsl/elemental/compute_partical/frag_partical_BASE_A.glsl");
      std::string str_fpA((std::istreambuf_iterator<char>(file_fpA)),
                             std::istreambuf_iterator<char>());

      std::cout << "convert to glchar*\n";
      const GLchar* in_frag_code = str_fpA.c_str();

      std::ifstream file_vmodel("../shaderzglsl/modelz/vertex_shader_baseC.glsl");
      std::string str_vm((std::istreambuf_iterator<char>(file_vmodel)),
                             std::istreambuf_iterator<char>());

      std::cout << "convert to glchar*\n";
      const GLchar* in_vm_code = str_vm.c_str();

      //model_shadersz
      std::ifstream file_fmodel("../shaderzglsl/modelz/frag_shader_lightC.glsl");
      std::string str_fragvm((std::istreambuf_iterator<char>(file_fmodel)),
                             std::istreambuf_iterator<char>());
      const GLchar* in_fragvm_code = str_fragvm.c_str();

      ss_milieu_compA->load_shader_file(shader_type::COMPUTE_SHADER,in_comp_code);
      ss_milieu_compA->link();
    std::cout << "\n\n*************************compute\n";

      ss_milieu_dispayA->load_shader_file(shader_type::VERTEX_SHADER,in_vrtx_code);
      ss_milieu_dispayA->load_shader_file(shader_type::FRAGMENT_SHADER,in_frag_code);
      ss_milieu_dispayA->link();
    std::cout << "\n\n*************************milieu_DisalzA\n";
    arrangment_log.run_log("\n\n*************************milieu_DisalzA\n");

      ss_texrender_A->load_shader_file(shader_type::VERTEX_SHADER,in_trv_code);
      ss_texrender_A->load_shader_file(shader_type::FRAGMENT_SHADER,in_trf_code);
      ss_texrender_A->link();
      std::cout << "\n\n*************************ss_texrender_A\n";
    arrangment_log.run_log("\n\n*************************ss_texrender_A\n");

      std::cout << "convert to glchar*\n";

      ss_terrain_A->load_shader_file(shader_type::VERTEX_SHADER,in_trran_vtx_code);
      ss_terrain_A->load_shader_file(shader_type::TESS_CONTROL_SHADER,in_trran_tcs_code);
      ss_terrain_A->load_shader_file(shader_type::TESS_EVAL_SHADER,in_trran_tes_code);
      ss_terrain_A->load_shader_file(shader_type::FRAGMENT_SHADER,in_trran_frg_code);
      ss_terrain_A->link();
    std::cout << "\n\n*************************terrianz\n";
    arrangment_log.run_log("\n\n*************************terrianz\n");

      ss_model_dispayA->load_shader_file(shader_type::VERTEX_SHADER,in_vm_code);
      ss_model_dispayA->load_shader_file(shader_type::FRAGMENT_SHADER,in_fragvm_code);
      ss_model_dispayA->link();
    std::cout << "\n\n*************************modelshaderzloaded\n";

      std::cout <<"shaderprgmlinked\n";
      sp_01->attach_use_stage(ss_milieu_compA->gl_shaderprgm_ID,GL_COMPUTE_SHADER_BIT);
      sp_01->attach_use_stage(ss_milieu_dispayA->gl_shaderprgm_ID,GL_VERTEX_SHADER_BIT|GL_FRAGMENT_SHADER_BIT);
      sp_01->attach_use_stage(ss_texrender_A->gl_shaderprgm_ID,GL_VERTEX_SHADER_BIT|GL_FRAGMENT_SHADER_BIT);
      sp_01->attach_use_stage(ss_model_dispayA->gl_shaderprgm_ID,GL_VERTEX_SHADER_BIT|GL_FRAGMENT_SHADER_BIT);
    }

    void arrangment_A1::init()
    {
      comp_part_fire.set_renderz_ID(ss_milieu_compA->gl_shaderprgm_ID,ss_milieu_dispayA->gl_shaderprgm_ID);
      comp_part_fire.set_lenz(local_lenz);
      comp_part_orginA = glm::vec4(-100.5,10.4,-100.4,1);
      comp_part_fire.set_orgin(comp_part_orginA);
      comp_part_fire.init();
      glphy_render_Maranallo.get_shader_loc(ss_texrender_A);
    }

    void arrangment_A1::process_local_data()
    {
      /*
       working DATA for current test.
       */

       ship2_model     =new model("../data_extrn/ship_A3/boat_Base2.ply");
       tree02_model     =new model("../data_extrn/neil/tree02.ply");
       neil_boatA_model = new model("../data_extrn/neil/boat/boat.ply");

        ajust_tree02A.rotation_ajust = glm::vec3(0.f);
        ajust_tree02A.posz_ajust  = glm::vec3(0.f);
        ajust_tree02A.scale_ajust = glm::vec3(0.f);

         test_ajustship.rotation_ajust = glm::vec3(0.f);
         test_ajustship.posz_ajust  = glm::vec3(0.f);
         test_ajustship.scale_ajust = glm::vec3(0.f);

         test_ajustship2.rotation_ajust = glm::vec3(0.f);
         test_ajustship2.posz_ajust  = glm::vec3(0.f);
         test_ajustship2.scale_ajust = glm::vec3(0.f);


         ship_2_orgin.posz_ajust.x=0.9f;
         ship_2_orgin.posz_ajust.y=0.5f;
         ship_2_orgin.posz_ajust.z= -0.1f;

         ship_2_orgin.scale_ajust = glm::vec3(0.1f);
         ship_2_orgin.rotation_ajust.y = 120.f;
         ship_2_orgin.rotation_ajust.x = 0.f;
         ship_2_orgin.rotation_ajust.z = 0.f;

         dog_orgin.posz_ajust.x=-0.9f;
         dog_orgin.posz_ajust.y=-0.5f;
         dog_orgin.posz_ajust.z= -0.1f;

         dog_orgin.scale_ajust = glm::vec3(0.5f);
         dog_orgin.rotation_ajust.y = 120.f;
         dog_orgin.rotation_ajust.x = 0.f;
         dog_orgin.rotation_ajust.z = 0.f;

         column6_orgin.posz_ajust.x=0.5f;
         column6_orgin.posz_ajust.y=-0.8f;
         column6_orgin.posz_ajust.z=-0.1f;

         column6_orgin.scale_ajust = glm::vec3(1.0f);
         column6_orgin.rotation_ajust.y = 120.f;
         column6_orgin.rotation_ajust.x = 0.f;
         column6_orgin.rotation_ajust.z = 0.f;

         tree02_orgin.posz_ajust.x=0.5f;
         tree02_orgin.posz_ajust.y=-0.8f;
         tree02_orgin.posz_ajust.z=-0.1f;

         tree02_orgin.scale_ajust = glm::vec3(0.9f);
         tree02_orgin.rotation_ajust.y = 120.f;
         tree02_orgin.rotation_ajust.x = 0.f;
         tree02_orgin.rotation_ajust.z = 0.f;

                    std::string shipA2_path = {"../data_extrn/ship_A3/boat_Base_2.obj"};
                    std::pair<std::shared_ptr<std::vector<mesh_vertex>>,
                            std::shared_ptr<std::vector<unsigned int>>>
                            shipA2_mesh_vertex_DATA = wp2.read_file(shipA2_path);
                   std::cout<<"->SHIP#3dataparzed\n";

                    std::string dog_path = {"../data_extrn/neil/dog.obj"};
                    std::pair<std::shared_ptr<std::vector<mesh_vertex>>,
                              std::shared_ptr<std::vector<unsigned int>>>
                              dog_mesh_vertex_DATA = wp2.read_file(dog_path);
                  std::cout<<"->dog#3dataparzed\n";
      //
                  std::string column6_path = {"../data_extrn/neil/mountain.obj"};
                   std::pair<std::shared_ptr<std::vector<mesh_vertex>>,
                            std::shared_ptr<std::vector<unsigned int>>>
                            column6_mesh_vertex_DATA = wp2.read_file(column6_path);
                std::cout<<"->mountan#3dataparzed\n";

                            std::string tree02_path = {"../data_extrn/neil/tree02.obj"};
                            std::pair<std::shared_ptr<std::vector<mesh_vertex>>,
                                      std::shared_ptr<std::vector<unsigned int>>>
                                      tree02_mesh_vertex_DATA = wp2.read_file(tree02_path);
                          std::cout<<"->tree02#3dataparzed\n";
      //mesh creaionintz and metiralzpropriz


      tree02 = new mesh();


      tree02->init(tree02_mesh_vertex_DATA,M_Model_Flag::MODEL_UNIFORM,HAS_LIGHTS);
      tree02->bindmesh_buf();

      glm::vec3 tree02_emis            =glm::vec3(0.0f);
      glm::vec3 tree02_amb_ref         =glm::vec3(0.2,0.6,0.8);
      glm::vec3 tree02_diff_ref        =glm::vec3(0.2,0.3,0.5);
      glm::vec3 tree02_spektral_reflect=glm::vec3(0.2,0.8,0.5);
      float     tree02_shinyz          =12;

      tree02->set_mesh_model_origin(tree02_orgin);
      tree02->set_meterial(tree02_emis,tree02_amb_ref,tree02_diff_ref,
                          tree02_spektral_reflect,tree02_shinyz);


          column6 = new mesh();

          column6->init(column6_mesh_vertex_DATA,M_Model_Flag::MODEL_UNIFORM,HAS_LIGHTS);
          column6->bindmesh_buf();

          glm::vec3 column6_emis            =glm::vec3(0.0f);
          glm::vec3 column6_amb_ref         =glm::vec3(0.1,0.6,0.8);
          glm::vec3 column6_diff_ref        =glm::vec3(0.5,0.3,0.3);
          glm::vec3 column6_spektral_reflect=glm::vec3(1.0,1.0,1.0);
          float     column6_shinyz          =6;

          column6->set_mesh_model_origin(column6_orgin);
          column6->set_meterial(column6_emis,column6_amb_ref,column6_diff_ref,
                              column6_spektral_reflect,column6_shinyz);

      ////
          dog = new mesh();

          dog->init(dog_mesh_vertex_DATA,M_Model_Flag::MODEL_UNIFORM,HAS_LIGHTS);
          dog->bindmesh_buf();

          glm::vec3 dog_emis            =glm::vec3(0.0f);
          glm::vec3 dog_amb_ref         =glm::vec3(0.5,0.6,0.8);
          glm::vec3 dog_diff_ref        =glm::vec3(0.5,0.3,0.3);
          glm::vec3 dog_spektral_reflect=glm::vec3(1.0,1.0,1.0);
          float     dog_shinyz          =60;

          dog->set_mesh_model_origin(dog_orgin);
          dog->set_meterial(dog_emis,dog_amb_ref,dog_diff_ref,
                              dog_spektral_reflect,dog_shinyz);

      ////////
          shipA3 = new mesh();



          shipA3->init(shipA2_mesh_vertex_DATA,M_Model_Flag::MODEL_UNIFORM,HAS_LIGHTS);
          shipA3->bindmesh_buf();

          glm::vec3 shipA2_emis            =glm::vec3(0.0f);
          glm::vec3 shipA2_amb_ref         =glm::vec3(0.5,0.6,0.8);
          glm::vec3 shipA2_diff_ref        =glm::vec3(0.5,0.3,0.3);
          glm::vec3 shipA2_spektral_reflect=glm::vec3(1.0,1.0,1.0);
          float     shipA2_shinyz          =600;

          shipA3->set_meterial(shipA2_emis,shipA2_amb_ref,shipA2_diff_ref,
                                shipA2_spektral_reflect,shipA2_shinyz);

      ////
          ship_basic = new mesh();

          ship_basic->init(shipA2_mesh_vertex_DATA,M_Model_Flag::MODEL_UNIFORM,HAS_LIGHTS);
          ship_basic->bindmesh_buf();
          ship_basic->set_mesh_model_origin(ship_2_orgin);

          ship_basic->set_meterial(shipA2_emis,shipA2_amb_ref,shipA2_diff_ref,
                              shipA2_spektral_reflect,shipA2_shinyz);

        /*
        texture setuptest_move to mesh
        */

        std::cout << "\n*******load texturez\n";

          //vglLoadTexture("data_extrn/ship_base_A03.bmp");

        ship_tex_A3_parmz.wm_s    = WarpMode::REPEAT;
        ship_tex_A3_parmz.wm_t    = WarpMode::REPEAT;
        ship_tex_A3_parmz.mag     = Filter::LINEAR;
        ship_tex_A3_parmz.min     = Filter::LINEAR;
        ship_tex_A3_parmz.path    = "../data_extrn/ship_A3/ship_base_A03.5.bmp";
        ship_tex_A3_parmz.channels= 3;
        ship_tex_A3_parmz.unform_name = "active_texture_sampler";
        ship_tex_A3_parmz.tex_unit_index = 0;
        ship_tex_A3_parmz.text_type_flag = M_Tex_Flag::TEXTYR_DEFFUSE;


        ship_tex_A3_normal_parmz.wm_s    = WarpMode::REPEAT;
        ship_tex_A3_normal_parmz.wm_t    = WarpMode::REPEAT;
        ship_tex_A3_normal_parmz.mag     = Filter::LINEAR;
        ship_tex_A3_normal_parmz.min     = Filter::LINEAR;
        ship_tex_A3_normal_parmz.path    = "../data_extrn/ship_A3/Ship_A3.05_hight_normal.bmp";
        ship_tex_A3_normal_parmz.channels= 3;
        ship_tex_A3_normal_parmz.unform_name = "normal_mapSampler";
        ship_tex_A3_normal_parmz.tex_unit_index = 1;
        ship_tex_A3_normal_parmz.text_type_flag = M_Tex_Flag::TEXTYR_NORMAL;

        tree02_tx_parmz.wm_s    = WarpMode::REPEAT;
        tree02_tx_parmz.wm_t    = WarpMode::REPEAT;
        tree02_tx_parmz.mag     = Filter::LINEAR;
        tree02_tx_parmz.min     = Filter::LINEAR;
        tree02_tx_parmz.path    = "../data_extrn/neil/tree02yellow.mtl";
        tree02_tx_parmz.channels= 3;
        tree02_tx_parmz.unform_name = "active_texture_sampler";
        tree02_tx_parmz.tex_unit_index = 0;
        tree02_tx_parmz.text_type_flag = M_Tex_Flag::TEXTYR_DEFFUSE;


        shipA3->texture_setup(ship_tex_A3_parmz);
        shipA3->texture_setup(ship_tex_A3_normal_parmz);
        //ship_basic->texture_setup(ship_tex_A3_parmz);

        std::string terrainA_displacement="../data_extrn/ship_A3/Ship_A3_DispMap.bmp";
        std::string terrainA_deffuse="../data_extrn/ship_A3/ship_base_txCORD.bmp";
        test_terrain.set_shader(ss_terrain_A);
        test_terrain.set_ecouterait(&local_r_mgmt->ecouterait);
        test_terrain.init();
        test_terrain.locate_uniform();
        test_terrain.configure();
        test_terrain.load_texturez(terrainA_displacement,terrainA_deffuse);
    }

    void arrangment_A1::update()
    {
      //data gen//
      float delta_time = local_r_mgmt->ecouterait.delta_time;
      comp_part_orginA.x+= pow(tan(delta_time*delta_time)*sin(delta_time),sin(delta_time))*tan(comp_part_orginA.x);
          comp_part_orginA.y+= tan(comp_part_orginA.y)/sin(comp_part_orginA.y)*delta_time;
          comp_part_orginA.z-=((tan(comp_part_orginA.z)/sin(comp_part_orginA.z)))*delta_time;
          if(comp_part_orginA.x>138||comp_part_orginA.x<-138)
          {
            comp_part_orginA.x = 1;
          }
          if(comp_part_orginA.z>176||comp_part_orginA.z<-1148)
          {
            comp_part_orginA.z = 1;
          }
          if(comp_part_orginA.y>138||comp_part_orginA.y<-138)
          {
            comp_part_orginA.y = 1;
          }
      //lightupdate
     float timeValue = glfwGetTime();
     float sin_green = sin(timeValue);
     float colour_angluretime = pow((sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue)),2);
     float sin_tsnz = sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue);
     glm::vec4 ambenshift =glm::vec4(colour_angluretime,sin_green,sin_tsnz,1);


     /*
      * MODEL TRANFORMZ
      */
      test_ajustship.rotation_ajust.y =0.09f;
      test_ajustship2.posz_ajust.x=-0.001f;

      ajust_tree02A.rotation_ajust.x =0.09f;
      ajust_tree02A.posz_ajust.y  =-0.001f;

      shipA3->update_mesh_model(test_ajustship2);
      ship2_model->move_meshes(test_ajustship2);
    //  tree02_model.disamove_meshz(modelmover);

    }

    void arrangment_A1::render(glm::mat4 view_matrix, glm::mat4 Projection)
    {
      comp_part_fire.partical_dispaly();
        //text_render_draw_Block();

        shipA3 ->draw(ss_model_dispayA,view_matrix,Projection);
        dog    ->draw(ss_model_dispayA,view_matrix,Projection);
        //column6->draw(&ss_model_dispayA,view_matrix,Projection);
        //tree02->draw(&ss_model_dispayA,view_matrix,Projection);
        //tree02_model.();
          tree02_model->model_draw(ss_model_dispayA,view_matrix,Projection);
          ship2_model->model_draw(ss_model_dispayA,view_matrix,Projection);
          neil_boatA_model->model_draw(ss_model_dispayA,view_matrix,Projection);
          test_terrain.draw(Projection,view_matrix);//
    }
