#include "../basez/sym_object.hpp"
#include "../basez/io_utilityz.hpp"
#include "../modualz/phyziz/pysic_lib.hpp"

int main(int argc, char* argv[])
{

  sym_object tso;
  //pathz tpath;

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



result = calc_fire_solution(start,end,muzzle,gravity);
std::cout << "result::" << result.x << " " << result.y << " " << result.z;


  //std::cout << tpath.full_path;
  std::cout <<"\n #####compleate\n \n  \a";
  return 0;
}
