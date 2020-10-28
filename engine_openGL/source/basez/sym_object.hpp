

#ifndef RZ_SYM_OBJ_HPP
#define RZ_SYM_OBJ_HPP

#include "cpp_libz_base.hpp"

inline static unsigned int nextobj_id =0;
static int num_sym_obj =0;
//when genreated call function to load the dynamic praperters, or via the non base?
///
enum class  sym_obj_paramz
{
  FBCSYM_
};

enum  class Sym_Object_Type : unsigned char
{
  OBJ_RENDER_STATIC = 0x02,
  OBJ_RENDER_ANIMI  = 0x04,
  TXT_RENDER_GLYPH  = 0x08,
  PARTICAL_COMP     = 0x13,
  TEXTURE_OBJ       = 0x15,
  SHADER_OBJ        = 0x23,
  PIPELINE_OBJ      = 0x31,
  MESH_OBJ          = 0x33,
  MODEL_OBJ         = 0x41,
  TERRERAIN_OBJ     = 0x43
  //LOGGER            = 0x33
};

/*
template<>
struct EnableBitMaskOperators<Sym_Object_Type>
{
    static const bool enable = true;
};*/
std::string to_string(Sym_Object_Type& in_sot);
std::string operator +=(std::string& in_string, const Sym_Object_Type& in_sot);

inline std::ostream &operator<<( std::ostream &os, const Sym_Object_Type cat )
{
  switch (cat) {
  case Sym_Object_Type::PIPELINE_OBJ:
      os << "|-PIPELINE_OBJ-|\n";
      break;
  case Sym_Object_Type::TEXTURE_OBJ:
      os << "|-TEXTTURE_OBJ-|\n";
      break;
  case Sym_Object_Type::TXT_RENDER_GLYPH:
      os << "|-GLYPH-|\n";
  break;
  case Sym_Object_Type::SHADER_OBJ:
      os << "|-SHADER-|\n";
  break;
  case Sym_Object_Type::PARTICAL_COMP:
      os << "|-PARTICAL_COMP-|\n";
  break;
  case Sym_Object_Type::MODEL_OBJ:
      os << "|-MODEL_OBJ-|\n";
  break;
  case Sym_Object_Type::MESH_OBJ:
      os << "|-MESH_OBJ-|\n";
  break;
  default :
  os << "|-UNKOWN TYPE-|\n";

  }
  return os;
}

class  sym_logger
{
  protected :
  std::string temp_log;

  public :
  void operator()( void* objptr,std::string& n);
  void operator()(std::string& n);
  void run_log(char* in_log) const;

  void run_log(std::string in_log) const;
};


class sym_object {

  protected :
  unsigned int obj_ID;
  int priotry=-1;

  public :
  sym_logger logger;
  Sym_Object_Type so_type;

  inline Sym_Object_Type get_type()
  {
    return so_type;
  }

  inline void set_priotry(int in_p)
  {
    priotry = in_p;
  }
  inline int get_priotry() const
  {
    return priotry;
  }
  bool operator ==(const sym_object &sym_o ) const
  {
    return this->priotry == sym_o.get_priotry();
  }

  bool operator <(const sym_object &sym_o ) const
  {
    return this->priotry < sym_o.get_priotry();
  }

  bool operator <=( const sym_object &sym_o ) const
  {
    return this->priotry <= sym_o.get_priotry();
  }

  bool operator >= ( const sym_object &sym_o ) const
  {
    return this->priotry <= sym_o.get_priotry();
  }

  inline void set_id(int in_id = NULL)
  {
    if(in_id == NULL)
    {
      obj_ID = nextobj_id;
      nextobj_id++;
    }
    else{
      obj_ID=in_id;
      if(in_id>=nextobj_id)
      {
        nextobj_id = in_id+1;
      }
    }
    num_sym_obj++;
  }

  inline void set_obj_type(Sym_Object_Type in_so_t)
  {
    so_type=in_so_t;
  }

  inline unsigned int get_id() const
  {
    return obj_ID;
  }
};



//template <class to_log>


//template<class obj>
//static void run_log<obj>()
//bool use_pipe = false;
    //virtual void initalize()=0;
  //virtual void draw() =0;
  //virtual void update() =0;
  //virtual void config(std::vector<>) = 0;


#endif
