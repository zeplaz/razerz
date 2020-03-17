#include "../basez/sym_object.hpp"
#include "../basez/io_utilityz.hpp"


int main(int argc, char* argv[])
{

  sym_object tso;
  pathz tpath;

  tpath.set_path("/localtion/local/lalala.xml");
  tso.set_obj_type(Sym_Object_Type::TEXTURE_OBJ);
  tpath.output_display();
  //std::cout  << "objecttype::test::" << tso.so_type;
  std::string sometestlog = "testloglolal\n";
  tso.logger(&tso,sometestlog);

  std::cout << tpath.full_path;
  std::cout <<"\n #####compleate\n \n  \a";
  return 0;
}
