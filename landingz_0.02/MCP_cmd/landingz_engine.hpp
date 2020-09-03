
#ifndef LANDINGZ_GUI_ENGINE_HPP
#define LANDINGZ_GUI_ENGINE_HPP


  #include <iostream>
  #include <memory>

#IF
  #include "basez/engine_enum_defz.hpp"



namespace landingz
{

    bool isNumeric(const std::string& str)
    {
       for (int i = 0; i < str.length(); i++)
          if (isdigit(str[i]) == false)
             return false; //when one non numeric value is found, return false
          return true;
    }

//#include "periphery_input.hpp"
enum class Engine_State : unsigned char
{
  INITAL,
  CONFIGURED,
  IGNITION,
  RUNNING,
  SHUTDOWN,
  STALL
};

enum Cycle_Outs{
  S_SHUTDOWN =5
};

enum class Cmd_Mode{
  INITAL,
  COMMITTEE,
  USER_INPUT,
  WAITING
};

inline static constexpr GLfloat STAIC_ONE = 1.0f;
GLint frame_buf_width,frame_buf_hight;


struct rez_mgmt
{
//  ecouter<text_render_glyph,character>  ecouterait_glyph;
  //priphery_compoent priphery_input;
//  multiframe_capturer mf_c;
      //ecouter<terrain,terrain_feture_tupl>  ecouterait_terrain;
  //  ecouter<std::shared_ptr<shader_seprate>,terrain_feture_tupl>  ecouterait_terrain;
    //  shader_pipeline_CMD shpipe_cmd;
    //texture_xml_parser t_xml_parser;
  //  std::array<view_lenz,6> lenz_array;
    //view_lenz* prim_lenz;
};

inline static rez_mgmt* global_r_mgmt=nullptr;


struct Engine
{
  Engine_State engine_state;
  Cmd_Mode cmd_mode;

  int gl_errocode;

  long double run_durration;
  unsigned long long int cycle_count;

  //rez_mgmt r_mgmt;
  std::string terminal_cmd;


class trait_tag
{

};

template<typename PTR_shr>//, typename trait = trait_tag::>
  class driver
  {
      protected :
    std::shared_ptr<PTR_shr> mptr;

  public :
  void init(std::shared_ptr<PTR_shr> in_handled)
  {
      mptr = in_handled;
  }

  void end_cyclez()
  {
    ccycle = 0;
  }

  void force_status(int new_stat)
  {
    status = new_stat;
  }

  std::string read_consle()
  {
    std::string l_cmd;

    std::cout << "\n PAUSEED::?::READUBG XCI::this should be a handle lol. input lcmd::";
    std::cin >> l_cmd;

    if(isNumeric(l_cmd))
    {
      int argnum=0;
      argnum = stoi(l_cmd);
      // std::getline (cin, l_cmd);
       std::string in;
      for(int i =0; i< argnum; i++)
      {
        std::cin>>in;
        l_cmd +=';';
        l_cmd +=in;
      }
    }
    std::cout <<'\n' << "this is cmdline now::" << l_cmd << '\n';
    //DO BASIC ERROR CHECK HERE? for semivailded cmd.
  return l_cmd;
  }

 bool clean_cmd(std::string& inout_string);

enum VAILD_CMDZ{
  VOID,
  STACKED_CMD,
  RUN_MEM_READ_TEST,
  LOAD_FILE_MIS,
  LOAD_FILE,
};

 int gen_cmd(std::string& s_cmd)
 {
   swtich(s_cmd)
   {
     case "read_scan_test" :
     {
       return RUN_MEM_READ_TEST;
      break;
     }

     }
   }

static int handler(int cmdtoh, void* handle)
{
  int status = 0;
  switch(cmdtoh)
  {
    case RUN_MEM_READ_TEST:
    {
       status = handle->read_test();
       break;

    }

  }

}

 }
 std::forward_list<int> cmd_list_parser(std::string in_cmd)
 {
    int num_cmdz= 0;
    if(isdigit(n_cmd[0]))
    {
      std::string tempnum;
      int i=0;
      while(isdigit(n_cmd[i])
      {
        tempnum +=n_cmd[i];
        i++;
      }
      num_cmdz = stoi(tempnum);
    }


    for(i =0; i< num_cmdz; i++)
    {









    }



 }



   static int cmd_loop()
  {
      int status = 0;
      int ccycle = 1;
      std::string l_cmd;

      while(ccycle)
      {


          read_consle()



          if(status >0)
          {
              ccycle =0;
          }
          if(l_cmd =="q")
          {
              ccycle = 0;
              status = 0;
          }

      }

      return status;

  }


  Engine();

  void ignition();
  int cylce();

  inline void set_engine_state(Engine_State in_state)
  {
    engine_state = in_state;
  }

  inline void set_cmd_mode(Cmd_Mode in_cmd_mode)
  {
    cmd_mode = in_cmd_mode;
  }
/*
  void configure(engine_config_pak& in_pak)
  {
    engine_state= Engine_State::CONFIGURED;
  }
  */
};

}
#endif
