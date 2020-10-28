
#pragma once

#include <vector>
#include <unordered_map>
#include <bitset>

class base_agent_dsc
{
  //private :
  public :
  virtual ~base_agent_dsc();
};

  template<class unittype>
  class agent_decision_component
  {
    private :

    std::vector<unittype> uint_controlist;
    std::unordered_map<int,unittype> uint_id_map;

    struct memorx
    {
      double intel_eror=0;

      int total_tracz=0;
      size_t Usr_ship_count=0;

      double pos_colliz=0;
      double collided=0;

      int lost_at_SEA=0;

      double accuml_damge=0;

      double cdional_colc=0;

    }memorx;


    struct cur_unit_telma{

      double move_penilty;
      double currnt_new_damge;
      std::vector<bool> damgemodel_new;
      size_t size_of_ship;
      size_t rspaal_dp;

    }cur_unit_telma;

    public:
    int agent_toalz;

    ~agent_decision_component() = default;

    size_t get_ctl_list_size()
    {
      return uint_controlist.size();
    }
    size_t get_unit_id_map_size()
    {
      return uint_id_map.size();
    }

    size_t diffrence_in_user_known(size_t& total_shipz)
    {
      memorx.intel_eror = static_cast<double>(total_shipz -memorx.Usr_ship_count - get_unit_id_map_size() -get_ctl_list_size());
      return (total_shipz -memorx.Usr_ship_count - get_unit_id_map_size() -get_ctl_list_size());
    }

    size_t contl_list_size()
    {
      return (uint_controlist.size());
    }

    void move_factorz(char (*matrix)[collum])
    {
      double ent_map_sizevar = (double)get_unit_id_map_size();
      double clt_list_size = (double)  get_ctl_list_size();

    //double probzneedmove =                      (ent_map_sizevar/clt_list_size)
      for (auto actl = uint_controlist.begin();
           actl != uint_controlist.end(); ++actl)
       {
        unittype* prt2_cu_unit = &*actl;
        unittype prt_cu_unit = *prt2_cu_unit;

        tie(cur_unit_telma.currnt_new_damge, cur_unit_telma.damgemodel_new) = prt_cu_unit->damage_report();

        memorx.accuml_damge +=cur_unit_telma.currnt_new_damge;

        std::cout<<"NEWDAMGEREPROTZ:::" <<cur_unit_telma.currnt_new_damge   << "||-ACCUMPATED DAMAGE:" << memorx.accuml_damge <<"*(^_____"<<'\n';

      int damge_count=  std::count(cur_unit_telma.damgemodel_new.begin(), cur_unit_telma.damgemodel_new.end(), true);
        //std::equal(damgemodel_new.begin(), damgemodel_new.begin() , s.rbegin());


          if(damge_count==cur_unit_telma.damgemodel_new.size())
           {
             memorx.lost_at_SEA++;
             std::cout <<"AGENT_AWAKLOSTSHIPZ" <<'\n';
             std::cout <<"ageinz---))lost_at_SEA-->" <<memorx.lost_at_SEA <<"|||==ovkz" <<'\n'
                       <<"--------------------------------------%%^^" <<'\n' <<'\n';
             //actl;
            }

            if(damge_count>cur_unit_telma.damgemodel_new.size()/2)
            {
              cur_unit_telma.move_penilty-=2.2;
            }

          cur_unit_telma.size_of_ship = prt_cu_unit->get_ship_size();
      //  = actl->ojk_ship_placr.coltion_intersection();
         matrix[cur_unit_telma.size_of_ship][cur_unit_telma.size_of_ship] = 'V';

         cur_unit_telma.rspaal_dp = cur_unit_telma.size_of_ship/uint_controlist.size();
         memorx.cdional_colc += (double)(cur_unit_telma.rspaal_dp*(cur_unit_telma.size_of_ship/uint_controlist.size()));

         std::cout << "cdional_colc:" << memorx.cdional_colc <<"rspaal_dp" << cur_unit_telma.rspaal_dp <<'\n' <<'\n'
                   <<"_________________________-----"<<'\n';

          if('#'!=matrix[cur_unit_telma.rspaal_dp+1][cur_unit_telma.rspaal_dp+1])
          {
            prt_cu_unit->rotate();
            std::cout <<"roate trig.." << '\n';
          }
       }
     }


    inline void add_unit_tocrl_list(unittype in_unit_ptr)
     {  std::cout <<"AI_ADDED_UNITZ:&"<< in_unit_ptr << '\n';
        uint_controlist.push_back(in_unit_ptr);
     }



    unittype unit_radm_access_ctl_list(int unit_at_vec_place)
     {
      return uint_controlist.at(unit_at_vec_place);
     }

     template <class unit_type>


    void regstar_unit_inmap(unit_type* in_uint)
     {
      uint_id_map.insert({in_uint->get_id(), in_uint});
     }


/*
   unittype*  lookup_unit_map(int in_id)
     {
      auto search = agent_id_map.find(in_id)
      {
        if (search != agent_id_map.end())
      {
        return search->second;
      }
      else
      {
        std::cout << "->>UNITNOTFOUNDZ ID:" << in_id << '\n' << '\n';
        return nullptr;
      }
      }
    }
    */

};
