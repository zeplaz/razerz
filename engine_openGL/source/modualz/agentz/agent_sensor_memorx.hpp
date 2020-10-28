
#pragma once

#include <vector>
#include <tuple>
#include <unordered_map>
#include <forward_list>

template <class unit_class>
class mission_evaluator
{
  //cal_priority(unit_class*)

};


typedef double rcd_dam;
typedef double rcd_avg_cmradre;

  struct cmmrad_statuz
  {
    rcd_avg_cmradre danger;
    rcd_avg_cmradre ambivalents;
    rcd_avg_cmradre like_ability;
  };


typedef  int array_int_2d[2];
using array_2d = array_int_2d;

//using array_2d = std_type arry[2];




class memoryx_rec
{
  public :
  double last_time_spotted;
  double time_found_visible;
  double last_time_visible;
  int known_uint_count;
  double pridicted_rate_change_of_influnce;
  double comm_range;

  bool visual_range;
  cmmrad_statuz comrad_statuz;


  std::vector<std::tuple<int*, rcd_dam,rcd_avg_cmradre>> prev_incouter_vec;



  memoryx_rec():  last_time_spotted(-999),
                  time_found_visible(-999),last_time_visible(0),
                  visual_range(false), comm_range(-0.99),known_uint_count(0),pridicted_rate_change_of_influnce(0)
                    {
                      comrad_statuz.danger =-999;
                      comrad_statuz.like_ability=-999;
                      comrad_statuz.ambivalents=-999;
                      int array_2d[2] = {0,0};
                      prev_incouter_vec.push_back(std::make_tuple(array_2d,0.0,0.0));
                    }
};

template <class recordable_idenity,typename std_type>
  class agent_sensor_memorx
  {
    private :
    typedef std::unordered_map<recordable_idenity,memoryx_rec> memrx_map;

    private :
    recordable_idenity ptr_agent_owner;
    memrx_map inst_memx_map;
    double depthz;


    public :
    agent_sensor_memorx(recordable_idenity self_ref,
                        double depthz_fix) :ptr_agent_owner(self_ref),
                                            depthz(depthz_fix)
    {}
    //agent_sensor_memorx(recordable_idenity* self_ref, double depthz_fix);

    void remove_contact_from_memx(recordable_idenity ptr_detectd_contact)
    {
      typename memrx_map::iterator contact = inst_memx_map.find(ptr_detectd_contact);

      if(!contact= inst_memx_map.end)
      {
        inst_memx_map.erase(contact);
      }
    }

    void update_new_comm_rec(recordable_idenity ptr_detectd_contact);
    void update_sonar(recordable_idenity ptr_detectd_contact);

    double is_comm_range(recordable_idenity ptr_detectd_contact) const;

    bool is_visual_range(recordable_idenity*ptr_detectd_contact) const;
    bool is_fire_range(recordable_idenity*ptr_detectd_contact) const;
    int* contactz_last_rec_pos(recordable_idenity* ptr_detectd_contact) const;

    double  get_last_time_spotted(recordable_idenity* ptr_detectd_contact)  const;
    double  get_time_found_visible(recordable_idenity*ptr_detectd_contact) const;
    double  get_last_time_visible(recordable_idenity*ptr_detectd_contact)  const;

    cmmrad_statuz get_comard_status(recordable_idenity*ptr_detectd_contact);
    //called recuvlz by toplevel func..
    void update_vision();

    std::forward_list<recordable_idenity*> list_recent_detected;

    void draw_mark_on_senced()const;


    void make_new_rec_IFNOTPREZ(recordable_idenity ptr_detectd_contact)
    {
      if(inst_memx_map.find(ptr_detectd_contact)==inst_memx_map.end())
      {
          inst_memx_map[ptr_detectd_contact] = memoryx_rec();
          memoryx_rec ptr_cur_detecd =   inst_memx_map.at(ptr_detectd_contact);
        //  ptr_cur_detecd->known_uint_count = ptr_detectd_contact->get_unit_ctllistcount();
      }
    }
  };

  //agent_sensor_memorx.cpp
/*
  agent_sensor_memorx::make_new_rec_IFNOTPREZ(recordable_idenity* ptr_detectd_contact)
  {
    if(memrx_map.find(ptr_detectd_contact)==memrx_map.end())
    {
      memrx_map[ptr_detectd_contact]  = memoryx_rec();
    }
  }

*/
//agent_sensor_memorx(recordable_idenity* owner, double memory_value) :
