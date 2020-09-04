#include "../modualz/milieu/partical_env.hpp"
#include "../basez/shader_lib.hpp"
#include "../basez/3rdparty/frame_to_video.hpp"
#include "../basez/rez_utility_lib.hpp"
#include "../basez/opengl_utilityz.hpp"
//#include "../parserz/shader_parser.hpp"
#include "../modualz/text_render/text_render.hpp"
#include "../MCP_cmd/écouterions_resourcer_CMD.hpp"
#include "../modualz/geometry/terrain.hpp"

#include "../MCP_cmd/engine.hpp"
#include "../MCP_cmd/arrangments.hpp"

float delta_time = 0.0f;        // time between current frame and last frame
float lastFrame = 0.0f;
sym_object so_main_loger;
void process_input_glfw(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void joystick_callback(int id,int event);
bool string_callback = false;

float lastX = MAIN_SCREEN_WIDTH / 2.0f;
float lastY = MAIN_SCREEN_HIGHT / 2.0f;
bool firstMouse = true;
bool is_cursor_captured = false;
GLint frame_buf_width,frame_buf_hight;

view_lenz* prim_lenz =nullptr;

//opencv capture to AVI REQUERD CALLBACKS
bool take_frame_video = false;
void (*vid_cap_callback)(GLFWwindow*,int,std::string);



int main(int argc, char* argv[])
{
  Engine engine;

  int errocode;
  GLFWwindow* glfw_window;
  std::cout <<"gen pipeobj and sepshader\n";


  std::cout << "launching Main Window\n";
  errocode = opengl_context_settup();

  std::cout << "###openglcontexcode::"<< errocode <<'\n';

  /*
  setcontext win and lenZ
  */
  prim_lenz = new view_lenz();
  glfw_window = glfwCreateWindow(MAIN_SCREEN_WIDTH,MAIN_SCREEN_HIGHT,"cmdz_tooltext_teser",NULL,NULL);
  errocode = run_opengl_setup(glfw_window);
  std::cout << "\n ###openglsetupcode::"<< errocode << "\n";
//sym_object tst_so;

 std::cout << "GLVIERSION::" << glGetString(GL_VERSION) <<'\n';
  std::cout << "GLVIERSION::" << glGetString(GL_SHADING_LANGUAGE_VERSION)<<'\n';

    glfwSetCursorPosCallback(glfw_window, mouse_callback);
    glfwSetScrollCallback(glfw_window, scroll_callback);
/*
SHADER SETUP CODE MOVW TO EGINEigniton
*/
  shader_pipeline sp_01;
  shader_seprate  ss_milieu_dispayA;
  shader_seprate  ss_milieu_compA;
  shader_seprate  ss_model_dispayA;
  shader_seprate ss_texrender_A;
  shader_seprate ss_terrain_A;


  //GLuint gl_shaderprgm_ID;
  //gl_shaderprgm_ID = glCreateProgram()

  /*
inputdeivez
  */

  glfwSetJoystickCallback(joystick_callback);

/*
load shader text.. lol all this shuold be in audofielz
*/

  std::cout <<"openfileshader\n";

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

  ss_milieu_compA.load_shader_file(shader_type::COMPUTE_SHADER,in_comp_code);
  ss_milieu_compA.link();
std::cout << "\n\n*************************compute\n";

  ss_milieu_dispayA.load_shader_file(shader_type::VERTEX_SHADER,in_vrtx_code);
  ss_milieu_dispayA.load_shader_file(shader_type::FRAGMENT_SHADER,in_frag_code);
  ss_milieu_dispayA.link();
std::cout << "\n\n*************************milieu_DisalzA\n";
so_main_loger.run_log("\n\n*************************milieu_DisalzA\n");

  ss_texrender_A.load_shader_file(shader_type::VERTEX_SHADER,in_trv_code);
  ss_texrender_A.load_shader_file(shader_type::FRAGMENT_SHADER,in_trf_code);
  ss_texrender_A.link();
  std::cout << "\n\n*************************ss_texrender_A\n";
so_main_loger.run_log("\n\n*************************ss_texrender_A\n");

  std::cout << "convert to glchar*\n";

  ss_terrain_A.load_shader_file(shader_type::VERTEX_SHADER,in_trran_vtx_code);
  ss_terrain_A.load_shader_file(shader_type::TESS_CONTROL_SHADER,in_trran_tcs_code);
  ss_terrain_A.load_shader_file(shader_type::TESS_EVAL_SHADER,in_trran_tes_code);
  ss_terrain_A.load_shader_file(shader_type::FRAGMENT_SHADER,in_trran_frg_code);
  ss_terrain_A.link();
std::cout << "\n\n*************************terrianz\n";
so_main_loger.run_log("\n\n*************************terrianz\n");

  ss_model_dispayA.load_shader_file(shader_type::VERTEX_SHADER,in_vm_code);
  ss_model_dispayA.load_shader_file(shader_type::FRAGMENT_SHADER,in_fragvm_code);
  ss_model_dispayA.link();
std::cout << "\n\n*************************modelshaderzloaded\n";





  std::cout <<"shaderprgmlinked\n";
  sp_01.attach_use_stage(ss_milieu_compA.gl_shaderprgm_ID,GL_COMPUTE_SHADER_BIT);
  sp_01.attach_use_stage(ss_milieu_dispayA.gl_shaderprgm_ID,GL_VERTEX_SHADER_BIT|GL_FRAGMENT_SHADER_BIT);
  sp_01.attach_use_stage(ss_texrender_A.gl_shaderprgm_ID,GL_VERTEX_SHADER_BIT|GL_FRAGMENT_SHADER_BIT);
  sp_01.attach_use_stage(ss_model_dispayA.gl_shaderprgm_ID,GL_VERTEX_SHADER_BIT|GL_FRAGMENT_SHADER_BIT);
  //congure obejcz
  //mului partical setuo
  compute_partic_attracto comp_part_fire;

  comp_part_fire.set_renderz_ID(ss_milieu_compA.gl_shaderprgm_ID,ss_milieu_dispayA.gl_shaderprgm_ID);
  comp_part_fire.set_lenz(prim_lenz);
  glm::vec4 tst_orgin = glm::vec4(-100.5,10.4,-100.4,1);
  comp_part_fire.set_orgin(tst_orgin);
  comp_part_fire.init();

  /*
  FINAL SETUP BEFORE MAINLOOP
  */

  /*
Terrian data
  */





  /*
 *LENZ SETUP>>>deal with it being gobalz?
 */

 std::cout << "load_lenz\n";

 glm::vec3 world_up(0.f,1.f,0.f);
 glm::vec3 lenz_front(0.f,0.f,-1.f);
 glm::vec3 lenz_pos(0.f,0.f,1.f);
 float fov= 90.f;
 float near_plane = 0.1f;
 float far_plane = 1000.f;
 float lenz_radius = 10.0f;


 /*
 *MATRIX INILAZATION SETZ
 */
 glm::mat4  view_projection =glm::mat4(1.f);
 glm::mat4 view_matrix(1.f);
 glm::mat4 Projection(1.f);

 view_matrix =  prim_lenz->return_lenz_view();
 Projection  = prim_lenz->lenz_projection();
 view_projection = Projection*view_matrix;

/*
uniformz
*/

glm::mat4 terrain_model_matrix;

glClearColor(0.2f, 0.2f, 0.1f, 1.0f);


  //  glm::mat4 Projection(1.f);
  //  Projection  = prim_lenz->lenz_projection();
/*
inputstuff
*/

int pad_present = glfwJoystickPresent(GLFW_JOYSTICK_1);

 std::cout<< "JOYSTICK_STATUZ::\n"<< pad_present;
if( pad_present==GLFW_TRUE)
{
  const char* pad_name = glfwGetJoystickName(GLFW_JOYSTICK_1);

  std::string pad_log;
  int pad_count;
  const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &pad_count);

  int but_pad_count;
  const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &but_pad_count);

  pad_log = "\n*##->INPUTE_SENIZOR_DETECTED++Z<<::\n";
  pad_log += "pad_count::";
  pad_log+= std::to_string(pad_count);
  pad_log += "\n aexiz::";
  pad_log+= std::to_string(axes[0]);
  pad_log+= std::to_string(axes[1]);
  pad_log+="\n buttonzcount::";
  pad_log+=std::to_string(but_pad_count);
  pad_log+= "\n---**+\n\n";
  so_main_loger.run_log(pad_log);
}


    rez_mgmt r_mgmt;
    //r_mgmt.ecouterait;
    /*/
    #textrender setup
    */
    text_render_glyph glphy_render_Maranallo;
    glphy_render_Maranallo.get_shader_loc(&ss_texrender_A);

    text_render_pak trDef_pak;

    //trDef_pak.set
    std::string curr_font=  "../modualz/text_render/fonts/Maranallo.ttf";


    std::string thetext = "orbgurozzzz!";
    glm::vec4 font_colour = glm::vec4(1.0f,0.3f,0.6f,1.0f);

    glm::vec2 text_pos = glm::vec2(320.0f, 500.0f);
    GLfloat scale = 1.0f;
    //glphy_render_Maranallo.init(thetext,curr_font,size_64,
      //                          font_colour,text_pos,scale);
      /*
      add framecapture modual
      */

        multiframe_capturer mf_c;
        vid_cap_callback = &multiframe_capturer::set_paramz;

/*
OBJECK SHIP TESTZ
*/

/*
 working DATA for current test.
 */
  model_ajustment ajust_tree02A;
  ajust_tree02A.rotation_ajust = glm::vec3(0.f);
  ajust_tree02A.posz_ajust  = glm::vec3(0.f);
  ajust_tree02A.scale_ajust = glm::vec3(0.f);


   model_ajustment test_ajustship;
   model_ajustment test_ajustship2;

   test_ajustship.rotation_ajust = glm::vec3(0.f);
   test_ajustship.posz_ajust  = glm::vec3(0.f);
   test_ajustship.scale_ajust = glm::vec3(0.f);

   test_ajustship2.rotation_ajust = glm::vec3(0.f);
   test_ajustship2.posz_ajust  = glm::vec3(0.f);
   test_ajustship2.scale_ajust = glm::vec3(0.f);

   model_ajustment ship_2_orgin;

   ship_2_orgin.posz_ajust.x=0.9f;
   ship_2_orgin.posz_ajust.y=0.5f;
   ship_2_orgin.posz_ajust.z= -0.1f;

   ship_2_orgin.scale_ajust = glm::vec3(0.1f);
   ship_2_orgin.rotation_ajust.y = 120.f;
   ship_2_orgin.rotation_ajust.x = 0.f;
   ship_2_orgin.rotation_ajust.z = 0.f;


   model_ajustment dog_orgin;

   dog_orgin.posz_ajust.x=-0.9f;
   dog_orgin.posz_ajust.y=-0.5f;
   dog_orgin.posz_ajust.z= -0.1f;

   dog_orgin.scale_ajust = glm::vec3(0.5f);
   dog_orgin.rotation_ajust.y = 120.f;
   dog_orgin.rotation_ajust.x = 0.f;
   dog_orgin.rotation_ajust.z = 0.f;

   model_ajustment column6_orgin;

   column6_orgin.posz_ajust.x=0.5f;
   column6_orgin.posz_ajust.y=-0.8f;
   column6_orgin.posz_ajust.z=-0.1f;

   column6_orgin.scale_ajust = glm::vec3(1.0f);
   column6_orgin.rotation_ajust.y = 120.f;
   column6_orgin.rotation_ajust.x = 0.f;
   column6_orgin.rotation_ajust.z = 0.f;


   model_ajustment tree02_orgin;

   tree02_orgin.posz_ajust.x=0.5f;
   tree02_orgin.posz_ajust.y=-0.8f;
   tree02_orgin.posz_ajust.z=-0.1f;

   tree02_orgin.scale_ajust = glm::vec3(0.9f);
   tree02_orgin.rotation_ajust.y = 120.f;
   tree02_orgin.rotation_ajust.x = 0.f;
   tree02_orgin.rotation_ajust.z = 0.f;

std::cout<<"#setup_MESSHZED...\n";
wavefornt_parser2 wp2;

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


mesh* tree02 = new mesh();

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

    mesh* column6 = new mesh();

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
    mesh* dog = new mesh();

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
    mesh* shipA3 = new mesh();

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
    mesh* ship_basic = new mesh();
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
  texture_paramz_pak ship_tex_A3_parmz;
  ship_tex_A3_parmz.wm_s    = WarpMode::REPEAT;
  ship_tex_A3_parmz.wm_t    = WarpMode::REPEAT;
  ship_tex_A3_parmz.mag     = Filter::LINEAR;
  ship_tex_A3_parmz.min     = Filter::LINEAR;
  ship_tex_A3_parmz.path    = "../data_extrn/ship_A3/ship_base_A03.5.bmp";
  ship_tex_A3_parmz.channels= 3;
  ship_tex_A3_parmz.unform_name = "active_texture_sampler";
  ship_tex_A3_parmz.tex_unit_index = 0;
  ship_tex_A3_parmz.text_type_flag = M_Tex_Flag::TEXTYR_DEFFUSE;

  texture_paramz_pak ship_tex_A3_normal_parmz;
  ship_tex_A3_normal_parmz.wm_s    = WarpMode::REPEAT;
  ship_tex_A3_normal_parmz.wm_t    = WarpMode::REPEAT;
  ship_tex_A3_normal_parmz.mag     = Filter::LINEAR;
  ship_tex_A3_normal_parmz.min     = Filter::LINEAR;
  ship_tex_A3_normal_parmz.path    = "../data_extrn/ship_A3/Ship_A3.05_hight_normal.bmp";
  ship_tex_A3_normal_parmz.channels= 3;
  ship_tex_A3_normal_parmz.unform_name = "normal_mapSampler";
  ship_tex_A3_normal_parmz.tex_unit_index = 1;
  ship_tex_A3_normal_parmz.text_type_flag = M_Tex_Flag::TEXTYR_NORMAL;



  texture_paramz_pak tree02_tx_parmz;
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



 model ship2_model("../data_extrn/ship_A3/boat_Base2.ply");
 model tree02_model("../data_extrn/neil/tree02.ply");
 model neil_boatA_model("../data_extrn/neil/boat/boat.ply");
  /*
  PIMARY WHILE LOOP... move to own class?
  */

 /*
 * SCENE setupz and load
 */

terrain test_terrain;
std::string terrainA_displacement="../data_extrn/ship_A3/Ship_A3_DispMap.bmp";
std::string terrainA_deffuse="../data_extrn/ship_A3/ship_base_txCORD.bmp";
test_terrain.set_shader(&ss_terrain_A);
test_terrain.set_ecouterait(&r_mgmt.ecouterait);
test_terrain.init();
test_terrain.locate_uniform();
test_terrain.configure();
test_terrain.load_texturez(terrainA_displacement,terrainA_deffuse);

std::vector<model_ajustment> modelmover;



std::cout <<"#####entering main loop setup compleate;\n \n";

  while(!glfwWindowShouldClose(glfw_window))
  {
    modelmover.clear();
    r_mgmt.ecouterait.update_clock(glfwGetTime());
    //process keyz
   float currentFrame = glfwGetTime();
   delta_time = currentFrame - lastFrame;
   lastFrame = currentFrame;
   process_input_glfw(glfw_window);

   //lightupdate
  float timeValue = glfwGetTime();
  float sin_green = sin(timeValue);
  float colour_angluretime = pow((sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue)),2);
  float sin_tsnz = sin(timeValue)*sin(timeValue)/tan(timeValue)*tan(timeValue);
  glm::vec4 ambenshift =glm::vec4(colour_angluretime,sin_green,sin_tsnz,1);

//begin draw config
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearBufferfv(GL_DEPTH, 0, &STAIC_ONE);
   view_matrix =  prim_lenz->return_lenz_view();
   Projection  = prim_lenz->lenz_projection();


   view_projection = glm::mat4(1.f);
   view_projection = Projection*view_matrix;

   /*
    * MODEL TRANFORMZ
    */
    test_ajustship.rotation_ajust.y =0.09f;
    test_ajustship2.posz_ajust.x=-0.001f;

    ajust_tree02A.rotation_ajust.x =0.09f;
    ajust_tree02A.posz_ajust.y  =-0.001f;

    modelmover.push_back(test_ajustship);
    modelmover.push_back(test_ajustship2);
    modelmover.push_back(ajust_tree02A);
    //ajust_tree02A.scale_ajust = glm::vec3(0.f);


    std::cout << "\nshiplocx:" << test_ajustship2.posz_ajust.x <<'\n';
    //test_ajustship2.rotation_ajust.y=-0.01f;
    //test_ajustship2.posz_ajust.x = -0.08f;
    //shipA3.update_mesh_model(test_ajustship);
    shipA3->update_mesh_model(test_ajustship2);
    ship2_model.move_meshes(test_ajustship2);
    tree02_model.disamove_meshz(modelmover);
    //shipA3->draw(view_matrix,active_projection);
/*
DRAW
*/



    //setprojeciozn
    glfwGetFramebufferSize(glfw_window,&frame_buf_width,&frame_buf_hight);

/*
update
*/
//terrainz move to fun
//glProgramUniformMatrix4f(ss_terrain_A->gl_shaderprgm_ID,)

//glEnable(GL_DEPTH_TEST);
//glDepthFunc(GL_LEQUAL);
//data gen//
tst_orgin.x+= pow(tan(delta_time*delta_time)*sin(delta_time),sin(delta_time))*tan(tst_orgin.x);
    tst_orgin.y+= tan(tst_orgin.y)/sin(tst_orgin.y)*delta_time;
    tst_orgin.z-=((tan(tst_orgin.z)/sin(tst_orgin.z)))*delta_time;
    if(tst_orgin.x>138||tst_orgin.x<-138)
    {
      tst_orgin.x = 1;
    }
    if(tst_orgin.z>176||tst_orgin.z<-1148)
    {
      tst_orgin.z = 1;
    }
    if(tst_orgin.y>138||tst_orgin.y<-138)
    {
      tst_orgin.y = 1;
    }

//list of objs to update with data
//comp_part_fire.set_orgin(tst_orgin);

    /*
    DRAW
    */



  //  drawmodualsz

    comp_part_fire.partical_dispaly();
      //text_render_draw_Block();

      shipA3 ->draw(&ss_model_dispayA,view_matrix,Projection);
      dog    ->draw(&ss_model_dispayA,view_matrix,Projection);
      //column6->draw(&ss_model_dispayA,view_matrix,Projection);
      //tree02->draw(&ss_model_dispayA,view_matrix,Projection);
      //tree02_model.();
        tree02_model.model_draw(&ss_model_dispayA,view_matrix,Projection);
        ship2_model.model_draw(&ss_model_dispayA,view_matrix,Projection);
        neil_boatA_model.model_draw(&ss_model_dispayA,view_matrix,Projection);

        test_terrain.draw(Projection,view_matrix);//
    //  {
        //glphy_render_Maranallo.draw(&ss_texrender_A,frame_buf_width,frame_buf_hight);

      //  }//swap
    glfwSwapBuffers(glfw_window);

//anycapturez before refesing
if(take_frame_video == true)
    { bool compleate;

      mf_c.export_framebuff_avi(&compleate);
      if(compleate ==true)
      {
        take_frame_video = false;
      }
    }


    /*ifvideo
    if(take_frame_video == true)
    { bool compleate;

      mf_c.export_framebuff_avi(&compleate);
      if(compleate ==true)
      {
        take_frame_video = false;
      }
    }*/

    glfwPollEvents();
  }

std::cout <<"\n #####compleate\n \n  \a";
return 0;
}




///boilplate move to utilitiz

void joystick_callback(int id, int event)
{
  std::string call_log;
  call_log= "\n\n___-INPUTCMDZ_DIVIZE_DETK:ZDI_->\n";
  call_log +=std::to_string(id);
  call_log +="\nto_string(event)::";
  call_log +=std::to_string(event);
  call_log +="\n";
  if (event == GLFW_CONNECTED)
{
call_log +="&*^CONNEION_ESTABLISHEDz^^|\n";
}
else if (event == GLFW_DISCONNECTED)
{
    call_log +="\n&*^LOSTCONNEION_ISHE_-^%Dz^^|\n";
}

so_main_loger.run_log(call_log);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  if(firstMouse)
  {
    lastX = xpos;
    lastY= ypos;
    firstMouse = false;
  }
  float xoffset = xpos- lastX;
  float yoffset = lastY-ypos;
  lastX=xpos;
  lastY=ypos;
  prim_lenz->process_mouse(xoffset,yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  prim_lenz->process_scroll(yoffset);
}

void process_input_glfw(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {glfwSetWindowShouldClose(window, true);}

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
          {
            if(is_cursor_captured)
            {
              glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
              is_cursor_captured=false;
            }
            else
            {
              is_cursor_captured= true;
              glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            }
//  float lenz_speed = 2.5*delta_time;
  if(glfwGetKey(window,GLFW_KEY_F1) ==  GLFW_PRESS)
  {
    take_screenshot_to_file(frame_buf_width,frame_buf_hight);
  }

  if(glfwGetKey(window,GLFW_KEY_F2) ==  GLFW_PRESS)
  {
    capture_frame_buff_avi(window,vid_cap_callback);
    take_frame_video=true;
  }

  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    prim_lenz->lenz_move(delta_time,'w');
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    prim_lenz->lenz_move(delta_time,'s');
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    prim_lenz->lenz_move(delta_time,'a');
  }
  if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    prim_lenz->lenz_move(delta_time,'d');
  }
}
