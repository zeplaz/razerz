

#ifndef RZ_SYM_OBJ_HPP
#define RZ_SYM_OBJ_HPP

#include "gl_lib_z.hpp"

static unsigned int nextobj_id =0;
static int num_sym_obj =0;

//when genreated call function to load the dynamic praperters, or via the non base?
///

enum class  sym_obj_paramz
{
  FBCSYM_
};

class sym_object {

  protected :
  //std::string log_data;
  unsigned int obj_ID;
  Sym_Object_Type so_type;
  int priotry=-1;

  //bool use_pipe = false;

  public :

  void set_priotry(int in_p)
  {
    priotry = in_p;
  }
  int get_priotry() const
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

  void run_log(GLchar* in_log)
  {
    std::fstream w_stream;
    w_stream.open("log_sym_obj.txt",std::fstream::out | std::fstream::app);
    w_stream <<in_log;
  }
  void run_log(std::string in_log)
  {
    std::fstream w_stream;
    w_stream.open("log_sym_obj.txt",std::fstream::out | std::fstream::app);
    w_stream <<in_log;
  }
  //virtual void initalize()=0;
  //virtual void draw() =0;
  //virtual void update() =0;
  //virtual void config(std::vector<>) = 0;

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

  inline unsigned int get_id()
  {
    return obj_ID;
  }


};



#endif
