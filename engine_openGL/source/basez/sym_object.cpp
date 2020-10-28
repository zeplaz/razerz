

#include "sym_object.hpp"

std::string to_string(Sym_Object_Type& in_sot)
{
  std::string temp_string;

  switch (in_sot) {
  case Sym_Object_Type::PIPELINE_OBJ:
     temp_string= "|-PIPELINE_OBJ-|\n";
      break;
  case Sym_Object_Type::TEXTURE_OBJ:
     temp_string= "|-TEXTTURE_OBJ-|\n";
      break;
  case Sym_Object_Type::TXT_RENDER_GLYPH:
     temp_string= "|-GLYPH-|\n";
     break;
  case Sym_Object_Type::SHADER_OBJ:
      temp_string="|-SHADER-|\n";
 break;
  case Sym_Object_Type::PARTICAL_COMP:
     temp_string= "|-PARTICAL_COMP-|\n";
 break;
  case Sym_Object_Type::MODEL_OBJ:
     temp_string="|-MODEL_OBJ-|\n";
 break;
   case Sym_Object_Type::MESH_OBJ:
         temp_string=  "|-MESH_OBJ-|\n";
 break;
 default :
   temp_string= "|-UNKOWN TYPE-|\n";
  }
  return temp_string;
}

  void sym_logger::operator()(void* objptr,std::string& n)
  {

     sym_object* temp_sym_ojk = static_cast<sym_object*>(objptr);
      temp_log+= "###Log_OUt::\n";
      temp_log+= "OBJECTID::";
      temp_log+= std::to_string(temp_sym_ojk->get_id());
      temp_log+= "\n TYPE::";
      temp_log+= to_string(temp_sym_ojk->so_type);
      temp_log+= "\n priotry::";
      temp_log+= std::to_string(temp_sym_ojk->get_priotry());
      temp_log+= '\n####\n';
      temp_log+= n;
     run_log(temp_log);
    }

   void sym_logger::operator()(std::string& n) {
     //std::string = temp_log;
     //temp_log +="#logout__#OBJK::";
     //temp_log += get_id();
     //temp_log += '\n';
     temp_log+= "&$%-->logdump::\n";
     temp_log += n;

    run_log(temp_log);
    }
  void sym_logger::run_log(char* in_log) const
  {
    std::fstream w_stream;
    w_stream.open("log_sym_obj.txt",std::fstream::out | std::fstream::app);
    w_stream <<in_log;
  }

  void sym_logger::run_log(std::string in_log) const
  {
    std::fstream w_stream;
    w_stream.open("log_sym_obj.txt",std::fstream::out | std::fstream::app);
    w_stream <<in_log;
  }
