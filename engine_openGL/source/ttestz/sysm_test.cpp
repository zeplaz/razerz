
#include "../basez/texture.hpp"
//#include "../modualz/phyziz/pysic_lib.hpp"
//#include "../modualz/geometry/geometry.hpp"
//#include "../modualz/phyziz/collision_AI.hpp"
//#include "../modualz/committee/simula_entity.hpp"
//#include "../modualz/geometry/assimp_model.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../basez/3rdparty/tiny_obj_loader.h"


static bool TestLoadObj(const char* filename, const char* basepath = NULL,
                        bool triangulate = true) {
  std::cout << "Loading " << filename << std::endl;

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;


  std::string warn;
  std::string err;
  bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename,
                              basepath, triangulate);

  if (!warn.empty()) {
    std::cout << "WARN: " << warn << std::endl;
  }

  if (!err.empty()) {
    std::cerr << "ERR: " << err << std::endl;
  }

  if (!ret) {
    printf("Failed to load/parse .obj.\n");
    return false;
  }

  return true;
}






int main(int argc, char* argv[])
{

  //bullet_collision_detector bullet_phyz_systm;

//  sym_object tso;
  //pathz tpath;
  //wavefornt_parser2 wp2;
  //tpath.set_path("/localtion/local/lalala.xml");
//  tso.set_obj_type(Sym_Object_Type::TEXTURE_OBJ);
  //tpath.output_display();
  //std::cout  << "objecttype::test::" << tso.so_type;
  //std::string sometestlog = "testloglolal\n";
//  tso.logger(&tso,sometestlog);


glm::vec3 result;
glm::vec3 start(0.0f);
glm::vec3 end(200.f,10.f,500.f);
 float muzzle =200.f;
 glm::vec3 gravity(0.f,-9.8f,0.f);
/*
 std::string test_jeep = {"../../data_extrn/neil/tree04.obj"};
 std::pair<std::shared_ptr<std::vector<mesh_vertex>>,
         std::shared_ptr<std::vector<unsigned int>>>
         shipA2_mesh_vertex_DATA = wp2.read_file(test_jeep);

        bool tiloader = TestLoadObj(test_jeep.c_str());
*/
/*
glm::vec3 postest(2,2,0);
glm::quat rotaion_test(90.f,1.f,1.f,1.f);
glm::vec3 scaletest(1.f);
ai_Transformz model_test_orgianz(postest,rotaion_test,scaletest);
 std::shared_ptr<ai_model> testModel_train01 = ai_model::load_from_file("../../data_extrn/neil/train01.obj");

 std::cout<<"->UAZobj#3dataparzed::\n";//<< tiloader << "\n";

result = calc_fire_solution(start,end,muzzle,gravity);
std::cout << "result::" << result.x << " " << result.y << " " << result.z;
btTransform sheredp_tranformer;
bullet_phyz_systm.add_sphere(sheredp_tranformer,1.0,0,20,0,1.0,0);

  // fake loop
  bullet_phyz_systm.dynamicsWorld->stepSimulation(1/60.0);
*/
  //std::cout << tpath.full_path;
  std::cout <<"\n #####compleate\n \n  \a";
  return 0;
}
