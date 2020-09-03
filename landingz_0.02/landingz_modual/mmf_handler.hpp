

#ifndef MMF_HANDLER_LANDINGZ_HPP
#define MMF_HANDLER_LANDINGZ_HPP

#include "utilityz_header_ldingz.hpp"
#include "3rd_party/cpp_mmf/memory_mapped_file.hpp"
#include "landingz_base.hpp"

#include <vector>
#include <array>


using namespace landingz;


struct polled_data{

  //  int id;
  high_resolution_clock::time_point dispatch_time;
  std::array<notice_data_pair,MAX_UPDATE_FILES> update_noticez;

  high_resolution_clock::duration return_time_diffrental_for_flag(int file_to_check);

  high_resolution_clock::time_point return_flag_last_change(int file_to_check);

  bool return_flag_status(int file_to_check);
};

class mmf_handler : public handler_base
{
  protected :
    memory_mapped_file::read_only_mmf read_file;
    memory_mapped_file::read_only_mmf read_notice_file;
    memory_mapped_file::read_only_mmf read_buildz_dez_file;
    memory_mapped_file::writable_mmf  write_file;


    int checker(int mode);

  public :
    std::vector<building_db_data> retreive_building_pour_smmf();

    void gather_mmfstats();
    void open_read(std::string in_path,std::pair<int,int> in_olp);
    void open_read(std::string in_path);

    inline void close_read()
      {
        if(read_file.is_open())
        {
          read_file.close();
        }
      }
    void notify_update(int pollfile)
{
  //write_file.open(,if_exists_just_open);
}
    void poll_for_update(int pollfile, std::pair<int,int> offset_lenth_pair = DEF_OFFLNTH);
    void parse_update_data(std::string in_data);
    void parse_update_data(char* const in_data);

    void read_buildings_dez();

};

 #endif

  /*
  std::string file_name = file;
  size_t loc = file.find('.');
  if(loc != string::npos)
  {
  file_name.erase(loc);
  }
  */

/*
          void open_write(path in_path, size_t map_beging, size_t map_length)
          {
            //void run_write(const char* dest, memory_mapped_file::read_only_mmf source_file )
             memory_mapped_file::writable_mmf dest_mf(dest,
                 overwrite ? memory_mapped_file::if_exists_truncate :
                 memory_mapped_file::if_exists_fail,
                 memory_mapped_file::if_doesnt_exist_create);
              if (! dest_mf.is_open())
              {
                  std::cerr << "##!ERROR file failed to open or created in shard mapfile::" <<  dest << '\n';
              }
              /*
                             (dest,
                          overwrite ? memory_mapped_file::if_exists_truncate :
                          memory_mapped_file::if_exists_fail,
                          memory_mapped_file::if_doesnt_exist_create);

              dest_mf.map(0, source_file.file_size());

          }*/

//buffers_stringz[HEADER] =

/*
       case HEADER_VER_KEY :
     {
          for (String val: temp_title.split(" "))
            {
                 swtich(val)
                 {
                      case HEADER_VER_KEY :
                      {
                           temp_title.
                      }
                 }
            }
          break;
     }
  }*/
