
#pragma once
//écoute 	écoutera 	écoutait //écouterait /écoutât
#include "mcp_lib.hpp"
//#include "periphery_input.hpp"

template<auto VFnPtr> struct
wrapper;

template<typename TResult, typename... TArgs, TResult ( * VFnPtr)(TArgs...)>
struct wrapper<VFnPtr>
{
    TResult
    operator ()(TArgs... args) const noexcept(noexcept((*VFnPtr)(::std::forward<TArgs>(args)...)))
    {
        return (*VFnPtr)(::std::forward<TArgs>(args)...);
    }
};


class Emetteur
{
  public :
  constexpr static  double D_ZERO = 0.0;
  inline static double gobal_current_time= D_ZERO;
  double local_birth_time = D_ZERO;

  void update_clockz_via_global(double in_time)
  {
    gobal_current_time =in_time;
    update_global_delta();
    update_local_delta();
  }

  double get_lifspan_delta()
  {
    return gobal_current_time - local_birth_time;
  }

  double get_local_delta()
  {
    return local_delta;
  }

  float get_global_delta()
 {
   global_delta_time;
 }

 Emetteur(double in_sym_time) : gobal_current_time{in_sym_time},local_birth_time{in_sym_time},
                                global_delta_time{0.0f},local_delta{D_ZERO}
 {
   update_global_delta();
   update_local_delta();
 }

private:
  float global_delta_time =D_ZERO;
  double local_delta= D_ZERO;

  Emetteur() = default;

  void  update_global_delta()
  {
    global_delta_time = gobal_current_time-global_delta_time;
  }

  void  update_local_delta()
  {
    local_delta = gobal_current_time-local_delta-local_birth_time;
  }

};

template<class Listed, typename pak>
  class ecouter
{
  protected :
  Emetteur* engine_emetteur;
  void input_event();
  std::vector<pak> pack_arry;
  std::unordered_map<unsigned int,std::shared_ptr<Listed>> listed_map;


  public :

  inline int add_pak(pak& in_trp)
  {
    pack_arry.push_back(in_trp);
    return pack_arry.size()-1;
  }
  inline unsigned int registar_ojk(std::shared_ptr<Listed> in_obj)
  {
    listed_map.insert(std::make_pair(in_obj->get_id(),in_obj));
    return in_obj->get_id();
  }

  };

  /*
  struct path_handler{
    std::unordered_map<unsigned int,std::string_view>
  };*/

  /*
  symid,priotry,blockID,drawfunc,ptr_paramz;
  typedef int Block_ID;
  std::<>
  typedef std::priority_queue<,>;

  typedef std::multimap<Block_ID,wrapper>;
  */
  //template<classType>
    //std::priority_queue<>
  //  std::mutlimap<unigned int,>
  //  Emetteur emetteur;
  //or
  //std::unordered_map<unsigned int,std::shared_ptr<gl_shader_t>> shader_map;
  //or
  ///std::unordered_map<unsigned int,std::shared_ptr<shader_seprate>> separated_shdr_prgm_map;
  //std::unordered_map<unsigned int,std::shared_ptr<>> shdr_prgm_map;
  //std::unordered_map<unsigned int,,std::shared_ptr<>> pipeline_map;
    /*template<class func, class obj>
    void (*callback_setter) (func in_func,obj in_obj)
    {

    }*/
  /*

  inline unsigned int registar_shader(std::shared_ptr<Listed> in_shader)
  {

    shader_map.insert(std::make_pair(in_shader->get_id(),in_shader));
      return in_shader->get_id();
  }

  inline unsigned int registar_separated_shader(std::shared_ptr<shader_seprate> in_shader)
  {

    separated_shdr_prgm_map.insert(std::make_pair(in_shader->get_id(),in_shader));
    return in_shader->get_id();
  }
*/







/*

class shader_ecouter : public singleton_exd
{
  protected :


  inline int registar_texture(unsigned int index,std::shared_ptr<gl_shader_t> in_texture)
  {
    shader_map.insert(std::make_pair(index,in_texture));
  }


};*/

  /*  void preform_texturexml_scan(pathz& in_path)
    {
      //t_path_map* t_path_m_ptr;

      int parsSTATUS = t_xml_lister.load_run(in_sv_xmlpath);

      if(parsSTATUS<0)
      {
          std::cerr << "parseerror::" << parsSTATUS << '\n';
          return;
      }

      t_path_m_ptr = t_xml_lister.pointer_mapreturn();
      gen_texture_from_tt(t_path_m_ptr);


    }

    void gen_texture_from_tt(t_path_map* t_path_m_ptr)
    {

    }*/
