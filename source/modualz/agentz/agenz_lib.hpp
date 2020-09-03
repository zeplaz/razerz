

const static double MEM_DEPTH = -12.00;

class agentz
{
  private :
   agent_decision_component//
     //agent_decision_component<game_board*> bord_dis_comp;
   //std::vector<ships*> contrl_list_ships;

    public :

    void test_ctl_list();
    void scan_proccedure_incomeing();
    void update_agent_visionz();
    void scan_other(agentz* other_ptr_agnztz);


    agent_sensor_memorx<agentz*, double>* senz_memrx;
    agent_decision_component<agentz*> agent_dis_comp;

    template<class unit_type>
    std::vector<unit_type*> capture_ai_controlist(agentz* prt_to_contact);

     inline agentz* get_self_ptr()
     {
       return this;
     }

   void create_gb_setup(game_board* prt_toactive_gid)
     {
        std::cout <<"LOADING BOARD TO AGENTZID:" << a_id << 'n'
        << "*-ptr->gb|" << prt_toactive_gid << '\n';
        gb_ptr_collection.push_back(prt_toactive_gid);
        //bord_dis_comp.add_unit_tocrl_list(prt_toactive_gid);
        std::cout << "newsizeCLTZ:" << gb_ptr_collection.size() << '\n' <<'\n';
     }

     bool Calculate_playr_probedata(size_t& toalsipz)
     { size_t res_error;
       res_error = ship_dis_comp.diffrence_in_user_known(toalsipz);
       if(toalsipz-res_error>3)
       {
         //        tranzmitor.trazmit_telagram();
         return false;
       }
       return true;
     }
   //template <typename uni_tpy>
   void test_ctl_list();

   void scan_other(agentz* other_ptr_agnztz);

   template<class unit_type>

   std::vector<unit_type*> capture_ai_controlist(agentz* prt_to_contact)
   {
   //  if(prt_to_contact->senz_memrx())
   }

   size_t get_unit_ctllistcount()
   {
     return this->agent_dis_comp.contl_list_size();
   }

   void scan_proccedure_incomeing();

   void update_agent_visionz()
   {


   }

};
       /*  ~agentz()
         {
           delete senz_memrx;
         }*/
