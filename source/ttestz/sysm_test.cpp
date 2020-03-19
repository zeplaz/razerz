#include "../basez/sym_object.hpp"
#include "../basez/io_utilityz.hpp"
#include "../modualz/phyziz/pysic_lib.hpp"
#include "../modualz/geometry/geometry.hpp"


#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"


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

  sym_object tso;
  //pathz tpath;
  wavefornt_parser2 wp2;
  //tpath.set_path("/localtion/local/lalala.xml");
  tso.set_obj_type(Sym_Object_Type::TEXTURE_OBJ);
  //tpath.output_display();
  //std::cout  << "objecttype::test::" << tso.so_type;
  std::string sometestlog = "testloglolal\n";
  tso.logger(&tso,sometestlog);


glm::vec3 result;
glm::vec3 start(0.0f);
glm::vec3 end(200.f,10.f,500.f);
 float muzzle =200.f;
 glm::vec3 gravity(0.f,-9.8f,0.f);

 std::string test_jeep = {"../../source/data_extrn/neil/tree04.obj"};
 std::pair<std::shared_ptr<std::vector<mesh_vertex>>,
         std::shared_ptr<std::vector<unsigned int>>>
         shipA2_mesh_vertex_DATA = wp2.read_file(test_jeep);

        bool tiloader = TestLoadObj(test_jeep.c_str());

 std::cout<<"->UAZobj#3dataparzed::"<< tiloader << "\n";

result = calc_fire_solution(start,end,muzzle,gravity);
std::cout << "result::" << result.x << " " << result.y << " " << result.z;


  //std::cout << tpath.full_path;
  std::cout <<"\n #####compleate\n \n  \a";
  return 0;
}
